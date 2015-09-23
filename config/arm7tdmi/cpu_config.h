/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
 *  ������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ�������֥륪��
 *      �������ȥե������饤�֥��ʤɡˤη������Ѥ�����ˤϡ�����
 *      ��ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ����
 *      �������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ�������������Բ�ǽ�ʥХ��ʥꥳ���ɤη��ޤ��ϵ������
 *      �߹�����������Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: cpu_config.h,v 1.9 2002/04/05 07:43:51 honda Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���ARM7TDMI�ѡ�
 */
#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#ifndef OMIT_RENAME

#define activate_r      _kernel_activate_r
#define ret_int         _kernel_ret_int
#define ret_exc         _kernel_ret_exc

#ifdef LABEL_ASM

#define _activate_r     __kernel_activate_r
#define _ret_int        __kernel_ret_int
#define _ret_exc        __kernel_ret_exc

#endif /* LABEL_ASM */
#endif /* OMIT_RENAME */

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#ifndef _MACRO_ONLY
#include "cpu_insn.h"
#endif /* _MACRO_ONLY */

/*
 *  TCB ��Ϣ�����
 *
 *  cpu_context.h ��������������쥬��Ȥ��������Ȥΰ�¸���δط��ǡ�
 *  cpu_context.h �ˤ�������ʤ���
 */

/*
 *  TCB ��Υե�����ɤΥӥå��������
 */
#define	TBIT_TCB_TSTAT		8	/* tstat �ե�����ɤΥӥå��� */
#define	TBIT_TCB_PRIORITY	8	/* priority �ե�����ɤΥӥå��� */

#ifndef _MACRO_ONLY
/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	VP	sp;		/* �����å��ݥ��� */
	FP	pc;		/* �ץ���५���� */
} CTXB;

/*
 * �����ߤΥͥ��Ȳ���Υ������
 */
extern UW interrupt_count;


/*
 *  �����ƥ���ֻ���
 */
Inline UB
current_mode()
{
    return(current_sr() & CPSR_MODE_MASK);
}

Inline BOOL
sense_context()
{
	return(interrupt_count > 0);
}

