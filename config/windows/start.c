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
 *  @(#) $Id: start.c,v 1.6 2001/11/12 14:55:23 takayuki Exp $
 */


#include "jsp_kernel.h"
#include "task.h"
#include "vwindows.h"
#include "hal_msg.h"
#include "hw_timer.h"
#include "objbase.h"
#include "shellapi.h"
#include "resource.h"


struct tagDestructionProcedureQueue
{
	struct tagDestructionProcedureQueue * Next;
	void (*DestructionProcedure)(void *);
	void * Parameter;
};

extern void kernel_start();
extern void kernel_exit();

HINSTANCE ProcessInstance;
HANDLE PrimaryThreadHandle;
HWND PrimaryDialogHandle;
HANDLE CurrentRunningThreadHandle;
HANDLE ForceShutdownHandle = INVALID_HANDLE_VALUE;

struct tagDestructionProcedureQueue * DestructionProcedureQueue;

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

DWORD WINAPI
ForceShutdownHandler(LPVOID param)
{
	Sleep(10000);
	ExitProcess(0);
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
			tcb->tskctxb.ThreadHandle = INVALID_HANDLE_VALUE;
		}else
		{
			if(CurrentRunningThreadHandle != INVALID_HANDLE_VALUE)
			{
				TerminateThread(CurrentRunningThreadHandle,0);
				CloseHandle(CurrentRunningThreadHandle);
				if(runtsk != 0)
					runtsk->tskctxb.ThreadHandle = INVALID_HANDLE_VALUE;
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
			_kernel_calltex();
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
	case HALMSG_ADDDESTRUCTIONPROCEDURE:
		{
			struct tagDestructionProcedureQueue * scope;
			void ** work = (void **)lParam;

			scope = DestructionProcedureQueue;

			if((DestructionProcedureQueue = GlobalAlloc(GMEM_FIXED, sizeof(struct tagDestructionProcedureQueue))) != NULL)
			{
				DestructionProcedureQueue->DestructionProcedure = *(work);
				DestructionProcedureQueue->Parameter = *(work+1);
				DestructionProcedureQueue->Next = scope;
			}
			break;
		}
	case HALMSG_QUITREQUEST:
		{
			struct tagDestructionProcedureQueue * destqueue;
			void * destarea;

			ForceShutdownHandle = CreateThread(NULL, 0, ForceShutdownHandler, 0, NULL, NULL);

			hw_timer_terminate();

			if(CurrentRunningThreadHandle != NULL)
				SuspendThread(CurrentRunningThreadHandle);

			destqueue = DestructionProcedureQueue;
			while(destqueue != NULL)
			{
				(*destqueue->DestructionProcedure)(destqueue->Parameter);
				destarea = destqueue;
				destqueue = destqueue->Next;
				GlobalFree((HGLOBAL)destarea);
			}

			fin_int();
			fin_exc();
			DeleteCriticalSection(&CPULock);

			DestroyWindow(PrimaryDialogHandle);
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

			PrimaryDialogHandle = hDlg;

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
			break;

	case WM_DESTROY:
		{
			NOTIFYICONDATA nid;

			nid.cbSize = sizeof(NOTIFYICONDATA);
			nid.hWnd = PrimaryThreadHandle;
			nid.uID = ID_NOTIFYICON;
			Shell_NotifyIcon(NIM_DELETE,&nid);

			PrimaryThreadHandle = INVALID_HANDLE_VALUE;
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
	DestructionProcedureQueue = NULL;

	OnDebug InitializeDebugServices(hInstance,PrimaryDialogHandle);
	OnDevice InitializeDeviceSupportModule();

	CurrentRunningThreadHandle = INVALID_HANDLE_VALUE;
	CreateDialog(hInstance,"PrimaryDialog",NULL,PrimaryDialogProc);
	ShowWindow(PrimaryDialogHandle,SW_HIDE);

	OnDebug ShowWindow(PrimaryDialogHandle,SW_SHOW);

	while(GetMessage(&msg,NULL,0,0) != 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message == WM_QUIT)
			msg.message = 0;
	}

	OnDevice FinalizeDeviceSupportModule();
	OnDebug FinalizeDebugServices();

	{
		int i;
			for(i=0;i<_kernel_tmax_tskid;i++)
			{
				if(_kernel_tcb_table[i].tskctxb.ThreadHandle != INVALID_HANDLE_VALUE)
				{
					TerminateThread(_kernel_tcb_table[i].tskctxb.ThreadHandle,0);
					CloseHandle(_kernel_tcb_table[i].tskctxb.ThreadHandle);
					_kernel_tcb_table[i].tskctxb.ThreadHandle = INVALID_HANDLE_VALUE;
				}
			}
	}

	CoUninitialize();

	if(ForceShutdownHandle != INVALID_HANDLE_VALUE)
	{
		TerminateThread(ForceShutdownHandle,0);
		CloseHandle(ForceShutdownHandle);
	}

	ExitProcess(msg.wParam);
	return msg.wParam;
}