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
 *  @(#) $Id: mpstrstream.cpp,v 1.2 2002/04/05 08:48:31 takayuki Exp $
 */


// $Header: /home/CVS/configurator/mpstrstream.cpp,v 1.2 2002/04/05 08:48:31 takayuki Exp $

#include "mpstrstream.h"
#include <stdarg.h>

using namespace std;

typedef std::list<struct mpstrstream::tagStreamPartInfo *> List;

list<struct mpstrstream::tagStreamPartInfo *>::iterator mpstrstream::_find(const char * partname) const
{
	List::const_iterator scope;

	scope = container.begin();
	while(scope != container.end())
	{
		if((*scope)->name.compare(partname) == 0)
			break;
		scope++;
	}
	return *reinterpret_cast<List::iterator *>(&scope);
}

mpstrstream::~mpstrstream(void)
{
	if(!filename.empty())
		serialize();

	while(!container.empty())
	{
		delete *(container.begin());
		container.pop_front();
	}
}

strstream & mpstrstream::moveto(const char * partname)
{
	List::iterator scope;

	scope = container.begin();
	while(scope != container.end())
	{
		if((*scope)->name.compare(partname) == 0)
			break;
		scope ++;
	}

	current = scope;
	return (*current)->stream;
}

strstream & mpstrstream::moveto(unsigned int pos)
{
	List::iterator scope;

	scope = container.begin();
	while(pos -- > 0)
		scope ++;

	current = scope;
	return (*current)->stream;
}

strstream & mpstrstream::moveto(enum tagPosition pos)
{
	switch(pos)
	{
	case BEGIN:
		current = container.begin();
		break;
	case END:
		current = container.end();
		break;
	}
	return (*current)->stream;
}

strstream & mpstrstream::createpart(const char * partname, const char * second, ... )
{
	struct tagStreamPartInfo * info;
	va_list vl;

	va_start(vl, second);
	vl = (char *)vl - sizeof(const char *);

	while(partname != 0)
	{
		info = new struct tagStreamPartInfo;
		info->name.assign(partname);
		info->flags = DEFAULT;
		container.insert(current, info);

		partname = va_arg(vl, const char *);
	}

	return (*current)->stream;
}

strstream & mpstrstream::insertpart(const char * partname, const char * successor)
{
	struct tagStreamPartInfo * info;
	List::iterator scope;

	scope = container.end();
	if(successor != 0)
		if((scope = _find(successor)) == container.end())
			Exception("Stream does not have the part (%s).","���ȥ꡼��϶��(%s)������ޤ���").format(successor);

	info = new struct tagStreamPartInfo;
	info->name.assign(partname);
	info->flags = DEFAULT;
	current = container.insert(scope, info);
	
	return (*current)->stream;
}

void mpstrstream::erasepart(const char * partname)
{
	List::iterator scope;

	if((scope = _find(partname)) == container.end())
		return;

	if(scope == container.begin())
	{
		current = container.begin();
		current ++;
	}else
	{
		current = scope;
		current --;
	}

	delete (*scope);
	container.erase(scope);
}

void mpstrstream::movepart(const char * partname, const char * successor)
{
	List::iterator src;
	List::iterator dest;

	if((src = _find(partname)) == container.end())
		Exception("Stream dones not have the part (%s).","���ȥ꡼��϶��(%s)������ޤ���").format(partname);
	if(successor != 0)
	{
		if((dest = _find(successor)) == container.end())
			Exception("Stream dones not have the part (%s).","���ȥ꡼��϶��(%s)������ޤ���").format(successor);
	}else
		dest = container.end();

	current = container.insert(dest, (*src));
	container.erase(src);
}

void mpstrstream::serialize(void)
{
	fstream file(filename.c_str(), ios::out);

	if(!file.is_open())
		Exception("File creation failure of %s","�ե�����(%s)�����ޤ���").format(filename.c_str());

	serialize(file);

	file.close();
}

ostream & mpstrstream::serialize(ostream & out)
{
	List::iterator scope;

	scope = container.begin();
	while(scope != container.end())
	{
		if(((*scope)->flags & NO_SERIALIZE) == 0)
			out.write((*scope)->stream.str(), (*scope)->stream.pcount());
		scope ++;
	}

	return out;
}

int mpstrstream::setf(int flag)
{
	int old_flag;
	if(current == container.end())
		return -1;

	old_flag = (*current)->flags;
	(*current)->flags = flag;

	return old_flag;
}

