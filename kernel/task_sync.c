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
 *  @(#) $Id: task_sync.c,v 1.3 2002/03/26 08:19:38 hiro Exp $
 */

/*
 *	��������°Ʊ����ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"

/*
 *  �����Ԥ�
 */
SYSCALL ER
slp_tsk()
{
	WINFO	winfo;
	ER	ercd;

	CHECK_DISPATCH();

	t_lock_cpu();
	if (runtsk->wupcnt) {
		runtsk->wupcnt = FALSE;
		ercd = E_OK;
	}
	else {
		runtsk->tstat = (TS_WAITING | TS_WAIT_SLEEP);
		make_wait(&winfo);
		dispatch();
		ercd = winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �����Ԥ��ʥ����ॢ���Ȥ����
 */
SYSCALL ER
tslp_tsk(TMO tmout)
{
	WINFO	winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_TMOUT(tmout);

	t_lock_cpu();
	if (runtsk->wupcnt) {
		runtsk->wupcnt = FALSE;
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		runtsk->tstat = (TS_WAITING | TS_WAIT_SLEEP);
		make_wait_tmout(&winfo, &tmevtb, tmout);
		dispatch();
		ercd = winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �������ε���
 */
SYSCALL ER
wup_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if ((tstat & TS_WAIT_SLEEP) != 0) {
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (!(tcb->wupcnt)) {
		tcb->wupcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �������ε������󥿥�������ƥ������ѡ�
 */
SYSCALL ER
iwup_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if ((tstat & TS_WAIT_SLEEP) != 0) {
		if (wait_complete(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (!(tcb->wupcnt)) {
		tcb->wupcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	i_unlock_cpu();
	return(ercd);
}

/*
 *  �����������׵�Υ���󥻥�
 */
SYSCALL ER_UINT
can_wup(ID tskid)
{
	TCB	*tcb;
	ER_UINT	wupcnt;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		wupcnt = E_OBJ;
	}
	else {
		wupcnt = tcb->wupcnt ? 1 : 0;
		tcb->wupcnt = FALSE;
	}
	t_unlock_cpu();
	return(wupcnt);
}

/*
 *  �Ԥ����֤ζ������
 */
SYSCALL ER
rel_wai(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	t_lock_cpu();
	if (!(TSTAT_WAITING(tcb->tstat))) {
		ercd = E_OBJ;
	}
	else {
		if (wait_release(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �Ԥ����֤ζ���������󥿥�������ƥ������ѡ�
 */
SYSCALL ER
irel_wai(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (!(TSTAT_WAITING(tcb->tstat))) {
		ercd = E_OBJ;
	}
	else {
		if (wait_release(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	i_unlock_cpu();
	return(ercd);
}

/*
 *  �����Ԥ����֤ؤΰܹ�
 */
SYSCALL ER
sus_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (tcb == runtsk && !(enadsp)) {
		ercd = E_CTX;
	}
	else if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(tstat)) {
		/*
		 *  �¹ԤǤ�����֤��鶯���Ԥ����֤ؤ�����
		 */
		tcb->tstat = TS_SUSPENDED;
		if (make_non_runnable(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (TSTAT_SUSPENDED(tstat)) {
		ercd = E_QOVR;
	}
	else {
		/*
		 *  �Ԥ����֤�������Ԥ����֤ؤ�����
		 */
		tcb->tstat |= TS_SUSPENDED;
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �����Ԥ����֤���κƳ�
 */
SYSCALL ER
rsm_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	t_lock_cpu();
	if (!(TSTAT_SUSPENDED(tstat = tcb->tstat))) {
		ercd = E_OBJ;
	}
	else if (!(TSTAT_WAITING(tstat))) {
		/*
		 *  �����Ԥ����֤���¹ԤǤ�����֤ؤ�����
		 */
		if (make_runnable(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		/*
		 *  ����Ԥ����֤����Ԥ����֤ؤ�����
		 */
		tcb->tstat &= ~TS_SUSPENDED;
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �����Ԥ����֤���ζ����Ƴ�
 *
 *  JSP�����ͥ�Ǥϡ�frsm_tsk �� rsm_tsk ��Ʊ��ν����Ȥʤ롥
 */
#ifdef LABEL_ALIAS
LABEL_ALIAS(frsm_tsk, rsm_tsk)
#else /* LABEL_ALIAS */

SYSCALL ER
frsm_tsk(ID tskid)
{
	return(rsm_tsk(tskid));
}

#endif /* LABEL_ALIAS */

/*
 *  �����������ٱ�
 */
SYSCALL ER
dly_tsk(RELTIM dlytim)
{
	WINFO	winfo;
	TMEVTB	tmevtb;

	CHECK_DISPATCH();
	CHECK_PAR(dlytim <= TMAX_RELTIM);

	t_lock_cpu();
	runtsk->tstat = TS_WAITING;
	make_non_runnable(runtsk);
	runtsk->winfo = &winfo;
	winfo.tmevtb = &tmevtb;
	tmevtb_enqueue(&tmevtb, dlytim, (CBACK) wait_tmout_ok, (VP) runtsk);
	dispatch();
	t_unlock_cpu();
	return(winfo.wercd);
}
