/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: hw_timer.h,v 1.2 2002/04/13 13:14:45 imai Exp $
 */

#ifndef _HW_TIMER_H_
#define _HW_TIMER_H_

/*
 *  CPU��¸�����ޥ⥸�塼���H8S�ѡ�
 *  TPU0�����
 */

#include "sys_defs.h"
#include "sys_config.h"
#include "cpu_config.h"


#pragma inline(hw_timer_int_clear, hw_timer_initialize, hw_timer_terminate) 
#pragma inline(hw_timer_get_current, hw_timer_fetch_interrupt)


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
 *	TSR�쥸������IMFA�ӥåȤ�1���ɤ߽Ф�����ˣ���񤭹���
 */

Inline void
hw_timer_int_clear(void)
{
    /* GRA����ڥ��ޥå��γ������׵�ե饰�򥯥ꥢ */
    UW addr = SYSTEM_TPU + H8STSR;
    
    bitclr(addr, SYSTEM_TPU_IF_BIT);
}

/*
 *  �����ޤε�ư����
 *
 *  �����ޤ�������������Ū�ʥ����޳�����׵��ȯ�������롥
 */

Inline void
hw_timer_initialize(void)
{
    UW addr = H8STPU_TSTR;

    /*  �⥸�塼�륹�ȥåץ⡼�ɲ��  */
    MSTPCR &= ~MSTPCR_TPU;

    /* ��������� */
    bitclr(addr, SYSTEM_STR_BIT);
    
    /*  GRA����ڥ��ޥå��ǥ����󥿤򥯥ꥢ��ʬ�������� */
    outb(SYSTEM_TPU + H8STCR, H8STCR_CCLR | H8STCR_CKEG | H8STCR_TPSC);

    /*  GRA����ڥ��ޥå��ˤ�������׵����� */
    outb(SYSTEM_TPU + H8STIER, SYSTEM_TPU_IE);

    /*  GRA����ڥ��ޥå��ˤ��ü�ҽ��϶ػ� */
    outb(SYSTEM_TPU + H8STIORH, H8STIOR_IOB | H8STIOR_IOA);
    outb(SYSTEM_TPU + H8STIORL, H8STIOR_IOC | H8STIOR_IOD);
    /*  GRA�쥸��������ʥ�������ɸ�͡�  	*/
    outw(SYSTEM_TPU + SYSTEM_GR, CLOCK_PER_TICK);

    outw(SYSTEM_TPU + H8STCNT, 0);	/* �����󥿤򥯥ꥢ	*/

	/*
	 *  ����ߴ�Ϣ������
	 */
    					/* �����ߥ�٥����� 	*/
    outb(SYSTEM_TPU_IPR,(UB)((inb(SYSTEM_TPU_IPR)&~(0x7<<TPU_BIT_SHIFT)) | (TPU_INTLVL<<TPU_BIT_SHIFT)));
    hw_timer_int_clear();		/*  ������׵�򥯥ꥢ  */

    /* �����ޥ������� */
        bitset(addr, SYSTEM_STR_BIT);
}

/*
 *  �����ޤ���߽���
 */

Inline void
hw_timer_terminate(void)
{
    UW addr = H8STPU_TSTR;

    /* ��������� */
        bitclr(addr, SYSTEM_STR_BIT);

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
	return(CLOCK_PER_TICK - (CLOCK)(inw(SYSTEM_TPU + H8STCNT)));
}

/*
 *  �����޳�����׵�Υ����å�
 */

Inline BOOL
hw_timer_fetch_interrupt(void)
{
	return(inb(SYSTEM_TPU + H8STSR) & H8STSR_TGFA);
}

#endif /* _HW_TIMER_H_ */
