/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2002 by Monami software, Limited Partners.
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
 *  @(#) $Id: cpu_config.h,v 1.2 2002/04/06 12:23:01 honda Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���i386�ѡ�
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

#ifndef _MACRO_ONLY
#include "i386.h"
#endif /* _MACRO_ONLY */

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#ifndef OMIT_RENAME

#define activate_r      _kernel_activate_r
#define ret_int         _kernel_ret_int
#define ret_exc         _kernel_ret_exc
#define task_intmask    _kernel_task_intmask
#define int_intmask     _kernel_int_intmask

#ifdef LABEL_ASM

#define _activate_r     __kernel_activate_r
#define _ret_int        __kernel_ret_int
#define _ret_exc        __kernel_ret_exc
#define _task_intmask   __kernel_task_intmask
#define _int_intmask    __kernel_int_intmask

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
#define	TBIT_TCB_PRIORITY	8	/* priority �ե�����ɤΥӥå��� */
#define	TBIT_TCB_TSTAT		8	/* tstat �ե�����ɤΥӥå��� */
#define	TBIT_TCB_TWAIT		8	/* twait �ե�����ɤΥӥå��� */

#ifndef _MACRO_ONLY
/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	VP	esp;		/* �����å��ݥ��� */
	FP	eip;		/* �ץ���५���� */
} CTXB;

/*
 *  �����ߤΥͥ��Ȳ��
 *
 *  1�ʾ�λ����󥿥�������ƥ����Ȥˤʤ롣�����ߥϥ�ɥ���㳰�ϥ�ɥ��
 *  �������ǥ��󥯥���ȡ��ǥ�����Ȥ���롣
 */
extern UW nest;

/*
 *  �����ƥ���ֻ���
 */

Inline BOOL
sense_context()
{
	return (nest != 0);
}

Inline BOOL
sense_lock()
{
	unsigned __int32 eflag;

	Asm("pushf");
	Asm("popl %0" : "=g"(eflag));

	return ((eflag & 0x200) == 0);
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU��å��Ȥ��β��
 * �ʥ���������ƥ�����/�󥿥�������ƥ����ȶ��̡�
 *
 */

Inline void
i386_lock_cpu()
{
	Asm("cli");
}

Inline void
i386_unlock_cpu()
{
	Asm("sti");
}

/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 */

Inline void
i_lock_cpu()
{
	i386_lock_cpu();
}

Inline void
t_lock_cpu()
{
	i386_lock_cpu();
}

/*
 *  CPU��å��Ȥ��β�����󥿥�������ƥ������ѡ�
 */
Inline void
i_unlock_cpu()
{
	i386_unlock_cpu();
}

Inline void
t_unlock_cpu()
{
	i386_unlock_cpu();
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
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ������
 */

/*
 *  �㳰�ϥ�ɥ�ν�����������cpu_support.S��
 */
extern void exception0(void);
extern void exception1(void);
extern void exception2(void);
extern void exception3(void);
extern void exception4(void);
extern void exception5(void);
extern void exception6(void);
extern void exception7(void);
extern void exception8(void);
extern void exception9(void);
extern void exception10(void);
extern void exception11(void);
extern void exception12(void);
extern void exception13(void);
extern void exception14(void);
extern void exception16(void);
extern void exception17(void);
extern void exception18(void);
extern void exception19(void);

/*
 *  CPU�㳰�ϥ�ɥ�Υơ��֥��cpu_config.c��
 *
 *  CPU�㳰�ϥ�ɥ�ϰ�ö���Υơ��֥����Ͽ���졢�̤��Ѱդ��줿����������
 *  ��ƤӽФ���
 */
extern FP exc_table[0x20];

/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
extern void define_inh(INHNO inhno, FP inthdr);

/*
 *  CPU�㳰�ϥ�ɥ������
 *  �٥��ȥ��ֹ� excno ��CPU�㳰�ϥ�ɥ�ε�ư���Ϥ� exchdr ������
 */
extern void define_exc(EXCNO excno, FP exchdr);

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν���������
 */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 */

#define	INTHDR_ENTRY(inthdr)		\
extern void inthdr##_entry(void);	\
asm(".text				\n"\
#inthdr "_entry:			\n"\
"	pusha				\n"\
"	movl	$"#inthdr", %eax	\n"\
"	jmp	interrupt		\n")

#define INT_ENTRY(inthdr)		inthdr##_entry

/*
 *  CPU�㳰�ϥ�ɥ�ν������������������ޥ���
 */

#define	EXCHDR_ENTRY(exchdr)		\
extern void exchdr##_entry(VP p_excinf);	\
asm(".text				\n"\
#exchdr "_entry:			\n"\
"	jmp	" #exchdr "		\n")

#define EXC_ENTRY(exchdr)	exchdr##_entry

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	return (nest > 1);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
	return ((((UW *)p_excinf)[3] & 0x200) == 0);
}

/*
 *  ��٥����̾��������뤿��Υޥ���
 */
#define	LABEL_ALIAS(new_label, defined_label) \
	asm(".globl " #new_label "\n" #new_label " = " #defined_label);

/*
 *  �ץ��å���¸�ν����
 */
extern void	cpu_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void	cpu_terminate(void);

#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
