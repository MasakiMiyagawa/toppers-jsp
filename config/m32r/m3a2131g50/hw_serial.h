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
 *  @(#) $Id: hw_serial.h,v 1.2 2002/04/05 09:01:29 takayuki Exp $
 */

/*
 *	�������åȰ�¸���ꥢ��I/O�⥸�塼���M32102��¢��Ʊ�����ꥢ���ѡ�
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include "sys_config.h"

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */

typedef struct hardware_serial_port_descripter {
} HWPORT;
#define HWPORT1 {}

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN		(48 + SERIAL_PORT)
#define INHNO_SERIAL_OUT	(49 + SERIAL_PORT)

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
  			/* ��Ʊ�����ꥢ���̿�ϩ�ν���� */
	*(volatile unsigned char *)(SIOCR(SERIAL_PORT)+3) = 0;

			/* �ݡ��Ȥ򳫤��� */
	*(volatile unsigned char  *) PDATA(5) = 0;
	*(volatile unsigned char  *) PDIR(5)  = 0x80;	//TxD����Ϥ�

			//UART, Non-parity, 1 stop-bit
	*(volatile unsigned char  *)(SIOMOD0(SERIAL_PORT)+3) = 0;	

			//8bit, internal clock
	*(volatile unsigned short *)(SIOMOD1(SERIAL_PORT)+2) = 0x0800;

			//M32R(32102) - f(BLK)=16MHz��115200bps
	*(volatile unsigned short *)(SIOBAUR(SERIAL_PORT)+2)  = SERIAL_CLKDIV;
	*(volatile unsigned char  *)(SIORBAUR(SERIAL_PORT)+3) = SERIAL_CLKCMP;

			//�����������ȯ������
	*(volatile unsigned short *)(SIOTRCR(SERIAL_PORT)+2) = 0x6;

			//���ơ��������ꥢ, ������ư���
	*(volatile unsigned char  *)(SIOCR(SERIAL_PORT)+2) = 0x3;
	*(volatile unsigned char  *)(SIOCR(SERIAL_PORT)+3) = 0x3;

			//��������߼��յ���
	*(volatile unsigned short *)(ICUCR(SIO,SERIAL_PORT)+2) = 0x1000;
	*(volatile unsigned short *)(ICUCR(SIO,SERIAL_PORT)+6) = 0x1000;

		//TxD,RxD�ԥ�ͭ��
	*(volatile unsigned short *) PMOD(5) = 0x5500;

	return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥν�λ
 */
Inline void
hw_port_terminate(HWPORT *p)
{
		//������ư�����
	*(volatile unsigned char *)(SIOCR(SERIAL_PORT)+3) = 0;
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
	return ((*(volatile char *)(SIOSTS(SERIAL_PORT)+3)) & 0x4) != 0 ? TRUE : FALSE;
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
	return ((*(volatile char *)(SIOSTS(SERIAL_PORT)+3)) & 0x1) != 0 ? TRUE : FALSE;
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline unsigned char
hw_port_getchar(HWPORT *p)
{	return *(volatile unsigned char *)(SIORXB(SERIAL_PORT)+3);	}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, unsigned char c)
{
	*(volatile unsigned char *)(SIOTXB(SERIAL_PORT)+3) = c;
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{}

Inline void
hw_port_sendstop(HWPORT *p)
{}

Inline void
hw_serial_handler_in(void)
{
    serial_handler_in(CONSOLE_PORTID);
}

Inline void
hw_serial_handler_out(void)
{
	*(volatile unsigned char  *)(SIOCR(SERIAL_PORT)+2) = 0x1;
	serial_handler_out(CONSOLE_PORTID);
}

#endif /* _HW_SERIAL_H_ */
