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
 *  @(#) $Id: mempfix.c,v 1.2 2000/12/22 07:53:11 hiro Exp $
 */

/*
 *	����Ĺ����ס��뵡ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mempfix.h"

/*
 *  ����Ĺ����ס���ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_mpfid;

/*
 *  ����Ĺ����ס��������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const MPFINIB	mpfinib_table[];

/*
 *  ����Ĺ����ס�������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern MPFCB	mpfcb_table[];

/*
 *  ����Ĺ����ס���ID�������Ĺ����ס�������֥�å�����Ф���
 *  ��Υޥ���
 */
#define INDEX_MPF(mpfid)	((mpfid) - TMIN_MPFID)
#define get_mpfcb(mpfid)	(&(mpfcb_table[INDEX_MPF(mpfid)]))

/*
 *  ����Ĺ����ס����Ԥ�����֥�å������
 */
typedef struct fixed_memorypool_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������ȤΥ���ȥ���֥�å� */
	VP	blk;		/* ������������֥�å� */
} WINFO_MPF;

/* 
 *  ����Ĺ����ס��뵡ǽ�ν����
 */
void
mempfix_initialize()
{
	INT	i;
	MPFCB	*mpfcb;

	for (mpfcb = mpfcb_table, i = 0; i < tmax_mpfid; mpfcb++, i++) {
		queue_initialize(&(mpfcb->wait_queue));
		mpfcb->mpfinib = &(mpfinib_table[i]);
		mpfcb->unused = mpfcb->mpfinib->mpf;
		mpfcb->freelist = NULL;
	}
}

/*
 *  ����Ĺ����ס��뤫��֥�å������
 */
static BOOL
get_block(MPFCB *mpfcb, VP *p_blk)
{
	FREEL	*free;

	if (mpfcb->freelist != NULL) {
		free = mpfcb->freelist;
		mpfcb->freelist = free->next;
		*p_blk = (VP) free;
		return(TRUE);
	}
	else if (mpfcb->unused < mpfcb->mpfinib->limit) {
		*p_blk = mpfcb->unused;
		mpfcb->unused = (VB *)(mpfcb->unused) + mpfcb->mpfinib->blksz;
		return(TRUE);
	}
	return(FALSE);
}

/*
 *  ����Ĺ����֥�å��γ���
 */
SYSCALL ER
get_mpf(ID mpfid, VP *p_blk)
{
	MPFCB	*mpfcb;
	WINFO_MPF winfo;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (get_block(mpfcb, p_blk)) {
		ercd = E_OK;
	}
	else {
		wobj_make_wait((WOBJCB *) mpfcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		*p_blk = winfo.blk;
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ����Ĺ����֥�å��γ����ʥݡ���󥰡�
 */
SYSCALL ER
pget_mpf(ID mpfid, VP *p_blk)
{
	MPFCB	*mpfcb;
	ER	ercd;

	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (get_block(mpfcb, p_blk)) {
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ����Ĺ����֥�å��γ����ʥ����ॢ���Ȥ����
 */
SYSCALL ER
tget_mpf(ID mpfid, VP *p_blk, TMO tmout)
{
	MPFCB	*mpfcb;
	WINFO_MPF winfo;
	TMEVTB	tmevtb;
	ER	ercd;

	CHECK_DISPATCH();
	CHECK_MPFID(mpfid);
	CHECK_TMOUT(tmout);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (get_block(mpfcb, p_blk)) {
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		wobj_make_wait_tmout((WOBJCB *) mpfcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		*p_blk = winfo.blk;
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  ����Ĺ����֥�å����ֵ�
 */
SYSCALL ER
rel_mpf(ID mpfid, VP blk)
{
	MPFCB	*mpfcb;
	TCB	*tcb;
	FREEL	*free;
	ER	ercd;
    
	CHECK_TSKCTX_UNL();
	CHECK_MPFID(mpfid);
	mpfcb = get_mpfcb(mpfid);

	t_lock_cpu();
	if (!(mpfcb->mpfinib->mpf <= blk && blk < mpfcb->mpfinib->limit
			&& (((VB *) blk) - ((VB *)(mpfcb->mpfinib->mpf)))
					% mpfcb->mpfinib->blksz == 0)) {
		ercd = E_PAR;
	}
	else if (!(queue_empty(&(mpfcb->wait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(mpfcb->wait_queue));
		((WINFO_MPF *)(tcb->winfo))->blk = blk;
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else {
		free = (FREEL *) blk;
		free->next = mpfcb->freelist;
		mpfcb->freelist = free;
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}
