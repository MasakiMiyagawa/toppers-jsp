/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2006 by Witz Corporation, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: kernel_inline_defs.h,v 1.1 2006/04/10 08:19:25 honda Exp $
 */

/*
 *	TOSHIBA��ȯ�Ķ������ӥ�ȥ���(inline)�ؿ������
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ������ͥ�������c�ե����뤫�饤�󥯥롼��
 *  ����Ƥ���tool_defs.h ���饤�󥯥롼�ɤ���롥¾�Υե����뤫���ľ��
 *  ���󥯥롼�ɤ��뤳�ȤϤʤ���¾�Υ��󥯥롼�ɥե��������Ω�äƽ�����
 *  ��뤿�ᡤ¾�Υ��󥯥롼�ɥե�����˰�¸���ƤϤʤ�ʤ���
 */

#ifndef _KERNEL_INLINE_DEFS_H_
#define _KERNEL_INLINE_DEFS_H_

/*
 *  TOSHIBA IDE�Ǥ�#pragma inline���Ҥˤƥ���饤��ؿ����������
 *  ���Τ��ᥫ���ͥ������ˤΤ߰ʲ��ν�����Ŭ�Ѥ��롥
 *  tool_defs.h �ˤƥ����ͥ붦������Inline�����inline�����������
 *  ̵���Ȥ������ΤΥ���饤��ؿ����Ф���#pragma inline����ܥե�
 *  ����˵��ܤ��롥
 */
/* sil.h	*/
#pragma inline sil_reb_mem
#pragma inline sil_wrb_mem
#pragma inline sil_reh_mem
#pragma inline sil_wrh_mem
#pragma inline sil_reh_lem
#pragma inline sil_wrh_lem
#pragma inline sil_reh_bem
#pragma inline sil_wrh_bem
#pragma inline sil_rew_mem
#pragma inline sil_wrw_mem
#pragma inline sil_rew_lem
#pragma inline sil_wrw_lem
#pragma inline sil_rew_bem
#pragma inline sil_wrw_bem

/* t_services.h	*/
#pragma inline _t_perror
#pragma inline _t_panic

/* t_syslog.h	*/
#pragma inline _syslog_0
#pragma inline _syslog_1
#pragma inline _syslog_2
#pragma inline _syslog_3
#pragma inline _syslog_4
#pragma inline _syslog_5
#pragma inline _syslog_6

/* mailbox.c	*/
#pragma inline enqueue_msg_pri

/* task.c	*/
#pragma inline bitmap_search

/* time_event.c	*/
#pragma inline tmevtb_delete_top

/* wait.c	*/
#pragma inline make_non_wait
#pragma inline queue_insert_tpri
#pragma inline wobj_queue_insert

/* queue.h	*/
#pragma inline queue_initialize
#pragma inline queue_insert_prev
#pragma inline queue_delete
#pragma inline queue_delete_next
#pragma inline queue_empty

/* task_event.h	*/
#pragma inline tmevtb_enqueue
#pragma inline tmevtb_enqueue_evttim
#pragma inline tmevtb_dequeue

/* wait.h	*/
#pragma inline make_wait

/* serial.c	*/
#pragma inline serial_snd_chr


#endif	/* _KERNEL_INLINE_DEFS_H_	*/
