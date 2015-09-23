/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: excalibur.h,v 1.7 2003/12/11 00:44:27 honda Exp $
 */

#ifndef _EXCALIBUR_H_
#define _EXCALIBUR_H_

#ifndef _MACRO_ONLY
#include <itron.h>
#include <sil.h>
#endif /* _MACRO_ONLY */

#include <armv4.h>

/*
 *  Device Registers
 */
/*
 * Interrupt controller
 */
#define INT_MASK_SET        (EXCALIBUR_DEV_BASE + 0xC00)
#define INT_MASK            (EXCALIBUR_DEV_BASE + 0xC00)
#define INT_MASK_CLEAR      (EXCALIBUR_DEV_BASE + 0xC04)
#define INT_SOURCE_STATUS   (EXCALIBUR_DEV_BASE + 0xC08)
#define INT_REQUEST_STATUS  (EXCALIBUR_DEV_BASE + 0xC0C)

#define INT_ID              (EXCALIBUR_DEV_BASE + 0xC10)
#define INT_PLD_PRIORITY    (EXCALIBUR_DEV_BASE + 0xC14)
#define INT_MODE            (EXCALIBUR_DEV_BASE + 0xC18)

#define INT_PRIORITY_PLD0       (EXCALIBUR_DEV_BASE + 0xC80)
#define INT_PRIORITY_PLD1       (EXCALIBUR_DEV_BASE + 0xC84)
#define INT_PRIORITY_PLD2       (EXCALIBUR_DEV_BASE + 0xC88)
#define INT_PRIORITY_PLD3       (EXCALIBUR_DEV_BASE + 0xC8C)
#define INT_PRIORITY_PLD4       (EXCALIBUR_DEV_BASE + 0xC90)
#define INT_PRIORITY_PLD5       (EXCALIBUR_DEV_BASE + 0xC94)
#define INT_PRIORITY_EXTPIN     (EXCALIBUR_DEV_BASE + 0xC98)
#define INT_PRIORITY_UART       (EXCALIBUR_DEV_BASE + 0xC9C)
#define INT_PRIORITY_TIMER0     (EXCALIBUR_DEV_BASE + 0xCA0)
#define INT_PRIORITY_TIMER1     (EXCALIBUR_DEV_BASE + 0xCA4)
#define INT_PRIORITY_PLL        (EXCALIBUR_DEV_BASE + 0xCA8)
#define INT_PRIORITY_EBI        (EXCALIBUR_DEV_BASE + 0xCAC)
#define INT_PRIORITY_STRIPE_PLD (EXCALIBUR_DEV_BASE + 0xCB0)
#define INT_PRIORITY_AHB1_2     (EXCALIBUR_DEV_BASE + 0xCB4)
#define INT_PRIORITY_TX         (EXCALIBUR_DEV_BASE + 0xCB8)
#define INT_PRIORITY_RX         (EXCALIBUR_DEV_BASE + 0xCBC)
#define INT_PRIORITY_FASTCOMMS  (EXCALIBUR_DEV_BASE + 0xCC0)

#define INT_MASK_PLD0      0x00001
#define INT_MASK_PLD1      0x00002
#define INT_MASK_PLD2      0x00004
#define INT_MASK_PLD3      0x00008
#define INT_MASK_PLD4      0x00010
#define INT_MASK_PLD5      0x00020
#define INT_MASK_IP        0x00040
#define INT_MASK_UA        0x00080
#define INT_MASK_T0        0x00100
#define INT_MASK_T1        0x00200
#define INT_MASK_PS        0x00400
#define INT_MASK_EE        0x00800
#define INT_MASK_PE        0x01000
#define INT_MASK_AE        0x02000
#define INT_MASK_CT        0x04000
#define INT_MASK_CR        0x08000
#define INT_MASK_FC        0x10000

#define INT_MODE_SII       0x03   /* Six individual interrupts */
#define INT_MODE_SPV       0x00   /* Six-bit priority value    */
#define INT_MODE_FP1I      0x01   /* Five-bit priority value plus individual interrupt */

