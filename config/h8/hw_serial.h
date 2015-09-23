/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: hw_serial.h,v 1.4 2002/04/14 11:36:50 hiro Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���H8�ѡ�
 *    ���ݡ��Ȥ� 1�ܤξ��� HWPORT1_ADDR�˻��ꤵ�줿�ݡ��Ȥ���Ѥ���
 *      2�ܤξ��ϡ�HWPORT1_ADDR��桼���ѡ�HWPORT2_ADDR�򥳥󥽡���
 *      ���ϤȤ��ƻ��Ѥ��롣
 *      HWPORTx_ADDR�� �������åȰ�¸�� sys_config.h��ǻ��ꤹ�롣
 *    ���������Υ⥸�塼��ˤ�äơ�XON/XOFF�ե����椬�Ԥ�
 *      ��Ƥ���Τǡ���������TxD��RxD��2�ܤǤ褤
 */

#include "sys_config.h"
#include "cpu_config.h"

#ifndef _MACRO_ONLY

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */

typedef struct hardware_serial_port_descripter {
	UW	base;	/* SCI �Υ١������ɥ쥹		*/
} HWPORT;

#endif	/* of #ifndef _MACRO_ONLY */

/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define PORT_ID1	1
#define PORT_ID2	2

#define HWPORT1	{ HWPORT1_ADDR	}
#define HWPORT2	{ HWPORT2_ADDR	}

#ifndef _MACRO_ONLY

/*
 *  ���ꥢ��ݡ��Ȥν����
 */

Inline void
SCI_initialize(UW base)
{
    int i;
					/* ���������		*/
    outb(base + H8SCR, inb(base + H8SCR) & ~(H8SCR_TE | H8SCR_RE));

    					/* �������ե����ޥå�	*/
         		/* Ĵ��Ʊ����				*/
         		/* ����饯����󥰥���8�ӥå�		*/
         		/* �ѥ�ƥ��ʤ�				*/
         		/* ���ȥåץӥåȥ�󥰥���1		*/
         		/* ����å����쥯�ȡ�ʬ�����		*/
    outb(base + H8SMR, 0);

    outb(base + H8BRR, H8BRR_RATE);	/*  �ܡ��졼������  	*/

    			/* ����߶ػߤȥ���å�������������	*/
    outb(base + H8SCR,
     inb(base + H8SCR) & ~(H8SCR_TIE  | H8SCR_RIE  |
                           H8SCR_MPIE | H8SCR_TEIE |
                           H8SCR_CKE1 | H8SCR_CKE0 ));

    /* �ܡ��졼�Ȥ�����塢1�ӥå�ʬ�Ԥ��ʤ���Фʤ�ʤ���*/

    for(i = SCI_SETUP_COUNT; i -- > 0; )
    	;

    				/* ���顼�ե饰�򥯥ꥢ		*/
    outb(base + H8SSR,
     inb(base + H8SSR) & ~(H8SSR_ORER | H8SSR_FER | H8SSR_PER));

    /* ���������ߵ���, ��������ߤε��Ĥ���������ؿ��ǹԤ�	*/
    /* ���������� */

    outb(base + H8SCR,
     inb(base + H8SCR) | (H8SCR_RIE | H8SCR_TE | H8SCR_RE));
}

/*
 * serial_open��serial_close [systask/serial.c] ����ƤФ��
 * �ؿ��Ǥϲ��⤷�ʤ���
 * sys_initialize [config/h8/akih8_3048f/sys_config.c] �ǹԤ���
 */

Inline BOOL
hw_port_initialize(HWPORT *p)
{
	return (FALSE);
}

Inline void
hw_port_terminate(HWPORT *p)
{
}

/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */

extern void	serial_handler_in(int portid);
extern void	serial_handler_out(int portid);

/*
 *  ���ꥢ��I/O�ݡ��Ȥγ���ߥϥ�ɥ�
 */

#if NUM_PORT == 1

Inline void
hw_serial_handler_in()
{
	unsigned char status;

	status = inb(SYSTEM_SCI + H8SSR);
	if (status & (H8SSR_ORER | H8SSR_FER | H8SSR_PER)) {

		/* ���顼����		*/

	    	/* ���顼�ե饰�򥯥ꥢ	*/
		outb(SYSTEM_SCI + H8SSR, status & ~(H8SSR_ORER | H8SSR_FER | H8SSR_PER));
		}

	if (status & H8SSR_RDRF)
		serial_handler_in(SYSTEM_PORTID);

}

