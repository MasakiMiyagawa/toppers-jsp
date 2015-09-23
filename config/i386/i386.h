/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2002 by Monami software, Limited Partners.
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
 *  @(#) $Id: i386.h,v 1.3 2002/04/06 12:23:01 honda Exp $
 */

#ifndef	_I386_H_
#define	_I386_H_

/* Segment type */
#define	I386_TYPE_SEG_DATA       (0x00) /* 0000	�ǡ����������� */
#define	I386_TYPE_SEG_EXPAND     (0x04) /* 0100 �������ѥ�ɥ����� */
#define	I386_TYPE_SEG_WRITEABLE  (0x02) /* 0010 �񤭹��߲� */
#define	I386_TYPE_SEG_ACCESSED   (0x01) /* 0001 �����������줿���� */
#define	I386_TYPE_SEG_CODE       (0x08) /* 1000 �����ɥ������� */

#define	I386_TYPE_SEG_CONFORMING (0x04) /* 0100 ����ե����ߥ� */
#define	I386_TYPE_SEG_READABLE   (0x02) /* 0010 �ɤ߼��� */
#define	I386_TYPE_SEG_ACCESSED   (0x01) /* 0001 �����������줿���� */

/* Gate type */
#define	I386_TYPE_GATE_INTR		0xe
#define	I386_TYPE_GATE_TRAP		0xf

/* Segment descriptor */
typedef struct __i386_segment_descriptor {
	unsigned	limit_L:16;
	unsigned	base_L:24 __attribute__ ((packed));
	unsigned	type:4;
	unsigned	s:1;
	unsigned	dpl:2;
	unsigned	p:1;
	unsigned	limit_H:4;
	unsigned	avl:1;
	unsigned	x:1;
	unsigned	db:1;
	unsigned	g:1;
	unsigned	base_H:8;
} SEGDESC;

/* Gate descriptor */
typedef struct __i386_gate_descriptor {
	unsigned	offset_L:16;
	unsigned	selector:16;
	unsigned	copy:8;
	unsigned	type:4;
	unsigned	s:1;
	unsigned	dpl:2;
	unsigned	p:1;
	unsigned	offset_H:16;
} GATEDESC;

typedef	struct {
	unsigned	limit:16;
	unsigned	base:32 __attribute__ ((packed));
} DESCPTR;

#endif	/* _I386_H_ */
