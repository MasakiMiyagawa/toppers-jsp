/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: hw_timer.h,v 1.1 2006/04/10 08:19:25 honda Exp $
 */

/*
 *	�����ޥɥ饤�С�Zup-F16��ĥ�ܡ����ѡ�
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>
#include <sil.h>
#include <tmp91cy22.h>

/*
 *  �����޳���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define	INHNO_TIMER		INT_NO_TA0

/*
 *  �����ޡ��γ����ߥ�٥�
 */
#define INT_LEVEL_TIMER	0x04

#ifndef _MACRO_ONLY

/*
 *  1ms�Υ����ޡ������ߤ���Ѥ���ΤǤ��Υ���å���������롥
 */
#define TIMER_CLOCK		192


/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
#pragma inline hw_timer_initialize
void
hw_timer_initialize()
{
	/* ������0���	*/
	sil_wrb_mem((VP)TADR_SFR_TA01RUN,
		(VB)(sil_reb_mem((VP)TADR_SFR_TA01RUN) & ~TBIT_TA0RUN));
	/* �⡼������	 IDLE2:ư��,8bit�⡼��,����������å�/16,1ms	*/
	sil_wrb_mem((VP)TADR_SFR_TA01RUN,
		(sil_reb_mem((VP)TADR_SFR_TA01RUN) | TBIT_I2TA01));
	sil_wrb_mem((VP)TADR_SFR_TA01MOD,
		(sil_reb_mem((VP)TADR_SFR_TA01MOD) | TBIT_TA0CLK16));
	sil_wrb_mem((VP)TADR_SFR_TA0REG, (VB)(TIMER_CLOCK - 1) );
	/* ���������	������׵᥯�ꥢ,����ߥ�٥�5	*/
	sil_wrb_mem((VP)TADR_SFR_INTCLR, TBIT_TA0_CLR );
	sil_wrb_mem((VP)TADR_SFR_INTETA01,
		(VB)((sil_reb_mem((VP)TADR_SFR_INTETA01) & ~TBIT_INTM_L) | INT_LEVEL_TIMER));
	/* ������0����ӥץꥹ�����鵯ư	*/
	sil_wrb_mem((VP)TADR_SFR_TA01RUN,
		(VB)(sil_reb_mem((VP)TADR_SFR_TA01RUN) | (TBIT_TA01PRUN | TBIT_TA0RUN)));
}

/*
 *  �����޳�����׵�Υ��ꥢ
 */
#pragma inline hw_timer_int_clear
void
hw_timer_int_clear()
{
	/* ������׵᥯�ꥢ	*/
	sil_wrb_mem((VP)TADR_SFR_INTCLR, TBIT_TA0_CLR );
}

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
#pragma inline hw_timer_terminate
void
hw_timer_terminate()
{
	/* ������0���	*/
	sil_wrb_mem((VP)TADR_SFR_TA01RUN,
		(VB)(sil_reb_mem((VP)TADR_SFR_TA01RUN) & ~TBIT_TA0RUN));
}

/*
 *  �����޳�����׵�Υ����å�
 */
#pragma inline hw_timer_fetch_interrupt
BOOL
hw_timer_fetch_interrupt(void)
{
	return (sil_reb_mem((VP)TADR_SFR_INTETA01) & TBIT_INTC_L);
}

#endif /* _MACRO_ONLY */
#endif /* _HW_TIMER_H_ */
