#include <s_services.h>
#include <cpu_insn.h>

#define APIC_PERIODIC 	(1 << 16)
void lapic_timer_init(UW vector)
{
	UD start = rdtsc();
	syslog(LOG_NOTICE, "%lu\n", start);
	syslog(LOG_NOTICE, "%s:%s:%d", __FILE__, __func__, __LINE__);
	write_msr(X2APIC_TDCR, 3, 0);	/* To make counter is devided by 1 */
	write_msr(X2APIC_TMICT, 6000, 0);	/* FIXME! */
	write_msr(X2APIC_LVTT, vector|APIC_PERIODIC, 0);
	syslog(LOG_NOTICE, "%s:%s:%d", __FILE__, __func__, __LINE__);
}

void lapic_enable(void)
{
	syslog(LOG_NOTICE, "%s:%s:%d", __FILE__, __func__, __LINE__);
	write_msr(X2APIC_SPIV, 0x1ff, 0);
	syslog(LOG_NOTICE, "%s:%s:%d", __FILE__, __func__, __LINE__);
}

void lapic_int_clr(void)
{
	syslog(LOG_NOTICE, "%s:%s:%d", __FILE__, __func__, __LINE__);
	write_msr(X2APIC_EOI, 0, 0);
	syslog(LOG_NOTICE, "%s:%s:%d", __FILE__, __func__, __LINE__);
}