#define INT_PRIORITY_FIQ   0x40   /* Generate FIQ interrupt */

/*
 * PLL��Ϣ�Υ쥸����
 */
#define CLK_PLL1_NCNT       (EXCALIBUR_DEV_BASE + 0x300)
#define CLK_PLL1_MCNT       (EXCALIBUR_DEV_BASE + 0x304)
#define CLK_PLL1_KCNT       (EXCALIBUR_DEV_BASE + 0x308)
#define CLK_PLL1_CTRL       (EXCALIBUR_DEV_BASE + 0x30C)
#define CLK_PLL1_CTRL_VAL   0x01035
#define CLK_PLL2_NCNT       (EXCALIBUR_DEV_BASE + 0x310)
#define CLK_PLL2_MCNT       (EXCALIBUR_DEV_BASE + 0x314)
#define CLK_PLL2_KCNT       (EXCALIBUR_DEV_BASE + 0x318)
#define CLK_PLL2_CTRL       (EXCALIBUR_DEV_BASE + 0x31C)
#define CLK_PLL2_CTRL_VAL   0x01035

#define CLK_DERIVE          (EXCALIBUR_DEV_BASE + 0x320)
#define CLK_STATUS          (EXCALIBUR_DEV_BASE + 0x324)

/*
 * Stripe I/O
 */
#define IOCR_UART           (EXCALIBUR_DEV_BASE + 0x048)
#define IOCR_UART_VAL       (EXCALIBUR_DEV_BASE + 0x07)

/*
 *   �Х���Ϣ�Υ쥸����
 */
#define AHB12B_CR           (EXCALIBUR_DEV_BASE + 0x100)
#define AHB12B_CR_VAL       (EXCALIBUR_DEV_BASE + 0x03)


/*
 * PLD����ե�����졼�����쥸������Ϣ
 */
#define IDCODE              (EXCALIBUR_DEV_BASE + 0x8)
#define CONFIG_CONTROL      (EXCALIBUR_DEV_BASE + 0x140)
#define CONFIG_CONTROL_CO   0x02
#define CONFIG_CONTROL_BB   0x04
#define CONFIG_CONTROL_E    0x10

#define CONFIG_CLOCK        (EXCALIBUR_DEV_BASE + 0x144)
#define CONFIG_DATA         (EXCALIBUR_DEV_BASE + 0x148)
#define CONFIG_UNLOCK       (EXCALIBUR_DEV_BASE + 0x14C)
#define CONFIG_UNLOCK_MAGIC 0x554e4c4b

/*
 * �ӥ����롼�ײ��
 */
#define PLD_LOOP 1000


/*
 *  TIMER0 Registers
 */
#define TIMER0_CR        (EXCALIBUR_DEV_BASE + 0x200)
#define TIMER0_SR        (EXCALIBUR_DEV_BASE + 0x200)
#define TIMER0_PRE       (EXCALIBUR_DEV_BASE + 0x210)
#define TIMER0_LIMIT     (EXCALIBUR_DEV_BASE + 0x220)
#define TIMER0_READ      (EXCALIBUR_DEV_BASE + 0x230)

#define TIMER0_CR_IE     0x04
#define TIMER0_CR_CI     0x08
#define TIMER0_CR_S      0x10

#define TIMER0_SR_IE     0x40
#define TIMER0_SR_IS     0x80
#define TIMER0_SR_R      0x10



/*
 *  SCI Registers
 */
#define CAL_BPS(bps,clk) ((clk)/(16*(bps)))

#define UART_RSR        (EXCALIBUR_DEV_BASE + 0x280)
#define UART_RDS        (EXCALIBUR_DEV_BASE + 0x284)
#define UART_RD         (EXCALIBUR_DEV_BASE + 0x288)

#define UART_TSR        (EXCALIBUR_DEV_BASE + 0x28C)
#define UART_TD         (EXCALIBUR_DEV_BASE + 0x290)

