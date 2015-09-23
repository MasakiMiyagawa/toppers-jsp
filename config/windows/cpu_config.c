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
 *  @(#) $Id: cpu_config.c,v 1.3 2001/01/09 06:54:40 takayuki Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���Windows�ѡ�
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "hal_msg.h"
#include "vwindows.h"

CRITICAL_SECTION CPULock;
volatile char CPUStatus;

/*
 *  ����������ƥ����ȤǤγ���ߥޥ���
 */
#ifdef SUPPORT_CHG_IMS
unsigned int task_sigmask;
#endif /* SUPPORT_CHG_IMS */

/*
 *  �󥿥�������ƥ����ȤǤγ���ߥޥ���
 */

void
dispatch()
{	HALDispatchRequest(0);	}


/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */



void
exit_and_dispatch() 
{
	HALDestroyRequest(runtsk);
}


/*
 *  �ץ��å���¸�ν����
 */

void
cpu_initialize()
{
	CPUStatus = 0;
	InitializeCriticalSection(&CPULock);

	/*
	 * �Ǿ���㳰�ϥ�ɥ������
	 */
	ini_exc();

	/*
	 *  ����ߥ��ߥ�졼���ν����
	 */
	ini_int();
}

/*
 *  �ץ��å���¸�ν�λ����
 */
void
cpu_terminate()
{	HALQuitRequest();	}


/*
 * ��������ư�롼����
 *
 */

DWORD WINAPI
activate_r( LPVOID param)
{
	TCB * tcb = (TCB *)param;
	__try{
		CoInitialize(NULL);
		(*tcb->tinib->task)(tcb->tinib->exinf);
		CoUninitialize();
	}
	__except( HALExceptionHandler(GetExceptionInformation()) )
	{}
	HALDestroyRequest(tcb);
	return 0;
}