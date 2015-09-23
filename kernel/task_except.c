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
 *  @(#) $Id: task_except.c,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	�������㳰������ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

/*
 *  �������㳰�������׵�
 */
SYSCALL ER
ras_tex(ID tskid, TEXPTN rasptn)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_PAR(rasptn != 0);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat) || tcb->tinib->texrtn == NULL) {
		ercd = E_OBJ;
	}
	else if (tcb == runtsk && runtsk->enatex) {
		/*
		 *  ���ξ��֤Ǥϡ�runtsk->texptn �� 0 �ˤʤäƤ��롥��
		 *  ���ʤ顤�⤷�����Ǥʤ���С���������˥������㳰��
		 *  ���롼���󤬸ƤӽФ���Ƥ���Ϥ��Ǥ��롥
		 */
		assert(runtsk->texptn == 0);
		runtsk->enatex = FALSE;
		t_unlock_cpu();
		(*runtsk->tinib->texrtn)(rasptn, runtsk->tinib->exinf);
		t_lock_cpu();

		call_texrtn();
		ercd = E_OK;
	}
	else {
		tcb->texptn |= rasptn;
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �������㳰�������׵���󥿥�������ƥ������ѡ�
 */
SYSCALL ER
iras_tex(ID tskid, TEXPTN rasptn)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	CHECK_PAR(rasptn != 0);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat) || tcb->tinib->texrtn == NULL) {
		ercd = E_OBJ;
	}
	else {
		tcb->texptn |= rasptn;
		if (tcb == runtsk && runtsk->enatex) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	i_unlock_cpu();
	return(ercd);
}

/*
 *  �������㳰�����ζػ�
 */
SYSCALL ER
dis_tex()
{
	ER	ercd;

	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	if (runtsk->tinib->texrtn == NULL) {
		ercd = E_OBJ;
	}
	else {
		runtsk->enatex = FALSE;
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �������㳰�����ε���
 */
SYSCALL ER
ena_tex()
{
	ER	ercd;

	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	if (runtsk->tinib->texrtn == NULL) {
		ercd = E_OBJ;
	}
	else {
		/*
		 *  ���ξ��֤Ǥϡ�runtsk->texptn �� 0 ����
		 *  runtsk->enatex �� FALSE �Τ����줫������Ω�ġ��ʤ�
		 *  �ʤ顤�⤷�����Ǥʤ���С���������˥������㳰����
		 *  �롼���󤬸ƤӽФ���Ƥ���Ϥ��Ǥ��롥
		 */
		call_texrtn();
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �������㳰�����ػ߾��֤λ���
 */
SYSCALL BOOL
sns_tex()
{
	return((runtsk != NULL && runtsk->enatex) ? FALSE : TRUE);
}
