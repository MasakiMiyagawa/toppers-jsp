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
 *  @(#) $Id: manager.cpp,v 1.10 2001/11/12 14:59:27 takayuki Exp $
 */


#include "manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "multistream.h"
#include "serializer.h"

using namespace std;

Manager * ToplevelManagerComponent = NULL;

Manager::Manager(void)
{
	Option.clear();
	CurrentDomain = NULL;

	if(::ToplevelManagerComponent == NULL)
		::ToplevelManagerComponent = this;
	else
		throw Exception();
}

Manager::~Manager(void)
{}

void Manager::ParseBody(ParserComponent * top, const char * filename)
{
	Parser parser;
	fstream file;
	istream * in;

	if(filename != NULL && *filename != '\x0')
	{
		file.open(filename,ios::in);
		if(!file.is_open())
			throw Exception("�ե�����Υ����ץ�˼��Ԥ���");
		in = static_cast<istream *>(&file);
	}else
		in = &cin;

	parser.SetStream(in);
	top->Parse(this, &parser);

	if(filename != NULL)
		file.close();
}

void Manager::SerializeBody(void)
{
	unsigned int i;
	list<Serializer *> serializer;
	list<Serializer *>::iterator scope;
	MultiStream output;

		//Validation
	scope = SerializeUnit.begin();
	while(scope != SerializeUnit.end())
	{
		serializer.push_back(*scope);
		scope ++;
	}

	do{
		i = serializer.size();
		scope = serializer.begin();
		while(scope != serializer.end())
		{
			if((*scope)->Validation(this))
				scope = serializer.erase(scope);
			else
				scope ++;
		}
	}while(!serializer.empty() && (serializer.size() < i));

		//Serialization
	scope = SerializeUnit.begin();
	while(scope != SerializeUnit.end())
	{
		(*scope)->Serialization(this,output);
		scope ++;
	}
}
