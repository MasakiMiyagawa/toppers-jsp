/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 */

#ifndef _VR5500_H_ 
#define _VR5500_H_ 

/* CP0�ϥ����ɤΤ���λ��ֲԤ� NOP_FOR_CP0_HAZARD  */
/* VR5500�Ǥ�CP0�ϥ����ɤ�MIPS3������Ƚ�Ǥ��Ƥ���뤿��������Ԥ�
   ɬ�פ��ʤ���*/
#define NOP_FOR_CP0_HAZARD

/* TLB �Υ���ȥ�κ�����  */
#define TMAX_TLB	47

/* TLB VPN2�� */
#define TLB_VPN2	0x2000

/* ����å���̿�� */
#define Index_Store_Tag_I       0x8+0x0
#define Index_Store_Tag_D       0x8+0x1

/* ����å���Υ饤�󥵥���(�Х���ñ��)  */
#define D_CACHE_LINE_SIZE 0x20	/* ����� */
#define I_CACHE_LINE_SIZE 0x20	/* ����� */

/*============================================================================*/

/*
 *  GDB STUB / PARTNER-J�����ƥॳ���� / ľ�ܸƽФ� ���󥽡���ƽФ��롼����
 *  (PARTNER-J �ϥƥ��Ȥ��Ƥ��ޤ���)
 */

/*
 *  gdb stub �ˤ�륳�󥽡������
 */
/* a0($4) = 0xfe00, a1($5) = ���Ϥ���������饯�� ���������ơ�
   SYSCALL �㳰��ȯ�������롣 */
#ifndef _MACRO_ONLY

/* ���δؿ���ƤӽФ����ˤϡ����ơ������쥸������EXL�ӥå� = 0 �ǸƤӽФ����ȡ�
   �ʤ������ߡ������ͥ�Ǥϡ��Хʡ�ɽ���������ꥢ����ϻ��˸ƽФ�ԤäƤ��롣*/
Inline void stub_putc(int c) {

	Asm("	move	$5, %0;		\
	     	li	$4, 0xfe00;	\
		syscall;		\
		nop"
		:: "r"(c)
		: "$4","$5" );
}

#endif /* _MACRO_ONLY */

#ifdef GDB_STUB
#define vr5500_putc(c) stub_putc(c)
#else  /* GDB_STUB */
#define	vr5500_putc(c) tl16pir552_write_por( (VP) UART_CH01, THR, (UB) c )
#endif /* GDB_STUB */

/*
 *  PARTNER-J �Υ����ƥॳ����ˤ�륳�󥽡�����ϡʥƥ��Ȥ��Ƥ��ޤ��󡣡�
 */
#ifndef _MACRO_ONLY

Inline void partner_putc(int c) {

	Asm("	move	$2, %0;		\
		li	$1, 0xfe00;	\
		jal	SYSCALL;	\
		nop"
		:: "r"(c)
		: "$1","$2" );
}

#endif /* _MACRO_ONLY */

#ifdef PARTNER_J	/* PARTNER_J �ξ�� *
#define vr5500_putc(c) partner_putc(c)
#else  /* GDB_STUB */
#define	vr5500_putc(c) tl16pir552_write_por( (VP) UART_CH01, THR, (UB) c )
#endif /* GDB_STUB */

#ifndef _MACRO_ONLY
Inline void
vr5500_exit() {
}
#endif /* _MACRO_ONLY */

#endif /* _VR5500_H_  */
