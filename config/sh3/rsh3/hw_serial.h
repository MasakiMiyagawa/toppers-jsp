/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ�
 *  �եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�����
 *  �ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�������Х��ʥꥳ���ɤη��ޤ��ϵ�����Ȥ߹����������
 *      �Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (3) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: hw_serial.h,v 1.1 2000/11/14 16:30:22 honda Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���RSH3�ѡ�
 *  SCI1�����
 */

#include "sh3.h"
#include "sys_config.h"
#include "cpu_config.h"


/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN	 SCI1_RXI_INTEVT       
#define INHNO_SERIAL_OUT SCI1_TXI_INTEVT	
#define INHNO_SERIAL_ERROR  SCI1_BRI_INTEVT

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


#define SCI1INTLVL   6


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
    SCI1.SCSCR1 = 0;          /* SCI1�����,����P����å���Ȥ� */
    SCI1.SCFCR1 = SCFCR1_TFRST | SCFCR1_RFRST; /* ��������FIFO�򥯥ꥢ */
    SCI1.SCSMR1 = 0;          /* 8�ǡ���,1���ȥåץӥå�,no parity */
    SCI1.SCBRR1 = SCI1_BPS_VALUE;        

    /*
     * �ܡ��졼�Ȥ�����塢1�������ʬ�Ԥ��ʤ���Фʤ�ʤ���
     * �Х����ơ��ȥ���ȥ���Υ�ե�å��奫���󥿤�Ȥ�
     * 1�������ʬ�Ԥ�
     */

    *RFCR = RFCR_CLEAR;
    while( *RFCR < WAIT_RFCR_FOR_SCI);
    
        
    SCI1.SCFCR1 = 0x30;           /* R-FIFO=1,T-FIFO=1 �ȥꥬ������ */

    SCI1.SCSSR1 = 0x0060;         /* ���顼�ե饰�򥯥ꥢ           */
    SCI1.SCSCR1 = 0x70;           /* Start Tx Rx ���������ߵ���   */

    
    /*
     * �����ߴ�Ϣ������
     * ���顼�ϥ�ɥ����Ͽ���٤�
     */
    if (initflag[0] <= 0) {
        *IPRE=(*IPRE&0xf0ff)|(SCI1INTLVL<<8); /* �����ߥ�٥����� */
        define_int_plevel(SCI1_RXI_INTEVT,SCI1INTLVL);
        define_int_plevel(SCI1_TXI_INTEVT,SCI1INTLVL);
        *IRR1=0;                              /* �������׵᥯�ꥢ */  
    }
    
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
    SCI1.SCSCR1 = 0x00;         /* ���ꥢ�륳��ȥ������� */
    *IPRE=(*IPRE&0xf0ff);       /* �����ߥޥ������ꥢ       */
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
        SCI1.SCSCR1 &= ~(SCSCR1_RIE);
}

Inline void
hw_serial_handler_out()
{
    if (initflag[0] > 0)
        serial_handler_out(1);
    else
        SCI1.SCSCR1 &= ~(SCSCR1_TIE);
}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	return((SCI1.SCSSR1 & SCSSR1_RDF)!=0);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
    return((SCI1.SCSSR1 & SCSSR1_TDFE) !=0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
    byte data;
    data = SCI1.SCFRDR1;         
    SCI1.SCSSR1 &= ~SCSSR1_RDF ; 
    return data;
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
    SCI1.SCFTDR1=c;
    SCI1.SCSSR1 &= ~(SCSSR1_TDFE |SCSSR1_TEND);  
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
    if (!(p->sendflag)) {
        SCI1.SCSCR1 |= SCSCR1_TIE;   /* �����������׵����� */
        p->sendflag = 1;
    }
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	if (p->sendflag) {
        SCI1.SCSCR1 &= ~SCSCR1_TIE; /* �����������׵��ػ� */
        p->sendflag = 0;
	}
}

#endif /* _HW_SERIAL_H_ */





















