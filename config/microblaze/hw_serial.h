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
 *  @(#) $Id: hw_serial.h,v 1.1 2002/04/05 08:47:14 honda Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���MicroBlaze�ѡ�
 */

#include "microblaze.h"
#include "sys_config.h"
#include "cpu_config.h"


/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */
typedef struct hardware_serial_port_descripter {
    INT	  *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
    BOOL  sendflag;        /* ���������ߥ��͡��֥�ե饰 */
} HWPORT;



/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */
#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

static INT	initflag[1] = { 0 } ;	/* ������ѥե饰 */

#define HWPORT1	{ &initflag[0],  0 }


/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�γ�����ֹ�
 */
#define INHNO_SERIAL UARTINTLVL



/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
Inline BOOL
hw_port_initialize(HWPORT *p)
{
  /*
   *  �������Хåե����ꥢ������ߵ���
   * 
   */
  *UARTLITE_CTREG = UARTLITE_RST_RX_FIFO | UARTLITE_RST_TX_FIFO | UARTLITE_ENABLE_INTR;

  /*
   * INTC�γ���ߵ���
   */
  intc_enable_interrupt((1 << (UARTINTLVL - 1)));
  
  *(p->initflag) = 1;			/* ������ե饰���� */
  return(FALSE);
}


/*
 * ���ꥢ��I/O�ݡ��Ȥν�λ
 */
Inline void
hw_port_terminate(HWPORT *p)
{
  int dummy;
  
  *UARTLITE_CTREG =  ~UARTLITE_ENABLE_INTR; /* ����߶ػ�         */
  
  /*
   * ���Ǥ˳���ߤ����äƤ����礬����Τǳ�����׵�򥯥ꥢ
   */
  dummy = 1 << (UARTINTLVL -1);
  intc_ack_interrupt(dummy);
  intc_disable_interrupt(dummy);  /* INTC�μ����դ��ػ� */
}


/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */
extern void	serial_handler_in(ID portid);
extern void	serial_handler_out(ID portid);


/*
 * ���ꥢ��I/O�ݡ��Ȥγ���ߥϥ�ɥ�
 */
Inline void
hw_serial_handler()
{
  volatile  char  dummy;
  
  if(initflag[0] > 0){
    serial_handler_in(1);
    serial_handler_out(1);
  }else{
    /*
     * ��������ߤξ��ϥǡ�������Ф��ޤǳ���ߤϥ��ꥢ����ʤ�
     * �����ϡ��Хåե������ˤʤ�Ȱ���������ߤ�ȯ������Τ�
     * �ä˳���ߤ򥯥ꥢ���������Ԥ�ʤ��Ƥ�褤 
     */
    dummy = (char)(*UARTLITE_RXREG);
  }
}


/*
 * ʸ�������������?
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
  return((*UARTLITE_SRREG & UARTLITE_RX_FIFO_VALID_DATA) != 0);
}


/*
 * ʸ���������Ǥ��뤫?
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
  return((*UARTLITE_SRREG & UARTLITE_TX_FIFO_FULL) == 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
  return(*UARTLITE_RXREG);
}


/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
  *UARTLITE_TXREG = c;
}


/*
 * ��������ؿ�
 * UART Lite �ˤ���������ߤ���̤˶ػߵ��Ĥ��뵡ǽ�Ϥʤ�
 * ���Τ��ᡤ������λ���ˤ�ɬ��1�����ߤ�����  
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
  p->sendflag = 1;
}

Inline void
hw_port_sendstop(HWPORT *p)
{
  p->sendflag = 0;
}

#endif /*  _HW_SERIAL_H_ */
