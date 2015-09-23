/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: sys_manage.c,v 1.4 2002/03/26 08:19:38 hiro Exp $
 */

/*
 *	�����ƥ���ִ�����ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

/*
 *  ��������ͥ���̤β�ž
 */
SYSCALL ER
rot_rdq(PRI tskpri)
{
	UINT	pri;

	CHECK_TSKCTX_UNL();
	CHECK_TPRI_SELF(tskpri);

	t_lock_cpu();
	pri = (tskpri == TPRI_SELF) ? runtsk->priority : INT_PRIORITY(tskpri);
	if (rotate_ready_queue(pri)) {
		dispatch();
	}
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  ��������ͥ���̤β�ž���󥿥�������ƥ������ѡ�
 */
SYSCALL ER
irot_rdq(PRI tskpri)
{
	CHECK_INTCTX_UNL();
	CHECK_TPRI(tskpri);

	i_lock_cpu();
	if (rotate_ready_queue(INT_PRIORITY(tskpri))) {
		reqflg = TRUE;
	}
	i_unlock_cpu();
	return(E_OK);
}

/*
 *  �¹Ծ��֤Υ�����ID�λ���
 */
SYSCALL ER
get_tid(ID *p_tskid)
{
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	*p_tskid = TSKID(runtsk);
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  �¹Ծ��֤Υ�����ID�λ��ȡ��󥿥�������ƥ������ѡ�
 */
SYSCALL ER
iget_tid(ID *p_tskid)
{
	CHECK_INTCTX_UNL();

	i_lock_cpu();
	*p_tskid = (runtsk == NULL) ? TSK_NONE : TSKID(runtsk);
	i_unlock_cpu();
	return(E_OK);
}

/*
 *  CPU��å����֤ؤΰܹ�
 */
SYSCALL ER
loc_cpu(void)
{
	CHECK_TSKCTX();

	if (!(t_sense_lock())) {
		t_lock_cpu();
	}
	return(E_OK);
}

/*
 *  CPU��å����֤ؤΰܹԡ��󥿥�������ƥ������ѡ�
 */
SYSCALL ER
iloc_cpu(void)
{
	CHECK_INTCTX();

	if (!(i_sense_lock())) {
		i_lock_cpu();
	}
	return(E_OK);
}

/*
 *  CPU��å����֤β��
 *
 *  CPU��å���ϡ��ǥ����ѥå���ɬ�פȤʤ륵���ӥ��������ƤӽФ���
 *  �ȤϤǤ��ʤ����ᡤCPU��å����֤β�����˥ǥ����ѥå����ư����
 *  ɬ�פϤʤ���
 */
SYSCALL ER
unl_cpu(void)
{
	CHECK_TSKCTX();

	if (t_sense_lock()) {
		t_unlock_cpu();
	}
	return(E_OK);
}

/*
 *  CPU��å����֤β�����󥿥�������ƥ������ѡ�
 *
 *  CPU��å���ϡ��ǥ����ѥå���ɬ�פȤʤ륵���ӥ��������ƤӽФ���
 *  �ȤϤǤ��ʤ����ᡤCPU��å����֤β�����˥ǥ����ѥå���ε�ư����
 *  �᤹��ɬ�פϤʤ���
 */
SYSCALL ER
iunl_cpu(void)
{
	CHECK_INTCTX();

	if (i_sense_lock()) {
		i_unlock_cpu();
	}
	return(E_OK);
}

/*
 *  �ǥ����ѥå��ζػ�
 */
SYSCALL ER
dis_dsp(void)
{
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	enadsp = FALSE;
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  �ǥ����ѥå��ε���
 */
SYSCALL ER
ena_dsp(void)
{
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	enadsp = TRUE;
	if (runtsk != schedtsk) {
		dispatch();
	}
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  ����ƥ����Ȥλ���
 */
SYSCALL BOOL
sns_ctx()
{
	return(sense_context() ? TRUE : FALSE);
}

/*
 *  CPU��å����֤λ���
 */
SYSCALL BOOL
sns_loc()
{
	return(sense_lock() ? TRUE : FALSE);
}

/*
 *  �ǥ����ѥå��ػ߾��֤λ���
 */
SYSCALL BOOL
sns_dsp()
{
	return(!(enadsp) ? TRUE : FALSE);
}

/*
 *  �ǥ����ѥå���α���֤λ���
 */
SYSCALL BOOL
sns_dpn()
{
	return((sense_context() || sense_lock() || !(enadsp)) ? TRUE : FALSE);
}
