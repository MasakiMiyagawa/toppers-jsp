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
 *  @(#) $Id: devicecontrol.cpp,v 1.1 2001/02/23 12:33:45 takayuki Exp $
 */

#include "stdafx.h"
#include "device.h"
#include "devicecontrol.h"

/////////////////////////////////////////////////////////////////////////////
// CDeviceControl

const CLSID CLSID_Device = {0xFEE2A68B,0x7F98,0x40E0,{0x98,0x53,0x18,0x3E,0xE6,0x8B,0xC7,0xF8}};

__declspec(naked) void * __fastcall MemoryCopy(void * dest, void * src, unsigned int size)
{
	__asm	mov	eax, ecx
	__asm	mov edi, ecx
	__asm	mov esi, edx
	__asm	pop ebx
	__asm	pop ecx
	__asm	rep movsb
	__asm	jmp ebx
}

STDMETHODIMP CDeviceControl::Connect()
{
	if(!FAILED(manager.CoCreateInstance(CLSID_Device)) && !FAILED(manager.Advise((_IDeviceEvents *)this,__uuidof(_IDeviceEvents),&cookie)))
		return S_OK;

	if(! !manager)
		manager.Release();
	return E_FAIL;
}

STDMETHODIMP CDeviceControl::Close()
{
	if(!manager)
		return E_FAIL;

	AtlUnadvise(manager,__uuidof(_IDeviceEvents),cookie);
	manager.Release();
	cookie = 0;
	return S_OK;
}

STDMETHODIMP CDeviceControl::get_Valid(BOOL *pVal)
{
	*pVal = !manager ? FALSE : ~0;
	return S_OK;
}

STDMETHODIMP CDeviceControl::RaiseInterrupt(long inhno)
{
	if(!manager)
		return E_FAIL;
	
	return manager->RaiseInterrupt(inhno);
}

STDMETHODIMP CDeviceControl::Map(long address, long size)
{
	if(!manager)
		return E_FAIL;

	return manager->Map(address, size);
}

STDMETHODIMP CDeviceControl::Unmap(long address)
{
	if(!manager)
		return E_FAIL;

	return manager->Unmap(address);
}


STDMETHODIMP CDeviceControl::get_IsKernelStarted(BOOL *pVal)
{
	*pVal = KernelStarted ? ~0 : 0;
	return S_OK;
}

STDMETHODIMP CDeviceControl::get_Offset(long *pVal)
{
	*pVal = Offset;
	return S_OK;
}

STDMETHODIMP CDeviceControl::put_Offset(long newVal)
{
	if(newVal >= Limitation)
		return E_FAIL;

	Offset = newVal;

	return S_OK;
}

STDMETHODIMP CDeviceControl::get_AccessSize(short *pVal)
{
	*pVal = AccessSize;
	return S_OK;
}

STDMETHODIMP CDeviceControl::put_AccessSize(short newVal)
{
	switch(newVal)
	{
	case 1: case 2: case 4:
		break;
	default:
		return E_FAIL;
	}

	AccessSize = newVal;
	return S_OK;
}

STDMETHODIMP CDeviceControl::get_Value(long *pVal)
{
	if(DataPointer == 0)
		return E_FAIL;

	*pVal = 0;
	MemoryCopy(pVal, DataPointer + Offset, AccessSize);

	Offset += AccessSize;
	if(Offset >= Limitation)
		Offset = Limitation -1;
	
	return S_OK;
}

STDMETHODIMP CDeviceControl::put_Value(long newVal)
{
	if(DataPointer == 0)
		return E_FAIL;

	MemoryCopy(DataPointer + Offset, &newVal, AccessSize);

	Offset += AccessSize;
	if(Offset >= Limitation)
		Offset = Limitation -1;

	return S_OK;
}

STDMETHODIMP CDeviceControl::OnRead(long address,long sz,byte __RPC_FAR data[])
{
	if(!KernelStarted)
		this->OnKernelStart();

	DataPointer = (unsigned char *)data;
	Limitation = sz;
	Offset = 0;

	Fire_OnRead(address, sz);
	
	DataPointer = 0;
	return S_OK;
}

STDMETHODIMP CDeviceControl::OnWrite(long address,long sz,byte __RPC_FAR data[])
{
	if(!KernelStarted)
		this->OnKernelStart();

	DataPointer = (unsigned char *)data;
	Limitation = sz;
	Offset = 0;
	Fire_OnWrite(address,sz);
	DataPointer = 0;
	return S_OK;
}

STDMETHODIMP CDeviceControl::OnKernelStart()
{
	KernelStarted = true;
	Fire_OnKernelStart();
	return S_OK;
}

STDMETHODIMP CDeviceControl::OnKernelExit()
{
	KernelStarted = false;
	Fire_OnKernelExit();
	return S_OK;
}
