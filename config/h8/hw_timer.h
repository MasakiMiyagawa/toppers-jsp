/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: hw_timer.h,v 1.9 2004/09/03 15:39:07 honda Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

#include <s_services.h>

#ifndef _MACRO_ONLY

/*
 *  CPU��¸�����ޥ⥸�塼���H8�ѡ�
 */

/*
 *  �������ͤ�����ɽ���η�
 */

typedef UH	CLOCK;

/*
 *  �����޼�����ñ�̤�����ɽ�����Ѵ�
 *  	jsp/kernel/time_manage.c�Ǥ����
 */

#define TO_CLOCK(nume, deno)	(TIMER_CLOCK * (nume) / (deno))
#define TO_USEC(clock)		((clock) * 1000 / TIMER_CLOCK)

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
#define	BEFORE_IREQ(clock) \
		((clock) >= TO_CLOCK(TIC_NUME, TIC_DENO) - GET_TOLERANCE)

/*
 *  �����޳�����׵�Υ��ꥢ
 *	TCR�쥸������IMFA�ӥåȤ�1���ɤ߽Ф�����ˣ���񤭹���
 */

Inline void
hw_timer_int_clear(void)
{
    /* GRA����ڥ��ޥå��γ������׵�ե饰�򥯥ꥢ */
    /*sil_wrb_mem((VP)SYSTEM_TIMER_IFR,
                  sil_reb_mem((VP)SYSTEM_TIMER_IFR) & ~SYSTEM_TIMER_IF);*/
    UW addr = SYSTEM_TIMER_IFR;

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(SYSTEM_TIMER_IF_BIT));
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
    UW addr = SYSTEM_TIMER_TSTR;

    /* ��������� */
    /*sil_wrb_mem((VP)SYSTEM_TIMER_TSTR,
                  sil_reb_mem((VP)SYSTEM_TIMER_TSTR) & ~SYSTEM_TIMER_STR);*/

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(SYSTEM_TIMER_STR_BIT));
#undef  BITCLR

    /*  GRA����ڥ��ޥå��ǥ����󥿤򥯥ꥢ��ʬ�������� */
    sil_wrb_mem((VP)SYSTEM_TIMER_TCR, SYSTEM_TIMER_TCR_BIT);

    /*  GRA����ڥ��ޥå��ˤ�������׵����� */
    sil_wrb_mem((VP)SYSTEM_TIMER_IER, SYSTEM_TIMER_IE);

    /*  GRA����ڥ��ޥå��ˤ��ü�ҽ��϶ػ� */
    sil_wrb_mem((VP)SYSTEM_TIMER_TIOR, SYSTEM_TIMER_TIOR_BIT);

    /*  GRA�쥸��������ʥ�������ɸ�͡�  	*/
    sil_wrh_mem((VP)SYSTEM_TIMER_GR, CLOCK_PER_TICK);

    sil_wrh_mem((VP)SYSTEM_TIMER_CNT, 0);	/* �����󥿤򥯥ꥢ	*/

    hw_timer_int_clear();			/*  ������׵�򥯥ꥢ	*/

    /* �����ޥ������� */
    /*sil_wrb_mem((VP)SYSTEM_TIMER_TSTR,
                  sil_reb_mem((VP)SYSTEM_TIMER_TSTR) | SYSTEM_TIMER_STR);*/

#define BITSET(bit)	Asm("bset #" bit ", @%0" : : "r"(addr))
	BITSET(_TO_STRING(SYSTEM_TIMER_STR_BIT));
#undef  BITSET
}

/*
 *  �����ޤ���߽���
 */

Inline void
hw_timer_terminate()
{
    UW addr = SYSTEM_TIMER_TSTR;

    /* ��������� */
    /*sil_wrb_mem((VP)SYSTEM_TIMER_TSTR,
                  sil_reb_mem((VP)SYSTEM_TIMER_TSTR) & ~SYSTEM_TIMER_STR);*/

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(SYSTEM_TIMER_STR_BIT));
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
	return((CLOCK)(sil_reh_mem((VP)SYSTEM_TIMER_CNT)));
}

/*
 *  �����޳�����׵�Υ����å�
 */

Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(sil_reb_mem((VP)SYSTEM_TIMER_IFR) & SYSTEM_TIMER_IF);
}

#endif	/* of #ifndef _MACRO_ONLY */

#endif /* _HW_TIMER_H_ */
