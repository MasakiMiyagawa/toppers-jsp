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
 *  @(#) $Id: multistream.cpp,v 1.7 2001/11/12 14:59:27 takayuki Exp $
 */


#include "multistream.h"
#include "exception.h"
#include "message.h"

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

using namespace std;

Message MSG_COULDNOTCREATE("Failed to create the file","�ե�����������˼��Ԥ��ޤ���");



MultiStream::MultiStream(void)
{
	Stream.clear();
}

MultiStream::~MultiStream(void)
{
	CloseAllStreams();
}

bool MultiStream::Add(const string & name)
{
	if(name.empty())
		return false;

	if(Stream.find(name) != Stream.end())
		return false;

	fstream * work = new fstream(name.c_str(),ios::out|ios::trunc);

	if(!work->is_open())
	{
		delete work;
		return false;
	}

	Stream[name] = work;
	LastReferedStream = work;

	return true;
}

fstream * MultiStream::operator [](const string & name)
{
	map<string, fstream *>::iterator scope;

	scope = Stream.find(name);
	if(scope == Stream.end())
	{
		if(!Add(name))
			throw Exception(string(MSG_COULDNOTCREATE) + " [" + name + "]");
		return Stream[name];
	}

	LastReferedStream = (*scope).second;
	return LastReferedStream;
}

bool MultiStream::Close(const string & src)
{
	map<string, fstream *>::iterator scope;

	scope = Stream.find(src);
	if(scope == Stream.end())
		return false;

	if((*scope).second != 0l)
	{
		(*scope).second->close();
		delete (*scope).second;
	}

	Stream.erase(scope);
	LastReferedStream = NULL;

	return true;
}

bool MultiStream::CloseAllStreams(void)
{
	map<string,fstream *>::iterator scope;

	scope = Stream.begin();
	while(scope != Stream.end())
	{
		if((*scope).second != 0l)
		{
			(*scope).second->close();
			delete (*scope).second;
		}

		scope ++;
	}

	Stream.clear();

	LastReferedStream = NULL;
	return true;
}

