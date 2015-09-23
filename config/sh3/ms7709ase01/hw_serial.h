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
 *  @(#) $Id: hw_serial.h,v 1.4 2001/10/20 15:39:15 honda Exp $
 */


#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���MS7709ASE01�ѡ�
 *  �����ѡ�I/O(FDC37C935A)��Υ��ꥢ��1�����
 */

#include "sh3.h"
#include "sys_config.h"
#include "cpu_config.h"
#include "ms7709ase01.h"

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL	 UART_IRQ0


/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 *  Not yet! m68k�Τ褦�˥���ȥ���쥸������¤�Τˤ��롣
 */
typedef struct hardware_serial_port_descripter {
    INT	  *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
    BOOL  sendflag;        /* ���������ߥ��͡��֥�ե饰 */
} HWPORT;



/*
 * �����ߥ�٥�ϸ���Ǥ��롥
 */
#define SCI1INTLVL   8


/*
 *  �ܡ��졼�Ȥ�����
 *  19200bps������
 */

#define BPS_SETTING 0x0006

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
    HIOREG dummy;

    /* BIT7 = 1 */
    *SMSC_SCI0_LCR = 0x83 << 8;

    /* Set BPS */
    *SMSC_SCI0_DLL = ((BPS_SETTING & 0x00ff) << 8);   
    *SMSC_SCI0_DLM = ((BPS_SETTING >> 8) << 8);

    /* BIT7 = 0 Divisor Latch BIT6 = 0 No Break : BIT3 = 0 NoParity
       : BIT2 = 0 1Stopbit : BIT1,0 = {1.1} 8bitData */    
    *SMSC_SCI0_LCR = 0x03 << 8;

    /* Do not use FIFO */
    *SMSC_SCI0_FCR = 0x0000;

    /* Clear Status */
    dummy = *SMSC_SCI0_RBR;
    dummy = *SMSC_SCI0_LSR;
    
    
    
    /* Enable Receive Data Interrupt */
    *SMSC_SCI0_IER = (0x01 << 8);
    *SMSC_SCI0_MCR = 0x08 << 8;
    

    /*
     * �����ߴ�Ϣ������
     * ���顼�ϥ�ɥ����Ͽ���٤�
     */
    if (initflag[0] <= 0) {
        define_int_plevel(INHNO_SERIAL,SCI1INTLVL);
    }

    /*
     * MS7729RSE01�Ǥϡ�������������ߤ�ȯ�������Ƥ����ʤ��ȳ����
     * ��٥�16�γ���ߤ�ȯ�����Ƥ��ޤ�������ư��ʤ���
     */
    /* �����������׵����� */
    *SMSC_SCI0_IER = (((*SMSC_SCI0_IER >> 8) | 0x02) << 8);   
    /* �����������׵��ػ� */        
    *SMSC_SCI0_IER = (((*SMSC_SCI0_IER >> 8) & ~0x02) << 8);   
    
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
    *SMSC_SCI0_IER   = 0x00;      /* ����ߤζػ�               */
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
hw_serial_handler()
{
    HIOREG dummy;
    
    if (initflag[0] > 0){
        serial_handler_in(1);
        serial_handler_out(1);
    }
    else
        dummy = *SMSC_SCI0_LSR;
}

/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	return(((*SMSC_SCI0_LSR >> 8) & 0x01) != 0);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
	return(((*SMSC_SCI0_LSR >> 8) & 0x60) != 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
    return (*SMSC_SCI0_RBR >> 8);
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
    *SMSC_SCI0_THR = c << 8;
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
    if (!(p->sendflag)) {
        /* �����������׵����� */
        *SMSC_SCI0_IER = (((*SMSC_SCI0_IER >> 8) | 0x02) << 8);   
        p->sendflag = 1;
    }
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	if (p->sendflag) {
        /* �����������׵��ػ� */        
        *SMSC_SCI0_IER = (((*SMSC_SCI0_IER >> 8) & ~0x02) << 8);   
        p->sendflag = 0;
	}
}

#endif /* _HW_SERIAL_H_ */





















