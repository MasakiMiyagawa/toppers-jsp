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
 *  @(#) $Id: serial_pipe.c,v 1.1 2000/11/14 16:31:38 takayuki Exp $
 */
/*
 * Windows�Υѥ��פ�Ȥä����ꥢ�륤�󥿡��ե������⥸�塼��
 *  (��)���̤Υ��ꥢ��ϻȤ��ޤ���
 */

#include "Debug.h"
#include <jsp_services.h>
#include "kernel_id.h"

#define TRANSLATE_PORTID(x) \
	x = (x != 0) ? (x) : CONSOLE_PORTID 

#define CHECK_PORTID(x) \
	( (x) > 0 && (x) <= NUM_PORT )

#define INHNO_SERIAL	3
#define NUM_PORT 1
#define SIO_POLINTERVAL 300

	/* �ץ�ȥ����ԥ� */
void	serial_initialize(ID portid);
ER		serial_open(ID portid);
int		serial_close(ID portid, int flush);
ER_UINT serial_read(ID portid, char *buf, unsigned int len);
ER_UINT serial_write(ID portid, char *buf, unsigned int len);
int		serial_ioctl(ID portid, int req, int arg);
void	serial_handler(void);


typedef struct serial_port_control_block {
	char *	DeviceName;
	HANDLE	DeviceHandle;
	ID		InSem;
	HANDLE	PipeWatcherHandle;
	DWORD	PipeWatcherID;
} SPCB;

SPCB spcb[NUM_PORT] =
{
	{ "\\\\.\\pipe\\toppersserial", INVALID_HANDLE_VALUE, SEM_SERIAL1_IN, INVALID_HANDLE_VALUE, 0 }
};

DWORD WINAPI
PipeWatcher(LPVOID param)
{
	SPCB * cb = (SPCB *)param;
	DWORD count;
	char Buffer;

	while(1==1)
	{
		if(ReadFile(cb->DeviceHandle,&Buffer,0,&count,NULL)==0)
		{
			syscall(sig_sem(cb->InSem));
			ExitThread(0);
		}
		syscall(sig_sem(cb->InSem));
		SuspendThread(GetCurrentThread());
	}
	return 0;
}

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фε�ư
 */
void
serial_initialize(ID portid)
{
	syscall(serial_open(portid));
	syslog(LOG_NOTICE, "Serial driver service starts on port %d.", portid);
}

ER
serial_open(ID portid)
{
	SPCB * cb;

	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	cb->DeviceHandle = CreateFile(cb->DeviceName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	cb->PipeWatcherHandle = CreateThread(NULL,0,PipeWatcher,(LPVOID)cb,0,&cb->PipeWatcherID);

	return (cb->DeviceHandle != INVALID_HANDLE_VALUE) ? E_OK : E_OBJ;
}

int
serial_close(ID portid, int flush)
{
	SPCB * cb;

	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->DeviceHandle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	if(flush != 0)
		FlushFileBuffers(cb->DeviceHandle);
	CloseHandle(cb->DeviceHandle);
	TerminateThread(cb->PipeWatcherHandle,0);
	CloseHandle(cb->PipeWatcherHandle);
	cb->DeviceHandle = INVALID_HANDLE_VALUE;

	return (cb->DeviceHandle != INVALID_HANDLE_VALUE) ? E_OK : E_OBJ;
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
	if(cb->DeviceHandle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	DebugOut(wsprintf(DebugBuffer,"SERIAL_READ"));

	do{
		PeekNamedPipe(cb->DeviceHandle,NULL,NULL,NULL,&cnt,NULL);
		if(cnt < len)
		{
			ResumeThread(cb->PipeWatcherHandle);
			syscall(wai_sem(cb->InSem));
		}
	}while(cnt < len);


	if(ReadFile(cb->DeviceHandle,buf,len,&cnt,NULL) == 0)
		return E_OBJ;
	
	return (UINT)cnt;
}

ER_UINT
serial_write(ID portid,char * buf, unsigned int len)
{
	SPCB * cb;
	DWORD cnt;
	OVERLAPPED ovr;

	if(len == 0)
		return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid) || buf == 0l)
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->DeviceHandle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	DebugOut(wsprintf(DebugBuffer,"SERIAL_WRITE"));

	ovr.hEvent = INVALID_HANDLE_VALUE;
	if(WriteFile(cb->DeviceHandle,buf,len,&cnt,&ovr) == 0)
		return E_OBJ;
	
	return (UINT)cnt;
}

int
serial_ioctl(ID portid,int req,int arg)
{
	return E_OK;
}

void
serial_handler(void)
{}
