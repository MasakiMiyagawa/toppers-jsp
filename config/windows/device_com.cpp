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
 *  @(#) $Id: device_com.cpp,v 1.5 2001/11/12 14:55:23 takayuki Exp $
 */


#include "sys_defs.h"

#ifdef DEVICE_ENABLE

#include <windows.h>
#define __HAL_MSG_MSGONLY
#include "hal_msg.h"

#include <objbase.h>
#include <unknwn.h>
#include <ocidl.h>

#define DEV_READ  (WM_APP + 0x10)
#define DEV_WRITE (WM_APP + 0x11)
#define DEV_QUIT WM_QUIT

/*
 * �ǥХ������ݡ��� (COM�С������)
 *    ����֥�å�
 */

//typedef struct _IID
//{
//    unsigned long x;
//    unsigned short s1;
//    unsigned short s2;
//    unsigned char  c[8];
//} IID;

	//������ID�����
const IID IID__IKernelEvents = {0x1353969D,0xE84F,0x463F,{0xB2,0x11,0x33,0x7E,0x9B,0xCF,0xB9,0x9E}};
const IID IID_IKernel = {0xD3E42099,0x3FDD,0x4A78,{0xBD,0xBD,0x4E,0x57,0xD3,0x62,0xF5,0xED}};
const CLSID CLSID_Kernel = {0x51789667,0x9F20,0x40AF,{0xAF,0x7F,0x98,0x56,0x32,0x5D,0xFB,0x0B}};


class IKernel : public IUnknown
{
public:
	STDMETHOD(Read)(unsigned long address,unsigned long sz,char __RPC_FAR data[]) PURE;
	STDMETHOD(IsValid)(BOOL __RPC_FAR * valid) PURE;
	STDMETHOD(Write)(unsigned long address,unsigned long sz,char __RPC_FAR data[]) PURE;
};

class IKernelEvents : public IUnknown
{
public:
	STDMETHOD(QueryInterface)(REFIID iid, void ** unk);
	STDMETHOD_(ULONG,AddRef)();
	STDMETHOD_(ULONG,Release)();
	STDMETHOD(OnInterruptRequest)(unsigned long inhno);

	IKernelEvents(void);

	long RefCount;
};


	//�ץ�ȥ�������� (device_com.h��C������ͤʤΤ�)
extern "C" void _cdecl InitializeDeviceSupportModule(void);
extern "C" void _cdecl FinalizeDeviceSupportModule(void);
extern "C" int _cdecl DeviceRead(unsigned long address, unsigned long size, void * storage);
extern "C" int _cdecl DeviceWrite(unsigned long address, unsigned long size, void * storage);

extern "C" int ena_int(unsigned int);
extern "C" int dis_int(unsigned int);


/*
 * �ǥХ������ݡ��� (COM version)
 *    �����֥�å�
 */

static HANDLE WorkerThread;
static DWORD WorkerThreadID;
static HANDLE Blocker;

struct tagParameter
{
	unsigned long address;
	unsigned long size;
	void * storage;
};

bool Advise(IUnknown * container, REFIID iid, IUnknown * sink, DWORD * cookie, IConnectionPoint ** pcp = NULL)
{
	IConnectionPointContainer * cpc;
	IConnectionPoint * cp;

	if(pcp == NULL)
		pcp = &cp;

	container->QueryInterface(IID_IConnectionPointContainer, (void **)&cpc);
	if(cpc == 0)
		return false;

	cpc->FindConnectionPoint(iid, pcp);
	cpc->Release();
	if(*pcp == 0)
		return false;

	if(FAILED((*pcp)->Advise(sink, cookie)))
		return false;

	if(pcp == &cp)
		cp->Release();
	return true;
}

DWORD WINAPI WorkerThreadProcess(LPVOID _param)
{
	IKernel * manager;
	IKernelEvents * sink;
	IConnectionPoint * cp;
	DWORD cookie;
	BOOL Success;
	MSG msg;
	tagParameter * param;

		/*
		 * Initialize
		 */
	::CoInitialize(NULL);

	manager = 0;
	if(FAILED(::CoCreateInstance(CLSID_Kernel, NULL, CLSCTX_ALL, IID_IKernel, (void **)&manager)))
		goto _WorkerThreadProc_Cleanup;

	cp = 0;
	sink = new IKernelEvents;
	if(!Advise(manager, IID__IKernelEvents, sink, &cookie,&cp))
	{
		delete sink;
		goto _WorkerThreadProc_Cleanup;
	}

	manager->IsValid(&Success);
	if(Success != 0)
	{
		::SetEvent(Blocker);

		while( ::GetMessage(&msg, NULL, 0,0) != 0 )
		{
			switch(msg.message)
			{
			case DEV_READ:
				param = (tagParameter *)msg.lParam;
				manager->Read(param->address, param->size, (char *)param->storage);
				break;
			case DEV_WRITE:
				param = (tagParameter *)msg.lParam;
				manager->Write(param->address, param->size, (char *)param->storage);
				break;
			default:
				::DispatchMessage(msg);
			}
			::SetEvent(Blocker);
		}
	}
		/*
		 * Finalize
		 */

	if(cp != 0)
	{
		cp->Unadvise(cookie);
		cp->Release();
		cp = 0;
		sink = 0;
	}


_WorkerThreadProc_Cleanup:

	if(manager != 0)
		manager->Release();
	manager = 0l;
	WorkerThreadID = 0;
	WorkerThread = 0;
	::SetEvent(Blocker);
	::CloseHandle(Blocker);
	Blocker = INVALID_HANDLE_VALUE;
	::CoUninitialize();
	return 0;
}


extern "C"
void _cdecl InitializeDeviceSupportModule(void)
{
	Blocker = ::CreateEvent(NULL,FALSE,FALSE,NULL);
	WorkerThread = ::CreateThread(NULL,0,WorkerThreadProcess,NULL,NULL,&WorkerThreadID);
	::WaitForSingleObject(Blocker,INFINITE);
}

extern "C"
void _cdecl FinalizeDeviceSupportModule(void)
{
	::PostThreadMessage(WorkerThreadID,DEV_QUIT,0,0);
	::WaitForSingleObject(WorkerThread,INFINITE);
}

extern "C"
int _cdecl DeviceRead(unsigned long address, unsigned long size, void * storage)
{
	tagParameter param;

	if(WorkerThreadID == 0)
		return -1;
	
	dis_int(0);
	param.address = address;
	param.size = size;
	param.storage = storage;
	::PostThreadMessage(WorkerThreadID, DEV_READ, 0, (LPARAM)&param);
	::WaitForSingleObject(Blocker,INFINITE);
	ena_int(0);

	return size;
}

extern "C"
int _cdecl DeviceWrite(unsigned long address, unsigned long size, void * storage)
{
	tagParameter param;

	if(WorkerThreadID == 0)
		return -1;

	dis_int(0);
	param.address = address;
	param.size = size;
	param.storage = storage;
	::PostThreadMessage(WorkerThreadID, DEV_WRITE, 0, (LPARAM)&param);
	::WaitForSingleObject(Blocker,INFINITE);
	ena_int(0);

	return size;
}


/*
 *   IKernelEvents����
 */

IKernelEvents::IKernelEvents(void) : RefCount(0)
{}

HRESULT IKernelEvents::QueryInterface(REFIID iid, void ** unk)
{
	if( iid == IID__IKernelEvents || iid == IID_IUnknown )
	{
		*unk = this;
		::InterlockedIncrement(&RefCount);
		return S_OK;
	}

	return E_NOINTERFACE;
}

ULONG IKernelEvents::AddRef()
{	return ::InterlockedIncrement(&RefCount);	}

ULONG IKernelEvents::Release()
{
	if( ::InterlockedDecrement(&RefCount) == 0)
		delete this;
	return RefCount;
}

extern "C" HANDLE PrimaryDialogHandle;
HRESULT IKernelEvents::OnInterruptRequest(unsigned long inhno)
{
	::PostMessage((HWND)PrimaryDialogHandle,HALMSG_MESSAGE,HALMSG_INTERRUPT,(LPARAM)inhno);
	return S_OK;
}

#endif
