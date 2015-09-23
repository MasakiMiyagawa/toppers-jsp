/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: hw_timer.h,v 1.2 2001/10/22 02:16:43 imai Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*
 *  CPU��¸�����ޥ⥸�塼���SH1�ѡ�
 *  TMU0�����
 */

#include "sh1.h"
#include "sys_defs.h"
#include "cpu_config.h"

/*
 *  �����޳���ߥϥ�ɥ�Υ٥����ֹ�
 *	jsp/systask/timer.cfg�ǳ���ߥϥ�ɥ����Ͽ�˻���
 */
#define	INHNO_TIMER	IMIA0

/*
 *  �������ͤ�����ɽ���η�
 */
typedef UH	CLOCK;

/*
 *  �����ޡ��γ����ߥ�٥�
 */
#define TINTLVL0	4

/*  ����ߥ�٥������쥸��������������Ȥ��Υ��եȿ�  */
#define ITU_BIT_SHIFT	4

/*
 *  �����޼�����ñ�̤�����ɽ�����Ѵ�
 *  	jsp/kernel/time_manage.c�Ǥ����
 */
#define TO_CLOCK(nume, deno)	(TIMER_CLOCK * (nume) / (deno))

/*
 *  �����޼�����ñ�̤�����ɽ�����Ѵ�
 */
#define CLOCK_PER_TICK	((CLOCK) TO_CLOCK(TIC_NUME, TIC_DENO))

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK	((CLOCK) 0xffff)

/*
 *  ��ǽɾ���ѥ����ƥ�������Ф��ݤν������֤θ��Ѥ���
 *	��ñ�̤�����ɽ����
 *	��ա�������ʬ������å��˰�¸��
 */
#define GET_TOLERANCE	100


/*
 *  �����޳�����׵�Υ��ꥢ
 *	TCR�쥸������IMFA�ӥåȤ�1���ɤ߽Ф�����ˣ���񤭹���
 */


Inline void
hw_timer_int_clear()
{
    ITU.TSR0 &= ~TSR_IMFA;	/* �������׵�򥯥ꥢ 	*/
}				/*  ��GRA����ڥ��ޥå��ե饰�� */


/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */
Inline void
hw_timer_initialize()
{
	/*
	 *  �����޴�Ϣ������
	 */
    ITU.TSTR &= ~TSTR_STR0;	/* ��������� */
    		     		/* �����޾���ͤΥ����å� */
    assert(CLOCK_PER_TICK <= MAX_CLOCK);
			/*  GRA����ڥ��ޥå��ǥ����󥿤򥯥ꥢ */
			/*  ʬ��������  			*/
    ITU.TCR0 = (TCR_CCLR_GRA | TCR_TPSC);
			/*  GRA����ڥ��ޥå��ˤ�������׵����� */
    ITU.TIER0 = TIER_RESERVE | TIER_IMIEA;
			/*  GRA����ڥ��ޥå��ˤ��ü�ҽ��϶ػ� */
    ITU.TIOR0 = TIOR_RESERVE | TIOR_IOA;
			/*  GRA�쥸��������ʥ�������ɸ�͡�  	*/
    ITU.GRA0 = CLOCK_PER_TICK;
    ITU.TCNT0 = 0;	/* �����󥿤򥯥ꥢ 			*/

	/*
	 *  ����ߴ�Ϣ������
	 */
    					/* �����ߥ�٥����� 	*/
    define_int_plevel(IPRC, TINTLVL0, ITU_BIT_SHIFT);
    hw_timer_int_clear();		/*  ������׵�򥯥ꥢ  */


    ITU.TSTR  |= TSTR_STR0;		/* �����ޥ�������    	*/
}


/*
 *  �����ޤ���߽���
 */
Inline void
hw_timer_terminate()
{
    ITU.TSTR &= ~TSTR_STR0;		  /* �����ޤ���� 	  */
    hw_timer_int_clear();		  /* �������׵�򥯥ꥢ */
}

/*
 *  �����ޤθ����ͤ��ɤ߽Ф�
 *
 *  ����߶ػ߶����ǸƤӽФ����ȡ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
	return(CLOCK_PER_TICK - (CLOCK)(ITU.TCNT0));
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(ITU.TSR0 & TSR_IMFA);
}

#endif /* _HW_TIMER_H_ */
