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
 *  @(#) $Id: cpu_config.h,v 1.7 2002/04/10 11:20:09 takayuki Exp $
 */


/*
 *	�ץ��å���¸�⥸�塼���Windows�ѡ�
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  Windows-HAL�ȼ��Υ��󥯥롼�ɥե�����
 */


/*
 *  chg_ims/ref_ims �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_CHG_IMS

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

#include "cpu_defs.h"
#include "hal_msg.h"
#include "vwindows.h"

/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	HANDLE	ThreadHandle;
	DWORD	ThreadID;
} CTXB;


extern CRITICAL_SECTION CPULock;

#define CPU_STAT_LOCK	0x01
#define CPU_STAT_EXC	0x02
extern volatile char CPUStatus;

/*
 *   CPU�㳰�ϥ�ɥ�
 */

/*#define EXCHNO_ZDIV  EXCEPTION_INT_DIVIDE_BY_ZERO */

/*
 *  �����ƥ���ֻ���
 */

Inline BOOL
sense_context()
{
	return (CurrentInterruptLevel != 0) ? TRUE : FALSE;
}

Inline BOOL
sense_lock()
{
	return (CPUStatus & (CPU_STAT_LOCK|CPU_STAT_EXC)) != 0 ? TRUE : FALSE;
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 *  task_intmask �ϡ�chg_ipm �򥵥ݡ��Ȥ��뤿����ѿ���chg_ipm �򥵥ݡ�
 *  �Ȥ��ʤ����ˤϡ�task_intmask ����� 0 �ˤʤäƤ���ȹͤ���Ф褤��
 */

#include "debugout.h"
#include "device.h"

Inline void
i_lock_cpu()
{
	dis_int(0);
}

Inline void
i_unlock_cpu()
{
	ena_int(0);
}

#define t_lock_cpu	i_lock_cpu
#define t_unlock_cpu	i_unlock_cpu

/*
 *  �������ǥ����ѥå���
 */

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå�
 *
 *  dispatch �ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ����������
 *  ��ǡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	dispatch();


/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */

extern void    exit_and_dispatch(void);

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ������
 */


/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */

Inline void
define_inh(INHNO inhno, FP inthdr)
{
	def_int((unsigned int)inhno,(void *)inthdr);
}

/*
 *  CPU�㳰�ϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� excno ��CPU�㳰�ϥ�ɥ�ε�ư���Ϥ� exchdr �����ꤹ�롥
 */
Inline void
define_exc(EXCNO excno, FP exchdr)
{
	def_exc( (DWORD)excno, (void *)exchdr);
}

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν���������
 */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 *  ���Ƥγ����ߥϥ�ɥ�ϥǥ����ѥå����ư����SIGUSR1��ޥ�������
 *  ư��롣
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 */

	/* Windows-HAL�ˤ����Ƥ��ν����ϳ���ߥ��ߥ�졼���˰�Ǥ���Ƥ��� */

#define INT_ENTRY(hdr) hdr
#define INTHDR_ENTRY(inthdr) extern void inthdr(void)

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
#define EXCHDR_ENTRY(inthdr) extern void inthdr(void)

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå�
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	return (CPUStatus & CPU_STAT_EXC) != 0 ? TRUE : FALSE;
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
#define exc_sense_lock sense_lock


/*
 *  �ץ��å���¸�ν����
 */
extern void	cpu_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void	cpu_terminate(void);

/* Windows Dedicated Routines */
extern LONG WINAPI HALExceptionHandler( EXCEPTION_POINTERS * exc );

#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
