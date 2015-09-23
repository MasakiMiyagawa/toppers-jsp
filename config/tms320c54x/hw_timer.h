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
 *  @(#) $Id: hw_timer.h,v 1.3 2002/04/14 14:19:50 reiji Exp $
 */


#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_


#include "c54x.h"
#include "sys_defs.h"
#include "cpu_config.h"

#define INHNO_TIMER TINT0_VEC

#define TO_CLOCK(nume,deno) (TIMER_CLOCK * (nume) / (deno))

#define MAX_CLOCK ((CLOCK) 0xffff)

#define GET_TOLERANCE 100

#ifndef _MACRO_ONLY

typedef UH CLOCK;

Inline void
hw_timer_initialize()
{
  CLOCK c=TO_CLOCK(TIC_NUME,TIC_DENO);

   TMU0.TCR=TCR_TSS | 0x0009;   /* 0.25 ��sec�ǥ�����Ȥ���   */
  //TMU0.TCR = TCR_TSS | 0x0001;
  TMU0.PRD=c-1;                  /* �����󥿤�����             */
  TMU0.TCR|=TCR_TRB;           /* �����󥫥��󥿤ν�������� */
  TMU0.TCR&=~TCR_TSS;          /* �����ޤε�ư               */

  IFR|=(0x1 << TINT0);
  IMR|=(0x1 << TINT0);
}

Inline void
hw_timer_int_clear()
{
}

Inline void
hw_timer_terminate()
{
  TMU0.TCR|=TCR_TSS;
  IFR|=(0x1 << TINT0);
}

Inline CLOCK
hw_timer_get_current(void)
{
  return (TO_CLOCK(TIC_NUME,TIC_DENO) - TMU0.TIM);
}

Inline BOOL
hw_timer_fetch_interrupt(void)
{
  return (IFR & (0x1 << TINT0));
}

#endif

#endif
