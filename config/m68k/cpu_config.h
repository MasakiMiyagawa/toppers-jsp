/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ�
 *  �եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�����
 *  �ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�������Х��ʥꥳ���ɤη��ޤ��ϵ�����Ȥ߹����������
 *      �Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (3) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: cpu_config.h,v 1.1 2000/11/14 14:44:14 hiro Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���68040�ѡ�
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#ifndef _MACRO_ONLY
#include "cpu_insn.h"
#endif /* _MACRO_ONLY */

/*
 *  chg_ipm/ref_ipm �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_CHG_IPM

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
	VP	msp;		/* �����å��ݥ��� */
	FP	pc;		/* �ץ���५���� */
} CTXB;

/*
 *  ����ߥޥ������饤�֥��
 *
 *  ����ߥޥ�����intmask�ˤϡ�IPM��Interrupt Priority Mask�ˤ�8�ӥå�
 *  ���˥��եȤ�����ΤǤ��롥
 */

/*
 *  ���ߤγ���ߥޥ������ɽФ�
 */
Inline UH
current_intmask()
{
	return(current_sr() & 0x0700);
}

/*
 *  ����ߥޥ���������
 */
Inline void
set_intmask(UH intmask)
{
	set_sr((current_sr() & ~0x0700) | intmask);
}

/*
 *  �����ƥ���ֻ���
 */

Inline BOOL
sense_context()
{
	return((current_sr() & 0x1000) == 0);
}

