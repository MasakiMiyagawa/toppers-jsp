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
 *  @(#) $Id: stdafx.h,v 1.2 2002/04/10 11:27:26 takayuki Exp $
 */

#if !defined(AFX_STDAFX_H__4015F3E9_0639_43DE_A5EE_C32ECAFDFC74__INCLUDED_)
#define AFX_STDAFX_H__4015F3E9_0639_43DE_A5EE_C32ECAFDFC74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0400
#endif
#define _ATL_APARTMENT_THREADED

#pragma warning(push)
#pragma warning(disable:4786)

#include <list>
#include <map>
#include "range.h"
#include "messages.h"

typedef unsigned long DeviceID;

#include <atlbase.h>
// CComModule ���饹���������������饹����Ѥ��ơ������С��饤�ɤ�����
// _Module ��̾�����ѹ����ʤ��Ǥ���������
class CExeModule : public CComModule
{
public:
	bool RaiseInterrupt(unsigned long inhno);
	bool Write(class CKernel * kernel, unsigned long address, unsigned long sz, unsigned char data[]);
	bool Read(class CKernel * kernel, unsigned long address, unsigned long sz, unsigned char data[]);
	bool DetachKernel(class CKernel * kernel);
	bool AttachKernel(class CKernel * kernel);
	void RemoveViewer(class CInformation * view);
	void AddViewer(class CInformation * view);
	bool Unmap(class CDevice * device, unsigned long address);
	bool Map(class CDevice * device, Range map);
	bool DeleteDevice(class CDevice * device);
	DeviceID AddDevice(class CDevice * device);

		//����˺��줿��ʬ
	LONG Unlock();
	DWORD dwThreadID;
	HANDLE hEventShutdown;
	void MonitorShutdown();
	bool StartMonitor();
	bool bActivity;


		//��ʬ�Ǻ�ä���ʬ
	CRITICAL_SECTION cs;
	class CKernel * Kernel;
	std::map<Range, class CDevice *> DeviceMap;
	std::list<class CDevice *> DeviceList;
	std::list<class CInformation *> ViewerList;
	

	CExeModule(void);
	
};
extern CExeModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �����Ԥ�ľ�����ɲä�������������ޤ���

#pragma warning(pop)

#endif // !defined(AFX_STDAFX_H__4015F3E9_0639_43DE_A5EE_C32ECAFDFC74__INCLUDED)
