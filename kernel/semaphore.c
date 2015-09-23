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
 *  @(#) $Id: semaphore.c,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	���ޥե���ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "semaphore.h"

/*
 *  ���ޥե�ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_semid;

/*
 *  ���ޥե�������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const SEMINIB	seminib_table[];

/*
 *  ���ޥե������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern SEMCB	semcb_table[];

/*
 *  ���ޥե�ID���饻�ޥե������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SEM(semid)	((semid) - TMIN_SEMID)
#define get_semcb(semid)	(&(semcb_table[INDEX_SEM(semid)]))

/* 
 *  ���ޥե���ǽ�ν����
 */
void
semaphore_initialize()
{
	INT	i;
	SEMCB	*semcb;

	for (semcb = semcb_table, i = 0; i < tmax_semid; semcb++, i++) {
		queue_initialize(&(semcb->wait_queue));
		semcb->seminib = &(seminib_table[i]);
		semcb->semcnt = semcb->seminib->isemcnt;
	}
}

/*
 *  ���ޥե��񸻤��ֵ�
 */
SYSCALL ER
sig_sem(ID semid)
{
	SEMCB	*semcb;
	TCB	*tcb;
	ER	ercd;
    
	CHECK_TSKCTX_UNL();
	CHECK_SEMID(semid);
	semcb = get_semcb(semid);

	t_lock_cpu();
	if (!(queue_empty(&(semcb->wait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(semcb->wait_queue));
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if (semcb->semcnt < semcb->seminib->maxsem) {
		semcb->semcnt += 1;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ���ޥե��񸻤��ֵѡ��󥿥�������ƥ������ѡ�
 */
SYSCALL ER
isig_sem(ID semid)
{
	SEMCB	*semcb;
	TCB	*tcb;
	ER	ercd;
    
	CHECK_INTCTX_UNL();
	CHECK_SEMID(semid);
	semcb = get_semcb(semid);

	i_lock_cpu();
	if (!queue_empty(&(semcb->wait_queue))) {
		tcb = (TCB *) queue_delete_next(&(semcb->wait_queue));
		if (wait_complete(tcb)) {
			reqflg = TRUE;
		}
		ercd = E_OK;
	}
	else if (semcb->semcnt < semcb->seminib->maxsem) {
		semcb->semcnt += 1;
		ercd = E_OK;
	}
	else {
		ercd = E_QOVR;
	}
	i_unlock_cpu();
	return(ercd);
}

/*
 *  ���ޥե��񸻤γ���
 */
SYSCALL ER
wai_sem(ID semid)
{
	SEMCB	*semcb;
	WINFO_WOBJ winfo;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_SEMID(semid);
	semcb = get_semcb(semid);

	t_lock_cpu();
	if (semcb->semcnt >= 1) {
		semcb->semcnt -= 1;
		ercd = E_OK;
	}
	else {
		wobj_make_wait((WOBJCB *) semcb, &winfo);
		dispatch();
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ���ޥե��񸻤γ����ʥݡ���󥰡�
 */
SYSCALL ER
pol_sem(ID semid)
{
	SEMCB	*semcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_SEMID(semid);
	semcb = get_semcb(semid);

	t_lock_cpu();
	if (semcb->semcnt >= 1) {
		semcb->semcnt -= 1;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ���ޥե��񸻤γ����ʥ����ॢ���Ȥ����
 */
SYSCALL ER
twai_sem(ID semid, TMO tmout)
{
	SEMCB	*semcb;
	WINFO_WOBJ winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_SEMID(semid);
	CHECK_TMOUT(tmout);
	semcb = get_semcb(semid);

	t_lock_cpu();
	if (semcb->semcnt >= 1) {
		semcb->semcnt -= 1;
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		wobj_make_wait_tmout((WOBJCB *) semcb, &winfo, &tmevtb, tmout);
		dispatch();
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}
