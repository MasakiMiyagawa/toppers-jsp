/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001-2003 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: h8.h,v 1.4 2003/11/11 10:07:15 honda Exp $
 */

#ifndef _H8_H_
#define _H8_H_

/*
 *  H8 �����
 */

/*
 *  ���ͥǡ���ʸ�����ѥޥ���
 */

#define TO_STRING(arg)	#arg
#define _TO_STRING(arg)	TO_STRING(arg)

/* Condition Code Register (CCR) */

#define H8CCR_I_BIT		7
#define H8CCR_UI_BIT		6
#define H8CCR_H_BIT		5
#define H8CCR_U_BIT		4
#define H8CCR_N_BIT		3
#define H8CCR_Z_BIT		2
#define H8CCR_V_BIT		1
#define H8CCR_C_BIT		0

#define H8CCR_I			(1<<H8CCR_I_BIT)
#define H8CCR_UI		(1<<H8CCR_UI_BIT)
#define H8CCR_H			(1<<H8CCR_H_BIT)
#define H8CCR_U			(1<<H8CCR_U_BIT)
#define H8CCR_N			(1<<H8CCR_N_BIT)
#define H8CCR_Z			(1<<H8CCR_Z_BIT)
#define H8CCR_V			(1<<H8CCR_V_BIT)
#define H8CCR_C			(1<<H8CCR_C_BIT)

/* CCR �� UI �ӥåȤ�����ߥޥ����ӥåȤȤ��ƻ��Ѥ��롣*/

#define H8INT_MASK_ALL		H8CCR_UI

#define H8INT_DIS_ALL		H8INT_MASK_ALL
#define H8INT_ENA_ALL		(~(H8INT_MASK_ALL))

#define str_H8INT_DIS_ALL	_TO_STRING(H8INT_DIS_ALL)
#define str_H8INT_ENA_ALL	_TO_STRING(H8INT_ENA_ALL)

/*
 *  SCI ����������ޥ���
 */

#define H8BRR_RATE(b)		((b)>38400?((UB)(((CPU_CLOCK+(16*(b)))/(32*(b)))-1))\
				          :((UB)((CPU_CLOCK/(32*(b)))-1)))
#define SCI_SETUP_COUNT(b)	((CPU_CLOCK)/(b)/5)

/* port access */

#define inb(p)			(*(volatile UB*)(p))
#define inw(p)			(*(volatile UH*)(p))
#define outb(p,d)		(*(volatile UB*)(p)=(d))
#define outw(p,d)		(*(volatile UH*)(p)=(d))

#endif /* _H8_H_ */
