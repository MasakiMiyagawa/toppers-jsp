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
 *  @(#) $Id: hw_serial.c,v 1.2 2001/11/12 14:55:23 takayuki Exp $
 */


#include "hw_serial.h"


extern HANDLE PrimaryThreadHandle;

/*
 * ���ꥢ��(����)�ǥХ����ν����
 */

BOOL
hw_port_initialize(HWPORT *p)
{
	if(p->Handle != INVALID_HANDLE_VALUE)
		CloseHandle(p->Handle);

	if( (p->Flag & SIO_SERVER) != 0)
	{
		p->Handle = CreateNamedPipe(p->DeviceName,PIPE_ACCESS_DUPLEX|FILE_FLAG_OVERLAPPED,PIPE_TYPE_BYTE|PIPE_NOWAIT,PIPE_UNLIMITED_INSTANCES,2048,2048,0,NULL);
	}else
	{
		p->Handle = CreateFile(p->DeviceName,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	}
	if(p->Handle != INVALID_HANDLE_VALUE)
	{
		SetTimer(PrimaryThreadHandle,(0xffff0000|INHNO_SERIAL),100,NULL);
		return FALSE;
	}
	return TRUE;
}

/*
 * ���ꥢ��(����)�ǥХ����Υ���åȥ�����
 */

void
hw_port_terminate(HWPORT *p)
{
	if(p->Handle != INVALID_HANDLE_VALUE)
	{
		CloseHandle(p->Handle);
		p->Handle = INVALID_HANDLE_VALUE;
	}
}

/*
 *  ʸ���������������
 */
BOOL
hw_port_getready(HWPORT *p)
{
	DWORD charinbuf;
	if((p->Flag & SIO_PIPE) != 0)
	{
		PeekNamedPipe(p->Handle,NULL,0,NULL,&charinbuf,NULL);
		return (charinbuf != 0) ? TRUE : FALSE;
	}
	return FALSE;
}

/*
 *  ʸ���������Ǥ��뤫��
 */
BOOL
hw_port_putready(HWPORT *p)
{
		/*�񤤤Ƥߤʤ��Ȥ狼��ʤ��ΤǾ�˽񤱤��Ƚ��*/
	return TRUE;
}

/*
 *  ��������ʸ���μ��Ф�
 */
byte
hw_port_getchar(HWPORT *p)
{
	DWORD chars;
	char Buffer;
	ReadFile(p->Handle,&Buffer,1,&chars,NULL);
    return Buffer;
}

/*
 *  ��������ʸ���ν񤭹���
 */
void
hw_port_putchar(HWPORT *p, byte c)
{
	DWORD chars;
	WriteFile(p->Handle,&c,1,&chars,NULL);
}

/*
 *  ��������ؿ�
 */
void
hw_port_sendstart(HWPORT *p)
{}

void
hw_port_sendstop(HWPORT *p)
{}

