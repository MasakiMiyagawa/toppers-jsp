/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: makeoffset.c,v 1.3 2001/11/12 14:19:34 hiro Exp $
 */


#include "jsp_kernel.h"
#include "task.h"

#define offsetof(structure, field) \
                        ((INT) &(((structure *) 0)->field))

#define OFFSET_DEF(TYPE, FIELD)						\
	Asm("! BEGIN\n" #TYPE "_" #FIELD " = %0\n\t! END"		\
	  : /* no output */						\
	  : "g"(offsetof(TYPE, FIELD)))

#define OFFSET_DEF2(TYPE, FIELD, FIELDNAME)				\
	Asm("! BEGIN\n" #TYPE "_" #FIELDNAME " = %0\n\t! END"		\
	  : /* no output */						\
	  : "g"(offsetof(TYPE, FIELD)))

void
makeoffset()
{
        OFFSET_DEF2(TCB, tinib, tinib);
        OFFSET_DEF2(TINIB, task, task);
        OFFSET_DEF2(TINIB, exinf, exinf);
	OFFSET_DEF(TCB, texptn);

	OFFSET_DEF2(TCB, tskctxb.sp, sp);
        OFFSET_DEF2(TCB, tskctxb.pc, pc);
}

asm("! BIT_REF");
UW	ref_4 = 0;
UH	ref_2 = 0;
UB	ref_1 = 0;
asm("! END");

asm("! BIT_BB");
TCB	TCB_enatex = {
		{ NULL, NULL }, NULL, 0, 0,
		FALSE, FALSE, TRUE,
		0, NULL, { NULL, NULL }
	};
asm("! END");
