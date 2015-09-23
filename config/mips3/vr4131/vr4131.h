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

#ifndef _VR4131_H_
#define _VR4131_H_

/* CP0�ϥ����ɤΤ���λ��ֲԤ� NOP_FOR_CP0_HAZARD  */
/* VR4131�Ǥ�mtc0̿���ľ�夫�����߶ػߤˤʤäƤ���Τ�nop̿����������ʤ��Ƥ�
   ����� */
#define NOP_FOR_CP0_HAZARD

/* Config�쥸����  */
#define BP		BIT16	/* ʬ��ͽ¬������ */

/* TLB �Υ���ȥ�κ�����  */
#define TMAX_TLB	31

/* TLB�ޥ����� */
#define TLB_VPN2	0x800

/* ����å���̿�� */
#define Index_Invalidate_I	0x0+0x0
#define Index_Store_Tag_I       0x8+0x0
#define Index_Store_Tag_D       0x8+0x1

/* ����å���Υ饤�󥵥���(�Х���ñ��)  */
#define D_CACHE_LINE_SIZE 	0x10	/* 16�Х��� */
#define I_CACHE_LINE_SIZE 	0x10	/* 16�Х��� */

/*============================================================================*/

/*
 *  GDB STUB / PARTNER-J�����ƥॳ���� / ľ�ܸƽФ� ���󥽡���ƽФ��롼����
 *  (GDB_STUB, PARTNER-J �ϥƥ��Ȥ��Ƥ��ޤ���)
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
#define vr4131_putc(c) stub_putc(c)
#else  /* GDB_STUB */
#define	vr4131_putc(c) vr4131_dsiu_write_por( (VP) DSIUTH, (UB) c )
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
#define vr4131_putc(c) partner_putc(c)
#else  /* GDB_STUB */
#define	vr4131_putc(c) vr4131_dsiu_write_por( (VP) DSIUTH, (UB) c )
#endif /* GDB_STUB */

#ifndef _MACRO_ONLY
Inline void
vr4131_exit() {
	/* GDB_STUB ���ѻ��ˤϡ�STUB��Ƭ�����ֽ�����ɬ�פ��⡣ */
}
#endif /* _MACRO_ONLY */


/*============================================================================*/
/* �ʲ�������ϡ��ƥ�˥åȤ��Ȥˡ�vr4131_xxx.h�Ȥ��ƤޤȤ�뤳�Ȥ�ɬ�פ��⡣ */

/*
 * ����å��ޥ�����˥å�(CMU)�ط������
 */
#define CMUCLKMSK	(BASE_ADDR + 0x0f000060)

#define MSKSIU		BIT1	/* SIU, DSIU�ؤ�TClock��������� */
#define MSKSSIU		BIT8	/* SIU�ؤ�18.432MHz����å���������� */
#define MSKDSIU		BIT11	/* DSIU�ؤ�18.432MHz����å���������� */

/*
 * �ѥ�ޥ͡������ȥ�˥å�(PMU)�ط������
 */
#define PMUINTREG	(BASE_ADDR + 0x0f0000c0)	/* PMU ����ߡ����ơ������쥸���� */
#define PMUCNTREG	(BASE_ADDR + 0x0f0000c2)	/* PMU ����ȥ���쥸���� */
#define PMUTCLKDIVREG	(BASE_ADDR + 0x0f0000cc)

/* for PMUINTREG */
#define TIMOUTRST	BIT5		/* HALTimer�ꥻ�åȸ��� */
/* for PMUCNTREG */
#define HALTIMERRST	BIT2		/* HALTimer�ꥻ�å�*/
/* for PMUTCLKDIVREG */
#define VTDIV_3		BIT1 | BIT0

/*
 * �Х�����ȥ����˥å�(BCU)�ط������
 */
#define BCUCNTREG1	(BASE_ADDR + 0x0f000000)
#define ROMSIZEREG	(BASE_ADDR + 0x0f000004)
#define ROMSPEEDREG	(BASE_ADDR + 0x0f000006)
#define IO0SPEEDREG	(BASE_ADDR + 0x0f000008)
#define IO1SPEEDREG	(BASE_ADDR + 0x0f00000a)
#define BCUCNTREG3	(BASE_ADDR + 0x0f000016)

/* for ROMSIZEREG */
#define SIZE3_4		BIT12
#define SIZE2_4		BIT8
#define SIZE1_4		BIT4
#define SIZE0_4		BIT0
/* for ROMSPEEDREG */
#define ROM4_WAIT_5VTClock	BIT13 | BIT12
#define ROM2_WAIT_8VTClock	BIT2 | BIT0
/* for IO0SPEEDREG */
#define IO0_1_WAIT_4	BIT1 | BIT0
/* for IO1SPEEDREG */
#define IO1_3_WAIT_11	BIT11
/* for BCUCNTREG3 */
#define EXT_ROMCS_3ROM_2ROM	BIT13 | BIT12
#define IO32			BIT7
#define LCDSEL1_BUFFER		BIT1
#define LCDSEL0_BUFFER		BIT0

/*
 * SDRAM����ȥ����˥å�(SDRAMU)�ط������
 */
#define SDRAMMODEREG	(BASE_ADDR + 0x0f000400)
#define SDRAMCNTREG	(BASE_ADDR + 0x0f000402)
#define BCURFCNTREG	(BASE_ADDR + 0x0f000404)
#define BCURFCOUNTREG	(BASE_ADDR + 0x0f000406)
#define RAMSIZEREG	(BASE_ADDR + 0x0f000408)

/* for SDRAMMODEREG */
#define SCLK		BIT15
#define LTMODE_2	BIT5
/* for SDRAMCNTREG */
#define TRC_3VTClock	BIT9 | BIT8
#define TDAL_2VTClock	BIT5
#define TRCD_2VTClock	BIT1
/* for RAMSIZEREG */
#define SIZE3_64	BIT14 | BIT12
#define SIZE2_64	BIT10 | BIT8
#define SIZE1_64	BIT6 | BIT4
#define SIZE0_64	BIT2 | BIT0

/*
 * ���ꥢ�륤�󥿥ե�������˥å�(SIU)�ط������
 */
#define SIURESET	(BASE_ADDR + 0x0f000809)

/* for RESET */
#define DSIURESET	BIT1	/*  DSIU��ꥻ�åȤ���ե饰  */

#endif /* _VR4131_H_ */
