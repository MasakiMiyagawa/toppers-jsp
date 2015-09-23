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
 *  @(#) $Id: cpu_context.h,v 1.1 2000/11/14 16:31:38 takayuki Exp $
 */

/*
 *	����������ƥ��������롼����
 *
 *  ���Υե������ cpu_config.h ��ʬΥ���Ƥ���Τϡ����Υե������ TCB
 *  ��������줿����ɤ�ɬ�פ�����Τ��Ф��ơ�cpu_config.h �ˤ� TCB ��
 *  ������������ɤ�ɬ�פ����������ޤ�Ǥ��뤿��Ǥ��롥
 */

#ifndef _CPU_CONTEXT_H_
#define _CPU_CONTEXT_H_

#include "task.h"

/*
 *  ����������ƥ����Ȥν����
 *
 *  ���������ٻ߾��֤˰ܹԤ�����ʥ����������������������ν�λ���ˤ˸�
 *  �Ф�롥����Ū�ˤϡ�����������ƥ����Ȥ򥿥�������ư�Ǥ�����֤���
 *  �ꤹ�������create_context �� activate_context �ǹԤ��Ф褤��
 */
Inline void
create_context(TCB *tcb)
{
	tcb->tskctxb.ThreadHandle = INVALID_HANDLE_VALUE;
}

/*
 *  �������ε�ư����
 *
 *  ���������ٻ߾��֤���¹ԤǤ�����֤˰ܹԤ�����˸ƤФ�롥
 */
extern DWORD WINAPI activate_r(LPVOID);

Inline void
activate_context(TCB *tcb)
{
	tcb->tskctxb.ThreadHandle = CreateThread(NULL,0,activate_r,(LPVOID)tcb,CREATE_SUSPENDED,&tcb->tskctxb.ThreadID);
}

/*
 *  ext_tsk �������å���˳��ݤ�����ߡ��ΰ�Υ�����
 */
#define	ACTIVATED_STACK_SIZE	0

#endif /* _CPU_CONTEXT_H_ */
