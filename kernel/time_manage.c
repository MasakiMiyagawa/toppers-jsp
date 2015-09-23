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
 *  @(#) $Id: time_manage.c,v 1.1 2000/11/14 14:44:21 hiro Exp $
 */

/*
 *	�����ƥ���������ǽ
 */

#include "jsp_kernel.h"
#include "check.h"
#include "time_event.h"

/*
 *  �����ƥ����Υ��ե��å�
 *
 *  systim_offset �� 0 �˽��������뤳�Ȥ��ꤷ�Ƥ��롥0 �˽������
 *  ��ʤ��Ķ��Ǥϡ�set_tim ��ƤӽФ��� systim_offset ���������뤳
 *  �Ȥ�ɬ�ס�
 */
static SYSTIM	systim_offset;

/*
 *  �����ƥ���������
 */
SYSCALL ER
set_tim(SYSTIM *pk_systim)
{
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	systim_offset = *pk_systim - current_time;
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  �����ƥ����λ���
 */
SYSCALL ER
get_tim(SYSTIM *pk_systim)
{
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	*pk_systim = systim_offset + current_time;
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  ��ǽɾ���ѥ����ƥ����λ���
 */
#ifdef SUPPORT_VXGET_TIM
#include "hw_timer.h"

SYSCALL ER
vxget_tim(SYSUTIM *pk_sysutim)
{
	SYSUTIM	utime;
	SYSTIM	time;
#if TIC_DENO != 1
	INT	subtime;
#endif /* TIC_DENO != 1 */
	CLOCK	clock;
	BOOL	ireq;
	BOOL	locked;

	CHECK_TSKCTX();

	locked = sense_lock();
	if (!(locked)) {
		t_lock_cpu();
	}
	time = systim_offset + next_time;
#if TIC_DENO != 1
	subtime = (INT) next_subtime;
#endif /* TIC_DENO != 1 */
	clock = hw_timer_get_current();
	ireq = hw_timer_fetch_interrupt();
	if (!(locked)) {
		t_unlock_cpu();
	}

	utime = ((SYSUTIM) time) * 1000;
#if TIC_DENO != 1
	utime += subtime * 1000 / TIC_DENO
#endif /* TIC_DENO != 1 */
	if (!(ireq) || clock >= (TO_CLOCK(TIC_NUME, TIC_DENO)
					- GET_TOLERANCE)) {
		utime -= TIC_NUME * 1000 / TIC_DENO;
	}
	utime += clock * 1000 / TIMER_CLOCK;
	*pk_sysutim = utime;
	return(E_OK);
}

#endif /* SUPPORT_VXGET_TIM */
