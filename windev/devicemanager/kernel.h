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
 *  @(#) $Id: kernel.h,v 1.2 2001/02/23 09:46:47 takayuki Exp $
 */

#ifndef __KERNEL_H_
#define __KERNEL_H_

#include "resource.h"       // �ᥤ�� ����ܥ�
#include "devicemanagerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CKernel
class ATL_NO_VTABLE CKernel : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CKernel, &CLSID_Kernel>,
	public IConnectionPointContainerImpl<CKernel>,
	public IKernel,
	public CProxy_IKernelEvents< CKernel >
{
public:
	CKernel();
	~CKernel();

DECLARE_REGISTRY_RESOURCEID(IDR_KERNEL)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CKernel)
	COM_INTERFACE_ENTRY(IKernel)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CKernel)
CONNECTION_POINT_ENTRY(IID__IKernelEvents)
END_CONNECTION_POINT_MAP()


// IKernel
public:
	STDMETHOD(Write)(unsigned long address, unsigned long sz, unsigned char data[]);
	STDMETHOD(IsValid)(BOOL * valid);
	STDMETHOD(Read)(unsigned long address, unsigned long sz, unsigned char data[]);

	bool Valid;
};

#endif //__KERNEL_H_
