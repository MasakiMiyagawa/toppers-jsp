/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2002 by Monami software, Limited Partners.
 *  Copyright (C) 2002 by MURANAKA Masaki
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
 *  @(#) $Id: hw_timer.h,v 1.2 2002/04/10 12:08:17 honda Exp $
 */

/*
 *	�������åȰ�¸�����ޥ⥸�塼���PC/AT�ѡ�
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include "cpu_insn.h"
#include "sys_config.h"
#include "irc.h"

/*
 *  �����޳���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define	INHNO_TIMER	0x20

/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW	CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 *
 *  PC/AT �Ǥϡ������ޤ�1������˥�����ȥ��åפ��롥
 */
#define TIMER_CLOCK		1000
#define TO_CLOCK(nume, deno)	(TIMER_CLOCK * (nume) / (deno))

/*
 *  ����Ǥ������Υ����޼�����ñ�̤�����ɽ����
 */
#define MAX_CLOCK	((CLOCK) 0xffffff)

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
	static const int count = 1193182 / 1000;
	outb(0x43, 0x36);
	outb(0x40, count & 0xff);
	outb(0x40, count >> 8);
	irc_ena_irq(PIT_IRQ);
}

/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
	irc_eoi_irq(PIT_IRQ);
	irc_ena_irq(PIT_IRQ);
}

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
Inline void
hw_timer_terminate()
{
	irc_dis_irq(PIT_IRQ);
}

#if 0
/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
#error "undefined."
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline BOOL
hw_timer_fetch_interrupt(void)
{
#error "undefined."
}
#endif

#endif /* _HW_TIMER_H_ */
