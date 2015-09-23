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
 *  @(#) $Id: ms7709ase01.h,v 1.5 2001/10/20 15:47:34 honda Exp $
 */

#ifndef _MS7709ASE01_ 
#define _MS7709ASE01_ 


#include "sh3.h"

/*
 *  MS7709ASE01�Υϡ��ɥ������񸻤����
 */

/*
 *  FPGA1(U17)�ˤ��������������ߤ�INTEVT������
 */
 
#define SLOT_IRQ8  0x200
#define KBC0_IRQ0  0x220
#define PCIC_IRQ2  0x240
#define UART_IRQ1  0x260
#define SLOT_IRQ6  0x280
#define KBC_IRQ1   0x2A0
#define PCIC_IRQ1  0x2C0
#define UART_IRQ0  0x2E0
#define SLOT_IRQ4  0x300
#define SLOT_IRQ3  0x320
#define PRN_IRQ    0x340
#define SLOT_IRQ2  0x360
#define LAN_IRQ    0x380
#define FDC_IRQ    0x3A0
#define PCIC_IRQ0  0x3C0


/* SMSC Super I/O ������ */ 

#define BASE_ADDR 0xB0400000

#define SMSC_CONFIG_PORT ((HIOREG *)(BASE_ADDR + 0x7E0))
#define SMSC_INDEX_PORT  ((HIOREG *)(BASE_ADDR + 0x7E0))
#define SMSC_DATA_PORT   ((HIOREG *)(BASE_ADDR + 0x7E2))

/* Super I/O ���SCI0 */
#define SMSC_SCI0_BASE_ADDR  0x03f8

#define SMSC_SCI0_RBR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x0))
#define SMSC_SCI0_THR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x0))
#define SMSC_SCI0_DLL ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x0))
#define SMSC_SCI0_IER ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x2))
#define SMSC_SCI0_DLM ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x2))
#define SMSC_SCI0_IIR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x4))
#define SMSC_SCI0_FCR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x4))  
#define SMSC_SCI0_LCR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x6))
#define SMSC_SCI0_MCR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0x8))
#define SMSC_SCI0_LSR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0xA))
#define SMSC_SCI0_MSR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0xC))
#define SMSC_SCI0_SCR ((HIOREG *)(BASE_ADDR + SMSC_SCI0_BASE_ADDR * 2 + 0xE))

Inline void
smsc_config_write(word index, word data)
{
    *SMSC_INDEX_PORT = (index << 8);
    *SMSC_DATA_PORT  = (data << 8);
}

Inline word
smsc_config_read(word index)
{
    *SMSC_INDEX_PORT = (index << 8);
    return(*SMSC_DATA_PORT >> 8);
}



#ifdef PARTNER_J

#define PARTNER_OUT   0xfffffe00
#define PARTNER_IN    0xfffffe01

/*
 *  PARTNER�ؤ�ʸ���ν���
 */
void partner_putc(char c);

#endif /* PARTNER_J */


#endif /*  _MS7709ASE01_ */



