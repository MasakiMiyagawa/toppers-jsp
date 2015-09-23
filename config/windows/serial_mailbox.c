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
 *  @(#) $Id: serial_mailbox.c,v 1.3 2001/11/12 14:55:23 takayuki Exp $
 */


/*
 * Windows�Υ᡼�륹��åȤ�Ȥä����ꥢ�륤�󥿡��ե������⥸�塼��
 *  (��)���̤Υ��ꥢ��(COM�ǥХ���)�ϻȤ��ޤ���
 */

#include <jsp_services.h>
#include "kernel_id.h"

#define TRANSLATE_PORTID(x) \
	x = (x != 0) ? (x) : CONSOLE_PORTID 

#define CHECK_PORTID(x) \
	( (x) > 0 && (x) <= NUM_PORT )

#define CLOSE_HANDLE(x) \
	CloseHandle(x), x=INVALID_HANDLE_VALUE;

#define INHNO_SERIAL	3
#define NUM_PORT 1
#define SIO_POLINTERVAL 300

	/* �ץ�ȥ����ԥ� */
void	serial_initialize(VP_INT portid);
ER		serial_open(ID portid);
int		serial_close(ID portid, int flush);
ER_UINT serial_read(ID portid, char *buf, unsigned int len);
ER_UINT serial_write(ID portid, char *buf, unsigned int len);
ER		serial_ioctl(ID portid, UINT ioctl);
void	serial_handler(void);

typedef struct serial_port_control_block {
	char *	InDevName;
	HANDLE	InDevHandle;
	ID		InSemaphore;

	char *	OutDevName;
	HANDLE	OutDevHandle;

	HANDLE	MailWatcherHandle;
	DWORD	MailWatcherID;
} SPCB;

SPCB spcb[NUM_PORT] =
{
	{
		"\\\\.\\mailslot\\toppers\\serial_in", INVALID_HANDLE_VALUE, SEM_SERIAL1_IN,
		"\\\\.\\mailslot\\toppers\\serial_out", INVALID_HANDLE_VALUE,
		INVALID_HANDLE_VALUE, 0
	}
};

DWORD WINAPI
MailWatcher(LPVOID param)
{
	SPCB * cb = (SPCB *)param;
	DWORD count;
	char Buffer;

	while(1==1)
	{
		ReadFile(cb->InDevHandle,&Buffer,0,&count,NULL);
		/*{
			count = GetLastError();
			syscall(sig_sem(cb->InSemaphore));
			CloseHandle(cb->MailWatcherHandle);
			cb->MailWatcherHandle = INVALID_HANDLE_VALUE;
			ExitThread(0);
		}*/
		syscall(sig_sem(cb->InSemaphore));
		SuspendThread(GetCurrentThread());
	}
	return 0;
}

Inline void
CloseAllHandles(SPCB * cb)
{
	if(cb->MailWatcherHandle != INVALID_HANDLE_VALUE)
	{
		TerminateThread(cb->MailWatcherHandle,0);
		CLOSE_HANDLE(cb->MailWatcherHandle);

		if(cb->OutDevHandle != INVALID_HANDLE_VALUE)
			CLOSE_HANDLE(cb->OutDevHandle);
	
		if(cb->InDevHandle != INVALID_HANDLE_VALUE)
			CLOSE_HANDLE(cb->InDevHandle);
	}
}


/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фε�ư
 */
void
serial_initialize(VP_INT portid)
{
	syscall(serial_open((int)portid));
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


	if((cb->OutDevHandle = CreateFile(cb->OutDevName,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL)) == INVALID_HANDLE_VALUE)
	{
		CloseAllHandles(cb);
		return E_OBJ;
	}

	if((cb->InDevHandle = CreateMailslot(cb->InDevName,0,MAILSLOT_WAIT_FOREVER,NULL)) == INVALID_HANDLE_VALUE)
	{
		CloseAllHandles(cb);
		return E_OBJ;
	}

	if((cb->MailWatcherHandle = CreateThread(NULL,0,MailWatcher,(void *)cb,CREATE_SUSPENDED,&cb->MailWatcherID)) == NULL)
	{
		cb->MailWatcherHandle = INVALID_HANDLE_VALUE;
		CloseAllHandles(cb);
		return E_OBJ;
	}

	return E_OK;
}

int
serial_close(ID portid, int flush)
{
	SPCB * cb;

	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid))
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->MailWatcherHandle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	if(flush != 0)
		FlushFileBuffers(cb->OutDevHandle);

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
	if(cb->MailWatcherHandle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	while(len>0)
	{
		GetMailslotInfo(cb->InDevHandle,NULL,&cnt,NULL,NULL);
		if(cnt == MAILSLOT_NO_MESSAGE)
		{
			ResumeThread(cb->MailWatcherHandle);
			syscall(wai_sem(cb->InSemaphore));
		}

		if(ReadFile(cb->InDevHandle,buf,len,&cnt,NULL)==0)
		{
			cnt = GetLastError();
			return E_OBJ;
		}

		len -= cnt;
		buf += cnt;
	}

	return E_OK;
}

ER_UINT
serial_write(ID portid,char * buf, unsigned int len)
{
	SPCB * cb;
	DWORD cnt;

	if(len == 0)
		return 0;
	TRANSLATE_PORTID(portid);
	if(!CHECK_PORTID(portid) || buf == 0l)
		return E_PAR;

	cb = &spcb[portid-1];
	if(cb->MailWatcherHandle == INVALID_HANDLE_VALUE)
		return E_OBJ;

	if(WriteFile(cb->OutDevHandle,buf,len,&cnt,NULL) == 0)
		return E_OBJ;
	
	return (UINT)cnt;
}

int
serial_ioctl(ID portid,UINT ioctl)
{
	return E_OK;
}

void
serial_handler(void)
{}
