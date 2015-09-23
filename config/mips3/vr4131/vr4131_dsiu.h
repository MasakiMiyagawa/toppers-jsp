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

#ifndef _VR4131_DSIU_H_
#define _VR4131_DSIU_H_

#include <t_config.h>

/*
 *  VR4131��¢�ǥХå����ꥢ�륤�󥿥ե�������˥å�(DSIU)��Ϣ�����
 *  (�ʰ�NS16550)
 */

/* DSIU�쥸�����Υ��ɥ쥹 */
#define DSIURB		(BASE_ADDR + 0x0f000820)	/* �����Хåե��쥸����(�꡼�ɻ�) */
#define DSIUTH		(BASE_ADDR + 0x0f000820)	/* �����ݻ��쥸����(�饤�Ȼ�) */
#define DSIUDLL		(BASE_ADDR + 0x0f000820)	/* ʬ���沼�̥쥸���� */
#define DSIUIE		(BASE_ADDR + 0x0f000821)	/* ����ߵ��ĥ쥸���� */
#define DSIUDLM		(BASE_ADDR + 0x0f000821)	/* ʬ�����̥쥸���� */
#define DSIUIID		(BASE_ADDR + 0x0f000822)	/* �����ɽ���쥸����(�꡼�ɻ�) */
#define DSIUFC		(BASE_ADDR + 0x0f000822)	/* FIFO ����쥸����(�饤�Ȼ�) */
#define DSIULC		(BASE_ADDR + 0x0f000823)	/* �饤������쥸���� */
#define DSIUMC		(BASE_ADDR + 0x0f000824)	/* ��ǥ�����쥸���� */
#define DSIULS		(BASE_ADDR + 0x0f000825)	/* �饤����֥쥸���� */
#define DSIUMS		(BASE_ADDR + 0x0f000826)	/* ��ǥ���֥쥸���� */
#define DSIUSC		(BASE_ADDR + 0x0f000827)	/* ������å��쥸���� */

/* for DSIULC */
#define	WORD_LENGTH_8		BIT1 | BIT0
#define	STOP_BITS_1		0		/* BIT2 */
#define	PARITY_NON		0		/* BIT3, 4 */
/* BIT5,6 ��ά */
#define	DIVISOR_LATCH_ACC	BIT7

/* for DSIUIE */
#define	DIS_INT			0
#define	RECEIVE_DATA_AVAILABLE	BIT0
#define	TRANS_REG_EMPTY		BIT1
#define RECEIVE_LINE_STATUS	BIT2
#define MODEM_STATUS		BIT3

/* for DSIUMC */
#define	DTR			BIT0
#define	RTS			BIT1

/* for DSIUFC */
#define	FIFO_ENABLE		BIT0
#define	RECEIVE_FIFO_RESET	BIT1
#define	TRANS_FIFO_RESET	BIT2
#define RECEIVE_TRIG_1_BYTE	0	/* BIT6, 7 */
#define RECEIVE_TRIG_4_BYTE	BIT6
#define	RECEIVE_TRIG_8_BYTE	BIT7
#define	RECEIVE_TRIG_14_BYTE	BIT6 | BIT7

/* for DSIUIID */
#define	INT_MASK		0x0e
#define	INT_RECEIVE_DATA	BIT2
#define INT_CHAR_TIME_OUT	BIT3 | BIT2
#define	INT_TRANS_EMPTY		BIT1

/* �ܡ��졼������ط� */
#define	DIVISOR			XIN_CLOCK / (16 * DEVIDE_RATIO)

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
typedef struct sio_port_control_block	SIOPCB;

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_ERDY_SND	1u		/* ������ǽ������Хå� */
#define SIO_ERDY_RCV	2u		/* �������Υ�����Хå� */

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void	vr4131_dsiu_initialize(void);

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
extern BOOL	vr4131_dsiu_openflag(void);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB	*vr4131_dsiu_opn_por(ID siopid, VP_INT exinf);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void	vr4131_dsiu_cls_por(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern BOOL	vr4131_dsiu_snd_chr(SIOPCB *siopcb, char c);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern INT	vr4131_dsiu_rcv_chr(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void	vr4131_dsiu_ena_cbr(SIOPCB *siopcb, UINT cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void	vr4131_dsiu_dis_cbr(SIOPCB *siopcb, UINT cbrtn);

/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
extern void	vr4131_dsiu_dsiu_isr(void);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void	vr4131_dsiu_ierdy_snd(VP_INT exinf);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void	vr4131_dsiu_ierdy_rcv(VP_INT exinf);

/*============================================================================*/
/* �ʲ��ϡ�������vr4131_dsiu_sil.h�Ȥ����ե����������٤����Ȼפ��� */

/*
 *  �ǥХ����쥸�����Υ��������ֳֻ��֡�nsecñ�̡�
 */
#define	VR4131_DSIU_DELAY	100u		/* �ͤ˺���Ϥʤ� */

/*
 *  �ǥХ����쥸�����Υ��������ֳֻ��֡ʥݡ���󥰽��ϸ�����nsecñ�̡�
 *
 *  �������㡧��ư���ΥХʡ�����
 *  ���ͤϡ�kseg1(����å���ͭ����)�Ǥ�ư����ˡ�ʸ������Ȥ��ʤ����٤�����
 *  ��kseg0(����å���̵����)�Ǥ�ư����ϡ�
 *      VR4131_DSIU_DELAY_POR = 1000000u ���٤����ꤹ��ȡ����礦���ɤ���
 */
#define	VR4131_DSIU_DELAY_POR	100000000u

/*
 *  �ǥХ����쥸�����ؤΥ��������ؿ�
 */
Inline UB vr4131_dsiu_read_reg( VP reg ) {

	UB	val;

	/* �����ǡ�reg���ϰϥ����å���������Ф��줷���ʡ� */
	val = sil_reb_mem( reg );
	sil_dly_nse( VR4131_DSIU_DELAY );

	return( val );
}

Inline void vr4131_dsiu_write_reg( VP reg, UB val) {

	/* �����ǡ�reg���ϰϥ����å���������Ф��줷���ʡ� */
	sil_wrb_mem( reg, (VB) (val & 0x000000ff) );
	sil_dly_nse( VR4131_DSIU_DELAY );
}

/* �ݡ���󥰽��� sys_putc(c) ���� */
Inline void vr4131_dsiu_write_por( VP reg, UB val) {

	/* �����ǡ�reg���ϰϥ����å���������Ф��줷���ʡ� */
	sil_wrb_mem( reg, (VB) (val & 0x000000ff) );
	sil_dly_nse( VR4131_DSIU_DELAY_POR );
}

/*============================================================================*/
/* sys_config.c����(�ݡ���󥰽��ϻ��Ѥκ���¤�)���ꥢ�륳��ȥ���ν���� */
#define scc_init							\
	vr4131_dsiu_write_reg( (VP) DSIUIE,  DIS_INT );			\
	vr4131_dsiu_write_reg( (VP) DSIULC,  WORD_LENGTH_8 | STOP_BITS_1 | PARITY_NON | DIVISOR_LATCH_ACC ); \
	vr4131_dsiu_write_reg( (VP) DSIUDLL, LO8(DIVISOR) );		\
	vr4131_dsiu_write_reg( (VP) DSIUDLM, HI8(DIVISOR) );		\
	vr4131_dsiu_write_reg( (VP) DSIULC,  WORD_LENGTH_8 | STOP_BITS_1 | PARITY_NON ); \
	vr4131_dsiu_write_reg( (VP) DSIUIE,  RECEIVE_DATA_AVAILABLE)

#endif /* _VR4131_DSIU_H_ */
