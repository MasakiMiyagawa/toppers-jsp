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
 *  @(#) $Id: eventflag.c,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	���٥�ȥե饰��ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "eventflag.h"

/*
 *  ���٥�ȥե饰ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_flgid;

/*
 *  ���٥�ȥե饰������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const FLGINIB	flginib_table[];

/*
 *  ���٥�ȥե饰�����֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern FLGCB	flgcb_table[];

/*
 *  ���٥�ȥե饰ID���饤�٥�ȥե饰�����֥�å�����Ф�����Υޥ���
 */
#define INDEX_FLG(flgid)	((flgid) - TMIN_FLGID)
#define get_flgcb(flgid)	(&(flgcb_table[INDEX_FLG(flgid)]))

/*
 *  ���٥�ȥե饰�Ԥ�����֥�å������
 *
 *  flgptn �ϡ�waiptn ����� wfmode ��Ʊ���˻Ȥ����ȤϤʤ����ᡤunion 
 *  ��Ȥ��Х�������󤹤뤳�Ȥ���ǽ�Ǥ��롥
 */
typedef struct eventflag_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������ȤΥ���ȥ���֥�å� */
	FLGPTN	waiptn;		/* �Ԥ��ѥ����� */
	MODE	wfmode;		/* �Ԥ��⡼�� */
	FLGPTN	flgptn;		/* �Ԥ�������Υѥ����� */
} WINFO_FLG;

/*
 *  ���٥�ȥե饰��ǽ�ν����
 */
void
eventflag_initialize(void)
{
	INT	i;
	FLGCB	*flgcb;

	for(flgcb = flgcb_table, i = 0; i < tmax_flgid; flgcb++, i++) {
		queue_initialize(&(flgcb->wait_queue));
		flgcb->flginib = &(flginib_table[i]);
		flgcb->flgptn = flgcb->flginib->iflgptn;
	}
}

/*
 *  ���٥�ȥե饰�Ԥ�������Υ����å�
 */
static BOOL
eventflag_cond(FLGCB *flgcb, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	if ((wfmode & TWF_ORW) != 0 ? (flgcb->flgptn & waiptn) != 0
				: (flgcb->flgptn & waiptn) == waiptn) {
		*p_flgptn = flgcb->flgptn;
		if ((flgcb->flginib->flgatr & TA_CLR) != 0) {
			flgcb->flgptn = 0;
		}
		return(TRUE);
	}
	return(FALSE);
}

/*
 *  ���٥�ȥե饰�Υ��å�
 */
SYSCALL ER
set_flg(ID flgid, FLGPTN setptn)
{
	FLGCB	*flgcb;
	TCB	*tcb;
	WINFO_FLG *winfo;

	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	flgcb->flgptn |= setptn;
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		tcb = (TCB *)(flgcb->wait_queue.next);
		winfo = (WINFO_FLG *)(tcb->winfo);
		if (eventflag_cond(flgcb, winfo->waiptn,
					winfo->wfmode, &(winfo->flgptn))) {
			queue_delete(&(tcb->task_queue));
			if (wait_complete(tcb)) {
				dispatch();
			}
		}
	}
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  ���٥�ȥե饰�Υ��åȡ��󥿥�������ƥ������ѡ�
 */
SYSCALL ER
iset_flg(ID flgid, FLGPTN setptn)
{
	FLGCB	*flgcb;
	TCB	*tcb;
	WINFO_FLG *winfo;

	CHECK_INTCTX_UNL();
	CHECK_FLGID(flgid);
	flgcb = get_flgcb(flgid);

	i_lock_cpu();
	flgcb->flgptn |= setptn;
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		tcb = (TCB *)(flgcb->wait_queue.next);
		winfo = (WINFO_FLG *)(tcb->winfo);
		if (eventflag_cond(flgcb, winfo->waiptn,
					winfo->wfmode, &(winfo->flgptn))) {
			queue_delete(&(tcb->task_queue));
			if (wait_complete(tcb)) {
				reqflg = TRUE;
			}
		}
	}
	i_unlock_cpu();
	return(E_OK);
}

/*
 *  ���٥�ȥե饰�Υ��ꥢ
 */
SYSCALL ER
clr_flg(ID flgid, FLGPTN clrptn)
{
	FLGCB	*flgcb;

	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	flgcb->flgptn &= clrptn; 
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  ���٥�ȥե饰�Ԥ�
 */
SYSCALL ER
wai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	FLGCB	*flgcb;
	WINFO_FLG winfo;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0);
	CHECK_PAR((wfmode & ~TWF_ORW) == 0);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		ercd = E_ILUSE;
	}
	else if (eventflag_cond(flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else {
		winfo.waiptn = waiptn;
		winfo.wfmode = wfmode;
		wobj_make_wait((WOBJCB *) flgcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		*p_flgptn = winfo.flgptn;
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ���٥�ȥե饰�Ԥ��ʥݡ���󥰡�
 */
SYSCALL ER
pol_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn)
{
	FLGCB	*flgcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0);
	CHECK_PAR((wfmode & ~TWF_ORW) == 0);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		ercd = E_ILUSE;
	}
	else if (eventflag_cond(flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ���٥�ȥե饰�Ԥ��ʥ����ॢ���Ȥ����
 */
SYSCALL ER
twai_flg(ID flgid, FLGPTN waiptn, MODE wfmode, FLGPTN *p_flgptn, TMO tmout)
{
	FLGCB	*flgcb;
	WINFO_FLG winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_FLGID(flgid);
	CHECK_PAR(waiptn != 0);
	CHECK_PAR((wfmode & ~TWF_ORW) == 0);
	CHECK_TMOUT(tmout);
	flgcb = get_flgcb(flgid);

	t_lock_cpu();
	if (!(queue_empty(&(flgcb->wait_queue)))) {
		ercd = E_ILUSE;
	}
	else if (eventflag_cond(flgcb, waiptn, wfmode, p_flgptn)) {
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		winfo.waiptn = waiptn;
		winfo.wfmode = wfmode;
		wobj_make_wait_tmout((WOBJCB *) flgcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		*p_flgptn = winfo.flgptn;
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}
