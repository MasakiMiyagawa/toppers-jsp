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
 *  @(#) $Id: task_manage.c,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	������������ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"

/*
 *  �������ε�ư
 */
SYSCALL ER
act_tsk(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		if (make_active(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (!(tcb->actcnt)) {
		tcb->actcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �������ε�ư���󥿥�������ƥ������ѡ�
 */
SYSCALL ER
iact_tsk(ID tskid)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_INTCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);

	i_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		if (make_active(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (!(tcb->actcnt)) {
		tcb->actcnt = TRUE;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	i_unlock_cpu();
	return(ercd);
}

/*
 *  ��������ư�׵�Υ���󥻥�
 */
SYSCALL ER_UINT
can_act(ID tskid)
{
	TCB	*tcb;
	UINT	actcnt;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	actcnt = tcb->actcnt ? 1 : 0;
	tcb->actcnt = FALSE;
	t_unlock_cpu();
	return(actcnt);
}

/*
 *  ���������ν�λ
 */
SYSCALL void
ext_tsk()
{
#ifdef ACTIVATED_STACK_SIZE
	/*
	 *  create_context �� activate_context �ǡ�������Υ����å���
	 *  ����˲����ʤ��褦�ˡ������å���˥��ߡ��ΰ����ݤ��롥
	 */
	(void) alloca(ACTIVATED_STACK_SIZE);
#endif /* ACTIVATED_STACK_SIZE */

	if (sense_context()) {
		/*
		 *  �󥿥�������ƥ����Ȥ��� ext_tsk ���ƤФ줿��硤
		 *  ����Ū�˥���������ƥ����Ȥ��ڤ괹���Ƽ¹Ԥ��³��
		 *  �뤬���������åȤˤ�äƤ��󥿥�������ƥ������Ѥ�
		 *  �����å��˥��ߤ��Ĥ��礬���롥
		 */
		syslog(LOG_ALERT, "ext_tsk reports E_CTX.");
	}
	if (t_sense_lock()) {
		/*
		 *  CPU��å����֤� ext_tsk ���ƤФ줿���ϡ�CPU���
		 *  ���������Ƥ��饿������λ���롥������ϡ�������
		 *  ����������Ǥ�CPU��å����ά����Ф褤������
		 */
		syslog(LOG_WARNING, "ext_tsk reports E_CTX.");
	}
	else {
		t_lock_cpu();
	}
	if (!(enadsp)) {
		/*
		 *  �ǥ����ѥå��ػ߾��֤� ext_tsk ���ƤФ줿���ϡ�
		 *  �ǥ����ѥå����ľ��֤ˤ��Ƥ��饿������λ���롥
		 */
		syslog(LOG_WARNING, "ext_tsk reports E_CTX.");
		enadsp = TRUE;
	}
	exit_task();
}

/*
 *  �������ζ�����λ
 */
SYSCALL ER
ter_tsk(ID tskid)
{
	TCB	*tcb;
	UINT	tstat;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID(tskid);
	tcb = get_tcb(tskid);
	CHECK_NONSELF(tcb);

	t_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		if (TSTAT_RUNNABLE(tstat)) {
			make_non_runnable(tcb);
		}
		else if (TSTAT_WAITING(tstat)) {
			wait_cancel(tcb);
		}
		make_dormant(tcb);
		if (tcb->actcnt) {
			tcb->actcnt = FALSE;
			if (make_active(tcb)) {
				dispatch();
			}
		}
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ������ͥ���٤��ѹ�
 */
SYSCALL ER
chg_pri(ID tskid, PRI tskpri)
{
	TCB	*tcb;
	UINT	newpri;
	UINT	tstat;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	CHECK_TPRI_INI(tskpri);
	tcb = get_tcb_self(tskid);
	newpri = (tskpri == TPRI_INI) ? tcb->tinib->ipriority
					: INT_PRIORITY(tskpri);

	t_lock_cpu();
	if (TSTAT_DORMANT(tstat = tcb->tstat)) {
		ercd = E_OBJ;
	}
	else if (TSTAT_RUNNABLE(tstat)) {
		if (change_priority(tcb, newpri)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		tcb->priority = newpri;
		if ((tstat & TS_WAIT_WOBJCB) != 0) {
			wobj_change_priority(((WINFO_WOBJ *)(tcb->winfo))
							->wobjcb, tcb);
		}
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ������ͥ���٤λ���
 */
SYSCALL ER
get_pri(ID tskid, PRI *p_tskpri)
{
	TCB	*tcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_TSKID_SELF(tskid);
	tcb = get_tcb_self(tskid);

	t_lock_cpu();
	if (TSTAT_DORMANT(tcb->tstat)) {
		ercd = E_OBJ;
	}
	else {
		*p_tskpri = EXT_TSKPRI(tcb->priority);
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}
