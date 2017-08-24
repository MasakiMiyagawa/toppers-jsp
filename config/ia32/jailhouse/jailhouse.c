#include "jsp_kernel.h"

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

