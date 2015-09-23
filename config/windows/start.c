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
 *  @(#) $Id: start.c,v 1.1 2000/11/14 16:31:38 takayuki Exp $
 */
#include "jsp_kernel.h"
#include "task.h"
#include "vwindows.h"
#include "hal_msg.h"
#include "hw_timer.h"
#include "objbase.h"
#include "shellapi.h"
#include "resource.h"

extern void kernel_start();
extern void kernel_exit();

HANDLE ProcessInstance;
HANDLE PrimaryDialogHandle;
HANDLE PrimaryThreadHandle;
HANDLE CurrentRunningThreadHandle;

 /*
  * �����ͥ륹������
  *   kernel_start�ϺǸ��exit_and_dispatch��Ƥ֤Τǡ�����ƥ������˴���
  *   �����ƿ���������åɤ��������롣
  */

DWORD WINAPI
KernelStarter(LPVOID param)
{
	kernel_start();
	return 0;
}

Inline LRESULT CALLBACK
PrimaryDialogCommandHandler(WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
		case IDC_CLOCKSUPPLY:
		{
			int state;

			state = SendDlgItemMessage(PrimaryDialogHandle, IDC_CLOCKSUPPLY,BM_GETCHECK,0,0);
			if(state == BST_CHECKED)
			{
				hw_timer_terminate();
				if(CurrentRunningThreadHandle != INVALID_HANDLE_VALUE)
					SuspendThread(CurrentRunningThreadHandle);
			}else
			{
				if(state == BST_UNCHECKED)
				{
					if(CurrentRunningThreadHandle != INVALID_HANDLE_VALUE)
						ResumeThread(CurrentRunningThreadHandle);
					hw_timer_initialize();
				}
			}

			break;
		}

	default:
		return FALSE;
	}

	return TRUE;
}
Inline LRESULT CALLBACK
HALMessageHandler(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case HALMSG_DESTROY:
		if(lParam != 0)
		{
			TCB * tcb = (TCB *)lParam;
			TerminateThread(tcb->tskctxb.ThreadHandle,0);
			CloseHandle(tcb->tskctxb.ThreadHandle);
		}else
		{
			if(CurrentRunningThreadHandle != INVALID_HANDLE_VALUE)
			{
				TerminateThread(CurrentRunningThreadHandle,0);
				CloseHandle(CurrentRunningThreadHandle);
				CurrentRunningThreadHandle = INVALID_HANDLE_VALUE;
			}
		}
		runtsk = 0l;

	case HALMSG_DISPATCH:
		if(CurrentRunningThreadHandle != INVALID_HANDLE_VALUE)
			SuspendThread(CurrentRunningThreadHandle);

		if(runtsk != schedtsk)
		{
			if((int)((long)schedtsk-(long)tcb_table)/sizeof(TCB)>10)
				runtsk = 0l;
		}

		if(lParam == 0)
			runtsk = schedtsk;
		else
			runtsk = (TCB *)lParam;

		if(runtsk != 0l)
		{
			CurrentRunningThreadHandle = runtsk->tskctxb.ThreadHandle;
			ResumeThread(runtsk->tskctxb.ThreadHandle);
		}else
		{
			CurrentRunningThreadHandle = 0l;
		}

		break;

	case HALMSG_INTERRUPT:
		{
			HANDLE work;
			if(lParam != 0)
				ras_int((unsigned int)lParam);

			if((work = sch_int()) != INVALID_HANDLE_VALUE)
			{
				SuspendThread(CurrentRunningThreadHandle);
				CurrentRunningThreadHandle = work;
				ResumeThread(work);
			}

			break;
		}
	case HALMSG_EXECUTEPROCEDURE:
		{
			void ** work = (void **)lParam;
			((void (*)(void *))(*work))(*(work+1));
			break;
		}

	default:
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK PrimaryDialogProc(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case HALMSG_MESSAGE+1:
		if(lParam == WM_RBUTTONUP)
			kernel_exit();

		break;

	case HALMSG_MESSAGE:
		return HALMessageHandler(wParam,lParam);

	case WM_COMMAND:
		return PrimaryDialogCommandHandler(wParam,lParam);
	
	case WM_INITDIALOG:
		{
			DWORD ThreadID;
			NOTIFYICONDATA nid;

			nid.cbSize = sizeof(NOTIFYICONDATA);
			nid.uFlags = NIF_ICON|NIF_TIP|NIF_MESSAGE;
			nid.uID = ID_NOTIFYICON;
			lstrcpy(nid.szTip,"TOPPERS/JSP");
			nid.hWnd = hDlg;
			nid.uCallbackMessage = HALMSG_MESSAGE+1;
			nid.hIcon = LoadIcon(ProcessInstance,MAKEINTRESOURCE(IDI_ERTLICON));

			Shell_NotifyIcon(NIM_ADD,&nid);

			PrimaryThreadHandle = (HANDLE)hDlg;
			CurrentRunningThreadHandle = CreateThread(NULL,0,KernelStarter,NULL,0,&ThreadID);
			break;
		}
	case WM_CLOSE:
			kernel_exit();
			DestroyWindow(hDlg);
			break;

	case WM_DESTROY:
		{
			NOTIFYICONDATA nid;
			nid.cbSize = sizeof(NOTIFYICONDATA);
			nid.uID = ID_NOTIFYICON;
			nid.hWnd = hDlg;
			Shell_NotifyIcon(NIM_DELETE,&nid);
			InvalidateRect(GetDesktopWindow(),NULL,FALSE);
			UpdateWindow(GetDesktopWindow());
			PostQuitMessage(0);
			break;
		}
	case WM_TIMER:
		if((wParam & 0xffff0000) == 0xffff0000)
		{
			return HALMessageHandler(HALMSG_INTERRUPT,(wParam&0xffff));
		}
	default:
		return FALSE;
	}
	return TRUE;
}


int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShow)
{
	MSG msg;

	if(FAILED(CoInitialize(NULL)))
		return 0;

	ProcessInstance = hInstance;

	OnDebug InitializeDebugServices(hInstance,PrimaryDialogHandle);
	
	CurrentRunningThreadHandle = INVALID_HANDLE_VALUE;
	PrimaryDialogHandle = CreateDialog(hInstance,"PrimaryDialog",NULL,PrimaryDialogProc);
	ShowWindow(PrimaryDialogHandle,SW_HIDE);

	OnDebug ShowWindow(PrimaryDialogHandle,SW_SHOW);

	while(GetMessage(&msg,NULL,0,0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	OnDebug FinalizeDebugServices();

	CoUninitialize();
	ExitProcess(msg.wParam);
	return msg.wParam;
}