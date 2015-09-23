/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
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
 *  @(#) $Id: serial_console.c,v 1.7 2002/04/10 11:20:09 takayuki Exp $
 */


/*
 * ���ǥ��åȥܥå�����Ȥä����ꥢ�륤�󥿡��ե������⥸�塼��
 */

#include "debugout.h"
#include <jsp_services.h>
#include "kernel_id.h"
#include "hal_msg.h"
#include "resource.h"

#define SERMSG_CREATE WM_APP

#define TRANSLATE_PORTID(x) \
	x = (x != 0) ? (x) : CONSOLE_PORTID 

#define CHECK_PORTID(x) \
	( (x) > 0 && (x) <= NUM_PORT )

#define NUM_PORT 1

	/* �����ѥХåե������� (2^n�Ǥ��뤳��) */
#define SERIAL_INPUTBUFFERSIZE 0x80

	/* ɽ����ߥå��������� */
#define SERIAL_LIMITTERUPPERBOUND 0x1000
#define SERIAL_LIMITTERSIZE 0x500

	/* �ץ�ȥ����ԥ� */
void	serial_initialize(VP_INT portid);
ER		serial_open(ID portid);
int		serial_close(ID portid, int flush);
ER_UINT serial_read(ID portid, char *buf, unsigned int len);
ER_UINT serial_write(ID portid, char *buf, unsigned int len);
ER serial_ioctl(ID portid, UINT ioctl);
void	serial_handler(void);

static LRESULT CALLBACK KeyEventTrapper(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);

typedef struct serial_port_control_block {
	void * DefWndProc;
	HWND	Handle;
	ID		InputSemaphore;
	char	Buffer[SERIAL_INPUTBUFFERSIZE];
	int		Top;
	int		Tail;
} SPCB;

SPCB spcb[NUM_PORT] =
{
	{	0l, 0l, SEM_SERIAL1_IN,"",0,0	}	
};

extern HINSTANCE ProcessInstance;

#define NEXT(x) (((x)+1) & (SERIAL_INPUTBUFFERSIZE-1))


#ifdef _MSC_VER

__forceinline __declspec(naked) void * __fastcall MemoryCopy(void * dest, void * src, unsigned int size)
{
	__asm	mov	eax, ecx
	__asm	mov edi, ecx
	__asm	mov esi, edx
	__asm	pop ebx
	__asm	pop ecx
	__asm	rep movsb
	__asm	jmp ebx
}

#else
#include <string.h>
#define MemoryCopy memcpy
#endif

Inline void
CloseAllHandles(SPCB * cb)
{
	if(cb->Handle != 0l)
	{
		DestroyWindow(cb->Handle);
		cb->Handle = 0l;
	}
}

static LRESULT CALLBACK ConsoleProc(HWND hDlg,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	switch(Msg)
	{
	case SERMSG_CREATE:
		{
			SPCB * work;
			work = (SPCB *)lParam;
			work->DefWndProc = (void *)GetWindowLong(GetDlgItem(hDlg,IDC_CONSOLE),GWL_WNDPROC);
			SetWindowLong(hDlg,GWL_USERDATA,lParam);
			SetWindowLong(GetDlgItem(hDlg,IDC_CONSOLE),GWL_WNDPROC,(long)KeyEventTrapper);
			SetWindowLong(GetDlgItem(hDlg,IDC_CONSOLE),GWL_USERDATA,lParam);
			ShowWindow(hDlg,SW_SHOWNA);
			break;
		}
	case WM_DESTROY:
		{
			SPCB * scope;
			scope = (SPCB *)GetWindowLong(hDlg,GWL_USERDATA);
			scope->Handle = 0l;
			break;
		}
	case WM_CLOSE:
		break;

	case WM_CHAR:
		{
			SPCB * scope;
			scope = (SPCB *)GetWindowLong(hDlg,GWL_USERDATA);
			if(NEXT(scope->Tail) == scope->Top)
				break;	/* Buffer Overflow */
			scope->Buffer[scope->Tail] = (char)wParam;
			scope->Tail = NEXT(scope->Tail);
			syscall(sig_sem(scope->InputSemaphore));
			break;
		}


	case WM_INITDIALOG:
	case WM_SIZE:
		{
			RECT client;
			GetClientRect(hDlg,&client);
			MoveWindow(GetDlgItem(hDlg,IDC_CONSOLE),0,0,client.right,client.bottom,TRUE);
			break;
		}

	default:
		return FALSE;
	}

	return TRUE;
}

static LRESULT CALLBACK KeyEventTrapper(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	SPCB * scope;
	
	if(Msg == WM_CHAR)
	{
		scope = (SPCB *)GetWindowLong(hWnd,GWL_USERDATA);
		PostMessage(scope->Handle,WM_CHAR,wParam,lParam);
		return TRUE;
	}

	scope = (SPCB *)GetWindowLong(hWnd, GWL_USERDATA);
	return CallWindowProc(scope->DefWndProc,hWnd,Msg,wParam,lParam);
}


static void SerialConsole_FinalRelease(void * param)
{
	SPCB * cb = (SPCB *)param;
	if(cb->Handle != 0l)
		DestroyWindow(cb->Handle);
}

	/*���δؿ���PrimaryThread�ˤ�äƼ¹Ԥ����
	 *#�������ʤ��Ƚ�����ѥ���åɽ�λ���˥�����ɥ����Ĥ����Ƥ��ޤ�
	 */
static void CreateSerialConsole(SPCB * cb)
{
	cb->Handle = CreateDialog(ProcessInstance, MAKEINTRESOURCE(CONSOLEDIALOG), PrimaryDialogHandle, ConsoleProc);
	SendMessage(cb->Handle,SERMSG_CREATE,0,(LPARAM)cb);
	UpdateWindow(cb->Handle);
	HALAddDestructionProcedure(SerialConsole_FinalRelease,cb);
}




/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фε�ư
 */
void
serial_initialize(VP_INT portid)
{
	syscall(serial_open((ID)portid));
	syslog_1(LOG_NOTICE, "Serial driver service starts on port %d.", portid);
}

ER
serial_open(ID portid)
{
	SPCB * cb;

	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	HALExecuteProcedure(CreateSerialConsole,cb);

	return E_OK;
}

int
serial_close(ID portid, int flush)
{
	SPCB * cb;

	return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->Handle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	CloseAllHandles(cb);

	return E_OK;
}

ER_UINT
serial_read(ID portid, char * buf, unsigned int len)
{
	SPCB * cb;
	DWORD cnt;

	if(len == 0)
		return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid) || buf == 0l)
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->Handle == 0l)
		return E_OBJ;

	while(len>0)
	{
		cnt = 0;
		if(cb->Top != cb->Tail)
		{
			if(cb->Top > cb->Tail)
			{
				cnt = SERIAL_INPUTBUFFERSIZE - cb->Top;
				MemoryCopy(buf,cb->Buffer + cb->Top, cnt);
				buf += cnt;
				if(cb->Tail != 0)
				{
					MemoryCopy(buf,cb->Buffer, cb->Tail);
					buf += cb->Tail;
					cnt += cb->Tail;
				}
			}else
			{
				cnt = cb->Tail - cb->Top;
				MemoryCopy(buf,cb->Buffer + cb->Top, cnt);
				buf += cnt;
			}

			cb->Top = cb->Tail;
		}else
		{
			syscall(wai_sem(cb->InputSemaphore));
		}
		len -= cnt;
	}

	return E_OK;
}

