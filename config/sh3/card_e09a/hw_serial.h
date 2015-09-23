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
 *  @(#) $Id: hw_serial.h,v 1.2 2001/10/19 14:20:47 honda Exp $
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

/*
 *  �������åȰ�¸���ꥢ��I/O�⥸�塼���CARD-E09A�ѡ�
 *  Companion Chip���16550�ߴ���serial3�����
 */


#include "sh3.h"
#include "card_e09a.h"
#include "sys_config.h"
#include "cpu_config.h"


/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL	 IRQ0_INTEVT

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 *  Not yet! m68k�Τ褦�˥���ȥ���쥸������¤�Τˤ��롣
 */
typedef struct hardware_serial_port_descripter {
    INT	    *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
    BOOL    sendflag;      /* ���������ߥ��͡��֥�ե饰 */
} HWPORT;



/*
 *  SCIF�γ����ߥ�٥�
 *  ������������Ʊ�������ꤹ�롣
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
    CARD_E09A_SERIAL.LS = 0x00;
    *CARD_E09A_IER1 = 0x10;
    CARD_E09A_SERIAL.IE =  IER_ERBFI;
    if (initflag[0] <= 0) {
        *IPRC=(*IPRC&0xfff0)|(SCIFINTLVL);        /* �����ߥ�٥����� */
        define_int_plevel(IRQ0_INTEVT,SCIFINTLVL);
        *ICR1 = 0x02;
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
    
	*(p->initflag) = -1;			/* ������ե饰���� */
    SCIF.SCSCR2 = 0x00;                  /* ���ꥢ�륳��ȥ������� */
	CARD_E09A_SERIAL.IE =  0x00;
    
    /*
	 *  �����ߴ�Ϣ������
	 */
    *IPRC=(*IPRC&0xfff0);                   /* �����ߥޥ������ꥢ */
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
	if (initflag[0] > 0) {
		serial_handler_in(1);
		serial_handler_out(1);
	}
	/*	CARD_E09A_SERIAL.LS = 0x00; */
}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
  return((CARD_E09A_SERIAL.LS & 0x0001) != 0);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
  return((CARD_E09A_SERIAL.LS & 0x0060) != 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
    return(CARD_E09A_SERIAL.data);
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
  CARD_E09A_SERIAL.data=c;
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
    if (!(p->sendflag)) {
        CARD_E09A_SERIAL.IE |= IER_ETBEI; /* �����������׵����� */
        p->sendflag = 1;
	}
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	if (p->sendflag) {
        CARD_E09A_SERIAL.IE &= ~IER_ETBEI; /* �����������׵��ػ� */
        p->sendflag = 0;
	}
}

#endif /* _HW_SERIAL_H_ */
