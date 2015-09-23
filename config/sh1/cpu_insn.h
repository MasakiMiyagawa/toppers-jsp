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
 *  @(#) $Id: cpu_insn.h,v 1.2 2001/10/22 02:16:43 imai Exp $
 */

#ifndef	_CPU_INSN_H_
#define	_CPU_INSN_H_

/*
 *  ����쥸���������ؿ�
 */

/*
 *  ���ơ������쥸������SR�ˤθ����ͤ��ɽФ�
 */
Inline UW
current_sr(void)
{
	UW sr;
	Asm("stc  sr,%0" : "=r"(sr));
	return(sr);
}


/*
 *  ���ơ������쥸������SR�ˤθ����ͤ��ѹ�
 */
Inline void
set_sr(UW sr)
{
	Asm("ldc %0, sr" : : "r"(sr) );
}


/*
 *  NMI�ȥǥХå���������٤Ƥγ���ߤ�ػ�
 */
Inline void
disint(void)
{
    set_sr((current_sr() & ~0x000000f0) |  MAX_IPM << 4 );
}


/*
 *  ���٤Ƥγ���ߤ����
 */
Inline void
enaint()
{
	set_sr(current_sr() & ~0x000000f0);
}

/*
 *  �٥����١����쥸������VBR�ˤθ����ͤ��ɽФ�
 */
Inline VP
*current_vbr(void)
{
	VP vbr;
	Asm("stc vbr,%0" : "=r"(vbr));
	return(vbr);
}


/*
 *  �٥����١����쥸������VBR�ˤ�����
 */
Inline void
set_vbr(VP vbr)
{
	Asm("ldc  %0, vbr" : : "r"(vbr) );
}


#endif /* _CPU_INSN_H_ */
