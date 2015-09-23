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
 *  @(#) $Id: staticapi.cpp,v 1.6 2001/11/12 14:59:27 takayuki Exp $
 */



#include "staticapi.h"
#include "exception.h"
#include "message.h"

using namespace std;

StaticAPIContainer::StaticAPIContainer(void)
{}

StaticAPIContainer::~StaticAPIContainer(void)
{}

bool StaticAPIContainer::Add(StaticAPI * api)
{
	string work;

	if(api == NULL || api->GetAPIName() == NULL)
		return false;

	work = api->GetAPIName();
	if(API.find(work) != API.end())
		return false;

	API[work] = api;
	return true;
}

void StaticAPIContainer::ParseParameterBlock(Manager * mgr, Parser * p, Array * parameter, Token delimiter)
{
	Token token;
	Token param;
	int nest;
	bool skip;

	skip = true;
	nest = 0;
	for(p->GetToken(token,true); token != delimiter; p->GetToken(token,true))
	{
		if(token == Token::PUNCTUATOR)
		{
			if(token.compare(",") == 0)
			{
				if(nest > 0)
				{
					param += token;
					continue;
				}

				if(!skip)
				{
					if(param == Token::INTEGER)
						parameter->push_back(new Integer(param.Value));
					else
						parameter->push_back(new String(param.Trim()));
				}
				param.erase();
				continue;
			}

			skip = false;

			if(token.compare("(") == 0)
			{
				param.Type = Token::SPECIAL;
				nest ++, param += token;
				continue;
			}

			if(token.compare(")") == 0)
			{
				nest --, param += token;
				continue;
			}

			if(token.compare("{") == 0)
			{
				Array * child = new Array;
				parameter->push_back(child);
				ParseParameterBlock(mgr,p,child,Token(Token::PUNCTUATOR,"}"));
				skip = true;
				continue;
			}
		}

		if(skip == true && token != Token::SPACE)
			skip = false;

		if(param.empty())
		{
			if(token != Token::SPACE)
				param = token;
		}else
		{
			param.Type = Token::SPECIAL;
			if(token == Token::SPACE)
				param += ' ';
			else
				param += token;
		}
	}

	if(!skip)
	{
		if(param == Token::INTEGER)
			parameter->push_back(new Integer(param.Value));
		else
			parameter->push_back(new String(param.Trim()));
	}
}

void StaticAPIContainer::Parse(Manager * mgr, Parser * p)
{
	map<string,StaticAPI *>::iterator scope;
	Token token;
	string api;
	Array parameter;

	p->GetToken(token,Token::IDENTIFIER);
	api = token;

	if((scope = API.find(api)) == API.end())
		throw Exception(string(Message("Unknown Static API Name [","������API̾�� [")) + api + "]");

	p->GetToken(token,Token::PUNCTUATOR,"(");
	ParseParameterBlock(mgr, p, &parameter, Token(Token::PUNCTUATOR,")"));

	p->GetToken(token, Token::PUNCTUATOR,";");

	if((*scope).second->Enabled == true)
		(*scope).second->Body(mgr, &parameter);
}
	