ER_UINT
serial_write(ID portid,char * buf, unsigned int len)
{
	SPCB * cb;
	DWORD cnt;
	int i,j;
	char buffer[1024];
	HANDLE console;

	if(len == 0)
		return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid) || buf == 0l)
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->Handle == 0l)
		return E_OBJ;

	console = GetDlgItem(cb->Handle,IDC_CONSOLE);

	i = GetWindowTextLength(console);
	if(i > SERIAL_LIMITTERUPPERBOUND)
	{
		SendMessage(console,EM_SETSEL,0,i - SERIAL_LIMITTERSIZE);
		SendMessage(console,EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)"");
	}

	cnt = 0;
	while(cnt<len)
	{
		i = len-cnt;
		if(i>512)
			i = 511;

		for(j=0;j<i;j++,buf++)
		{
			if( (buffer[j] = *buf) == '\n')
			{
				buffer[j] = '\r';
				buffer[++j] = '\n';
			}
		}
		buffer[j] = '\x0';

		j = GetWindowTextLength(console);
		SendMessage(console,EM_SETSEL,j,j);
		SendMessage(console,EM_REPLACESEL,(WPARAM)FALSE,(LPARAM)buffer);
		
		cnt += i;
	}
	return 1;

	
	return (UINT)cnt;
}

ER
serial_ioctl(ID portid, UINT ioctl)
{
	return E_OK;
}

void
serial_handler(void)
{}
