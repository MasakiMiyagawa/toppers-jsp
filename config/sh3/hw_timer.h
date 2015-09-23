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
 *  ���ξ��Τ����줫�����������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
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
 *  @(#) $Id: hw_timer.h,v 1.3 2001/11/05 13:31:13 honda Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*
 *  CPU��¸�����ޥ⥸�塼���SH3�ѡ�
 *  TMU0�����
 */


#include "sys_defs.h"
#include "cpu_config.h"

#if defined(SH7750)
#include "sh4.h"
#else
#include "sh3.h"
#endif /* SH7750 */

/*
 *  �����޳���ߥϥ�ɥ��INTEVT�ֹ�
 */
#define	INHNO_TIMER	TMU0_INTEVT

/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW	CLOCK;

/*
 *  �����ޡ��γ����ߥ�٥�
 */

#define TINTLVL0        4


#define TO_CLOCK(nume, deno)	(TIMER_CLOCK * (nume) / (deno))

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK	((CLOCK) 0xffffffff)

/*
 *  ��ǽɾ���ѥ����ƥ�������Ф��ݤν������֤θ��Ѥ��͡�ñ�̤�����ɽ����
 */
#define GET_TOLERANCE	100

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
Inline void
hw_timer_initialize()
{
	CLOCK	c = TO_CLOCK(TIC_NUME, TIC_DENO);
        
	/*
	 *  �����޴�Ϣ������
	 */
    TMU.TSTR&=~TMU_STR0;             /* ��������� */
    assert(c <= MAX_CLOCK);		     /* �����޾���ͤΥ����å� */
    
    TMU.TCR0  = (0x020 | TCR0_TPSC); /* ʬ�������ꡢ�����ߵ��� */
    
    TMU.TCOR0 = c;                   /* timer constant�쥸�����򥻥å� */
    TMU.TCNT0 = c;                   /* �����󥿡��򥻥å� */
    TMU.TSTR  |= TMU_STR0;           /* ������0��������    */

    
    /*
	 *  ����ߴ�Ϣ������
	 */
    define_int_plevel(TMU0_INTEVT,TINTLVL0); /* �����ߥ�٥�����(SF) */
    *IPRA=(*IPRA&0x0fff)|(TINTLVL0<<12);     /* �����ߥ�٥�����(HW) */
    TMU.TCR0 &= ~TCR_UNF;                    /* �������׵�򥯥ꥢ   */
}


/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
    TMU.TCR0 &= ~TCR_UNF;                /* �������׵�򥯥ꥢ */
}

/*
 *  �����ޤ���߽���
 */
Inline void
hw_timer_terminate()
{
    TMU.TSTR&=~TMU_STR0;                  /* �����ޤ���� */
    TMU.TCR0 = 0;                         /* �������׵�򥯥ꥢ */
}

/*
 *  �����ޤθ����ͤ��ɤߤ���
 *
 *  ����߶ػ߶����ǸƤӽФ����ȡ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - TMU.TCNT0);
}

Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(TMU.TCR0 & TCR_UNF);
}

#endif /* _HW_TIMER_H_ */