Inline BOOL
sense_lock()
{
	return(current_sr() & CPSR_IRQ_BIT);
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock


/*
 *  CPU��å��Ȥ��β��
 *
 */

#define t_lock_cpu      lock_cpu
#define i_lock_cpu      lock_cpu
#define t_unlock_cpu    unlock_cpu
#define i_unlock_cpu    unlock_cpu


Inline void
lock_cpu()
{
	disint();
}

Inline void
unlock_cpu()
{
	enaint();
}


/*
 *  �������ǥ����ѥå���
 */

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���cpu_support.S��
 *
 *  dispatch �ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ����������
 *  ��ǡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	dispatch(void);


/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���cpu_support.S��
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	exit_and_dispatch(void);


/*
 * �㳰�٥����˽񤭹��ޤ줿������̿�᤬���Ȥ��륢�ɥ쥹
 */
extern UW *arm_vector_add[8];


/*
 * �㳰�˱������ϥ�ɥ�ε�ư����
 */
extern UW arm_handler_add[8];


/*
 *  CPU�㳰�ϥ�ɥ������
 */
extern void define_exc(EXCNO excno, FP exchdr);


Inline void
arm_install_handler(EXCNO excno, FP exchdr)
{
    *arm_vector_add[excno] = (UW)exchdr;
}


/*
 *  CPU�㳰�ϥ�ɥ�ν���������
 */


/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 *
 */
#define __EXCHDR_ENTRY(exchdr, stacktop)    \
extern void exchdr##_entry(VP sp);          \
asm(".text                             \n"  \
#exchdr "_entry:                       \n"  \
"       ldr   sp,.int_stack_"#exchdr"  \n"  /* �����å����ڤ��ؤ�        */\
"       sub   lr,lr,#4                 \n"  /* undef�Ǥ⤳��Ǥ�����?    */\
"       stmfd sp!, {r0 - r2,lr}        \n"  /* ���Ū��int_stack������   */ \
"       mrs   r0, spsr                 \n"  /* SYS�⡼�ɤ��ڤ��ؤ��뤿�� */ \
"       mov   r1, sp                   \n"  /* ��¸����                  */ \
"       mov   r2,#0xdf                 \n"  /* CPSR�ν񤭴���            */ \
"       msr   cpsr,r2                  \n" \
"       ldr   r2,[r1,#0x0C]            \n"     /* load  PC            */\
"       stmfd sp!,{r2}                 \n"     /* Store PC            */\
"       stmfd sp!,{r3,ip,lr}           \n"     /* Store r3,ip,lr      */\
"       ldmfd r1!,{r2,ip,lr}	       \n"     /* load  r0,r1,r2      */\
"       stmfd sp!,{r0,r2,ip,lr}        \n"     /* SPSR,Store r0,r1,r2 */\
"       ldr  r2, .interrupt_count_"#exchdr"\n" /* ¿�ų����ߤ�Ƚ��  */\
"       ldr  r3, [r2]                  \n" \
"       add  r0,r3,#1                  \n" \
"       str  r0, [r2]                  \n" \
"       mov  r0,sp                     \n" /* �㳰�ϥ�ɥ�ؤΰ��� */\
"       cmp  r3, #0x00                 \n" \
"       ldreq   sp,stack_"#exchdr"     \n" /* �����å����ѹ�       */\
"       stmeqfd sp!,{r0}               \n" /* �����������å�����¸ */\
"       mov   r2,#0x1f                 \n" /* �����ߵ���         */\
"       msr   cpsr,r2                  \n" \
"		bl    "#exchdr"                \n" /* �ϥ�ɥ�ƤӽФ�     */\
"       mov   r2,#0xdf                 \n" /* �����߶ػ�         */\
"       msr   cpsr,r2                  \n" \
"       ldr   r2,.interrupt_count_"#exchdr" \n"/* �����߲����   */\
"       ldr   r1, [r2]                 \n"     /* �ǥ������     */\
"       sub   r3,r1,#1                 \n"\
"       str   r3, [r2]                 \n"\
"       cmp   r3,#0x00                 \n" /* �����ߥͥ��ȿ�?    */\
"       bne   return_to_task_"#exchdr" \n" \
"       ldmfd sp!,{r0}                 \n" /* �����������å������� */\
"       mov   sp, r0                   \n"\
"		ldr   r1, reqflg_"#exchdr"     \n" /* Check reqflg         */\
"		ldr   r0,[r1]                  \n"\
"		cmp   r0,#0                    \n"\
"		beq   return_to_task_"#exchdr" \n"\
"       mov   r0,#0                    \n"\
"		str   r0,[r1]                  \n" /* Clear reqflg   */\
" 		b     _kernel_ret_exc          \n" /* ret_int��      */\
"return_to_task_"#exchdr":             \n" \
"       ldmfd sp!,{r1}                 \n" /* CPSR���������� */\
"       msr   cpsr, r1                 \n" /* �����ߵ���   */\
"       ldmfd sp!,{r0-r3,ip,lr,pc}     \n"\
"       .align 4                       \n"\
".int_stack_"#exchdr":                 \n"\
"        .long int_stack + 6 * 4       \n"\
"reqflg_"#exchdr":                     \n"\
"		.long     _kernel_reqflg       \n"\
"stack_"#exchdr":                      \n"\
"        .long   " #stacktop "         \n"\
".interrupt_count_"#exchdr":           \n"\
"        .long   interrupt_count       \n")


#define _EXCHDR_ENTRY(exchdr, stacktop)    __EXCHDR_ENTRY(exchdr, stacktop)

#define EXCHDR_ENTRY(exchdr)    _EXCHDR_ENTRY(exchdr, STACKTOP)

#define EXC_ENTRY(exchdr) exchdr##_entry


/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå�
 *  NotYet! 
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	return(interrupt_count > 1);    
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 *  NotYet! 
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
    return((*((UW *)p_excinf) & CPSR_IRQ_BIT) == CPSR_IRQ_BIT );
}


/*
 *  ��٥����̾��������뤿��Υޥ���
 */
#define	_LABEL_ALIAS(new_label, defined_label) \
	asm(".globl " #new_label "\n" #new_label " = " #defined_label);
#define LABEL_ALIAS(x, y) _LABEL_ALIAS(x, y)


/*
 *  �ץ��å���¸�ν����
 */
extern void	cpu_initialize(void);


/*
 *  �ץ��å���¸�ν�λ������
 */
extern void	cpu_terminate(void);


/*
 * CPU/����ߥϥ�ɥ�ν�����������ǰ��Ū�˻��Ѥ��륹���å�
 */
#define INT_STACK_SIZE 6
extern UW int_stack[INT_STACK_SIZE];


#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