#define UART_FCR        (EXCALIBUR_DEV_BASE + 0x294)

#define UART_IES        (EXCALIBUR_DEV_BASE + 0x298)
#define UART_IEC        (EXCALIBUR_DEV_BASE + 0x29C)
#define UART_ISR        (EXCALIBUR_DEV_BASE + 0x2A0)
#define UART_ID         (EXCALIBUR_DEV_BASE + 0x2A4)
#define UART_MC         (EXCALIBUR_DEV_BASE + 0x2A8)
#define UART_MCR        (EXCALIBUR_DEV_BASE + 0x2AC)
#define UART_MSR        (EXCALIBUR_DEV_BASE + 0x2B0)
#define UART_DIV_LO     (EXCALIBUR_DEV_BASE + 0x2B4)
#define UART_DIV_HI     (EXCALIBUR_DEV_BASE + 0x2B8)


#define UART_RSR_RX_LEVEL  0x1F
#define UART_RSR_RE        0x80

#define UART_RDS_OE        0x01
#define UART_RDS_PE        0x02
#define UART_RDS_FE        0x04
#define UART_RDS_BI        0x08

#define UART_TSR_TX_LEVEL  0x1F
#define UART_TSR_TXI       0x80

#define UART_FCR_TC        0x01
#define UART_FCR_RC        0x02
#define UART_FCR_TX_THR    0x1C
#define UART_FCR_RX_THR    0xE0

#define UART_INT_R        0x01
#define UART_INT_T        0x02 
#define UART_INT_TI       0x04
#define UART_INT_M        0x08

#define UART_ID_RI        0x01
#define UART_ID_TI        0x02
#define UART_ID_TII       0x03
#define UART_ID_MI        0x04

#define UART_MC_CLS       0x03
#define UART_MC_ST        0x04
#define UART_MC_PE        0x08
#define UART_MC_EP        0x10
#define UART_MC_SP        0x20
#define UART_MC_OE        0x40

#define UART_MCR_RTS      0x01
#define UART_MCR_DTR      0x02
#define UART_MCR_RI       0x04
#define UART_MCR_DCD      0x08
#define UART_MCR_LB       0x10
#define UART_MCR_BR       0x20
#define UART_MCR_AR       0x40
#define UART_MCR_AC       0x80

#define UART_DIV          0xff

#define UART_TX_FIFO_MAX  0x05


#ifndef _MACRO_ONLY
/*
 * ��¢UART�� �ʰ�SIO�ɥ饤��
 */


/*
 * �����ͥ뵯ư���Ѥν����(sys_putc����Ѥ��뤿��)
 */
extern void uart_init(void);

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block   SIOPCB;

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_ERDY_SND    1u      /* ������ǽ������Хå� */
#define SIO_ERDY_RCV    2u      /* �������Υ�����Хå� */


/*
 *  ������åפ�UART����Υݡ���󥰽���
 */
extern void uart_putc(char c);



/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void uart_initialize(void);


/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
extern BOOL uart_openflag(void);


/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB   *uart_opn_por(ID siopid, VP_INT exinf);


/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void uart_cls_por(SIOPCB *siopcb);


/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern BOOL uart_snd_chr(SIOPCB *siopcb, char c);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern INT  uart_rcv_chr(SIOPCB *siopcb);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn);


/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
extern void uart_isr(void);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void uart_ierdy_snd(VP_INT exinf);


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void uart_ierdy_rcv(VP_INT exinf);


#endif /* _MACRO_ONLY */



/*
 *  ����å����Ϣ
 */
#ifndef _MACRO_ONLY

#define CACHE_TAG_RAM 0x11000000 /* W */

Inline void
cache_on(void)
{

}


Inline void
cache_off(void)
{

}


Inline void
cache_purge(void)
{

}
#endif /* _MACRO_ONLY */




#endif  /*  _EXCALIBUR_H_ */
