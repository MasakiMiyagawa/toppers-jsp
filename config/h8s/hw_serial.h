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
 *  @(#) $Id: hw_serial.h,v 1.2 2002/04/13 13:14:45 imai Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���H8S�ѡ�
 *  SCI0�����
 *  �����������Υ⥸�塼��ˤ�äơ�XON/XOFF�ե����椬�Ԥ�
 *  ������Ƥ���Τǡ���������TxD��RxD��2�ܤǤ褤
 */

#include "sys_config.h"
#include "cpu_config.h"

#ifndef _MACRO_ONLY


/*  ����饤��ؿ�Ÿ���λ���  */

#pragma inline(SCI_initialize, hw_port_initialize, hw_port_terminate)
#pragma inline(hw_serial_handler_in, hw_serial_handler_out, hw_port_getready)
#pragma inline(hw_port_putready, hw_port_getchar, hw_port_putchar, SCI_putchar)
#pragma inline(hw_port_sendstart, hw_port_sendstop)

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */

typedef struct hardware_serial_port_descripter {
	UW	base;	/* SCI �Υ١������ɥ쥹		*/
	UW	enaix;	/* SCI ����������߾��֤κ���	*/
} HWPORT;

#endif	/* of #ifndef _MACRO_ONLY */

/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */
#define PORT_ID1	1	/* �ץ�������PORT1�ϡ�SCI0��ؤ��Ƥ��� */

#define HWPORT1	{ SYSTEM_SCI, 0 }

#ifndef _MACRO_ONLY

/*
 *  ���ꥢ��ݡ��Ȥν����
 */

/*  
 *  SCI_initialize()�ǤΥ��ꥢ��ݡ��Ȥν�����ϡ�hw_port_initialize()�������
 *  ���٤��Ǥ���Ȼפ�����H8�Ȥ�������θ�������ʳ��Ǥϡ��ѹ����ʤ�
 */

Inline void
SCI_initialize(UW base)
{
    int i;
    
		   /*  �⥸�塼�륹�ȥåץ⡼�ɲ��  */
    MSTPCR &= ~MSTPCR_SCI0;
    
					/* ��������� */
    outb(base + H8SSCR, (UB)(inb(base + H8SSCR) & ~(H8SSCR_TE | H8SSCR_RE)));

    					/*   �������ե����ޥå�	*/
         		/*  Ĵ��Ʊ����				*/
         		/*  ����饯����󥰥���8�ӥå�		*/
         		/*  �ѥ�ƥ��ʤ�			*/
         		/*  ���ȥåץӥåȥ�󥰥���1		*/
         		/*  ����å����쥯�ȡ�ʬ�����:ʬ���ʤ�	*/
    outb(base + H8SSMR, 0);

    outb(base + H8SBRR, H8SBRR_RATE);	/*  �ܡ��졼������  	*/

    			/* ����߶ػߤȥ���å�������������	*/
    outb(base + H8SSCR,
     (UB)(inb(base + H8SSCR) & ~(H8SSCR_TIE  | H8SSCR_RIE  |
                           H8SSCR_MPIE | H8SSCR_TEIE |
                           H8SSCR_CKE1 | H8SSCR_CKE0 )));

    /* �ܡ��졼�Ȥ�����塢1�ӥå�ʬ�Ԥ��ʤ���Фʤ�ʤ���*/

    for(i = SCI_SETUP_COUNT; i -- > 0; )
    	;

    				/* ���顼�ե饰�򥯥ꥢ		*/
    outb(base + H8SSSR,
     (UB)(inb(base + H8SSSR) & ~(H8SSSR_ORER | H8SSSR_FER | H8SSSR_PER)));

    /* ���������ߵ���, ��������ߤε��Ĥ���������ؿ��ǹԤ�	*/
    /* ���������� */

    outb(base + H8SSCR,
     (UB)(inb(base + H8SSCR) | (H8SSCR_RIE | H8SSCR_TE | H8SSCR_RE)));

    /*
     * �����ߴ�Ϣ������
     * ���顼�ϥ�ɥ����Ͽ���٤�
     */
        			/* �����ߥ�٥����� */
        outb(SYSTEM_SCI_IPR,(UB)((inb(SYSTEM_SCI_IPR)&~(0x7<<SCI_BIT_SHIFT)) | (SCI_INTLVL<<SCI_BIT_SHIFT)));
}

/*
 * serial_open��serial_close [systask/serial.c] ����ƤФ��
 * �ؿ��Ǥϲ��⤷�ʤ���
 * sys_initialize [config/h8/akih8_3048f/sys_config.c] �ǹԤ���
 *    	->���ѹ�
 */

Inline BOOL
hw_port_initialize(HWPORT *p)
{
	return (FALSE);
}

/*
 *  H8�ǤǤϡ�hw_port_terminate()��ϡ��������ꤷ�Ƥ��ʤ���H8�Ǥ�H8S�Ǥ�����
 *  �κݤϡ���դ�ɬ�פǤ���
 */
Inline void
hw_port_terminate(HWPORT *p)
{
              						/*  ���������  */
	outb(p->base + H8SSCR, (UB)(inb(p->base + H8SSCR) & ~(H8SSCR_TE | H8SSCR_RE)));
							/*  ����ߥ�٥륯�ꥢ  */

 	outb(SYSTEM_SCI_IPR,(UB)((inb(SYSTEM_SCI_IPR)&~(0x7<<SCI_BIT_SHIFT)) | (LEVEL0<<SCI_BIT_SHIFT)));
}

/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */

extern void	serial_handler_in(int portid);
extern void	serial_handler_out(int portid);

/*
 *  ���ꥢ��I/O�ݡ��Ȥγ���ߥϥ�ɥ�
 */

Inline void
hw_serial_handler_in(void)
{
	serial_handler_in(PORT_ID1);

    	/* ���顼�ե饰�򥯥ꥢ		*/
	outb(H8SSCI0 + H8SSSR,(UB)(inb(H8SSCI0 + H8SSSR) & ~(H8SSSR_ORER | H8SSSR_FER | H8SSSR_PER)));

}

Inline void
hw_serial_handler_out(void)
{
	serial_handler_out(PORT_ID1);
}

/*
 *  ʸ���������������
 */

Inline BOOL
hw_port_getready(HWPORT *p)
{
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ����å�  */
	return(inb(p->base + H8SSSR) & H8SSSR_RDRF);
}

/*
 *  ʸ���������Ǥ��뤫��
 */

Inline BOOL
hw_port_putready(HWPORT *p)
{
	/*  �ȥ�󥹥ߥåȥǡ����쥸��������ץƥ����ե饰�Υ����å�*/

	return(inb(p->base + H8SSSR) & H8SSSR_TDRE);
}

/*
 *  ��������ʸ���μ��Ф�
 */

Inline UB
hw_port_getchar(HWPORT *p)
{
	UB data;
	UW addr = p->base + H8SSSR;

	data = inb(p->base + H8SRDR);

 	/*  ���ꥢ�륹�ơ������쥸����(SSR�ˤΥ쥷���֥ǡ����쥸�����ե�(RDRF)�Υ��ꥢ  */
        bitclr(addr, H8SSSR_RDRF_BIT);

	return data;
}

/*
 *  ��������ʸ���ν񤭹���
 */

Inline void
hw_port_putchar(HWPORT *p, char c)
{
	UW addr = p->base + H8SSSR;

	outb(p->base + H8STDR, c);
  		/*  ���ꥢ�륹�ơ������쥸����(SSR�ˤΥȥ�󥹥ߥåȥǡ����쥸��������ץƥ�(TDRE)�Υ��ꥢ  */
	bitclr(addr, H8SSSR_TDRE_BIT);
}

/*
 * ľ�ܽ��� (�Ԥ�����)
 */

Inline void
SCI_putchar (int base, char c)		/*  int(16bits) -> UW(32bits)  */
{
	UW addr = base + H8SSSR;

	/* TDRE �� 1 �ˤʤ�ޤ��Ԥ� */
	while ((inb(addr) & H8SSSR_TDRE) == 0)
		;
	outb(base + H8STDR, c);
		/*  ���ꥢ�륹�ơ������쥸����(SSR�ˤΥȥ�󥹥ߥåȥǡ����쥸��������ץƥ�(TDRE)�Υ��ꥢ  */
	bitclr(addr, H8SSSR_TDRE_BIT);
}

/*
 *  ��������ؿ�
 */

Inline void
hw_port_sendstart(HWPORT *p)
{
	UW addr = p->base + H8SSCR;
		/*  ����������׵�����  */
	bitset(addr, H8SSCR_TIE_BIT);
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	UW addr = p->base + H8SSCR;
		/*  ����������׵��ػ�  */
	bitclr(addr, H8SSCR_TIE_BIT);
}


#endif	/* of #ifndef _MACRO_ONLY */

#endif /* _HW_SERIAL_H_ */
