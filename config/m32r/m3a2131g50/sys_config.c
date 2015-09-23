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
 *  @(#) $Id: sys_config.c,v 1.2 2002/04/05 09:01:29 takayuki Exp $
 */

/*
 *	�������åȥ����ƥ��¸�⥸�塼���M3A-2131G50�ѡ�
 */

#include "jsp_kernel.h"
#include "hw_serial.h"


/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
	*(volatile unsigned short *)0xef106e = 0;		//�ݡ���7����Ѥ���
	*(volatile unsigned char  *)0xef1047 = 0xff;	//���ϥ⡼��
	*(volatile unsigned char *)LED = 0;
	hw_port_initialize(0);
}

/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit(void)
{
	dis_int();
	*(volatile unsigned char *)(ICUIMASK+1) = 0;
	while(1==1)
	{
		*(volatile unsigned char *)LED = (*(volatile unsigned char *)LED) +1;
			/* ��������ϥ⡼�ɤذܹ� */
		__asm(	"stb	%0, @%1	\n"
				"ldb	%0, @%1 \n"
			  	"nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop"
			: : "r"(1), "r"(CLKMOD+3) );
	}
}

/*
 *  �������åȥ����ƥ��ʸ������
 */
void
sys_putc(char c)
{
//	if(c == '\n')
//	{
//	    while( ( *(volatile char *)(SIOSTS(SERIAL_PORT)+3) & 0x1) == 0);
//	    *(volatile char *)(SIOTXB(SERIAL_PORT)+3) = '\r';
//	}
    while( ( *(volatile char *)(SIOSTS(SERIAL_PORT)+3) & 0x1) == 0);
    *(volatile char *)(SIOTXB(SERIAL_PORT)+3) = c;
}
