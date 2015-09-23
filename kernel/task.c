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
 *  @(#) $Id: task.c,v 1.5 2001/10/07 06:16:56 hiro Exp $
 */

/*
 *	�����������⥸�塼��
 */

#include "jsp_kernel.h"
#include "task.h"
#include "cpu_context.h"

/*
 *  �¹Ծ��֤Υ�����
 */
TCB	*runtsk;

/*
 *  �ǹ�ͥ���̤Υ�����
 */
TCB	*schedtsk;

/*
 *  �������ǥ����ѥå����������㳰�����롼����ư�׵�ե饰
 */
BOOL	reqflg;

/*
 *  �������ǥ����ѥå����ľ���
 */
BOOL	enadsp;

/*
 *  ��ǥ����塼
 *
 *  ��ǥ����塼�ϡ��¹ԤǤ�����֤Υ�������������뤿��Υ��塼�ǡ�ͥ
 *  ���٤��ȤΥ��������塼�ǹ�������Ƥ��롥��������TCB�ϡ���������ͥ
 *  ���٤Υ��塼����Ͽ����롥
 */
static QUEUE	ready_queue[TNUM_TPRI];

/*
 *  ��ǥ����塼�������Τ���Υӥåȥޥå�
 *
 *  ��ǥ����塼�Υ��������Ψ�褯�Ԥ�����ˡ�ͥ���٤��ȤΥ��������塼
 *  �˥����������äƤ��뤫�ɤ����򼨤��ӥåȥޥåפ��Ѱդ��Ƥ��롥�ӥ�
 *  �ȥޥåפ�Ȥ����Ȥǡ����ꥢ�������β���򸺤餹���Ȥ��Ǥ��뤬��
 *  �ӥå����̿�᤬���¤��Ƥ��ʤ��ץ��å��ǡ�ͥ���٤��ʳ��������ʤ�
 *  ���ˤϡ��ӥåȥޥå����Υ����С��إåɤΤ���ˡ��դ˸�Ψ�����
 *  ���ǽ���⤢�롥
 *  �ӥåȥޥåפ� UINT ��������Ƥ��뤬���ӥåȥޥåץ������ؿ���ͥ��
 *  �٤�16�ʳ��ʲ��Ǥ��뤳�Ȥ��ꤷ�Ƥ��Ƥ��롥
 */
static UINT	ready_primap;

/*
 *  �����������⥸�塼��ν����
 */
void
task_initialize()
{
	INT	i;
	TCB	*tcb;

	runtsk = schedtsk = NULL;
	reqflg = FALSE;
	enadsp = TRUE;

	for (i = 0; i < TNUM_TPRI; i++) {
		queue_initialize(&(ready_queue[i]));
	}
	ready_primap = 0;

	for (tcb = tcb_table, i = 0; i < tmax_tskid; tcb++, i++) {
		tcb->tinib = &(tinib_table[i]);
		tcb->actcnt = FALSE;
		make_dormant(tcb);
		if ((tcb->tinib->tskatr & TA_ACT) != 0) {
			make_active(tcb);
		}
	}
}

/*
 *  �ӥåȥޥåץ������ؿ�
 *
 *  bitmap ��� 1 �ΥӥåȤ��⡤�ǤⲼ�̡ʱ��ˤΤ�Τ򥵡����������Υ�
 *  �å��ֹ���֤����ӥå��ֹ�ϡ��ǲ��̥ӥåȤ� 0 �Ȥ��롥bitmap �� 0
 *  ����ꤷ�ƤϤʤ�ʤ������δؿ��Ǥϡ�ͥ���٤�16�ʳ��ʲ��Ǥ��뤳�Ȥ�
 *  ���ꤷ��bitmap�β��� 16�ӥåȤΤߤ򥵡������롥
 *  �ӥåȥ�����̿������CPU�Ǥϡ��ӥåȥ�����̿���Ȥ��褦�˽�ľ
 *  ����������Ψ���ɤ����������Τ褦�ʾ��ˤϡ�cpu_insn.h �ǥӥå�
 *  ������̿���Ȥä� bitmap_search ���������CPU_BITMAP_SEARCH ���
 *  �����������Ф褤���ޤ����ӥåȥ�����̿��Υ������������դʤɤ���
 *  ͳ��ͥ���٤ȥӥåȤȤ��б����ѹ����������ˤϡ�PRIMAP_BIT ��ޥ�
 *  ���������Ф褤��
 *  �ޤ���ɸ��饤�֥��� ffs ������ʤ顤���Τ褦���������ɸ��饤
 *  �֥���Ȥä�������Ψ���ɤ���ǽ���⤢�롥
 *	#define	bitmap_search(bitmap) (ffs(bitmap) - 1)
 */
#ifndef PRIMAP_BIT
#define	PRIMAP_BIT(pri)		(1 << (pri))
#endif /* PRIMAP_BIT */

#ifndef CPU_BITMAP_SEARCH

Inline UINT
bitmap_search(UINT bitmap)
{
	static const VB search_table[] = { 0, 1, 0, 2, 0, 1, 0,
					3, 0, 1, 0, 2, 0, 1, 0 };
	INT	n = 0;

	assert((bitmap & 0xffff) != 0);
	if ((bitmap & 0x00ff) == 0) {
		bitmap >>= 8;
		n += 8;
	}
	if ((bitmap & 0x0f) == 0) {
		bitmap >>= 4;
		n += 4;
	}
	return(n + search_table[(bitmap & 0x0f) - 1]);
}

#endif /* CPU_BITMAP_SEARCH */

/*
 *  �ǹ�ͥ���̥������Υ�����
 *
 *  ��ǥ����塼��κǹ�ͥ���̤Υ������򥵡�����������TCB�ؤΥݥ���
 *  ���֤�����ǥ����塼�����ξ��ˤϡ����δؿ���ƤӽФ��ƤϤʤ�ʤ���
 */
static TCB *
search_schedtsk()
{
	UINT	schedpri;

	schedpri = bitmap_search(ready_primap);
	return((TCB *)(ready_queue[schedpri].next));
}

/*
 *  �¹ԤǤ�����֤ؤΰܹ�
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ��¹ԤǤ��륿�������ʤ��ä����
 *  �ȡ�tcb ��ͥ���٤��ǹ�ͥ���̤Υ�������ͥ���٤���⤤���Ǥ��롥
 */
BOOL
make_runnable(TCB *tcb)
{
	UINT	pri = tcb->priority;

	tcb->tstat = TS_RUNNABLE;
	queue_insert_prev(&(ready_queue[pri]), &(tcb->task_queue));
	ready_primap |= PRIMAP_BIT(pri);

	if (schedtsk == (TCB *) NULL || pri < schedtsk->priority) {
		schedtsk = tcb;
		return(enadsp);
	}
	return(FALSE);
}

/*
 *  �¹ԤǤ�����֤���¾�ξ��֤ؤΰܹ�
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ�tcb ���ǹ�ͥ���̤Υ������Ǥ���
 *  �����Ǥ��롥tcb ��Ʊ��ͥ���٤Υ�������¾�ˤ�����ϡ�tcb �μ���
 *  ���������ǹ�ͥ���̤ˤʤ롥�����Ǥʤ����ϡ���ǥ����塼�򥵡���
 *  ����ɬ�פ����롥
 */
BOOL
make_non_runnable(TCB *tcb)
{
	UINT	pri = tcb->priority;
	QUEUE	*queue = &(ready_queue[pri]);

	queue_delete(&(tcb->task_queue));
	if (queue_empty(queue)) {
		ready_primap &= ~PRIMAP_BIT(pri);
		if (schedtsk == tcb) {
			schedtsk = (ready_primap == 0) ? (TCB * ) NULL
						: search_schedtsk();
			return(enadsp);
		}
	}
	else {
		if (schedtsk == tcb) {
			schedtsk = (TCB *)(queue->next);
			return(enadsp);
		}
	}
	return(FALSE);
}

/*
 *  �ٻ߾��֤ؤΰܹ�
 */
void
make_dormant(TCB *tcb)
{
	tcb->priority = tcb->tinib->ipriority;
	tcb->tstat = TS_DORMANT;
	tcb->wupcnt = FALSE;
	tcb->enatex = FALSE;
	tcb->texptn = 0;
	create_context(tcb);
}

/*
 *  �ٻ߾��֤���¹ԤǤ�����֤ؤΰܹ�
 */
BOOL
make_active(TCB *tcb)
{
	activate_context(tcb);
	return(make_runnable(tcb));
}

/*
 *  �¹Ծ��֤Υ������ν�λ
 */
void
exit_task()
{
	make_non_runnable(runtsk);
	make_dormant(runtsk);
	if (runtsk->actcnt) {
		runtsk->actcnt = FALSE;
		make_active(runtsk);
	}
	exit_and_dispatch();
}

/*
 *  ��ǥ����塼��Υ�������ͥ���٤��ѹ�
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ�(1) tcb ���ǹ�ͥ���̤Υ�����
 *  �Ǥ��äơ�����ͥ���٤򲼤�����硤(2) tcb ���ǹ�ͥ���̤Υ�������
 *  �Ϥʤ����ѹ����ͥ���٤��ǹ�ͥ���̤Υ�������ͥ���٤���⤤���
 *  �Ǥ��롥(1) �ξ��ˤϡ���ǥ����塼�򥵡�������ɬ�פ����롥
 */
BOOL
change_priority(TCB *tcb, UINT newpri)
{
	UINT	oldpri = tcb->priority;

	tcb->priority = newpri;
	queue_delete(&(tcb->task_queue));
	if (queue_empty(&(ready_queue[oldpri]))) {
		ready_primap &= ~PRIMAP_BIT(oldpri);
	}
	queue_insert_prev(&(ready_queue[newpri]), &(tcb->task_queue));
	ready_primap |= PRIMAP_BIT(newpri);

	if (schedtsk == tcb) {
		if (newpri >= oldpri) {
			schedtsk = search_schedtsk();
			return(schedtsk != tcb && enadsp);
		}
	}
	else {
		if (newpri < schedtsk->priority) {
			schedtsk = tcb;
			return(enadsp);
		}
	}
	return(FALSE);
}

/*
 *  ��ǥ����塼�β�ž
 *
 *  �ǹ�ͥ���̤Υ������򹹿�����Τϡ��ǹ�ͥ���̤Υ���������������
 *  �塼�������˰�ư�������Ǥ��롥
 */
BOOL
rotate_ready_queue(UINT pri)
{
	QUEUE	*queue = &(ready_queue[pri]);
	QUEUE	*entry;

	if (!(queue_empty(queue)) && queue->next->next != queue) {
		entry = queue_delete_next(queue);
		queue_insert_prev(queue, entry);
		if (schedtsk == (TCB *) entry) {
			schedtsk = (TCB *)(queue->next);
			return(enadsp);
		}
	}
	return(FALSE);
}

/*
 *  �������㳰�����롼����θƽФ�
 */
void
call_texrtn()
{
	TEXPTN	texptn;

	do {
		texptn = runtsk->texptn;
		runtsk->enatex = FALSE;
		runtsk->texptn = 0;
		t_unlock_cpu();
		(*runtsk->tinib->texrtn)(texptn, runtsk->tinib->exinf);
		if (!t_sense_lock()) {
			t_lock_cpu();
		}
	} while (runtsk->texptn != 0);
	runtsk->enatex = TRUE;
}

/*
 *  �������㳰�����롼����ε�ư
 */
#ifndef OMIT_CALLTEX

void
calltex()
{
	if (runtsk->enatex && runtsk->texptn != 0) {
		call_texrtn();
	}
}

#endif /* OMIT_CALLTEX */
