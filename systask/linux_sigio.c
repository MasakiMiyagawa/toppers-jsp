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
 *  @(#) $Id: linux_sigio.c,v 1.1 2000/11/14 16:27:57 honda Exp $
 */


#include <jsp_services.h>
#include "../kernel/jsp_kernel.h"
#include "../kernel/queue.h"
#include "kernel_id.h"
#include <signal.h>
#include <linux_sigio.h>


/*
 *  SIGIO$BDLCN%$%Y%s%H%-%e!<(B
 */

static QUEUE	sigio_queue;

/*
 *  SIGIO$BDLCN%O%s%I%i(B
 *
 *  SIGIO$BDLCN=hM}%?%9%/$r5/>2$9$k!%(B
 */

void
linux_sigio_handler()
{
	syscall(iwup_tsk(TSK_LINUX_SIGIO));
}

/*
 *  $B%N%s%V%m%C%-%s%0(BI/O $B%b%8%e!<%k5/F0%k!<%A%s(B
 *
 *  SIGIO$BDLCN%$%Y%s%H%-%e!<$r=i4|2=!%(BSIGIO$BDLCN=hM}%?%9%/$H%;%^%U%)$r@8(B
 *  $B@.!%(BSIGIO$BDLCN%O%s%I%i$r@_Dj!%(B
 */

static int	initflag = 0;		/* $B=i4|2=:Q%U%i%0(B */

void
linux_sigio_initialize(VP_INT exinf)
{
    
	if (!initflag) {
		queue_initialize(&sigio_queue);
		initflag = 1;
	}
}

/*
 *  SIGIO$BDLCN=hM}%?%9%/K\BN(B
 */

void
linux_sigio_task(void)
{
	QUEUE	*q;
	SIGIOEB	*event;

	while (slp_tsk() == E_OK) {
		/*
		 *  SIGIO$BDLCN%$%Y%s%H%-%e!<Cf$N3F%$%Y%s%H%V%m%C%/$N%3!<(B
		 *  $B%k%P%C%/%k!<%A%s$r8F$S$@$9!%%3!<%k%P%C%/%k!<%A%s$,(B
		 *  0 $B0J30$rJV$7$?>l9g!$$=$N%$%Y%s%H%V%m%C%/$r:o=|$9$k!%(B
		 */
		syscall(wai_sem(SEM_LINUX_SIGIO));
		q = sigio_queue.next;
		while (q != &sigio_queue) {
			event = ((SIGIOEB *) q);
			q = q->next;
			if ((*(event->callback))(event->arg)) {
				queue_delete((QUEUE *) &(event->queue));
			}
		}
		syscall(sig_sem(SEM_LINUX_SIGIO));
	}
	ext_tsk();
}

/*
 *  SIGIO$BDLCN%$%Y%s%H$r(BSIGIO$BDLCN%$%Y%s%H%-%e!<$XA^F~(B
 *
 *  $B%7%9%F%`%*%V%8%'%/%H$K%"%/%;%9$9$k$?$a$K!$3HD%(BSVC$B%O%s%I%i$H$7$FF0(B
 *  $B:n$5$;$F$$$k!%(B
 */

ER
enqueue_sigioeb(SIGIOEB *event)
{
	syscall(wai_sem(SEM_LINUX_SIGIO));
	queue_insert_prev(&sigio_queue , (QUEUE *) &(event->queue));
	syscall(sig_sem(SEM_LINUX_SIGIO));
	return(E_OK);
}


/*
 *   $B%7%9%F%`5/F0;~EPO?MQ(B
 *   $B%7%9%F%`5/F0;~!"=i4|2=%k!<%A%s$OHs%?%9%/%3%s%F%-%9%H$+$i(B
 *   $B8F$P$l$k$?$a(Benqueue_sigioeb()$B$G%;%^%U%)$,;HMQ$G$-$J$$(B
 */

ER
enqueue_sigioeb_initialize(SIGIOEB *event)
{
	queue_insert_prev(&sigio_queue , (QUEUE *) &(event->queue));
	return(E_OK);
}






























