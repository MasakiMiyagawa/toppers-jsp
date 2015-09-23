/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: hw_serial.h,v 1.1 2001/05/04 09:07:50 imai Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼��ʾ��׾��� SH1/CPUB�ѡ�
 *  SCI0�����
 *  �����������Υ⥸�塼��ˤ�äơ�XON/XOFF�ե����椬�Ԥ�
 *  ������Ƥ���Τǡ���������TxD��RxD��2�ܤǤ褤
 */

#include "sh1.h"
#include "sys_config.h"
#include "cpu_config.h"

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN	 RXI0
#define INHNO_SERIAL_OUT TXI0
/*
 *  ���顼�����Ϥ��Ƥ��ʤ�
 * #define INHNO_SERIAL_ERROR  SCI_BRI_INTEVT
 */


/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */
typedef struct hardware_serial_port_descripter {
    INT	  *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
    BOOL  sendflag;        /* ���������ߥ��͡��֥�ե饰 */
} HWPORT;



/*
 * SCI�γ����ߥ�٥�
 * ������ߥϥ�ɥ���������̡�����Ͽ�Ǥ��뤬������ߥ�٥��
 * �������������Ʊ����٥�ˤ�������Ǥ��ʤ���
 */
#define SCIINTLVL	6	/*  ����������  */
#define LEVEL0		0	/*  ����߲�����Υ�٥�  */
#define SCI_SHIFT	0	/*  ����ߥ�٥���Ͽ���Υӥåȥ��ե�  */


/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

static INT	initflag[NUM_PORT] = { 0 } ;	/* ������ѥե饰 */
#define HWPORT1	{ &initflag[0],  0 }

/*
 *���ץ�������PORT1�ϡ�SCI0��ؤ��Ƥ���
 */
#define PORT_ID1	1
#define PORT_INDEX1	0


/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
Inline BOOL
hw_port_initialize(HWPORT *p)
{
    int i;

    SCI.SCR0 &= ~(SCR_TE | SCR_RE);	/*  ���������  */
    					/*  �ԥ󥢥�����  */
    					/*  	PB8:RxD0 PB9:TxD0  */
    *PBCR1 = (*PBCR1 & PBCR1_TD0_RD0_MASK) |
    		PBCR1_TD0 | PBCR1_RD0;
    					/*  �������ե����ޥå�  */
    SCI.SMR0 = 	SMR_CA_ASYNC |	/*  Ĵ��Ʊ����  		*/
    		SMR_CHR8 |	/*  ����饯����󥰥���8�ӥå� */
    		SMR_PE_NON |	/*  �ѥ�ƥ��ʤ�  		*/
    		SMR_STOP1 |	/*  ���ȥåץӥåȥ�󥰥���1 	*/
    		SMR_CKS;	/*  ����å����쥯�ȡ�ʬ�����  */
    				/*  ��sys_config.h��  		*/
    SCI.BRR0 = SCI_BRR;		/*  �ܡ��졼������  	*/
    				/*  ��sys_config.h��  	*/

    				/*  ����߶ػߤȥ���å������������� */
    SCI.SCR0 = (IOREG)(~(SCR_TIE | SCR_RIE | SCR_TE | SCR_RE |
    		  SCR_MPIE | SCR_TEIE | SCR_CKE_MASK) | SCR_CKE);

    /*
     * �ܡ��졼�Ȥ�����塢1�������ʬ�Ԥ��ʤ���Фʤ�ʤ���
     */
    for(i=0; i<WAIT_TIME; i++);	/*  ��sys_config.h��  	*/

    				/* ���顼�ե饰�򥯥ꥢ		*/
    SCI.SSR0 &= ~(SSR_ORER | SSR_FER | SSR_PER);
    				/* ���������ߵ���   	*/
    				/* ����������  		*/
    SCI.SCR0 |= (SCR_RIE | SCR_TE | SCR_RE);
    		/*  ��������ߤε��Ĥ���������ؿ��ǹԤ�  */

    /*
     * �����ߴ�Ϣ������
     * ���顼�ϥ�ɥ����Ͽ���٤�
     */
    if (initflag[PORT_INDEX1] <= 0) {
        			/* �����ߥ�٥����� */
        define_int_plevel(IPRD, SCIINTLVL, SCI_SHIFT);
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
    *(p->initflag) = -1;		/* ������ե饰����     */
    SCI.SCR0 &= ~(SCR_TE | SCR_RE);	/*  ���������  	*/
    					/* �����ߥ�٥륯�ꥢ */
    define_int_plevel(IPRD, LEVEL0, SCI_SHIFT);
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
    if (initflag[PORT_INDEX1] > 0)
        serial_handler_in(PORT_ID1);
    else
    	/*  ���������Ƥ��ʤ����ϼ��������ߤ�ػ�  */
        SCI.SCR0 &= ~SCR_RIE;
}

Inline void
hw_serial_handler_out()
{
    if (initflag[PORT_INDEX1] > 0)
        serial_handler_out(PORT_ID1);
    else
    	/*  ���������Ƥ��ʤ��������������ߤ�ػ�  */
        SCI.SCR0 &= ~SCR_TIE;
}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ����å�  */
	return(SCI.SSR0 & SSR_RDRF);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
	/*  �ȥ�󥹥ߥåȥǡ����쥸��������ץƥ����ե饰�Υ����å�*/
	return(SCI.SSR0 & SSR_TDRE);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
    byte data;
    data = SCI.RDR0;
 	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ��ꥢ  */
    SCI.SSR0 &= ~SSR_RDRF ;
    return data;
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
    SCI.TDR0 = c;
	/*  �ȥ�󥹥ߥåȥǡ����쥸��������ץƥ����ե饰�Υ��ꥢ*/
    SCI.SSR0 &= ~SSR_TDRE;
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
    if (!(p->sendflag)) {
        SCI.SCR0 |= SCR_TIE;   /* �����������׵����� */
        p->sendflag = 1;
    }
}

Inline void
hw_port_sendstop(HWPORT *p)
{
    if (p->sendflag) {
        SCI.SCR0 &= ~SCR_TIE; /* �����������׵��ػ� */
        p->sendflag = 0;
    }
}

#endif /* _HW_SERIAL_H_ */
