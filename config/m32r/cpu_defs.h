/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cpu_defs.h,v 1.2 2002/04/05 09:01:40 takayuki Exp $
 */

/*
 *	�ץ��å��˰�¸���������M32R�ѡ�
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#define M32R

	/* �ä˲���̵���Ȥ���PSW���� */
#define DEFAULT_PSW	0x0007c0c0	//�桼�������å� + ����ߵ��� + ����ߥޥ���7

	/* �㳰�װ��ֹ� */
#define NUM_EXCEPTION 20

#define EXC_RESET	0
#define EXC_SBI		1
#define EXC_RIE		2
#define EXC_AE		3
#define EXC_TRAP00	4
#define EXC_TRAP01	5
#define EXC_TRAP02	6
#define EXC_TRAP03	7
#define EXC_TRAP04	8
#define EXC_TRAP05	9
#define EXC_TRAP06	10
#define EXC_TRAP07	11
#define EXC_TRAP08	12
#define EXC_TRAP09	13
#define EXC_TRAP10	14
#define EXC_TRAP11	15
#define EXC_TRAP12	16
#define EXC_TRAP13	17
#define EXC_TRAP14	18
#define EXC_TRAP15	19

	/* ������װ��ֹ� */
#define INT_INT0	1
#define INT_INT1	2
#define INT_INT2	3
#define INT_INT3	4
#define INT_INT4	5
#define INT_INT5	6
#define INT_INT6	7
#define INT_MFT0	16
#define INT_MFT1	17
#define INT_MFT2	18
#define INT_MFT3	19
#define INT_MFT4	20
#define INT_MFT5	21
#define INT_DMA0	32
#define INT_SIO0RCV	48
#define INT_SIO0XMT	49
#define INT_SIO1RCV	50
#define INT_SIO1XMT	51
#define INT_SIO2RCV	52
#define INT_SIO2XMT	53
#define INT_SIO3RCV	54
#define INT_SIO3XMT	55
#define INT_SIO4RCV	56
#define INT_SIO4XMT	57


#ifndef _MACRO_ONLY

typedef	UINT		INHNO;		/* ����ߥϥ�ɥ��ֹ� */
typedef	UB			IPR;		/* �����ͥ���� */
typedef	UINT		EXCNO;		/* CPU�㳰�ϥ�ɥ��ֹ� */

#endif /* _MACRO_ONLY */
#endif /* _CPU_DEFS_H_ */
