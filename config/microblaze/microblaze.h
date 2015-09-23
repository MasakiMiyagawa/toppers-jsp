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
 *  @(#) $Id: microblaze.h,v 1.1 2002/04/05 08:47:14 honda Exp $
 */

#ifndef _MICROBLAZE_H_
#define _MICROBLAZE_H_

#include "sys_config.h"

#ifndef _MACRO_ONLY
typedef unsigned char   byte;
typedef volatile byte   IOREG;          
typedef unsigned short  word;
typedef volatile word   HIOREG;
typedef volatile int    LIOREG;
#endif /* _MACRO_ONLY */

/*
 *  MSR�Υӥå�
 */
#define MSR_IE 0x02
#define MSR_BE 0x01


/*
 * INTC Registers
 */
#define INTC_INT_STATUS_REG    0x00
#define INTC_INT_PENDING_REG   0x04
#define INTC_INT_ENABLE_REG    0x08
#define INTC_INT_ACK_REG       0x0c
#define INTC_SET_INT_ENABLE    0x10
#define INTC_CLEAR_INT_ENABLE  0x14
#define INTC_INT_VECTOR_REG    0x18
#define INTC_MASTER_ENABLE_REG 0x1c

/* 
 * Masks for the INTC Registers
 */
#define INTC_HIE_MASK 0x2
#define INTC_ME_MASK  0x1


#ifndef _MACRO_ONLY
#define INTC_ISR ((LIOREG *)(INTC_BASE + INTC_INT_STATUS_REG))
#define INTC_IPR ((LIOREG *)(INTC_BASE + INTC_INT_PENDING_REG))
#define INTC_IER ((LIOREG *)(INTC_BASE + INTC_INT_ENABLE_REG))
#define INTC_IAR ((LIOREG *)(INTC_BASE + INTC_INT_ACK_REG))
#define INTC_SIE ((LIOREG *)(INTC_BASE + INTC_SET_INT_ENABLE))
#define INTC_CIE ((LIOREG *)(INTC_BASE + INTC_CLEAR_INT_ENABLE))
#define INTC_IVR ((LIOREG *)(INTC_BASE + INTC_INT_VECTOR_REG))
#define INTC_MER ((LIOREG *)(INTC_BASE + INTC_MASTER_ENABLE_REG))

/*
 *  INTC���ؿ�
 */
Inline void
intc_start(void){
  *INTC_MER = INTC_HIE_MASK | INTC_ME_MASK;
}

Inline void
intc_disable_allinterrupt(){
  *INTC_MER = 0;
}

Inline void
intc_enable_interrupt(UW mask)
{
  *INTC_SIE = mask;
}

Inline void
intc_disable_interrupt(UW mask)
{
  *INTC_CIE = mask;
}

Inline void
intc_ack_interrupt(UW mask)
{
  *INTC_IAR = mask;
}

#endif /* _MACRO_ONLY */



/*
 * �����ޥɥ饤���ѤΥޥ������
 */


/*
 * Masks for the control/status register
 */
#define TIMER_ENABLE_ALL    0x400
#define TIMER_PWM           0x200
#define TIMER_INTERRUPT     0x100
#define TIMER_ENABLE        0x080
#define TIMER_ENABLE_INTR   0x040
#define TIMER_RESET         0x020
#define TIMER_RELOAD        0x010
#define TIMER_EXT_CAPTURE   0x008
#define TIMER_EXT_COMPARE   0x004
#define TIMER_DOWN_COUNT    0x002
#define TIMER_CAPTURE_MODE  0x001

#define TIMER_CONTROL_STATUS_0  0x0
#define TIMER_COMPARE_CAPTURE_0 0x4
#define TIMER_COUNTER_0         0x8
#define TIMER_CONTROL_STATUS_1  0x10
#define TIMER_COMPARE_CAPTURE_1 0x14
#define TIMER_COUNTER_1         0x18


#ifndef _MACRO_ONLY
#define TIMER_TCSR0 ((LIOREG *)(TIMER_BASE + TIMER_CONTROL_STATUS_0))
#define TIMER_TCCR0 ((LIOREG *)(TIMER_BASE + TIMER_COMPARE_CAPTURE_0))
#define TIMER_TCR0  ((LIOREG *)(TIMER_BASE + TIMER_COUNTER_0))
#define TIMER_TCSR1 ((LIOREG *)(TIMER_BASE + TIMER_CONTROL_STATUS_1))
#define TIMER_TCCR1 ((LIOREG *)(TIMER_BASE + TIMER_COMPARE_CAPTURE_1))
#define TIMER_TCR1  ((LIOREG *)(TIMER_BASE + TIMER_COUNTER_1))
#endif  /* _MACRO_ONLY */



/*
 *  UART�ɥ饤���ѤΥޥ������
 */


/*
 * Error condition masks 
 */
#define UARTLITE_PAR_ERROR     0x80
#define UARTLITE_FRAME_ERROR   0x40
#define UARTLITE_OVERRUN_ERROR 0x20


/*
 * Other status bit masks
 */
#define UARTLITE_INTR_ENABLED       0x10
#define UARTLITE_TX_FIFO_FULL       0x08
#define UARTLITE_TX_FIFO_EMPTY      0x04
#define UARTLITE_RX_FIFO_FULL       0x02
#define UARTLITE_RX_FIFO_VALID_DATA 0x01

/*
 * Control bit masks 
 */
#define UARTLITE_ENABLE_INTR  0x10
#define UARTLITE_RST_RX_FIFO  0x02
#define UARTLITE_RST_TX_FIFO  0x01

/*
 * UARTLITE Registers
 */
#define UARTLITE_RECEIVE_REG  0x0
#define UARTLITE_TRANSMIT_REG 0x4
#define UARTLITE_STATUS_REG   0x8
#define UARTLITE_CONTROL_REG  0xc



#ifndef _MACRO_ONLY
#define UARTLITE_RXREG ((LIOREG *)(UART_BASE + UARTLITE_RECEIVE_REG))
#define UARTLITE_TXREG ((LIOREG *)(UART_BASE + UARTLITE_TRANSMIT_REG))
#define UARTLITE_SRREG ((LIOREG *)(UART_BASE + UARTLITE_STATUS_REG))
#define UARTLITE_CTREG ((LIOREG *)(UART_BASE + UARTLITE_CONTROL_REG))


Inline void
uart_putc(unsigned char c){
  while(*UARTLITE_SRREG & UARTLITE_TX_FIFO_FULL);
  *UARTLITE_TXREG = c;
}

Inline unsigned char
uart_getc(void){
  while(!(*UARTLITE_SRREG & UARTLITE_RX_FIFO_VALID_DATA));
  return (char)(*UARTLITE_RXREG);
}

Inline void
uart_ena_int(void){
  *UARTLITE_CTREG |= UARTLITE_ENABLE_INTR;
}

Inline void
uart_dis_int(void){
  *UARTLITE_CTREG &= ~(UARTLITE_ENABLE_INTR);
}
#endif  /* _MACRO_ONLY */

#endif /* _MICROBLAZE_H_*/

