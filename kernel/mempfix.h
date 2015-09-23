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
 *  @(#) $Id: mempfix.h,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	����Ĺ����ס��뵡ǽ
 */

#ifndef _MEMPFIX_H_
#define _MEMPFIX_H_

#include "queue.h"

/*
 *  ����Ĺ����ס��������֥�å�
 */
typedef struct fixed_memorypool_initialization_block {
	ATR	mpfatr;		/* ����Ĺ����ס���°�� */
	UINT	blksz;		/* ����֥�å��Υ������ʴݤ᤿�͡� */
	VP	mpf;		/* ����Ĺ����ס����ΰ����Ƭ���� */
	VP	limit;		/* ����Ĺ����ס����ΰ�ξ������ */
} MPFINIB;

/*
 *  ���֥�å��ꥹ�Ȥ����
 */
typedef struct free_list {
	struct free_list *next;
} FREEL;

/*
 *  ����Ĺ����ס�������֥�å�
 */
typedef struct fixed_memorypool_control_block {
	QUEUE	wait_queue;	/* ����Ĺ����ס����Ԥ����塼 */
	const MPFINIB *mpfinib;	/* ����Ĺ����ס��������֥�å� */
	VP	unused;		/* ̤�����ΰ����Ƭ���� */
	FREEL	*freelist;	/* �����֥�å��Υꥹ�� */
} MPFCB;

/*
 *  ����Ĺ����ס��뵡ǽ�ν����
 */
extern void	mempfix_initialize(void);

#endif /* _MEMPFIX_H_ */
