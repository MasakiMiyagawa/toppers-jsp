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
 *  @(#) $Id: wait.c,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	�Ԥ����ִ����⥸�塼��
 */

#include "jsp_kernel.h"
#include "wait.h"

/*
 *  �Ԥ����֤ؤΰܹԡʥ����ॢ���Ȼ����
 *
 */
inline void
make_wait_tmout(WINFO *winfo, TMEVTB *tmevtb, TMO tmout)
{
	make_non_runnable(runtsk);
	runtsk->winfo = winfo;
	if (tmout > 0) {
		winfo->tmevtb = tmevtb;
		tmevtb_enqueue(tmevtb, (RELTIM) tmout,
					(CBACK) wait_tmout, (VP) runtsk);
	}
	else {
		assert(tmout == TMO_FEVR);
		winfo->tmevtb = NULL;
	}
}

/*
 *  �Ԥ�����Τ���Υ��������֤ι���
 *
 *  tcb �ǻ��ꤵ��륿�������Ԥ��������褦���������֤򹹿����롥��
 *  ��������륿�������¹ԤǤ�����֤ˤʤ���ϡ���ǥ����塼�ˤĤʤ���
 *  �ޤ����ǥ����ѥå���ɬ�פʾ��ˤ� TRUE ���֤���
 */
Inline BOOL
make_non_wait(TCB *tcb)
{
	assert(TSTAT_WAITING(tcb->tstat));

	if (!(TSTAT_SUSPENDED(tcb->tstat))) {
		/*
		 *  �Ԥ����֤���¹ԤǤ�����֤ؤ�����
		 */
		return(make_runnable(tcb));
	}
	else {
		/*
		 *  ����Ԥ����֤��鶯���Ԥ����֤ؤ�����
		 */
		tcb->tstat = TS_SUSPENDED;
		return(FALSE);
	}
}

/*
 *  �Ԥ����
 */
BOOL
wait_complete(TCB *tcb)
{
	if (tcb->winfo->tmevtb != NULL) {
		tmevtb_dequeue(tcb->winfo->tmevtb);
	}
	tcb->winfo->wercd = E_OK;
	return(make_non_wait(tcb));
}

/*
 *  �����ॢ���Ȥ�ȼ���Ԥ����
 */
void
wait_tmout(TCB *tcb)
{
	if ((tcb->tstat & TS_WAIT_WOBJ) != 0) {
		queue_delete(&(tcb->task_queue));
	}
	tcb->winfo->wercd = E_TMOUT;
	if (make_non_wait(tcb)) {
		reqflg = TRUE;
	}
}

void
wait_tmout_ok(TCB *tcb)
{
	tcb->winfo->wercd = E_OK;
	if (make_non_wait(tcb)) {
		reqflg = TRUE;
	}
}

/*
 *  �Ԥ����֤ζ������
 */
inline void
wait_cancel(TCB *tcb)
{
	if (tcb->winfo->tmevtb != NULL) {
		tmevtb_dequeue(tcb->winfo->tmevtb);
	}
	if ((tcb->tstat & TS_WAIT_WOBJ) != 0) {
		queue_delete(&(tcb->task_queue));
	}
}

BOOL
wait_release(TCB *tcb)
{
	wait_cancel(tcb);
	tcb->winfo->wercd = E_RLWAI;
	return(make_non_wait(tcb));
}

/*
 *  ��������ͥ���ٽ���Ԥ����塼�ؤ�����
 */
Inline void
queue_insert_tpri(TCB *tcb, QUEUE *queue)
{
	QUEUE	*entry;
	UINT	priority = tcb->priority;

	for (entry = queue->next; entry != queue; entry = entry->next) {
		if (priority < ((TCB *) entry)->priority) {
			break;
		}
	}
	queue_insert_prev(entry, &(tcb->task_queue));
}

/*
 *  �¹���Υ�������Ʊ�����̿����֥������Ȥ��Ԥ����塼�ؤ�����
 */
Inline void
wobj_queue_insert(WOBJCB *wobjcb)
{
	if ((wobjcb->wobjinib->wobjatr & TA_TPRI) != 0) {
		queue_insert_tpri(runtsk, &(wobjcb->wait_queue));
	}
	else {
		queue_insert_prev(&(wobjcb->wait_queue),
					&(runtsk->task_queue));
	}
}

/*
 *  Ʊ�����̿����֥������Ȥ��Ф����Ԥ����֤ؤΰܹ�
 */
void
wobj_make_wait(WOBJCB *wobjcb, WINFO_WOBJ *winfo)
{
	runtsk->tstat = (TS_WAITING | TS_WAIT_WOBJ | TS_WAIT_WOBJCB);
	make_wait(&(winfo->winfo));
	wobj_queue_insert(wobjcb);
	winfo->wobjcb = wobjcb;
}

void
wobj_make_wait_tmout(WOBJCB *wobjcb, WINFO_WOBJ *winfo,
					TMEVTB *tmevtb, TMO tmout)
{
	runtsk->tstat = (TS_WAITING | TS_WAIT_WOBJ | TS_WAIT_WOBJCB);
	make_wait_tmout(&(winfo->winfo), tmevtb, tmout);
	wobj_queue_insert(wobjcb);
	winfo->wobjcb = wobjcb;
}

/*
 *  ��������ͥ�����ѹ����ν���
 */
void
wobj_change_priority(WOBJCB *wobjcb, TCB *tcb)
{
	if ((wobjcb->wobjinib->wobjatr & TA_TPRI) != 0) {
		queue_delete(&(tcb->task_queue));
		queue_insert_tpri(tcb, &(wobjcb->wait_queue));
	}
}
