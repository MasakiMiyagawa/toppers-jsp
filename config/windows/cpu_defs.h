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
 *  @(#) $Id: cpu_defs.h,v 1.4 2002/04/10 11:20:09 takayuki Exp $
 */


/*
 *	�ץ��å��˰�¸���������Windows�ѡ�
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#define WINDOWS

#include "itron.h"
#include "vwindows.h"

#define INT_NUMINTERRUPTS	7	/* ������ܿ� */

#ifndef _MACRO_ONLY

typedef	UINT		INHNO;		/* ����ߥϥ�ɥ��ֹ� */
typedef	UINT		EXCNO;		/* CPU�㳰�ϥ�ɥ��ֹ� */

/*
 * ����ߥ��ߥ�졼������Ϣ
 */

#define INT_STAT_PENDING 0x01
#define INT_STAT_RUNNING 0x02
#define INT_STAT_ENABLED 0x04

struct tagInterruptLevel
{
	HANDLE	ThreadHandle;
	DWORD	ThreadID;
	void *	Routine;
	unsigned char Status;
};

extern struct tagInterruptLevel InterruptLevel[INT_NUMINTERRUPTS];
extern CRITICAL_SECTION InterruptCriticalSection;
extern unsigned int CurrentInterruptLevel;


#define EXC_MAXITEMS 32

struct tagExceptionLevel
{
	DWORD ExceptionCode;
	void * Routine;
};

extern struct tagExceptionLevel ExceptionLevel[EXC_MAXITEMS];

/*
 * ����ߥ��ߥ�졼����������ؿ�
 */

extern BOOL def_int( unsigned int ims, void * rtn);	/* �ϥ�ɥ���� */
extern BOOL		ini_int( void );				/* ����� */
extern void		fin_int( void );
extern BOOL		ras_int(unsigned int ims);		/* ������׵� */
extern unsigned int sns_int( void );			/* Sense the highest pending request */
extern HANDLE	sch_int( void );				/* �����ߤΥ������塼�� */

 /* ���Ĥȶػߤϰ����˴ط��ʤ�������&���ػߤȤʤ� */
extern ER	ena_int(unsigned int ims);			/* ���� */
extern ER	dis_int(unsigned int ims);			/* �ػ� */

extern ER	chg_ims(unsigned int ims);			/* ����ߥ�٥������ */
extern ER	get_ims(unsigned int *p_ims);		/* ����ߥ�٥�μ��� */

extern BOOL def_exc( DWORD exc, void * routine);
extern BOOL ini_exc(void);
extern void fin_exc(void);

#endif /* _MACRO_ONLY */

#include "hw_timer.h"

/*
 *  ������ƥ��å������
 */
#define	TIC_NUME	TIMER_CLOCK_WINDOWS		/* ������ƥ��å��μ�����ʬ�� */
#define	TIC_DENO	1		/* ������ƥ��å��μ�����ʬ�� */


/*
 * ��ĥ�����ޡ� (Pentium Timer)
 */

typedef UD SYSUTIM;

Inline ER
vxget_tim(SYSUTIM * pk_sysutim)
{
	QueryPerformanceCounter((LARGE_INTEGER *)pk_sysutim);
	return E_OK;
}

#endif /* _CPU_DEFS_H_ */
