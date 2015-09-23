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
 *  @(#) $Id: mailbox.c,v 1.2 2001/09/06 12:39:51 hiro Exp $
 */

/*
 *	�᡼��ܥå�����ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "wait.h"
#include "mailbox.h"

/*
 *  �᡼��ܥå���ID�κ����͡�kernel_cfg.c��
 */
extern const ID	tmax_mbxid;

/*
 *  �᡼��ܥå���������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern const MBXINIB	mbxinib_table[];

/*
 *  �᡼��ܥå��������֥�å��Υ��ꥢ��kernel_cfg.c��
 */
extern MBXCB	mbxcb_table[];

/*
 *  �᡼��ܥå���ID����᡼��ܥå��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_MBX(mbxid)	((mbxid) - TMIN_MBXID)
#define get_mbxcb(mbxid)	(&(mbxcb_table[INDEX_MBX(mbxid)]))

/*
 *  �᡼��ܥå����Ԥ�����֥�å������
 */
typedef struct mailbox_waiting_information {
	WINFO	winfo;		/* ɸ����Ԥ�����֥�å� */
	WOBJCB	*wobjcb;	/* �Ԥ����֥������ȤΥ���ȥ���֥�å� */
	T_MSG	*pk_msg;	/* ����������å����� */
} WINFO_MBX;

/* 
 *  �᡼��ܥå�����ǽ�ν����
 */
void
mailbox_initialize()
{
	INT	i;
	MBXCB	*mbxcb;

	for (mbxcb = mbxcb_table, i = 0; i < tmax_mbxid; mbxcb++, i++) {
		queue_initialize(&(mbxcb->wait_queue));
		mbxcb->mbxinib = &(mbxinib_table[i]);
		mbxcb->head = NULL;
	}
}

/*
 *  ��å�����ͥ���٤μ�Ф�
 */
#define	MSGPRI(pk_msg)	(((T_MSG_PRI *) pk_msg)->msgpri)

/*
 *  ͥ���ٽ��å��������塼�ؤ�����
 */
Inline void
enqueue_msg_pri(T_MSG **p_prevmsg_next, T_MSG *pk_msg)
{
	T_MSG	*pk_nextmsg;

	while ((pk_nextmsg = *p_prevmsg_next) != NULL) {
		if (MSGPRI(pk_nextmsg) > MSGPRI(pk_msg)) {
			break;
		}
		p_prevmsg_next = &(pk_nextmsg->next);
	}
	pk_msg->next = pk_nextmsg;
	*p_prevmsg_next = pk_msg;
}

/*
 *  �᡼��ܥå����ؤ�����
 */
SYSCALL ER
snd_mbx(ID mbxid, T_MSG *pk_msg)
{
	MBXCB	*mbxcb;
	TCB	*tcb;
	ER	ercd;
    
	CHECK_TSKCTX_UNL();
	CHECK_MBXID(mbxid);
	mbxcb = get_mbxcb(mbxid);

	t_lock_cpu();
	if (!(queue_empty(&(mbxcb->wait_queue)))) {
		tcb = (TCB *) queue_delete_next(&(mbxcb->wait_queue));
		((WINFO_MBX *)(tcb->winfo))->pk_msg = pk_msg;
		if (wait_complete(tcb)) {
			dispatch();
		}
		ercd = E_OK;
	}
	else if ((mbxcb->mbxinib->mbxatr & TA_MPRI) != 0) {
		if (TMIN_MPRI <= MSGPRI(pk_msg)
				&& MSGPRI(pk_msg) <= mbxcb->mbxinib->maxmpri) {
			enqueue_msg_pri(&(mbxcb->head), pk_msg);
			ercd = E_OK;
		}
		else {
			ercd = E_PAR;
		}
	}
	else {
		pk_msg->next = NULL;
		if (mbxcb->head != NULL) {
			mbxcb->last->next = pk_msg;
		}
		else {
			mbxcb->head = pk_msg;
		}
		mbxcb->last = pk_msg;
		ercd = E_OK;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �᡼��ܥå�������μ���
 */
SYSCALL ER
rcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	MBXCB	*mbxcb;
	WINFO_MBX winfo;
	ER	ercd;
    
	CHECK_DISPATCH();
	CHECK_MBXID(mbxid);
	mbxcb = get_mbxcb(mbxid);
    
	t_lock_cpu();
	if (mbxcb->head != NULL) {
		*ppk_msg = mbxcb->head;
		mbxcb->head = (*ppk_msg)->next;
		ercd = E_OK;
	}
	else {
		wobj_make_wait((WOBJCB *) mbxcb, (WINFO_WOBJ *) &winfo);
		dispatch();
		*ppk_msg = winfo.pk_msg;
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �᡼��ܥå�������μ����ʥݡ���󥰡�
 */
SYSCALL ER
prcv_mbx(ID mbxid, T_MSG **ppk_msg)
{
	MBXCB	*mbxcb;
	ER	ercd;
    
	CHECK_TSKCTX_UNL();
	CHECK_MBXID(mbxid);
	mbxcb = get_mbxcb(mbxid);
    
	t_lock_cpu();
	if (mbxcb->head != NULL) {
		*ppk_msg = mbxcb->head;
		mbxcb->head = (*ppk_msg)->next;
		ercd = E_OK;
	}
	else {
		ercd = E_TMOUT;
	}
	t_unlock_cpu();
	return(ercd);
}

/*
 *  �᡼��ܥå�������μ����ʥ����ॢ���Ȥ����
 */
SYSCALL ER
trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout)
{
	MBXCB	*mbxcb;
	WINFO_MBX winfo;
	TMEVTB	tmevtb;
	ER	ercd;
    
	CHECK_DISPATCH();
	CHECK_MBXID(mbxid);
	CHECK_TMOUT(tmout);
	mbxcb = get_mbxcb(mbxid);
    
	t_lock_cpu();
	if (mbxcb->head != NULL) {
		*ppk_msg = mbxcb->head;
		mbxcb->head = (*ppk_msg)->next;
		ercd = E_OK;
	}
	else if (tmout == TMO_POL) {
		ercd = E_TMOUT;
	}
	else {
		wobj_make_wait_tmout((WOBJCB *) mbxcb, (WINFO_WOBJ *) &winfo,
						&tmevtb, tmout);
		dispatch();
		*ppk_msg = winfo.pk_msg;
		ercd = winfo.winfo.wercd;
	}
	t_unlock_cpu();
	return(ercd);
}
