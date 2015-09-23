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
 *  @(#) $Id: exception.c,v 1.6 2002/03/26 08:19:38 hiro Exp $
 */

/*
 *	CPU�㳰������ǽ
 */

#include "jsp_kernel.h"
#include "task.h"
#include "exception.h"

/*
 *  CPU�㳰�ϥ�ɥ��ֹ�ο���kernel_cfg.c��
 */
extern const UINT	tnum_excno;

/*
 *  CPU�㳰�ϥ�ɥ������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const EXCINIB	excinib_table[];

/* 
 *  CPU�㳰�ϥ�ɥ������ǽ�ν����
 */
void
exception_initialize()
{
	UINT		i;
	const EXCINIB	*excinib;

	for (excinib = excinib_table, i = 0; i < tnum_excno; excinib++, i++) {
		define_exc(excinib->excno, excinib->exchdr);
	}
}

/*
 *  CPU�㳰��ȯ����������ƥ����Ȥλ���
 */
SYSCALL BOOL
vxsns_ctx(VP p_excinf)
{
	return(exc_sense_context(p_excinf) ? TRUE : FALSE);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
SYSCALL BOOL
vxsns_loc(VP p_excinf)
{
	return(exc_sense_lock(p_excinf) ? TRUE : FALSE);
}

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå��ػ߾��֤λ���
 *
 *  sns_dsp ��Ʊ��ν������ƤȤʤ롥
 */
SYSCALL BOOL
vxsns_dsp(VP p_excinf)
{
	return(!(enadsp) ? TRUE : FALSE);
}

/*
 *  CPU�㳰��ȯ���������Υǥ����ѥå���α���֤λ���
 */
SYSCALL BOOL
vxsns_dpn(VP p_excinf)
{
	return((exc_sense_context(p_excinf) || exc_sense_lock(p_excinf)
					|| !(enadsp)) ? TRUE : FALSE);
}

/*
 *  CPU�㳰��ȯ���������Υ������㳰�����ػ߾��֤λ���
 *
 *  sns_tex ��Ʊ��ν������ƤȤʤ롥
 */
SYSCALL BOOL
vxsns_tex(VP p_excinf)
{
	return((runtsk != NULL && runtsk->enatex) ? FALSE : TRUE);
}
