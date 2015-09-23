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
 *  @(#) $Id: device.c,v 1.3 2002/04/10 11:20:09 takayuki Exp $
 */

#include "device.h"
#include "messages.h"
#include "hal_msg.h"
#include "cpu_defs.h"

	//����ͤ���� (�����륹������)
#define BLOCK 1
#define NONBLOCK 0

	//����ѿ������
struct tagDeviceGlobalVariables DeviceVars;

	//����ѿ������ (�����륹������)
static unsigned char MessageBuffer[MAX_MSGSIZE];
static DWORD MessageSize;


Inline Lock(void)
{
	dis_int(0);
	//EnterCriticalSection(&DeviceVars.cs);	
}

Inline Unlock(void)
{
	ena_int(0);
	LeaveCriticalSection(&DeviceVars.cs);	
}
	
static BOOL Send(void * data, unsigned long size, int mode)
{
	DWORD count;

	if(WriteFile(DeviceVars.ManagerSlot, data, size, &count,NULL) == 0)
		return FALSE;

	if(mode == BLOCK)
		if(WaitForSingleObject(DeviceVars.Blocker, DEVICE_TIMEOUT) != WAIT_OBJECT_0)
			return FALSE;

	return TRUE;
}


static DWORD WINAPI ListenerThread(LPVOID param)
{
	while(1==1)
	{
		if(ReadFile(DeviceVars.ReplySlot,MessageBuffer,MAX_MSGSIZE,&MessageSize,NULL) == 0)
			break;
		
		switch(MessageBuffer[0])
		{
		case MSG_ACK:
		case MSG_NAK:
			SetEvent(DeviceVars.Blocker);
			WaitForSingleObject(DeviceVars.ThreadBlocker,INFINITE);
			break;

		case MSG_KERREP_INTERRUPT:
			{
				char msg = MSG_ACK;
				HALInterruptRequest(*(int *)&MessageBuffer[1]);
				Send(&msg,1,NONBLOCK);
				break;
			}

		default:
			if( (MessageBuffer[0] & 0x80) != 0)
			{
					//�����׵��NAK�Ǳ�����
				char msg;
				msg = MSG_NAK;
				Send(&msg,1,NONBLOCK);
			}
		}
	}

	return 0;
}

void InitializeDeviceSupportModule(void)
{
	unsigned char work = 0xff;
	char buffer[128];
	int i;

	InitializeCriticalSection(&DeviceVars.cs);

		//�᡼�륹��å�̾�η���
	i = wsprintf(buffer+1,"\\\\.\\mailslot\\toppers\\kernel%08x\\deviceport",GetCurrentProcessId())+1;

	work &= (DeviceVars.ReplySlot = CreateMailslot(buffer+1,MAX_MSGSIZE,MAILSLOT_WAIT_FOREVER,NULL)) != INVALID_HANDLE_VALUE;
	work &= (DeviceVars.Blocker = CreateEvent(NULL,FALSE,FALSE,NULL)) != INVALID_HANDLE_VALUE;
	work &= (DeviceVars.ThreadBlocker = CreateEvent(NULL,FALSE,FALSE,NULL)) != INVALID_HANDLE_VALUE;
	work &= (DeviceVars.ManagerSlot = CreateFile("\\\\.\\mailslot\\toppers\\device\\devicemanager",GENERIC_WRITE,FILE_SHARE_WRITE|FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) != INVALID_HANDLE_VALUE;

	if(work)
		work &= (DeviceVars.ListenerThread = CreateThread(NULL,0,ListenerThread,NULL,NULL,&DeviceVars.ListenerThreadID)) != NULL;

	if(!work)
	{
		CloseHandle(DeviceVars.ManagerSlot);
		CloseHandle(DeviceVars.Blocker);
		CloseHandle(DeviceVars.ThreadBlocker);
		return;
	}

	*(unsigned char *)&buffer[0] = MSG_KERREQ_KERNELSTART;
	Send(&buffer,i,BLOCK);
	SetEvent(DeviceVars.ThreadBlocker);
}

void FinalizeDeviceSupportModule(void)
{
	unsigned char msg;

	Lock();
	if(DeviceVars.ListenerThread != NULL)
	{
		msg = MSG_KERREQ_KERNELEXIT;
		Send(&msg,1,BLOCK);

		TerminateThread(DeviceVars.ListenerThread,0);
		WaitForSingleObject(DeviceVars.ListenerThread,INFINITE);
		CloseHandle(DeviceVars.ListenerThread);
		DeviceVars.ListenerThread = NULL;

		CloseHandle(DeviceVars.Blocker);
		CloseHandle(DeviceVars.ThreadBlocker);
		CloseHandle(DeviceVars.ManagerSlot);
		CloseHandle(DeviceVars.ReplySlot);
	}
	Unlock();
	DeleteCriticalSection(&DeviceVars.cs);
}

int DeviceRead(unsigned long address, unsigned long size, void * storage)
{
	unsigned char buffer[16];
	int result;

	if(size > MAX_MSGSIZE-9)
		return -1;

	Lock();

	if(DeviceVars.ListenerThread == NULL)
	{
		Unlock();
		return -1;
	}

	buffer[0] = MSG_KERREQ_READ;
	*(unsigned long *)&buffer[1] = address;
	*(unsigned long *)&buffer[5] = size;
	
	Send(buffer,9,BLOCK);

	if( MessageBuffer[0] == 0 )
	{
		result = MessageSize - 1;

		if((unsigned)result > size)
			result = size;

		MoveMemory(storage, &MessageBuffer[1], result);
	}else
		result = -1;

	SetEvent(DeviceVars.ThreadBlocker);
	Unlock();

	return result;
}

int DeviceWrite(unsigned long address, unsigned long size, void * storage)
{
	unsigned char buffer[MAX_MSGSIZE];
	int result;

	if(size > MAX_MSGSIZE-9)
		return -1;

	Lock();

	if(DeviceVars.ListenerThread == NULL)
	{
		Unlock();
		return -1;
	}

	buffer[0] = MSG_KERREQ_WRITE;
	*(unsigned long *)&buffer[1] = address;
	*(unsigned long *)&buffer[5] = size;
	MoveMemory( &buffer[9], storage, size);
	
	Send(buffer, 9+size, BLOCK);

	result = MessageBuffer[0] == 0 ? size : -1;

	SetEvent(DeviceVars.ThreadBlocker);
	Unlock();

	return result;
}
