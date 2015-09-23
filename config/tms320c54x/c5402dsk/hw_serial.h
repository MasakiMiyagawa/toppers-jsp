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
 *  @(#) $Id: hw_serial.h,v 1.4 2002/04/14 15:04:35 reiji Exp $
 */


#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include "c54x.h"
#include "sys_config.h"
#include "cpu_config.h"

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL   INT1_VEC


/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */
#ifndef _MACRO_ONLY
typedef struct hardware_serial_port_descripter{
  INT   *initflag;
  BOOL  sendflag;   /* ���������ߥ��͡��֥�ե饰 */
}HWPORT;
#endif //_MACRO_ONLY

#define NUM_PORT  1       /* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

static INT  initflag[1] = { 0 }; /* ������ѥե饰 */

#define HWPORT1 { &initflag[0], 0 }



/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
#ifndef _MACRO_ONLY
Inline BOOL
hw_port_initialize(HWPORT *p)
{
  /*  FIFO��ͭ���ˤ�����������FIFO�򥯥ꥢ��
   *  �ȥꥬ��٥�ᣱ(�����������̡�       
   */
  UART_FCR=FCR_FIFO | FCR_RFRST | FCR_TFRST | FIFO_TRIG;
  UART_LCR=0x03;  /*  8�ǡ�����1���ȥåץӥåȡ�no parity */
  UART_LCR|=LCR_DLAB;  /*  �ܡ��졼�ȥ쥸�����˥������� */
  UART_DLL=UART_BAUD_RATE;
  UART_DLM=UART_BAUD_RATE >> 8;
  UART_LCR&=~LCR_DLAB; /*  BAUD RATE���꽪λ  */
  UART_SCR=UART_LSR;   /*  ���顼�ե饰�򥯥ꥢ  */
  UART_IER=IER_RIE;       /*  ���������ߵ���  */


  if (initflag[0] <= 0){
    IFR|=(0x1 << INT1);  /* �����ߥե饰�Υ��ꥢ */
    IMR|=(0x1 << INT1);  /* �����ߥޥ����쥸���������� */
  };

  *(p->initflag) = 1;
  return (FALSE);
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥν�λ
 */
Inline void
hw_port_terminate(HWPORT *p)
{
  *(p->initflag) = -1; /* ������ե饰���� */
  UART_IER=0x0;   /* ���������������׵�ػ� */
  p->sendflag = 0; 
  IMR&=~(0x1 << INT1); /* �����ߥޥ������� */
}

/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */
extern void serial_handler_in(int portid);
extern void serial_handler_out(int portid);



/*
 *  ���ꥢ��I/O�ݡ��Ȥγ���ߥϥ�ɥ�
 */
Inline void
hw_serial_handler()
{
  if (initflag[0] > 0){
//      if ( UART_IIR & 0x02 ) {


      serial_handler_out(1);
      serial_handler_in(1);
//      }
//      else if ( !(UART_IIR & 0x0C) ) {

//      }

  }
  else
    UART_IER = 0;             /*  �����ߤ�ػ�  */
}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
  return ((UART_LSR & LSR_DR) != 0);
}


/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
  return ((UART_LSR & LSR_THRE) != 0);
}


/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
  return ((byte)UART_RBR & 0x00FF);
}


/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
  UART_THR = c;
}



/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
  if (!(p->sendflag)){
    UART_IER |= IER_TIE;  /* �����������׵����� */
    p->sendflag = 1;
  }
}



Inline void
hw_port_sendstop(HWPORT *p)
{
  if (p->sendflag){
    UART_IER &= ~IER_TIE; /* �����������׵��ػ� */
    p->sendflag = 0;
  }
}
#endif //_MACRO_ONLY
#endif
