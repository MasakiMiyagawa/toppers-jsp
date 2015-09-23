/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2003-2004 by CHUO ELECTRIC WORKS Co.,LTD.
 *   51 Tateminami, Watari-cyo, Watari-gun, Miyagi-ken 989-2361, JAPAN
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
 */
#ifndef _SYS_SUPPORT_H_
#define _SYS_SUPPORT_H_

/*
 *  �У����У½��ϥХåե������
 *  ���Υԥ�ե��󥯥��������򻲾Ȥ��Ƥ�������
 */
#define	VAL_PA_DR 	(1<<10 | 1<<9 | 1<<8)	/* RTC-4553-CS=1,RTC-4553-WR=1,LED1=1(off) */
#define	VAL_PB_DR 	(1<<11 | 1<<9 | 1<<6)	/* TXD1=1,TXD0=1,LED2=1(off) */

/*
 *  �ԥ�ե��󥯥����������
 *  ���Υԥ�ե��󥯥��������򻲾Ȥ��Ƥ�������
 */
#define VAL_PFC_PAIOR   0xf7aa
#define VAL_PFC_PACR1   0x0002
#define VAL_PFC_PACR2   0x3b11

#define VAL_PFC_PBIOR   0x1a7b
#define VAL_PFC_PBCR1   0x14aa
#define VAL_PFC_PBCR2   0x0000

#define VAL_PFC_CASCR   0x5fff

/*
 *  �ԥ�ե��󥯥�������
 *
 *  PORTA
 *
 *  PNO  I/O(1/0) PACR1/2[xx]
 *  PA15 OUT (1)  [00] �� ��ĥ�ɡ��Ϥ˳�����IRQ3��DREQ1��
 *  PA14 OUT (1)  [00] �� ��ĥ�ɡ��Ϥ˳�����IRQ2��DACK1��
 *  PA13 OUT (1)  [00] �� ��ĥ�ɡ��Ϥ˳�����IRQ1��DREQ0��TCLKB��
 *  PA12 OUT (1)  [00] �� ��ĥ�ɡ��Ϥ˳�����IRQ0��DACK0��TCLKA��
 *  PA11 IN  (0)  [00] �� RTC-4553-SOUT
 *  PA10 OUT (1)  [00] �� RTC-4553-CS(active-low)
 *  PA09 OUT (1)  [00] �� RTC-4553-WR(active-low)
 *  PA08 OUT (1)  [00] �� LEDCTL1 LED1����(active-low)
 *  PA07 OUT (1)  [00] �� ̤����
 *  PA06 ��  (0)  [11] �� RD �˳�����ơ�
 *  PA05 OUT (1)  [10] �� WD-PULSE �����å��ɥå��ꥻ�åȥѥ륹�������ˤ�
 *  PA04 ��  (0)  [11] �� WR �˳������
 *  PA03 OUT (1)  [00] �� ��ĥ�ɡ��Ϥ˳�����CS7��WAIT��
 *  PA02 ��  (0)  [01] �� CS6 �˳�����ơʣ̣��Υ���ȥ����ѡ�
 *  PA01 OUT (1)  [00] �� ��ĥ�ɡ��Ϥ˳�����CS5��TIOCA0��
 *  PA00 ��  (0)  [01] �� CS4 �˳�����ơ�ROMICE �ѡ�
 *  PAIOR=0xf7aa
 *  PACR1=0x0000
 *  PACR2=0x3b11
 *
 *
 *  PORTB
 *
 *  PB15 ��  (0)  [00] �� ̤���� IRQ7 �˳�����ơʣңԣ��ѡ�
 *  PB14 ��  (0)  [01] �� IRQ6 �˳�����ơʣգӣ¥���ȥ����ѡ�
 *  PB13 ��  (0)  [01] �� IRQ5 �˳�����ơʣ̣��Υ���ȥ����ѡ�
 *  PB12 OUT (1)  [00] �� LEDCTL3 LED3 ����(active-low)
 *  PB11 ��  (1)  [10] �� TDX1 �˳�����ơ�RS485 �ǡ������ϡ�
 *  PB10 ��  (0)  [10] �� RDX1 �˳�����ơ�RS485 �ǡ������ϡ�
 *  PB09 ��  (1)  [10] �� TDX0 �˳�����ơ�RS-232C �ǡ������ϡ�
 *  PB08 ��  (0)  [10] �� RDX0 �˳�����ơ�RS-232C �ǡ������ϡ�
 *  PB07 IN  (0)  [00] �� ���ꥢ��EEPROM-DO
 *  PB06 OUT (1)  [00] �� LEDCTL2 LED2 ����(active-low)
 *  PB05 OUT (1)  [00] �� TXE0 RS485 �������͡��֥�����������
 *  PB04 OUT (1)  [00] �� ���ꥢ��EEPROM-CS(active-high)
 *  PB03 OUT (1)  [00] �� CTS0 RS232C ��CTS �����̤������
 *  PB02 IN  (0)  [00] �� RTS0 RS232C ��RTS �����̤������
 *  PB01 OUT (1)  [00] �� ���ꥢ��EEPROM-SK��RTC-4553-SCK
 *  PB00 OUT (1)  [00] �� ���ꥢ��EEPROM-DI��RTC-4553-SIN
 *  PBIOR=0x1a7b
 *  PBCR1=0x14aa
 *  PBCR2=0x0000
 *
 */

#ifndef _MACRO_ONLY
/*
 * �ؿ����
 */
void	software_init_hook(void);
void	hardware_init_hook(void);

#endif /* _MACRO_ONLY */
#endif	/* _SYS_SUPPORT_H_ */
