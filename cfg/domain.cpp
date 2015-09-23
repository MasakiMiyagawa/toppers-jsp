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
 *  @(#) $Id: domain.cpp,v 1.3 2001/11/12 14:59:27 takayuki Exp $
 */



/*
 * ITRON-MMU �ץ�ƥ������ɥᥤ�󥵥ݡ��ȥ⥸�塼��
 *  ��)�ܥ⥸�塼��ϸ�Ƥ��λ���(2001/07)�򸵤ˤ��Ƥ��ꡤ
 *     ����Ū�ʤ�ΤǤ��뤿�ᡤ���ΥС������ǤϤʤ��ʤ��ǽ��������
 *
 * �ɥᥤ��Υե����ޥåȤϼ����̤�
 *   domain <name> [ : shared|system|user ] { ��ŪAPI };
 * �ɥᥤ��Υͥ��Ȥ���������Ǥ⳰�϶�ͭ�ˤʤ롥
 *
 * �ɵ�) �ɥᥤ��Υͥ��Ȥ������˻��ͤ��鳰���줿
 */

#include "domain.h"
#include <algorithm>
#include "exception.h"
#include "manager.h"

using namespace std;

map<string, ProtectionDomain *> ProtectionDomain::Domain;

ProtectionDomain::ProtectionDomain(void)
{
	ParentDomain = NULL;
	Type = UNKNOWN;
	Name = "UNKNOWN";
};

ProtectionDomain::~ProtectionDomain(void)
{
	list<ProtectionDomain *> * container;
	list<ProtectionDomain *>::iterator scope;
	map<string, ProtectionDomain *>::iterator mapping;

		//�Ƥȼ���ڤ�
	if(ParentDomain != NULL)
	{
		container = &ParentDomain->ChildDomain;
		scope = find(container->begin(), container->end(), this);
		if(scope != container->end())
			container->erase(scope);
		ParentDomain = NULL;
	}

		//�Ҥ����Ǥ�����
	scope = ChildDomain.begin();
	while(scope != ChildDomain.end())
	{
		(*scope)->ParentDomain = NULL;
		delete (*scope);
		scope ++;
	}
	ChildDomain.clear();

		//��Ͽ�����ä���
	mapping = Domain.find(Name);
	if(mapping != Domain.end())
		Domain.erase(mapping);
}

ProtectionDomain * ProtectionDomain::GetChildDomain(ProtectionDomain * prev)
{
	list<ProtectionDomain *>::iterator scope;

	if(prev != NULL)
	{
		scope = find(ChildDomain.begin(), ChildDomain.end(), prev);
	}else
		scope = ChildDomain.begin();

	if(scope != ChildDomain.end())
		scope ++;

	return scope == ChildDomain.end() ? NULL : (*scope);
}

void ProtectionDomain::Parse(Manager * mgr, Parser * p)
{
	Token token;

	mgr->CurrentDomain = this;
	p->GetToken(token,Token::IDENTIFIER,"domain");
	p->GetToken(token,Token::IDENTIFIER);
	Name = token;

	Type = USER;
	p->GetToken(token,Token::PUNCTUATOR);
	if(token.compare(":") == 0)
	{
		p->GetToken(token,Token::IDENTIFIER);
		if(token.compare("system") == 0)
			Type = SYSTEM;
		else if(token.compare("shared") == 0)
			Type = SHARED;
		else if(token.compare("user") == 0)
			Type = USER;
		else
			throw Exception();

		p->GetToken(token,Token::PUNCTUATOR);
	}

	if(token.compare("{") != 0)
		throw Exception();

	p->GetToken(token);
	while(token.compare("}") != 0)
	{
		if(token.Type != Token::IDENTIFIER)
			throw Exception();

		p->PutBack(token);
		if(token.compare("domain")==0)
		{
			ProtectionDomain * newdomain = CreateNewDomain(mgr);
			newdomain->ParentDomain = this;
			ChildDomain.push_back(newdomain);

			newdomain->Parse(mgr,p);
			mgr->CurrentDomain = this;
		}else
			mgr->API.Parse(mgr,p);
		p->GetToken(token);
	}
	p->GetToken(token,Token::PUNCTUATOR,";");
}
