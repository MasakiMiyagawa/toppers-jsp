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
 *  @(#) $Id: fc_windows.cpp,v 1.2 2001/11/12 14:59:27 takayuki Exp $
 */



#include "filecontainer.h"

#include "exception.h"
#include "message.h"

#include <windows.h>
#include <imagehlp.h>

#include <string>

using namespace std;

class filecontainer_windows : public filecontainer
{
protected:
	HANDLE process;
	LOADED_IMAGE image;
	DWORD base;

public:
	filecontainer_windows(void);
	~filecontainer_windows(void);

	virtual bool attach_module(const char *);
	virtual bool change_endian(void * target, unsigned int size);
	virtual bool load_contents(void * dest, unsigned long address, unsigned int size);
	virtual unsigned long get_symbol_address(const char *);
	virtual const char * get_architecture(void) { return "Windows"; };

} Instance_of_filecontainer_windows;

filecontainer_windows::filecontainer_windows(void)
{
	process = 0;
	base = 0;
	container = this;
}

filecontainer_windows::~filecontainer_windows(void)
{}


bool filecontainer_windows::attach_module(const char * filename)
{
	process = ::GetCurrentProcess();
	if(::SymInitialize( process , NULL, FALSE) == FALSE)
	{
		Exception::Throw(Message("Internal Error : ImageHelper API initialization failure","�������顼 : ������˼��Ԥ��ޤ��� (ImageHlp)"));
		return false;
	}
	
	base = ::SymLoadModule(process, NULL, const_cast<char *>(filename), NULL, 0, 0);
	
	image.SizeOfImage = sizeof(LOADED_IMAGE);
	if(::MapAndLoad(const_cast<char *>(filename), NULL, &image, FALSE, TRUE) == FALSE)
	{
		Exception::Throw(string(Message("Internel error : Module loading failure [","�������顼:�⥸�塼����ɤ߹��ߤ˼��Ԥ��ޤ��� [")) + filename + "]");
		return false;
	}
	return true;
}

bool filecontainer_windows::change_endian(void * target, unsigned int size)
{
		//Windows�ͥ��ƥ���Ʊ�Τ������Ѵ��ʤ���פ�ʤ�
	return true;
}


bool filecontainer_windows::load_contents(void * dest, unsigned long address, unsigned int size)
{
	PIMAGE_SECTION_HEADER header;
	unsigned int i;

	address -= base;
	for(i=0;i<image.NumberOfSections;i++)
	{
		header = image.Sections+i;
		if(address >= header->VirtualAddress && address < header->VirtualAddress + header->SizeOfRawData)
		{
			address -= header->VirtualAddress - header->PointerToRawData;
			::CopyMemory(dest,image.MappedAddress + address,size);

			return true;
		}
	}

	Exception::Throw(Message("Internel error: Memory read with unmapped address","�������顼; �ޥåפ���Ƥʤ����ɥ쥹��Ȥäƥ���꡼�ɤ��Ԥ��ޤ���"));

	return false;
}

unsigned long filecontainer_windows::get_symbol_address(const char * symbol)
{
	IMAGEHLP_SYMBOL sym;

	if(process == NULL || base == 0)
	{
		Exception::Throw(Message("Not initialized","���������Ƥޤ���"));
		return 0;
	}

	sym.SizeOfStruct = sizeof(sym);
	sym.MaxNameLength = 0;

	if(::SymGetSymFromName(process, const_cast<char *>(symbol), &sym) == FALSE)
	{
		Exception::Throw(string(Message("Unknown symbol [","�����ʥ���ܥ� [")) + symbol + "]");
		return 0;
	}
	return sym.Address;
}
