/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
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
 * 
 *  @(#) $Id: uart.h,v 1.1 2006/04/10 08:19:25 honda Exp $
 */

/*
 *  ��Ʊ���̿� (UART)���ꥢ������ͥ�ǥХ�����SIO�˥ɥ饤��
 *  ��Zup-F16��ĥ�ܡ����ѡ�
 */

#ifndef _UART_H_
#define _UART_H_

/*
 * ���ꥢ�륳��ȥ���쥸������������ 
 */
/* 19200bps = (6144000*4)/4/(BRCK)/(BRS+(16-BRK)/16)/16	*/
/* BRCK=4ʬ��,BRS=5�������,+(16-BRK)/16 ��̤���� */
#define	BRCR_19200  	(TBIT_SIOBRCK2 | 5)
#define	BRADD_19200		0
/* 38400bps = (6144000*4)/4/(BRCK)/(BRS+(16-BRK)/16)/16	*/
/* BRCK=1ʬ��,BRS=10�������,+(16-BRK)/16 ��̤���� */
#define	BRCR_38400		(TBIT_SIOBRCK0 | 10)
#define	BRADD_38400		0
#define	INT_LEVEL_UART	5		/* ����ߥ�٥� */

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define	INHNO_SERIAL_IN1	INT_NO_RX1
#define	INHNO_SERIAL_OUT1	INT_NO_TX1
#define INHNO_SERIAL_IN2	INT_NO_RX0
#define INHNO_SERIAL_OUT2	INT_NO_TX0

#ifndef _MACRO_ONLY

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å������
 */
typedef struct sio_port_initialization_block {
	UH  cntrl;		/* ����ȥ���쥸���������� */
	UH  hint;		/* ����ߥ쥸���������� */

	UB  pcrfc_def;		/* �ǥե�����Ȥ������� (P9CR/P9FC) */
	UB  scmod0_def;		/* �ǥե�����Ȥ������� (SCMOD0)	*/
	UB  sccr_def;		/* �ǥե�����Ȥ������� (SCCR)		*/
	UB  brcr_def;		/* �ǥե�����Ȥ������� (BRCR)		*/
	UB  bradd_def;		/* �ǥե�����Ȥ������� (BRADD)		*/
	UB  int_clr;		/* ������׵�ե饰���ꥢ���ޥ��	*/
} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block {
	const SIOPINIB	*siopinib;	/* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
	VP_INT			exinf;		/* ��ĥ���� */
	INT				rxb;		/* �����Хåե�	*/
	volatile UB		sts_flag;	/* �����Хåե����ե饰	*/
} SIOPCB;

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define UART_ERDY_SND		1u			/* ������ǽ������Хå�			*/
#define UART_ERDY_RCV		2u			/* �������Υ�����Хå�			*/

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void	uart_initialize(void);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB * uart_opn_por(ID siopid, VP_INT exinf);

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void	uart_cls_por(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern BOOL	uart_snd_chr(SIOPCB *siopcb, char c);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern INT	uart_rcv_chr(SIOPCB *siopcb);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void	uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void	uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void	uart_ierdy_snd(VP_INT exinf);

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void	uart_ierdy_rcv(VP_INT exinf);

#endif /* _MACRO_ONLY */
#endif /* _UART_H_ */

