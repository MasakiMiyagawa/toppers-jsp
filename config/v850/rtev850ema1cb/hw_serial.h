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
 *  @(#) $Id: hw_serial.h,v 1.2 2001/11/15 13:18:32 takayuki Exp $
 */

/*
 *	�������åȰ�¸���ꥢ��I/O�⥸�塼���V850E/MA1 ��¢��Ʊ�����ꥢ���ѡ�
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include "sys_config.h"

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */

#define FLG_RECEIVED 1

typedef struct hardware_serial_port_descripter {
} HWPORT;
#define HWPORT1 {}

static unsigned int _serial_flag = 0;

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN		(0x2e + (SERIAL_PORT * 4))
#define INHNO_SERIAL_OUT	(0x2f + (SERIAL_PORT * 4))

/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
Inline BOOL
hw_port_initialize(HWPORT *p)
{
	if( (*(volatile unsigned char *) ASIM(SERIAL_PORT) & 0x80) == 0 )
	{
	    	/* ��Ʊ�����ꥢ���̿�ϩ�ν���� */

			/* �ݡ��Ȥ򳫤��� */
		*(volatile unsigned char *) PFC4 = 0x1b;
		*(volatile unsigned char *) PMC4 = 7 << (3*SERIAL_PORT);

			/* �ܡ��졼��ȯ����ν���� */
		*(volatile unsigned char *) CKSR(SERIAL_PORT)  = SERIAL_CLKDIV;
		*(volatile unsigned char *) BRGC(SERIAL_PORT)  = SERIAL_COMPAREVALUE;
		*(volatile unsigned char *) ASIM(SERIAL_PORT) |= 0x80;	//enable ASIO

		__asm("nop; nop");

		*(volatile unsigned char *) ASIM(SERIAL_PORT) |= 0x04;	//8bit length

		__asm("nop; nop");

		*(volatile unsigned char *) ASIM(SERIAL_PORT) |= 0x60;	//Tx, Rx on

			/* ��������� */
		*(volatile unsigned char *)SRIC(SERIAL_PORT) = 0 | SERIAL_INT_PRIORITY;
		*(volatile unsigned char *)STIC(SERIAL_PORT) = 0 | SERIAL_INT_PRIORITY;
	}
	return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥν�λ
 */
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
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	return (_serial_flag & FLG_RECEIVED) != 0 ? TRUE : FALSE;
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
	return (*(volatile char *)ASIF(SERIAL_PORT) & 0x2) != 0 ? FALSE : TRUE;
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline unsigned char
hw_port_getchar(HWPORT *p)
{
	_serial_flag &= FLG_RECEIVED;
	*(volatile unsigned char *) SRIC(SERIAL_PORT) &= 0x7f;
	return *(volatile unsigned char *)RXB(SERIAL_PORT);
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, unsigned char c)
{
	*(volatile unsigned char *) TXB(SERIAL_PORT) = c;
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
}

Inline void
hw_port_sendstop(HWPORT *p)
{
}

Inline void
hw_serial_handler_in(void)
{
	_serial_flag |= FLG_RECEIVED;
    serial_handler_in(CONSOLE_PORTID);
}

Inline void
hw_serial_handler_out(void)
{
	serial_handler_out(CONSOLE_PORTID);
}

#endif /* _HW_SERIAL_H_ */
