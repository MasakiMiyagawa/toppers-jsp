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
 *  @(#) $Id: cpu_defs.h,v 1.4 2001/11/15 13:18:32 takayuki Exp $
 */

/*
 *	�ץ��å��˰�¸���������V850�ѡ�
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#define V850

	/* �ä˲���̵���Ȥ���PSW���� */
#define DEFAULT_PSW	0x0

	/* ������װ��ֹ� */
#define INT_RESET	0
#define INT_NMI		1
#define INT_WDT		2
#define INT_TRAP0	4
#define INT_TRAP1	5
#define INT_ILGOP	6
#define INT_WDTM	8
#define INT_P0		9
#define INT_P1		10
#define INT_P2		11
#define INT_P3		12
#define INT_P4		13
#define INT_P5		14
#define INT_P6		15
#define INT_WTI		16
#define INT_TM00	17
#define INT_TM01	18
#define INT_TM10	19
#define INT_TM11	20
#define INT_TM2		21
#define INT_TM3		22
#define INT_TM4		23
#define INT_TM5		24
#define INT_CSI0	25
#define INT_SER0	26
#define INT_CSI1	27
#define INT_ST0		28
#define INT_CSI2	29
#define INT_SER1	30
#define INT_SR1		31
#define INT_ST1		32
#define INT_AD		33
#define INT_DMA0	34
#define INT_DMA1	35
#define INT_DMA2	36
#define INT_WT		37



#ifndef _MACRO_ONLY

typedef	UINT		INHNO;		/* ����ߥϥ�ɥ��ֹ� */
typedef	UB			IPR;		/* �����ͥ���� */
typedef	UINT		EXCNO;		/* CPU�㳰�ϥ�ɥ��ֹ� */

#endif /* _MACRO_ONLY */
#endif /* _CPU_DEFS_H_ */
