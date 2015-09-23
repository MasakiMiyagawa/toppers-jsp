/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ�
 *  �եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�����
 *  �ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�������Х��ʥꥳ���ɤη��ޤ��ϵ�����Ȥ߹����������
 *      �Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (3) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: hw_timer.h,v 1.1 2000/11/14 14:44:16 hiro Exp $
 */

/*
 *	�������åȰ�¸�����ޥ⥸�塼���DVE68K/40�ѡ�
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include "dve68k.h"

/*
 *  �����޳���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define	INHNO_TIMER	TT0_VEC

/*
 *  �������ͤ�����ɽ���η�
 */
typedef UW	CLOCK;

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 *
 *  DVE68K/40 CPU�ܡ��ɤǤϡ������ޤ�1������˥�����ȥ��åפ��롥
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
	CLOCK	c = TO_CLOCK(TIC_NUME, TIC_DENO);

	/*
	 *  �����޴�Ϣ������
	 */
	assert(c <= MAX_CLOCK);		/* �����޼����ξ���ͤΥ����å� */
	*DGA_CSR12 = 0x80000000 | c;	/* ����ͤ����ꡤ�����ޥ������� */

	/*
	 *  ����ߴ�Ϣ������
	 */
	dga_set_ilv(DGA_CSR25, TT0IL_BIT, IRQ_LEVEL4);
					/* ����ߥ�٥����� */
	*DGA_CSR23 = TT0_BIT;		/* ������׵�򥯥ꥢ */
	*DGA_CSR21 |= TT0_BIT;		/* ����ߥޥ������ */
}

/*
 *  �����޳�����׵�Υ��ꥢ
 */
Inline void
hw_timer_int_clear()
{
	*DGA_CSR23 = TT0_BIT;		/* �����޳�����׵�򥯥ꥢ */
}

/*
 *  �����ޤ���߽���
 *
 *  �����ޤ�ư�����ߤ����롥
 */
Inline void
hw_timer_terminate()
{
	*DGA_CSR12 &= 0x7fffffff;	/* �����ޤ���� */
	*DGA_CSR21 &= ~TT0_BIT;		/* ����ߥޥ������� */
	*DGA_CSR23 = TT0_BIT;		/* ������׵�򥯥ꥢ */
}

/*
 *  �����ޤθ����ͤ��ɽФ�
 */
Inline CLOCK
hw_timer_get_current(void)
{
	CLOCK	c;

	*DGA_CSR12 &= 0x7fffffff;	/* �����ޤ���� */
	cpu_wait_io();			/* �����ޤ���ߤ���Τ��Ԥ� */
	cpu_wait_io();
	c = *DGA_CSR13 & 0x00ffffff;
	*DGA_CSR12 |= 0x80000000;	/* �����ޥ������� */
	return(c);
}

/*
 *  �����޳�����׵�Υ����å�
 */
Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(*DGA_CSR20 & TT0_BIT);
}

#endif /* _HW_TIMER_H_ */