Inline BOOL
sense_lock()
{
	return(current_intmask() == 0x0700);
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 *  task_intmask �ϡ�chg_ipm �򥵥ݡ��Ȥ��뤿����ѿ���chg_ipm �򥵥ݡ�
 *  �Ȥ��ʤ����ˤϡ�task_intmask ����� 0 �ˤʤäƤ���ȹͤ���Ф褤��
 */

#ifdef SUPPORT_CHG_IPM
extern UH	task_intmask;	/* ����������ƥ����ȤǤγ���ߥޥ��� */
#endif /* SUPPORT_CHG_IPM */

Inline void
t_lock_cpu()
{
	disint();
}

Inline void
t_unlock_cpu()
{
#ifdef SUPPORT_CHG_IPM
	/*
	 *  t_unlock_cpu ���ƤӽФ����Τ� CPU��å����֤ΤߤǤ��뤿
	 *  �ᡤ����������� task_intmask ���񤭴���뤳�ȤϤʤ���
	 */
	set_intmask(task_intmask);
#else /* SUPPORT_CHG_IPM */
	enaint();
#endif /* SUPPORT_CHG_IPM */
}

/*
 *  CPU��å��Ȥ��β�����󥿥�������ƥ������ѡ�
 */

extern UH	int_intmask;	/* �󥿥�������ƥ����ȤǤγ���ߥޥ��� */

Inline void
i_lock_cpu()
{
	UH	intmask;

	/*
	 *  ����ѿ� intmask ��ȤäƤ���Τϡ�current_intmask() ���
	 *  ���ľ��˳���ߤ�ȯ��������ư���줿����ߥϥ�ɥ����
	 *  int_intmask ���ѹ�������ǽ�������뤿��Ǥ��롥
	 */
	intmask = current_intmask();
	disint();
	int_intmask = intmask;
}

Inline void
i_unlock_cpu()
{
	set_intmask(int_intmask);
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
 *  �㳰�٥����ơ��֥�ι�¤�����
 */
typedef struct exc_vector_entry {
	FP	exchdr;			/* �㳰�ϥ�ɥ�ε�ư���� */
} EXCVE;

/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
Inline void
define_inh(INHNO inhno, FP inthdr)
{
	EXCVE	*excvt;

#ifdef EXCVT_KERNEL
	/*
	 *  EXCVT_KERNEL ���������Ƥ�����ϡ��������������� VBR �� 
	 *  EXCVT_KERNEL �����ꤹ��Τǡ�EXCVT_KERNEL ��Ȥ���
	 */
	excvt = (EXCVE *) EXCVT_KERNEL;
#else /* EXCVT_KERNEL */
	excvt = (EXCVE *) current_vbr();
#endif /* EXCVT_KERNEL */
	excvt[inhno].exchdr = inthdr;
}

/*
 *  CPU�㳰�ϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� excno ��CPU�㳰�ϥ�ɥ�ε�ư���Ϥ� exchdr �����ꤹ�롥
 */
Inline void
define_exc(EXCNO excno, FP exchdr)
{
	define_inh(excno, exchdr);
}

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν���������
 */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 */

#define ENTRY(inthdr)   inthdr##_entry

#define	_INTHDR_ENTRY(entry, inthdr)	\
extern void entry(void);		\
asm(".text				\n" \
#entry ":				\n" \
"	movem.l %d0-%d1/%a0-%a1, -(%sp)	\n" /* ������å��쥸��������¸ */ \
"	jsr " #inthdr "			\n" /* ����ߥϥ�ɥ��ƤӽФ� */ \
"	movem.l (%sp)+, %d0-%d1/%a0-%a1	\n" /* ������å��쥸���������� */ \
"	btst.b #4, (%sp)		\n" /* ����褬����ߥ⡼�ɤʤ� */ \
"	jbeq 1f				\n" /*           �����˥꥿���� */ \
"	or.w #0x0700, %sr		\n" /* ����߶ػ� */ \
"	tst.l _kernel_reqflg		\n" /* reqflg �� TRUE �Ǥ���� */ \
"	jbne _kernel_ret_int		\n" /*              ret_int �� */ \
"1:	rte				\n")

#define INTHDR_ENTRY(entry, inthdr)	_INTHDR_ENTRY(entry, inthdr)

/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 *
 *  CPU�㳰�ϥ�ɥ�ϡ��󥿥�������ƥ����ȤǼ¹Ԥ��롥���Τ��ᡤCPU��
 *  ���ϥ�ɥ��ƤӽФ����˳���ߥ⡼�ɤ˰ܹԤ����꥿���󤷤Ƥ������
 *  ���Υ⡼�ɤ��᤹�����Υ⡼�ɤ��᤹����ˡ�����ߥ⡼�ɤ˰ܹԤ�����
 *  �� SR �����ߥ����å������¸���롥CPU�㳰������������ƥ����Ȥ�
 *  ȯ������reqflg �� TRUE �ˤʤä����ˡ�ret_exc ��ʬ�����롥
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 */

#define	_EXCHDR_ENTRY(entry, exchdr)	\
extern void entry(VP sp);		\
asm(".text				\n" \
#entry ":				\n" \
"	movem.l %d0-%d1/%a0-%a1, -(%sp)	\n" /* ������å��쥸��������¸ */ \
"	lea.l (16,%sp), %a0		\n" /* �㳰�ե졼�����Ƭ�� A0 �� */ \
"	move.w %sr, %d0			\n" /* SR �� D0 �� */ \
"	and.w #~0x1000, %sr		\n" /* ����ߥ⡼�� */ \
"	move.l %d0, -(%sp)		\n" /* ���� SR �򥹥��å�����¸ */ \
"	move.l %a0, -(%sp)		\n" /* A0 ������Ȥ����Ϥ� */ \
"	jsr " #exchdr "			\n" /* CPU�㳰�ϥ�ɥ��ƤӽФ� */ \
"	addq.l #4, %sp			\n" \
"	move.l (%sp)+, %d0		\n" \
"	and.w #0x1000, %d0		\n" /* ��������ߥ⡼�ɤʤ� */ \
"	jbeq 1f				\n" /*       �����˥꥿���� */ \
"	or.w #0x1700, %sr		\n" /* �ޥ����⡼�ɡ�����߶ػ� */ \
"	tst.l _kernel_reqflg		\n" /* reqflg �� TRUE �Ǥ���� */ \
"	jbne _kernel_ret_exc		\n" /*              ret_exc �� */ \
"1:	movem.l (%sp)+, %d0-%d1/%a0-%a1	\n" /* ������å��쥸���������� */ \
"	rte				\n")

#define EXCHDR_ENTRY(entry, inthdr)	_EXCHDR_ENTRY(entry, inthdr)

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå�
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	return((*((UH *) p_excinf) & 0x1000) == 0);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
	return((*((UH *) p_excinf) & 0x0700) == 0x0700);
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
