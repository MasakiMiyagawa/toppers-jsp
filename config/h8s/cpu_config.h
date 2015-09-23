/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: cpu_config.h,v 1.2 2002/04/13 13:14:45 imai Exp $
 */


/*
 *  �ץ��å���¸�⥸�塼��(H8S��)
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#ifndef OMIT_RENAME

#define activate_r		_kernel_activate_r
#define ret_int			_kernel_ret_int
#define ret_exc			_kernel_ret_exc
#define task_intmask		_kernel_task_intmask
#define int_intmask		_kernel_int_intmask

#ifdef LABEL_ASM

#define _activate_r		__kernel_activate_r
#define _ret_int		__kernel_ret_int
#define _ret_exc		__kernel_ret_exc
#define _task_intmask		__kernel_task_intmask
#define _int_intmask		__kernel_int_intmask

#endif /* LABEL_ASM */
#endif /* OMIT_RENAME */




/*  �����ǽ�ʺǹ�ͥ����  */
#define  MAX_IPM	0x7
#define  str_MAX_IPM	_TO_STRING(MAX_IPM)
#define  MAX_IPM_CCR	0x80


/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */

#ifndef _MACRO_ONLY
#include "cpu_insn.h"
#endif /* _MACRO_ONLY */

#ifndef _MACRO_ONLY

/*  ����饤��ؿ�Ÿ���λ���  */
#pragma inline(current_intmask, set_intmask, sense_context) 
#pragma inline(sense_lock, t_lock_cpu, t_unlock_cpu)
#pragma inline(i_lock_cpu, i_unlock_cpu, define_inh, define_exc)
#pragma inline(exc_sense_context, exc_sense_lock)


/*
 *  chg_ipm/get_ipm �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define		SUPPORT_CHG_IPM

/*
 *  ����������ƥ����ȥ֥�å������
 */

typedef struct task_context_block {
	VP	sp;		/* �����å��ݥ��� */
	FP	pc;		/* �ץ���५���� */
} CTXB;


/*
 *  ����ߥޥ������饤�֥��
 */

/*
 *  ���ߤγ���ߥޥ������ɽФ�
 */

Inline UB
current_intmask(void)
{
	return((UB)(current_exr() & 0x07));
}

/*
 *  ����ߥޥ���������
 */

Inline void
set_intmask(IPM intmask)
{
	set_exr((UB)((current_exr() & ~0x07) | intmask));
}

/*
 *  ����ߥͥ��ȥ�����
 */

extern UW	intnest;

/*
 *  ����ƥ����Ȼ���
 *
 *  ����ߥͥ��ȥ����󥿤��ɤ߽Ф���ľ��˳���ߤ�ȯ�����Ƥ⡢��ä���
 *  ���ˤϥ���ƥ����Ȥ⸵����äƤ���
 */

Inline BOOL
sense_context(void)
{
	return(intnest > 0);
}


Inline BOOL
sense_lock(void)
{
	return(current_intmask() == 0x07);
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock
/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 *  task_intmask �ϡ�chg_ipm �򥵥ݡ��Ȥ��뤿����ѿ���chg_ipm �򥵥ݡ�
 *  �Ȥ��ʤ����ˤϡ�t_unlock_cpu ��� task_intmask �� 0 ���֤�������
 *  �褤��
 */

#ifdef SUPPORT_CHG_IPM
extern IPM	task_intmask;	/* ����������ƥ����ȤǤγ���ߥޥ��� */
#endif /* SUPPORT_CHG_IPM */

Inline void
t_lock_cpu(void)
{
	disint();
}

Inline void
t_unlock_cpu(void)
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

extern 	IPM	int_intmask;	/* �󥿥�������ƥ����ȤǤγ���ߥޥ��� */

Inline void
i_lock_cpu(void)
{
	IPM	intmask;

	/*
	 *  ����ѿ� intmask ��ȤäƤ���Τϡ�current_intmask()��Ƥ�
	 *  ��ľ��˳���ߤ�ȯ��������ư���줿����ߥϥ�ɥ����
	 *  int_intmask ���ѹ�������ǽ�������뤿��Ǥ��롥
	 */
	intmask = current_intmask();
	disint();
	int_intmask = intmask;
}

Inline void
i_unlock_cpu(void)
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
 *
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 *  ��(�㳰�����٥����ơ��֥뤬����Τ���ˡ����δؿ��ϲ�������򤷤ʤ���)
 */

Inline void
define_inh(INHNO inhno, FP inthdr)
{
}

/*
 *   CPU�㳰�ϥ�ɥ������
 *    (�㳰�����٥����ơ��֥뤬����Τ���ˡ����δؿ��ϲ�������򤷤ʤ���)
 */

Inline void
define_exc(EXCNO excno, FP exchdr)
{
}

/*
 *  ����ߥϥ�ɥ�ν���������
 *
 */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *		�ʼ������������
 *
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 *
 *
 */

/*  C����롼����δؿ�̾�������������Υ�٥������  */

#define	INT_ENTRY(inthdr)	inthdr##_entry
#define	EXC_ENTRY(exchdr)	exchdr##_entry

/*
 *  ����ߥϥ�ɥ����������
 *
 *	H8S�Ǥϡ�����ߤ�CPU�㳰�ΰ�����Ʊ���ʤΤǡ�
 *	���������Υޥ���ⶦ�̤�������Ƥ���
 *
 *	entry�����������Υ�٥�
 *	inthdr��C����롼�������Ƭ���ɥ쥹
 *
 */

/*  ����ߤν�����������ϡ�in_header.txt����perl�ˤ�ä�
 *  int_hdler.src���������Ƥ��롣  */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */


#define INTHDR_ENTRY(inthdr)				\
	extern void inthdr##_entry(void)		

/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 */

#define	EXCHDR_ENTRY(exchdr)	INTHDR_ENTRY(exchdr)

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ�����Ƚ��
 */

Inline BOOL
exc_sense_context(VP p_excinf)
{
	/* ������Ӥ���Τϡ����߼¹����CPU�㳰��ʬ 		*/
	/*  ����ߥͥ��ȥ����󥿤����󥯥���Ȥ���Ƥ��뤿�� 	*/
	return(intnest > 1);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 *  ��H8S�ǤǤϡ��ƤФ�뤳�Ȥ�̵������������ꤹ��� 
 */

Inline BOOL
exc_sense_lock(VP p_excinf)
{
	return(TRUE);
}

/*
 *  �ץ��å���¸�ν����
 */

extern void	cpu_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */

extern void	cpu_terminate(void);

/*
 *  ̤��������ȯ�����Υ��顼���ϻ��Υ����å���¤�����
 */

typedef struct exc_stack {
	VW	er0;
	VW	er1;
	VW	er2;
	VW	er3;
	VW	er4;
	VW	er5;
	VW	er6;
	VW	pc;	/*  �ץ���ࡦ������  	*/
} EXCSTACK;

/*
 * ̤��������ȯ�����Υ��顼���� (cpu_config.c, cpu_support.S)
 */

extern void     cpu_experr(EXCSTACK *);

#endif /* _MACRO_ONLY_ */

#endif /* _CPU_CONFIG_H_ */