Inline void
hw_serial_handler_out()
{
	serial_handler_out(SYSTEM_PORTID);
}

#elif NUM_PORT == 2	/* of #if NUM_PORT == 1 */

Inline void
hw_serial_handler_in()
{
	unsigned char status;

	/* USER_SCI �ν��� */

	status = inb(USER_SCI + H8SSR);
	if (status & (H8SSR_ORER | H8SSR_FER | H8SSR_PER)) {

		/* ���顼����		*/

	    	/* ���顼�ե饰�򥯥ꥢ	*/
		outb(USER_SCI + H8SSR, status & ~(H8SSR_ORER | H8SSR_FER | H8SSR_PER));
		}

	if (status & H8SSR_RDRF)
		serial_handler_in(USER_PORTID);

	/* SYSTEM_SCI �ν��� */

	status = inb(SYSTEM_SCI + H8SSR);
	if (status & (H8SSR_ORER | H8SSR_FER | H8SSR_PER)) {

		/* ���顼����		*/

	    	/* ���顼�ե饰�򥯥ꥢ	*/
		outb(SYSTEM_SCI + H8SSR, status & ~(H8SSR_ORER | H8SSR_FER | H8SSR_PER));
		}

	if (status & H8SSR_RDRF)
		serial_handler_in(SYSTEM_PORTID);

}

Inline void
hw_serial_handler_out()
{
	unsigned char status;

	/* USER SCI �ν��� */

	status = inb(USER_SCI + H8SSR);
	if (status & H8SSR_TDRE)
		serial_handler_out(USER_PORTID);

	/* SYSTEM SCI �ν��� */

	status = inb(SYSTEM_SCI + H8SSR);
	if (status & H8SSR_TDRE)
		serial_handler_out(SYSTEM_PORTID);
}

#else	/* of #if NUM_PORT == 1 */

#error NUM_PORT <= 2

#endif	/* of #if NUM_PORT == 1 */

/*
 *  ʸ���������������
 */

Inline BOOL
hw_port_getready(HWPORT *p)
{
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ����å�  */
	return(inb(p->base + H8SSR) & H8SSR_RDRF);
}

/*
 *  ʸ���������Ǥ��뤫��
 */

Inline BOOL
hw_port_putready(HWPORT *p)
{
	/*  �ȥ�󥹥ߥåȥǡ����쥸��������ץƥ����ե饰�Υ����å�*/

	return(inb(p->base + H8SSR) & H8SSR_TDRE);
}

/*
 *  ��������ʸ���μ��Ф�
 */

Inline UB
hw_port_getchar(HWPORT *p)
{
	UB data;
	UW addr = p->base + H8SSR;

	data = inb(p->base + H8RDR);

 	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ��ꥢ  */

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(H8SSR_RDRF_BIT));
#undef  BITCLR

	return data;
}

/*
 *  ��������ʸ���ν񤭹���
 */

Inline void
hw_port_putchar(HWPORT *p, UB c)
{
	UW addr = p->base + H8SSR;

	outb(p->base + H8TDR, c);

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(H8SSR_TDRE_BIT));
#undef  BITCLR
}

/*
 * ľ�ܽ��� (�Ԥ�����)
 */

Inline void
SCI_putchar (int base, int c)
{
	UW addr = base + H8SSR;

	/* TDRE �� 1 �ˤʤ�ޤ��Ԥ� */
	while ((inb(addr) & H8SSR_TDRE) == 0)
		;
	outb(base + H8TDR, c);

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(H8SSR_TDRE_BIT));
#undef  BITCLR

	}

/*
 *  ��������ؿ�
 */

Inline void
hw_port_sendstart(HWPORT *p)
{
	UW addr = p->base + H8SCR;

#define BITSET(bit)	Asm("bset #" bit ", @%0" : : "r"(addr))
	BITSET(_TO_STRING(H8SCR_TIE_BIT));
#undef  BITSET
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	UW addr = p->base + H8SCR;

#define BITCLR(bit)	Asm("bclr #" bit ", @%0" : : "r"(addr))
	BITCLR(_TO_STRING(H8SCR_TIE_BIT));
#undef  BITCLR
}

#endif	/* of #ifndef _MACRO_ONLY */

#endif /* _HW_SERIAL_H_ */
