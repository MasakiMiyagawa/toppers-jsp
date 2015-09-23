/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: card_e09a.h,v 1.2 2001/10/19 14:20:47 honda Exp $
 */

#ifndef _CARD_E09A_ 
#define _CARD_E09A_ 

#include "sh3.h"




/*
 *  ISH�ܡ��ɾ�ΥǥХå���LED�ȥ���ȥ��顼�Υ��ɥ쥹
 */

#define ISH_LED1         (*(IOREG *)0xBBC00080)
#define ISH_LED2         (*(IOREG *)0xBBC00081)
#define ISH_LED_CONTROL  (*(HIOREG *)0xB1000780)


/*
 *  LED�Υ���ȥ��顼���˥���饤��
 */
Inline void
led_init(void)
{
    ISH_LED_CONTROL = 0x0080;
}

/*
 *LED�ݡ��Ȥؤν���
 */

Inline void
led_set(HIOREG led_data)
{
    ISH_LED1 = (IOREG)led_data;
    ISH_LED2 = (IOREG)(led_data >> 8);
}



/*
 *  CARD-E09A�Υϡ��ɥ������񸻤����
 */



/*
 * CARD-E09A��γ���ߥ���ȥ���
 */

#define CARD_E09A_IER1    ((HIOREG *)(0xb1000000))  
#define CARD_E09A_IER2    ((HIOREG *)(0xb1000002))  
#define CARD_E09A_SR1     ((HIOREG *)(0xb1000004))  
#define CARD_E09A_SR2     ((HIOREG *)(0xb1000006))  

    
/*
 *  CARD-E09A���16550�ߴ���serial3
 */

typedef struct{
    HIOREG  data;
    HIOREG  IE;
    HIOREG  II;
    HIOREG  LC;
    HIOREG  MC;
    HIOREG  LS;
    HIOREG  MS;
    HIOREG  scratch;
} CARD_E09A_serial_t;

#define CARD_E09A_SERIAL     (*(volatile CARD_E09A_serial_t *)0xb1000200)

/*
 *  For IE
 */
#define IER_EDSSI     0x08
#define IER_ELSI      0x04
#define IER_ETBEI     0x02
#define IER_ERBFI     0x01

/*
 *  For II
 */
#define IIR_ID        0x06
#define IIR_IP        0x01

/*
 *  For LC
 */
#define LCR_DLAB      0x80
#define LCR_SB        0x40
#define LCR_SP        0x20
#define LCR_EPS       0x10
#define LCR_PEN       0x08
#define LCR_STB       0x06
#define LCR_WLS       0x01

 /*
  *  For LS 
  */
#define LSR_TEMT      0x40
#define LSR_THRE      0x20
#define LSR_BI        0x10
#define LSR_FE        0x08
#define LSR_PE        0x04
#define LSR_OE        0x02
#define LSR_DR        0x01


#endif /*  _CARD-E09A_ */



