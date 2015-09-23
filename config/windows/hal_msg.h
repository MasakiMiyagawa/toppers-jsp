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
 *  @(#) $Id: hal_msg.h,v 1.4 2001/02/23 15:44:39 takayuki Exp $
 */
#ifndef __HAL_MSG_H
#define __HAL_MSG_H

#include "jsp_stddef.h"
#include "vwindows.h"

#define HALMSG_MESSAGE WM_APP

#define HALMSG_DISPATCH		0x0001
#define HALMSG_DESTROY		0x0002
#define HALMSG_INTERRUPT	0x0003

#define HALMSG_EXECUTEPROCEDURE 0x0101
#define HALMSG_ADDDESTRUCTIONPROCEDURE 0x0102
#define HALMSG_QUITREQUEST 0x0103

#define HALTIM_AUTOINT		0xffff0000

#ifndef __HAL_MSG_MSGONLY

extern HWND PrimaryDialogHandle;

Inline void
HALDispatchRequest(void * tcb)
{
	if(GetWindowThreadProcessId(PrimaryDialogHandle,0l) != GetCurrentThreadId())
		SendMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_DISPATCH,(LPARAM)tcb);
	else
		PostMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_DISPATCH,(LPARAM)tcb);
}

Inline void
HALDestroyRequest(void * tcb)
{
	PostMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_DESTROY,(LPARAM)tcb);
	ExitThread(0);
}

Inline void
HALInterruptRequest(unsigned int intno)
{
	PostMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_INTERRUPT,(LPARAM)intno);
}

Inline void
HALInterruptRequestAndWait(unsigned int intno)
{
	SendMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_INTERRUPT,(LPARAM)intno);
}

Inline void
HALExecuteProcedure(void * func, void * param)
{
	void * _workofHALExecuteProcedure[2];
	_workofHALExecuteProcedure[0] = func;
	_workofHALExecuteProcedure[1] = param;
	SendMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_EXECUTEPROCEDURE,(LPARAM)_workofHALExecuteProcedure);
}

Inline void
HALAddDestructionProcedure(void * func, void * param)
{
	void * _workofHALExecuteProcedure[2];
	_workofHALExecuteProcedure[0] = func;
	_workofHALExecuteProcedure[1] = param;
	SendMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_ADDDESTRUCTIONPROCEDURE,(LPARAM)_workofHALExecuteProcedure);
}

Inline void
HALQuitRequest(void)
{
	if(PrimaryDialogHandle != GetCurrentThread())
		SendMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_QUITREQUEST,0);
	else
		PostMessage(PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_QUITREQUEST,0);
}

#endif

#endif