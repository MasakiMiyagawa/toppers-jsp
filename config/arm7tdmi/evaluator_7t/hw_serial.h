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
 *  @(#) $Id: hw_serial.h,v 1.3 2001/11/08 21:28:19 honda Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���Evaluator-7T�ѡ�
 *  SCI0�����
 */

#include "evaluator7t.h"
#include "sys_defs.h"
#include "sys_config.h"


/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN	 IRQ_NUMBER_UART0_RX
#define INHNO_SERIAL_OUT IRQ_NUMBER_UART0_TX


/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 *  Not yet! m68k�Τ褦�˥���ȥ���쥸������¤�Τˤ��롣
 */
typedef struct hardware_serial_port_descripter {
    INT	  *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
    BOOL  sendflag;        /* ���������ߥ��͡��֥�ե饰 */
} HWPORT;



/*
 * SCI1�γ����ߥ�٥�
 * ������������Ʊ�������ꤹ�롣
 */
#define SCI0INTLVL_TX   5
#define SCI0INTLVL_RX   6


/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */
static INT	initflag[1] = { 0 } ;	/* ������ѥե饰 */
#define HWPORT1	{ &initflag[0],  0 }


/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
Inline BOOL
hw_port_initialize(HWPORT *p)
{
    UART0.UCON = 0;                /* Disable Interrupt */
    UART0.ULCON = ULCON_WL_8BIT;   /* 8Data, 1Stop, No Parity */
    UART0.UBRDIV = UBRDIV_19200;    /* 9600bps */


    /*
     * ����ߴ�Ϣ������
     */
    UART0.UCON = UCON_RxM_INT;    /* Enable Interrupt */
    /* Clear Rx Tx Pending bit */    
    *INTPND = (IRQ_BIT_UART0_RX | IRQ_BIT_UART0_TX);



    /* Set Interrupt priority (SW) */
    
    /* Set Interrupt priority (HW) */
    
//    *(INTPRI0 + SCI0INTLVL_TX / 4) =
//        IRQ_NUMBER_UART0_TX << (SCI0INTLVL_TX % 4);
//    *(INTPRI0 + SCI0INTLVL_RX / 4) =
//        IRQ_NUMBER_UART0_RX << (SCI0INTLVL_RX % 4);

    
    /* Enable Interrupt Rx */
    *INTMSK &= ~((1 << INT_GLOBAL) | IRQ_BIT_UART0_RX |IRQ_BIT_UART0_TX); 
    
    *(p->initflag) = 1;			/* ������ե饰���� */
    return(FALSE);
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥν�λ
 */
Inline void
hw_port_terminate(HWPORT *p)
{
	*(p->initflag) = -1;		/* ������ե饰����           */
    UART0.UCON = 0;             /* Disable Interrupt */    
    /* Clear Rx Tx Pending bit */    
    *INTPND = (IRQ_BIT_UART0_RX | IRQ_BIT_UART0_TX);
}


/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */
extern void	serial_handler_in(int portid);
extern void	serial_handler_out(int portid);


/*
 *  ���ꥢ��I/O�ݡ��Ȥγ���ߥϥ�ɥ�
 */
Inline void
hw_serial_handler_in()
{
    if (initflag[0] > 0)
        serial_handler_in(1);        
    else
        *INTPND = IRQ_BIT_UART0_RX;
}


Inline void
hw_serial_handler_out()
{
    if (initflag[0] > 0)
        serial_handler_out(1);
    else
        *INTPND = IRQ_BIT_UART0_TX;
}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	return((UART0.USTAT & USTAT_RDR)!=0);
}


/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
	return((UART0.USTAT & USTAT_TBE)!=0);
}


/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
    return(UART0.URXBUF);         
}


/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
    UART0.UTXBUF=c;
}


/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
    
    if (!(p->sendflag)) {
        UART0.UCON = (UART0.UCON & ~UCON_TxM_MASK) | UCON_TxM_INT;
/*        *INTPND = IRQ_BIT_UART0_TX;        */
        /* Enable Interrupt */        
        p->sendflag = 1;
    }
}


Inline void
hw_port_sendstop(HWPORT *p)
{
	if (p->sendflag) {
//        UART0.UCON = (UART0.UCON & ~UCON_TxM_MASK) | UCON_TxM_DIS;
        UART0.UCON = (UART0.UCON & ~UCON_TxM_MASK) | UCON_TxM_GDMA0;
        *INTPND = IRQ_BIT_UART0_TX;                
       /* Disable Interrupt */
        p->sendflag = 0;
	}
}

#endif /* _HW_SERIAL_H_ */





















