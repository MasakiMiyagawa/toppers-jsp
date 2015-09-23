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
 *  @(#) $Id: hw_timer.h,v 1.1 2002/04/05 08:47:14 honda Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*
 * CPU��¸�����ޥ⥸�塼���MicroBlaze�ѡ�
 */ 
 
#include "sys_defs.h"
#include "cpu_config.h"
#include "sys_config.h"
#include "microblaze.h"

/*
 * �����޳���ߥϥ�ɥ�γ�����ֹ�
 */
#define INHNO_TIMER TIMINTLVL

/*
 * �������ͤ�����ɽ���η�
 */
typedef UW CLOCK;

#define TO_CLOCK(nume, deno)  (TIMER_CLOCK * (nume) / (deno))

/*
 *  ����Ǥ�����祿���޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK ((CLOCK) 0xffffffff)

/*
 *  ��ǽɾ���ѥ����ƥ�������Ф��ݤν������֤θ��Ѥ��͡�ñ�̤�����ɽ����
 */
#define GET_TOLERANCE	100



/*
 * �����ޤε�ư����
 *
 * �����ޤ�������������Ū�ʥ����޳���ߤ�ȯ��������
 */ 
Inline void
hw_timer_initialize(void)
{
  int dummy;
  
  CLOCK c = TO_CLOCK(TIC_NUME, TIC_DENO);

  *TIMER_TCSR0 = TIMER_RESET;  /* �ꥻ�å� */
  
  assert(c <= MAX_CLOCK);		     /* �����޾���ͤΥ����å� */
  *TIMER_TCCR0 = c;            /* �����󥿡����å� */
  
  /*
   * �����ޡ�0���͡��֥롤�����ȥ���ɡ������󥫥���ȡ�����ߵ��ġ�
   */
  *TIMER_TCSR0 = TIMER_ENABLE | TIMER_RELOAD
                   | TIMER_DOWN_COUNT | TIMER_ENABLE_INTR;

  /*
   *  INTC����ߵ���
   */
  dummy = 1 << (TIMINTLVL - 1);
  intc_enable_interrupt(dummy);
}



/*
 *   �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
  *TIMER_TCSR0 = *TIMER_TCSR0; 
}



/*
 *   �����ޤζػ߽���
 */
Inline void
hw_timer_terminate()
{
  int dummy;
  
  *TIMER_TCSR0 = ~TIMER_ENABLE; /* ���������         */
  *TIMER_TCSR0 = *TIMER_TCSR0;  /* ������׵�Υ��ꥢ */
  
  /*
   * ���Ǥ˳���ߤ����äƤ����礬����Τǳ�����׵�򥯥ꥢ
   */
  dummy = 1 << (TIMINTLVL - 1);
  intc_ack_interrupt(dummy);
  intc_disable_interrupt(dummy);  /* INTC�μ����դ��ػ� */
}



/*
 *   �����ޤθ����ͤ��ɤ߽Ф�
 *
 *   ����߶ػ߶����ǸƤӽФ�����
 */
Inline CLOCK
hw_timer_get_current(void)
{
  return(TO_CLOCK(TIC_NUME, TIC_DENO) - *TIMER_TCR0);
}



/*
 *   ����ߤ�ȯ�����Ƥ��뤫��Ƚ��
 */
Inline BOOL
hw_timer_fetch_interrupt(void)
{
  return(*TIMER_TCSR0 & TIMER_INTERRUPT);
}

#endif /* _HW_TIMER_H_ */