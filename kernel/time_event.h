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
 *  @(#) $Id: time_event.h,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	�����।�٥�ȴ����⥸�塼��
 */

#ifndef _TIME_EVENT_H_
#define _TIME_EVENT_H_

/*
 *  ���٥��ȯ������Υǡ����������
 *
 *  EVTTIM �ϡ�RELTIM �Ȥ��ƻ���Ǥ����ϰϤ��⹭���ϰϤ�ɽ���Ǥ���ɬ
 *  �פ����롥����������ɥץ�ե�����Ǥϡ�RELTIM �� 16bit �ʾ�Ǥʤ�
 *  ��Фʤ�ʤ����ᡤEVTTIM �� 17bit �ʾ�Ǥ��뤳�Ȥ�ɬ�פǤ��롥����
 *  ���ᡤ16bit �ξ�礬���� UINT �ǤϤʤ���UW ��������Ƥ��롥
 */
typedef UW	EVTTIM;

/*
 *  ���л��֡�RELTIM�ˤ˻���Ǥ��������
 */
#define	TMAX_RELTIM	((1u << (sizeof(EVTTIM) * 8 - 1)) - 1)

/* 
 *  �����।�٥�ȥ֥�å��Υǡ����������
 */
typedef void	(*CBACK)(VP);	/* ������Хå��ؿ��η� */

typedef struct time_event_block {
	UINT	index;		/* �����।�٥�ȥҡ�����Ǥΰ��� */
	CBACK	callback;	/* ������Хå��ؿ� */
	VP	arg;		/* ������Хå��ؿ����Ϥ����� */
} TMEVTB;

/*
 *  �����।�٥�ȥҡ�����ΥΡ��ɤΥǡ����������
 */
typedef struct time_event_node {
	EVTTIM	time;		/* ���٥��ȯ������ */
	TMEVTB	*tmevtb;	/* �б����륿���।�٥�ȥ֥�å� */
} TMEVTN;

/*
 *  �����।�٥�ȥҡ��ס�kernel_cfg.c��
 */
extern TMEVTN	tmevt_heap[];

/*
 *  ���ߤΥ����ƥ�����ñ��: �ߥ��á�
 *
 *  �����ƥ൯ư���� 0 �˽�������졤�ʹߡ�isig_tim ���ƤФ���٤�ñĴ
 *  �����ä��롥set_tim �ˤ�ä��ѹ�����ʤ���
 */
extern SYSTIM	current_time;

/*
 *  ���Υ�����ƥ��å��Υ����ƥ�����ñ��: 1�ߥ��á�
 */
extern SYSTIM	next_time;

/*
 *  �����ƥ�����ѻ����ѿ���ñ��: 1/TIM_DENO�ߥ��á�
 *
 *  ���Υ�����ƥ��å��Υ����ƥ����β��̷�򼨤��ʾ�̷�� next_time�ˡ�
 *  TIC_DENO �� 1 �λ��ϡ����̷�Ͼ�� 0 �Ǥ��뤿�ᡤ�����ѿ���ɬ�פʤ���
 */
#if TIC_DENO != 1
extern UINT	next_subtime;
#endif /* TIC_DENO != 1 */

/*
 *  ���л��֤Υ١��������ñ��: 1�ߥ��á�
 *
 *  ���Υ�����ƥ��å��Υ����ƥ������ڤ�夲�����TIC_DENO �� 1 ��
 *  ���ϡ�next_time �� EVTTIM ���Ѵ�������Τ˰��פ��롥
 */
#if TIC_DENO == 1
#define	base_time	((EVTTIM) next_time)
#else /* TIC_DENO == 1 */
extern EVTTIM	base_time;
#endif /* TIC_DENO == 1 */

/*
 *  �����।�٥�ȴ����⥸�塼��ν����
 */
extern void	tmevt_initialize(void);

/*
 *  �����।�٥�ȥҡ��פؤ���Ͽ�Ⱥ��
 */
extern void	tmevtb_insert(TMEVTB *tmevtb, EVTTIM time);
extern void	tmevtb_delete(TMEVTB *tmevtb);

/*
 *  �����।�٥�ȥ֥�å�����Ͽ�����л��ֻ����
 *
 *  time �ǻ��ꤷ�����л��֤��в��ˡ�arg ������Ȥ��� callback ����
 *  �ӽФ����褦�ˡ������।�٥�ȥ֥�å� tmevtb ����Ͽ���롥
 */
Inline void
tmevtb_enqueue(TMEVTB *tmevtb, RELTIM time, CBACK callback, VP arg)
{
	assert(time <= TMAX_RELTIM);

	tmevtb->callback = callback;
	tmevtb->arg = arg;
	tmevtb_insert(tmevtb, base_time + time);
}

/*
 *  �����।�٥�ȥ֥�å�����Ͽ�ʥ��٥��ȯ����������
 *
 *  time �ǻ��ꤷ�����٥��ȯ������ˡ�arg ������Ȥ��� callback ����
 *  �ӽФ����褦�ˡ������।�٥�ȥ֥�å� tmevtb ����Ͽ���롥
 */
Inline void
tmevtb_enqueue_evttim(TMEVTB *tmevtb, EVTTIM time, CBACK callback, VP arg)
{
	tmevtb->callback = callback;
	tmevtb->arg = arg;
	tmevtb_insert(tmevtb, time);
}

/*
 *  �����।�٥�ȥ֥�å�����Ͽ���
 */
Inline void
tmevtb_dequeue(TMEVTB *tmevtb)
{
	tmevtb_delete(tmevtb);
}

#endif /* _TIME_EVENT_H_ */
