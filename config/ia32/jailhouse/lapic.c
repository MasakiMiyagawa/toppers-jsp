#include <s_services.h>
#include <cpu_insn.h>

/* MSR */
#define MSR_IA32_APICBASE	0x0000001b
#define MSR_X2APIC_SPIV 	0x0000080f
#define MSR_X2APIC_LVTT 	0x00000832
#define MSR_X2APIC_TMICT	0x00000838
#define MSR_X2APIC_TMCCT 	0x00000839
#define MSR_X2APIC_TDCR		0x0000083e
#define MSR_X2APIC_EOI		0x0000080b

#define APIC_PERIODIC 	(1 << 17)
#define APIC_BASE_EXTD	(1 << 10)
#define APIC_BASE_EN	(1 << 11)
#define CPUID_X2APIC_SUPPORT (1 << 21)

static BOOL x2apic_is_available(void)
{
	UW a, b, c, d;
	a = 1;
	cpuid(&a, &b, &c, &d);
	if (!(CPUID_X2APIC_SUPPORT & c)) {
		return FALSE;
	}		
	return TRUE;
}

static UW lapic_estimate_count_per_ms(void)
{
	UD start, end;
	UW low, high;
	UW tmict_start = 0xFFFFFFFF;
	UW sub;	
	UW sub_us;

	write_msr(MSR_X2APIC_TMICT, tmict_start, 0);
retry:
	start = pm_timer_read_us();
	while (1) {
		end = pm_timer_read_us();
		if (end < start) {
			syslog(LOG_EMERG, 
				"Overflow is expected. start=%lu end=%lu",
				start, end);
			goto retry;
		}

		if (end - start > 1000)	/* 1ms */
			break;
	}	
	read_msr(MSR_X2APIC_TMCCT, &low, &high); 
	write_msr(MSR_X2APIC_TMICT, 0, 0);
	sub = tmict_start - low;
	sub_us = end - start;	/* sub_ns would be almost 1ms */
	
	syslog(LOG_NOTICE, "APIC count/ms=%u measurement time=%uus",
			sub, sub_us);
	return sub;
}

void lapic_timer_init(UW vector)
{
	UW low, high;
	UW count_per_ms;

	write_msr(MSR_X2APIC_TDCR, 0x3, 0); 
	count_per_ms = lapic_estimate_count_per_ms();
	write_msr(MSR_X2APIC_LVTT, vector|APIC_PERIODIC, 0);
	write_msr(MSR_X2APIC_TMICT, count_per_ms, 0);
	syslog(LOG_NOTICE, "Starting Local APIC Timer.");
}

void lapic_enable(void)
{
	UW low, high;

	read_msr(MSR_IA32_APICBASE, &low, &high);
	if (x2apic_is_available()) {
		if ((APIC_BASE_EN & low) && (APIC_BASE_EXTD & low)) { 
			/* Do nothing */	
		} else {
			syslog(LOG_EMERG, "x2apic is not enabled.");
			kernel_abort();
		}
	} else {
		syslog(LOG_EMERG, "x2apic is not available.");
		kernel_abort();
	}
	write_msr(MSR_X2APIC_TMICT, 0, 0);	/* stop timer */
	write_msr(MSR_X2APIC_SPIV, 0x1ff, 0);
}

void lapic_eoi(void)
{
	write_msr(MSR_X2APIC_EOI, 0, 0);
}
