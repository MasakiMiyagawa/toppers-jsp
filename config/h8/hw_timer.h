/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: hw_timer.h,v 1.1 2001/11/12 13:38:30 abe Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*
 *  CPU��¸�����ޥ⥸�塼���H8�ѡ�
 *  ITU0�����
 */

#include "sys_defs.h"
#include "sys_config.h"
#include "cpu_config.h"

/*
 *  �������ͤ�����ɽ���η�
 */

typedef UH	CLOCK;

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
hw_timer_int_clear(void)
{
    /* GRA����ڥ��ޥå��γ������׵�ե饰�򥯥ꥢ */
    /*outb(SYSTEM_ITU + H8TSR, inb(SYSTEM_ITU + H8TSR) & ~H8TSR_IMIFA);*/
    UW addr = SYSTEM_ITU + H8TSR;

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(H8TSR_IMIFA_BIT));
#undef  BITCLR
}

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */

Inline void
hw_timer_initialize()
{
    UW addr = H8ITU_TSTR;

    /* ��������� */
    /*outb(H8ITU_TSTR, inb(H8ITU_TSTR) & ~SYSTEM_STR);*/

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(SYSTEM_STR_BIT));
#undef  BITCLR

    /*  GRA����ڥ��ޥå��ǥ����󥿤򥯥ꥢ��ʬ�������� */
    outb(SYSTEM_ITU + H8TCR, H8TCR_CCLR | H8TCR_CKEG | H8TCR_TPSC);

    /*  GRA����ڥ��ޥå��ˤ�������׵����� */
    outb(SYSTEM_ITU + H8TIER, SYSTEM_ITU_IE);

    /*  GRA����ڥ��ޥå��ˤ��ü�ҽ��϶ػ� */
    outb(SYSTEM_ITU + H8TIOR, H8TIOR_IOB | H8TIOR_IOA);

    /*  GRA�쥸��������ʥ�������ɸ�͡�  	*/
    outw(SYSTEM_ITU + SYSTEM_GR, CLOCK_PER_TICK);

    outw(SYSTEM_ITU + H8TCNT, 0);	/* �����󥿤򥯥ꥢ	*/

    hw_timer_int_clear();		/*  ������׵�򥯥ꥢ  */

    /* �����ޥ������� */
    /*outb(H8ITU_TSTR, inb(H8ITU_TSTR) | SYSTEM_STR);*/

#define BITSET(bit)	Asm("bset #" bit ", @%0" : : "r"(addr))
	BITSET(_TO_STRING(SYSTEM_STR_BIT));
#undef  BITSET
}

/*
 *  �����ޤ���߽���
 */

Inline void
hw_timer_terminate()
{
    UW addr = H8ITU_TSTR;

    /* ��������� */
    /*outb(H8ITU_TSTR, inb(H8ITU_TSTR) & ~SYSTEM_STR);*/

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(SYSTEM_STR_BIT));
#undef  BITCLR

    hw_timer_int_clear();		/* �������׵�򥯥ꥢ */
}

/*
 *  �����ޤθ����ͤ��ɤ߽Ф�
 *
 *  ����߶ػ߶����ǸƤӽФ����ȡ�
 */

Inline CLOCK
hw_timer_get_current(void)
{
	return(CLOCK_PER_TICK - (CLOCK)(inw(SYSTEM_ITU + H8TCNT)));
}

/*
 *  �����޳�����׵�Υ����å�
 */

Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(inb(SYSTEM_ITU + H8TSR) & H8TSR_IMIFA);
}

#endif /* _HW_TIMER_H_ */
