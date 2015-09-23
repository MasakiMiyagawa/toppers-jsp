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
 *  @(#) $Id: cpu_insn.h,v 1.1 2000/11/14 14:44:14 hiro Exp $
 */

/*
 *	�ץ��å����ü�̿��Υ���饤��ؿ������68040�ѡ�
 */

#ifndef	_CPU_INSN_H_
#define	_CPU_INSN_H_

/*
 *  ���ơ������쥸������SR�ˤθ����ͤ��ɽФ�
 */
Inline UH
current_sr()
{
	UH	sr;

	Asm("move.w %%sr, %0" : "=g"(sr));
	return(sr);
}

/*
 *  ���ơ������쥸������SR�ˤθ����ͤ��ѹ�
 */
Inline void
set_sr(UH sr)
{
	Asm("move.w %0, %%sr" : : "g"(sr));
}

/*
 *  NMI��������٤Ƥγ���ߤ�ػ�
 */
Inline void
disint()
{
	Asm("or.w #0x0700, %sr");
}

/*
 *  ���٤Ƥγ���ߤ���Ķػ�
 */
Inline void
enaint()
{
	Asm("and.w #~0x0700, %sr");
}

/*
 *  �٥����١����쥸������VBR�ˤθ����ͤ��ɽФ�
 */
Inline VP
current_vbr()
{
	VP	vbr;

	Asm("movec.l %%vbr, %0" : "=r"(vbr));
	return(vbr);
}

/*
 *  �٥����١����쥸������VBR�ˤ�����
 */
Inline void
set_vbr(VP vbr)
{
	Asm("movec.l %0, %%vbr" : : "r"(vbr));
}

/*
 *  ��ǥ����塼�������Τ���Υӥåȥޥåץ������ؿ�
 *
 *  �ӥåȥޥåפβ���16�ӥåȤ���Ѥ����ǲ��̥ӥåȤ����ͥ���٤��б�
 *  �����롥
 */
#define	CPU_BITMAP_SEARCH
#define	PRIMAP_BIT(pri)		(0x8000u >> (pri))

Inline UINT
bitmap_search(UINT bitmap)
{
	INT	offset;

	Asm("bfffo %1{16,16}, %0" : "=d"(offset) : "g"(bitmap));
	return(offset - 16);
}

#endif /* _CPU_INSN_H_ */
