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
 *  @(#) $Id: hw_serial.h,v 1.1 2000/11/14 14:44:16 hiro Exp $
 */

/*
 *	�������åȰ�¸���ꥢ��I/O�⥸�塼���DVE68K/40�ѡ�
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include "dve68k.h"
#include "sys_config.h"

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */
typedef struct hardware_serial_port_descripter {
	INT	*initflag;	/* ������ѥե饰�ؤΥݥ��� */
	IOREG	*data;		/* �ǡ����쥸���������� */
	IOREG	*cntrl;		/* ����ȥ���쥸���������� */
	BOOL	sendflag;	/* ��������ߥ��͡��֥�ե饰 */

	byte	cr3_def;	/* �ǥե�����Ȥ������� (CR3) */
	byte	cr4_def;	/* �ǥե�����Ȥ������� (CR4) */
	byte	cr5_def;	/* �ǥե�����Ȥ������� (CR5) */
	byte	brg2_def;	/* �ǥե�����Ȥ������� (�ܡ��졼�Ȳ���) */
	byte	brg1_def;	/* �ǥե�����Ȥ������� (�ܡ��졼�Ⱦ��) */
} HWPORT;

/*
 *  MPSC����ȥ���쥸������������
 */

#define MPSC_RESET	0x18		/* �ݡ��ȥꥻ�åȥ��ޥ�� */
#define MPSC_EOI	0x38		/* EOI (End of Interrupt) */

#define CR3_DEF		0xc1		/* �ǡ��� 8bit, �������͡��֥� */
#define CR4_DEF		0x44		/* ���ȥåץӥå� 1bit, �ѥ�ƥ��ʤ� */
#define CR5_DEF		0xea		/* �ǡ��� 8bit, �������͡��֥� */
#define BRG2_DEF	0x1e		/* 9600bps (����) */
#define BRG1_DEF	0x00		/* 9600bps (���) */

#define CR10_DEF	0x00		/* NRZ */
#define CR14_DEF	0x07		/* �ܡ��졼�ȥ����ͥ졼�����͡��֥� */
#define CR15_DEF	0x56		/* �ܡ��졼�ȥ����ͥ졼������ */

#define CR1_ALL		0x12		/* ������ߤ���� */
#define CR1_RECV	0x10		/* ��������ߤΤߵ��� */
#define CR1_DOWN	0x00		/* ������ߤ�ػ� */

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL	GP0_VEC

/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define NUM_PORT	2	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

static INT	initflag[2] = { 0, 0 } ;	/* ������ѥե饰 */

#define HWPORT1		{ &initflag[0], MPSC_DATAA, MPSC_CNTRLA, 0,	\
			  CR3_DEF, CR4_DEF, CR5_DEF, BRG2_DEF, BRG1_DEF }
#define HWPORT2		{ &initflag[1], MPSC_DATAB, MPSC_CNTRLB, 0,	\
			  CR3_DEF, CR4_DEF, CR5_DEF, BRG2_DEF, BRG1_DEF }

/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
Inline BOOL
hw_port_initialize(HWPORT *p)
{
	/*
	 *  MPSC ������
	 */
	io_write(p->cntrl, MPSC_RESET);
	if (initflag[0] <= 0 && initflag[1] <= 0) {
		mpsc_write(MPSC_CNTRLA, MPSC_CR2, 0x18);
		mpsc_write(MPSC_CNTRLB, MPSC_CR2, 0x00);
	}
	mpsc_write(p->cntrl, MPSC_CR1, CR1_RECV);
	p->sendflag = 0;
	mpsc_write(p->cntrl, MPSC_CR4, p->cr4_def);
	mpsc_write_brg(p->cntrl, MPSC_CR12, 0x01, p->brg2_def, p->brg1_def);
	mpsc_write_brg(p->cntrl, MPSC_CR12, 0x02, p->brg2_def, p->brg1_def);
	mpsc_write(p->cntrl, MPSC_CR15, CR15_DEF);
	mpsc_write(p->cntrl, MPSC_CR14, CR14_DEF);
	mpsc_write(p->cntrl, MPSC_CR10, CR10_DEF);
	mpsc_write(p->cntrl, MPSC_CR3, p->cr3_def);
	mpsc_write(p->cntrl, MPSC_CR5, p->cr5_def);

	/*
	 *  ����ߴ�Ϣ������
	 */
	if (initflag[0] <= 0 && initflag[1] <= 0) {
		dga_set_ilv(DGA_CSR25, GP0IL_BIT, IRQ_LEVEL6);
						/* ����ߥ�٥����� */
		*DGA_CSR21 |= GP0_BIT;		/* ����ߥޥ������ */
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

	/*
	 *  MPSC �γ���ߴط�������
	 */
	mpsc_write(p->cntrl, MPSC_CR1, CR1_DOWN);
	p->sendflag = 0;

	/*
	 *  ����ߴ�Ϣ������
	 */
	if (initflag[0] <= 0 && initflag[1] <= 0) {
		*DGA_CSR21 &= ~GP0_BIT;		/* ����ߥޥ������� */
	}
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
	if (initflag[1] > 0) {
		serial_handler_in(2);
		serial_handler_out(2);
	}
	mpsc_write(MPSC_CNTRLA, MPSC_CR0, MPSC_EOI);
}

/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
	return((mpsc_read(p->cntrl, MPSC_SR0) & 0x01) != 0);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
	return((mpsc_read(p->cntrl, MPSC_SR0) & 0x04) != 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline byte
hw_port_getchar(HWPORT *p)
{
	return(io_read(p->data));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, byte c)
{
	io_write(p->data, c);
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
	if (!(p->sendflag)) {
		mpsc_write(p->cntrl, MPSC_CR1, CR1_ALL);
		p->sendflag = 1;
	}
}

Inline void
hw_port_sendstop(HWPORT *p)
{
	if (p->sendflag) {
		mpsc_write(p->cntrl, MPSC_CR1, CR1_RECV);
		p->sendflag = 0;
	}
}

#endif /* _HW_SERIAL_H_ */
