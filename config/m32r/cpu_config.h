/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cpu_config.h,v 1.2 2002/04/05 09:01:40 takayuki Exp $
 */

#include "sys_config.h"

/*
 *	�ץ��å���¸�⥸�塼���M32R�ѡ�
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_


/*
 *  chg_ipm/get_ipm �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
/*#define	SUPPORT_CHG_IPM*/

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

#ifndef _MACRO_ONLY
/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	unsigned long sp;		/* �����å��ݥ��� */
	FP	pc;					/* �ץ���५���� */
	unsigned long psw;		/* �ץ���ॹ�ơ�������� */
} CTXB;

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU��å��Ȥ��β��
 *     CPU��å���CPU�����ĳ�����׵����/�ػߤ��б��դ���
 */

#define t_lock_cpu		lock_cpu
#define i_lock_cpu		lock_cpu
#define t_unlock_cpu	unlock_cpu
#define i_unlock_cpu	unlock_cpu
#define ena_int			lock_cpu
#define dis_int			unlock_cpu

Inline void
lock_cpu()
{
	__asm("mvfc r0, psw ");
	__asm("and3 r1, r0, 0xffbf");
	__asm("mvtc r1, psw ");
}

Inline void
unlock_cpu()
{
	__asm("mvfc r0, psw     ");
	__asm("or3  r1, r0, 0x40");
	__asm("mvtc r1, psw     ");
}

/*
 * sense_context : �桼�������å���ȤäƤ���ʤ饿��������ƥ�����
 */

Inline BOOL
sense_context(void)
{
	int psw;
	__asm("mvfc	%0, psw" : "=r"(psw));
	return (psw & 0x80) != 0 ? FALSE : TRUE;
}

/*
 * sense_lock : ����߶ػߤʤ�CPU��å�����
 */
Inline BOOL
sense_lock(void)
{
	int psw;
	__asm("mvfc	%0, psw" : "=r"(psw));
	return (psw & 0x40) != 0 ? FALSE : TRUE;
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

extern FP InterruptHandlerEntry[NUM_INTERRUPT];
extern FP ExceptionHandlerEntry[NUM_EXCEPTION];

/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
Inline void
define_inh(INHNO inhno, FP inthdr)
{
	InterruptHandlerEntry[inhno-1] = inthdr;
}

/*
 *  CPU�㳰�ϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� excno ��CPU�㳰�ϥ�ɥ�ε�ư���Ϥ� exchdr �����ꤹ�롥
 */
Inline void
define_exc(EXCNO excno, FP exchdr)
{
	ExceptionHandlerEntry[excno-1] = exchdr;
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


#define INT_ENTRY(hdr) hdr
#define INTHDR_ENTRY(entry)	extern void entry();

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

#define EXC_ENTRY(hdr) hdr
#define EXCHDR_ENTRY(entry)	extern void entry();

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå�
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	int psw;
	__asm("mvfc	%0, psw" : "=r"(psw));
	return (psw & 0x8000) != 0 ? FALSE : TRUE;
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
	int psw;
	__asm("mvfc	%0, psw" : "=r"(psw));
	return (psw & 0x4000) != 0 ? FALSE : TRUE;
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
 * ���߽�����γ����ͥ����
 */
extern ER get_ipr(IPR *);

#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
