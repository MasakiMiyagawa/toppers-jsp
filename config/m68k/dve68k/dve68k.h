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
 *  @(#) $Id: dve68k.h,v 1.3 2002/04/10 11:08:33 hiro Exp $
 */

/*
 *	DVE68K/40 CPU�ܡ��ɤΥϡ��ɥ������񸻤����
 */

#ifndef _DVE68K_H_
#define _DVE68K_H_

typedef	unsigned char	byte;
typedef volatile byte	IOREG;		/* I/O�쥸�����η� */
typedef volatile int	LIOREG;

/*
 *  ��®�� I/O�ǥХ��������뤿��δؿ�
 */

Inline void
cpu_wait_io(void)
{
	Asm("nop");
	Asm("nop");
	Asm("nop");
	Asm("nop");
}

Inline byte
io_read(IOREG *addr)
{
	byte	val;

	val = *addr;
	cpu_wait_io();
	return(val);
}

Inline void
io_write(IOREG *addr, byte val)
{
	*addr = val;
	cpu_wait_io();
}

/*
 *  CPU�ܡ��ɾ�Υ쥸����
 */

#define BOARD_REG0	((LIOREG *) 0xfff48000)
#define BOARD_REG1	((LIOREG *) 0xfff48004)
#define BOARD_REG2	((LIOREG *) 0xfff48008)

/*
 *  DGA-001 �Υ쥸����
 */

#define DGA_CSR0_1	((IOREG *) 0xfff44001)
#define DGA_CSR1	((LIOREG *) 0xfff44004)
#define DGA_CSR3	((LIOREG *) 0xfff4400c)
#define DGA_CSR4	((LIOREG *) 0xfff44010)
#define DGA_CSR5	((LIOREG *) 0xfff44014)
#define DGA_CSR12	((LIOREG *) 0xfff44030)
#define DGA_CSR13	((LIOREG *) 0xfff44034)
#define	DGA_CSR19	((LIOREG *) 0xfff4404c)
#define	DGA_CSR20	((LIOREG *) 0xfff44050)
#define	DGA_CSR21	((LIOREG *) 0xfff44054)
#define DGA_CSR23	((LIOREG *) 0xfff4405c)
#define DGA_CSR24	((LIOREG *) 0xfff44060)
#define	DGA_CSR25	((LIOREG *) 0xfff44064)
#define	DGA_IFR0	((LIOREG *) 0xfff44070)
#define DGA_IFR3	((LIOREG *) 0xfff4407c)

/*
 *  DGA �γ���ߥ�٥�����Τ�������
 */

#define	IRQ_NMI		(0x7)		/* �Υ�ޥ����֥����� */
#define	IRQ_LEVEL6	(0x6)		/* ����ߥ�٥�6 */
#define	IRQ_LEVEL5	(0x5)		/* ����ߥ�٥�5 */
#define	IRQ_LEVEL4	(0x4)		/* ����ߥ�٥�4 */
#define	IRQ_LEVEL3	(0x3)		/* ����ߥ�٥�3 */
#define	IRQ_LEVEL2	(0x2)		/* ����ߥ�٥�2 */
#define	IRQ_LEVEL1	(0x1)		/* ����ߥ�٥�1 */

#define ABTIL_BIT	(24)		/* ���ܡ��ȳ���� */
#define SQRIL_BIT	(8)		/* SRQ ����� */

#define TT0IL_BIT	(16)		/* ������0 ����� */
#define GP0IL_BIT	(0)		/* ���ꥢ��I/O ����� */

Inline void
dga_set_ilv(LIOREG *addr, int shift, int val)
{
	*addr = (*addr & ~(0x07 << shift)) | (val << shift);
} 

/*
 *  ����ߥ٥��ȥ�����
 */

#define	G0I_VEC		(0x40)		/* ���롼��0 ����ߥ٥��ȥ� */
#define	G1I_VEC		(0x48)		/* ���롼��1 ����ߥ٥��ȥ� */
#define	SWI_VEC		(0X50)		/* ���եȥ���������ߥ٥��ȥ� */
#define	SPRI_VEC	(0x40)		/* ���ץꥢ������ߥ٥��ȥ� */

#define ABT_VEC		(G0I_VEC + 6)	/* ���ܡ��ȳ���ߥ٥��ȥ� */
#define SQR_VEC		(G0I_VEC + 2)	/* SQR ����ߥ٥��ȥ� */
#define	TT0_VEC		(G1I_VEC + 4)	/* ������0 ����ߥ٥��ȥ� */
#define	GP0_VEC		(G1I_VEC + 0)	/* ���ꥢ��I/O ����ߥ٥��ȥ� */

/*
 *  ���������ӥåȤ����
 */

#define ABT_BIT		(0x40000000)	/* ���ܡ��ȳ���ߥӥå� */
#define SQR_BIT		(0x04000000)	/* SQR ����ߥӥå� */
#define	TT0_BIT		(0x00100000)	/* ������0 ����ߥӥå� */
#define	GP0_BIT		(0x00010000)	/* ���ꥢ��I/O ����ߥӥå� */

/*
 *  MPSC (��PD72001-11) �Υ쥸����
 */

#define	MPSC_DATAA	((IOREG *) 0xfff45003)
#define	MPSC_CNTRLA	((IOREG *) 0xfff45007)
#define	MPSC_DATAB	((IOREG *) 0xfff4500b)
#define	MPSC_CNTRLB	((IOREG *) 0xfff4500f)

#define	MPSC_CR0	0x00		/* MPSC ����ȥ���쥸���� */
#define	MPSC_CR1	0x01
#define	MPSC_CR2	0x02
#define	MPSC_CR3	0x03
#define	MPSC_CR4	0x04
#define	MPSC_CR5	0x05
#define	MPSC_CR10	0x0a
#define	MPSC_CR12	0x0c
#define	MPSC_CR14	0x0e
#define	MPSC_CR15	0x0f

#define	MPSC_SR0	0x00		/* MPSC ���ơ������쥸���� */

Inline byte
mpsc_read(IOREG *addr, int reg)
{
	io_write(addr, reg);
	return(io_read(addr));
}

Inline void
mpsc_write(IOREG *addr, int reg, int val)
{
	io_write(addr, reg);
	io_write(addr, val);
}

Inline void
mpsc_write_brg(IOREG *addr, int reg, int val, int brg2, int brg1)
{
	io_write(addr, reg);
	io_write(addr, val);
	io_write(addr, brg2);
	io_write(addr, brg1);
	(void) io_read(addr);		/* ���ߡ��꡼�� */
}

/*
 *  ��˥��ƤӽФ��롼����
 */

Inline void
dve68k_exit(void)
{
	Asm("clr.l %%d0; trap #3"
	  : /* no output */
	  : /* no input */
	  : "d0", "d1", "d2", "d6", "d7");
}

Inline int
dve68k_getc(void)
{
	int	c;

	Asm("moveq.l #3, %%d0; trap #3; move.l %%d0, %0"
	  : "=g"(c)
	  : /* no input */
	  : "d0", "d1", "d2", "d6", "d7");
	  return(c);
}

Inline int
dve68k_putc(int c)
{
	Asm("moveq.l #5, %%d0; move.l %0, %%d1; trap #3"
	  : /* no output */
	  : "g"(c)
	  : "d0", "d1", "d2", "d6", "d7");
	  return(c);
}

#endif /* _DVE68K_H_ */
