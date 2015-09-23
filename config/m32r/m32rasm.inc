/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: m32rasm.inc,v 1.6 2003/12/24 07:35:03 takayuki Exp $
 */

#ifndef __M32RASM_INC
#define __M32RASM_INC

/*
 * 32�ӥå�¨�ͥ����� (¨�� & ����ܥ�)
 */

	.macro	lea reg, value
		seth	\reg, #shigh(\value)
		or3		\reg, \reg, #low(\value)
	.endm

/*
 * �ơ��֥���� 32�ӥå� ������ - �ޥ�����
 *    1�롼�����3�İʾ�32�ӥå�¨�ͤ�����ʤ�ơ��֥��
 *    3�İʾ�Υ롼���󤫤������륷��ܥ��ơ��֥��
 */

		//�ơ��֥���� ����
	.macro	begin_table
		.section ".rodata","a"
		.align   4
	_table_base:
	.endm

		//�ơ��֥륨��ȥ����
	.macro	entry	symbol
					.extern	\symbol
		p_\symbol:	.long	\symbol
	.endm

		//�ơ��֥���� ��λ
	.macro	end_table
	.endm

		//�ơ��֥��Υ���ܥ뻲��
	.macro	lds	dest, index, symbol
		ld	\dest, @(p_\symbol - _table_base, \index)
	.endm

		//�ơ��֥륤��ǥå����λ���
	.macro	ldidx dest
/*		bl	1f
			.long	_table_base
		1:	ld	r14, @r14 */
		seth	\dest, #shigh(_table_base)
		or3		\dest, \dest, #low(_table_base)
	.endm

/*
 * ����ߵ���
 *  �����ϤĤ֤��Ƥ⤤���쥸����
 */
	.macro	ei work=r0
		mvfc	\work, psw
		or3		\work, \work, 0x40
		mvtc	\work, psw
	.endm

/*
 * ����߶ػ�
 *  �����ϤĤ֤��Ƥ⤤���쥸����
 */
	.macro	di work=r0
		mvfc	\work, psw
		and3	\work, \work, 0xcf
		mvtc	\work, psw
	.endm

/* �������Ȳ�ǽ�ʥ���ܥ�κ��� */
	.macro Label name
		.globl \name
		\name:
	.endm

/* �ؿ�����ȥ�κ��� */
	.macro Function name
		.text
		.align 4
		.globl \name
		\name:
	.endm

/* �ؿ���������� */
	.macro rts
		jmp  r14
	.endm

/* �ؿ��ƽ� */
	.macro call \name
		st	r14,@-r15
		bl	\name
	.endm

/* �����å��Ѥ� */
	.macro stmdb regset
		.irp reg, \regset
			st	\reg, @-r15
		.endr
	.endm

/* �����å��ᤷ */
	.macro ldmia regset
		.irp reg, \regset
			ld	\reg, @r15+
		.endr
	.endm

#endif