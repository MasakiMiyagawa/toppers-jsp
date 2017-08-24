#include "jsp_kernel.h"

/* Common Region Access */
#define COMM_REGION_BASE  0x300000
static struct jailhouse_comm_region {
	UW msg_to_cell;
#define JAILHOUSE_MSG_SHUTDOWN_REQUEST	1
	UW reply_from_cell;
	UW cell_state;
#define JAILHOUSE_CELL_SHUT_DOWN	2
	UW padding;
	UH pm_timer_address;
#define PM_TIMER_HZ		3579545
	UH num_cpus;
} *comm_region;

extern UW __bss_start;
extern UW _kernel_stack;
extern UW _end;
void software_init_hook(void)
{
	/* to clear bss */
	char *p = &__bss_start; 
	char *end_p = &_kernel_stack;
	UW size = (UW)(end_p - p);
	UW i;

	while (1) {
		*p = 0;
		p++;
		if (p == end_p)
			break;
	}

	p = (end_p + STACKSIZE);
	end_p = &_end; 
	while (1) {
		*p = 0;
		p++;
		if (p == end_p)
			break;
	}

}

void jailhouse_guest_init(void)
{
	comm_region = (struct jailhouse_comm_region *)COMM_REGION_BASE;
}

void jailhouse_handle_shutdown(void)
{
	if (comm_region->msg_to_cell == JAILHOUSE_MSG_SHUTDOWN_REQUEST) {
		comm_region->cell_state = JAILHOUSE_CELL_SHUT_DOWN;
		while (1);
	}
}

UD pm_timer_read_us(void)
{
	UH port = comm_region->pm_timer_address;
	UW val = 0;
	UD us = 0;

	asm volatile("inl %1,%0" : "=a" (val) : "dN" (port));
	us = (UD)val;
	us = us * (1000 * 1000) / PM_TIMER_HZ;

	return us;
}

/* Hypercall */
static BOOL jailhouse_use_vmcall = TRUE;
#define JAILHOUSE_HC_DEBUG_CONSOLE_PUTC	8
#define JAILHOUSE_CALL_CODE	\
	"cmpb $0x01, %[use_vmcall]\n\t"\
	"jne 1f\n\t"\
	"vmcall\n\t"\
	"jmp 2f\n\t"\
	"1: vmmcall\n\t"\
	"2:"
#define JAILHOUSE_CALL_RESULT	"=a" (result)
#define JAILHOUSE_USE_VMCALL	[use_vmcall] "m" (jailhouse_use_vmcall)
#define JAILHOUSE_CALL_NUM	"a" (num)
#define JAILHOUSE_CALL_ARG1	"D" (arg1)

static UW jailhouse_call_arg1(UW num, UW arg1)
{
	UW result;

	asm volatile(JAILHOUSE_CALL_CODE
		: JAILHOUSE_CALL_RESULT
		: JAILHOUSE_USE_VMCALL,
		  JAILHOUSE_CALL_NUM, JAILHOUSE_CALL_ARG1
		: "memory");
	return result;
}

void jailhouse_putc(char c)
{
	jailhouse_call_arg1(JAILHOUSE_HC_DEBUG_CONSOLE_PUTC, c);
}
