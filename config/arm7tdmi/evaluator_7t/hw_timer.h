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
 *  @(#) $Id: hw_timer.h,v 1.4 2002/04/05 07:43:51 honda Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*
 *  CPU��¸�����ޥ⥸�塼���Evaluator-7T�ѡ�
 *  TMU0�����
 */
#include "evaluator7t.h"
#include "sys_defs.h"
#include "cpu_config.h"
#include "sys_config.h"


/*
 *  �����޳���ߤγ�����ֹ�
 */
#define	INHNO_TIMER	IRQ_NUMBER_TMU0


/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW	CLOCK;


/*
 *  �����ޡ��γ����ߥ�٥�
 */
#define TINTLVL0        4


/*
 *  �����ޡ�
 */
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
    *TMOD = 0;                       /* ��������� */
    assert(c <= MAX_CLOCK);		     /* �����޾���ͤΥ����å� */

    *INTPND = IRQ_BIT_TMU0;          /* ����ߤΥ��ꥢ  */
    *TCNT0       = 0;
    *TDATA0      = c;                /* ��������ͤ򥻥å� */
    *TMOD       |= TM_TE0;           /* ������ȥ�������   */

    
    /*
	 *  ����ߴ�Ϣ������
	 */
    /* �����ߥ�٥�����(SF) */
    
    /* �����ߥ�٥�����(HW) */    
//    *(INTPRI0 + TINTLVL0 / 4) =   IRQ_NUMBER_TMU0 << (TINTLVL0 % 4);

    *INTPND  = IRQ_BIT_TMU0;                 /* �������׵�򥯥ꥢ   */
    *INTMSK &= ~((1 << INT_GLOBAL) | IRQ_BIT_TMU0 ); /* ����ߵ��� */    
}


/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
  *INTPND  = IRQ_BIT_TMU0;                 /* �ڥ�ǥ��󥰥ӥåȤ򥯥ꥢ */
}


/*
 *  �����ޤ���߽���
 */
Inline void
hw_timer_terminate()
{
    *TMOD   |= ~TM_TE0;                      /* �����ޤ���� */
    *INTMSK |= IRQ_BIT_TMU0;                 /* ������Ե���*/    
    *INTPND  = IRQ_BIT_TMU0;                 /* �ڥ�ǥ��󥰥ӥåȤ򥯥ꥢ */
}


/*
 *  �����ޤθ����ͤ��ɤߤ���
 *
 *  ����߶ػ߶����ǸƤӽФ����ȡ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
	return(TO_CLOCK(TIC_NUME, TIC_DENO) - *TCNT0);
}


Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(*INTPND & IRQ_BIT_TMU0);
}

#endif /* _HW_TIMER_H_ */



