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
 *  @(#) $Id: filecontainer.cpp,v 1.2 2001/11/12 14:59:27 takayuki Exp $
 */


#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <stdio.h>

#include "exception.h"
#include "message.h"
#include "filecontainer.h"

using namespace std;

filecontainer * container;

static char * parse_uint(char * src, unsigned int * dest, unsigned int default_value = 0)
{
	while(*src >= '0' && *src <='9')
		default_value = default_value * 10 + *(src++) - '0';

	*dest = default_value;
	return src;
}

bool filecontainer::attach_infofile(const char * filename)
{
	char buffer[256];
	FILE * f;
	char * work;
	struct tagStructureInformation info;

	f = fopen(filename,"rt");
	if(f == NULL)
	{
		Exception::Throw(string(Message("Structure information file was not found. ","��¤�ξ���ե����뤬���Ĥ���ޤ��� ")) + "[" + filename + "]");
		return false;
	}
	while(fgets(buffer, 255, f) != NULL)
	{
		work = buffer + strlen(buffer) -1;
		if(*work == '\n')
			*work = '\x0';

		switch(buffer[0])
		{
		case 's':
			work = buffer+1;
			while(*work != ',' && *work != '\x0')
				work++;
			if(*work == '\x0')
				continue;

			*work = '\x0';
			work = parse_uint(work+1,&info.size);
			work = parse_uint(work+1,&info.offset);

			structure_information[string(buffer+1)] = info;
			break;

		case 'd':
			work = buffer+1;
			while(*work != ',' && *work != '\x0')
				work++;
			if(*work == '\x0')
				continue;

			*work = '\x0';

			objectname[string(buffer+1)] = string(work+1);
			break;

		default:
			Exception::Throw(string(Message("Unknown information type identifier found - [","̤�Τη����̻� - ")) + buffer[0] + "]");
		}
	}

	fclose(f);
	return true;
}

bool filecontainer::load_variable(void * dest, unsigned int size, const char * name)
{
	map<string, struct tagStructureInformation>::iterator scope;
	unsigned long address;

	scope = structure_information.find(string(name));
	if(scope == structure_information.end())
		return false;

	if(size > (*scope).second.size)
		return false;

	if((*scope).second.size < size)
		size = (*scope).second.size;

	address = get_symbol_address(name);
	if(address == 0 || !load_contents(dest, address + (*scope).second.offset, size))
		return false;

	if(!change_endian(dest,size))
		return false;

	return true;
}

bool filecontainer::load_variable(void * dest, unsigned int size, unsigned long address, const char * name)
{
	map<string, struct tagStructureInformation>::iterator scope;

	scope = structure_information.find(string(name));
	if(scope == structure_information.end())
		return false;

	if(size < (*scope).second.size)
		return false;

	if((*scope).second.size < size)
		size = (*scope).second.size;

	if(!load_contents(dest, address + (*scope).second.offset, size))
		return false;

	if(!change_endian(dest,size))
		return false;

	return true;
}

struct variable_information filecontainer::get_variable_information(const char * name, unsigned long base)
{
	struct variable_information result;
	map<string, struct tagStructureInformation>::iterator scope;
	const char * work;
	bool is_member = false;

	result.address = 0;
	result.size = 0;

	for(work = name; *work != '\x0'; work++)
		if(*work == ':')
		{
			is_member = true;
			break;
		}

	scope = structure_information.find(string(name));
	if(scope != structure_information.end())
	{
		if(!is_member)
		{
			bool old = Exception::SetThrowControl(false);
			result.address = this->get_symbol_address(name);
			Exception::SetThrowControl(old);
			if(result.address == 0)
				result.value = (long)((*scope).second.size);
			else
				result.size = (*scope).second.size;
		}else
		{
			result.address = base + (*scope).second.offset;
			result.size = (*scope).second.size;
		}
	}

	return result;
}

string filecontainer::get_objectname(int id, const char * type)
{
	char buffer[32];
	string work;
	map<string, string>::iterator scope;

	work = type;

	sprintf(buffer, "_%d", id);
	work += buffer;

	scope = objectname.find(work);
	if(scope != objectname.end())
		work = (*scope).second;
	else
		work.erase();

	return work;
}

