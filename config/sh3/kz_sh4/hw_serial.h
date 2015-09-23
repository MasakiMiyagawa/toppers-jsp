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
 *  @(#) $Id: hw_serial.h,v 1.1 2001/11/05 13:34:25 honda Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���KZ_SH4�ѡ�
 *  SCIF�����
 */

#include "sh4.h"
#include "sys_config.h"
#include "cpu_config.h"


/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN	 SCIF_RXI_INTEVT       
#define INHNO_SERIAL_OUT SCIF_TXI_INTEVT	
#define INHNO_SERIAL_ERROR  SCIF_BRI_INTEVT

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */
typedef struct hardware_serial_port_descripter {
    INT	  *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
    BOOL  sendflag;        /* ���������ߥ��͡��֥�ե饰 */
} HWPORT;



/*
 * SCIF�γ����ߥ�٥�
 * ������������Ʊ�������ꤹ�롣
 */


#define SCIFINTLVL   6


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
    
    *SCIF_SCSCR2  = 0;             /* SCI1�����,����P����å���Ȥ�     */
    *SCIF_SCFCR2  = SCFCR2_TFRST | SCFCR2_RFRST; /* ��������FIFO�򥯥ꥢ */
    *SCIF_SCSMR2  = 0;            /* 8�ǡ���,1���ȥåץӥå�,no parity   */
    *SCIF_SCSPTR2 = SCSPTR2_RTSIO;    /* ^RTS2 �˽���                    */    
    *SCIF_SCBRR2  = SCIF_BPS_VALUE;        

    /*
     * �ܡ��졼�Ȥ�����塢1�������ʬ�Ԥ��ʤ���Фʤ�ʤ���
     * �Х����ơ��ȥ���ȥ���Υ�ե�å��奫���󥿤�Ȥ�
     * 1�������ʬ�Ԥ�
     */

    *RFCR = RFCR_CLEAR;
    while( *RFCR < WAIT_RFCR_FOR_SCI);
        
    *SCIF_SCFCR2 = 0x30;           /* R-FIFO=1,T-FIFO=1 �ȥꥬ������ */

    *SCIF_SCSCR2 = 0x0060;         /* ���顼�ե饰�򥯥ꥢ           */
    *SCIF_SCSCR2 = 0x70;           /* Start Tx Rx ���������ߵ���   */
    
    /*
     * �����ߴ�Ϣ������
     * ���顼�ϥ�ɥ����Ͽ���٤�
     */
    if (initflag[0] <= 0) {
        *IPRC=(*IPRC&0xff0f)|(SCIFINTLVL<<4); /* �����ߥ�٥����� */
        define_int_plevel(SCIF_RXI_INTEVT,SCIFINTLVL);
        define_int_plevel(SCIF_TXI_INTEVT,SCIFINTLVL);
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
    *SCIF_SCSCR2 = 0x00;         /* ���ꥢ�륳��ȥ������� */
    *IPRC=(*IPRC&0xff0f);       /* �����ߥޥ������ꥢ       */
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
        *SCIF_SCSCR2 &= ~(SCSCR2_RIE);
}

Inline void
hw_serial_handler_out()
{
    if (initflag[0] > 0)
        serial_handler_out(1);
    else
        *SCIF_SCSCR2 &= ~(SCSCR2_TIE);
}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	return((*SCIF_SCFSR2 & SCFSR2_RDF)!=0);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
    return((*SCIF_SCFSR2 & SCFSR2_TDFE) !=0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
    byte data;
    data = *SCIF_SCFRDR2;         
    *SCIF_SCFSR2 &= ~SCFSR2_RDF ; 
    return data;
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
    *SCIF_SCFTDR2=c;
    *SCIF_SCFSR2 &= ~(SCFSR2_TDFE |SCFSR2_TEND);  
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
    if (!(p->sendflag)) {
        *SCIF_SCSCR2 |= SCSCR2_TIE;   /* �����������׵����� */
        p->sendflag = 1;
    }
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	if (p->sendflag) {
        *SCIF_SCSCR2 &= ~SCSCR2_TIE; /* �����������׵��ػ� */
        p->sendflag = 0;
	}
}

#endif /* _HW_SERIAL_H_ */





















