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
 *  @(#) $Id: array.cpp,v 1.4 2000/11/24 09:14:47 takayuki Exp $
 */

#include "array.h"

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

using namespace std;


Array::Array(void)
{
	Entity.clear();
}

Array::Array(const Array & src)
{
	vector<tagValue>::const_iterator scope;
	tagValue work;

	Entity.clear();

	scope = src.Entity.begin();
	while(scope != src.Entity.end())
	{
		work.Type = (*scope).Type;
		switch((*scope).Type)
		{
		case ARRAY:
			if((work.ArrayedValue = new Array(*(*scope).ArrayedValue)) == 0l)
				work.Type = EMPTY;
			break;
		case VALUE:
			if((work.SingleValue = new Valient(*(*scope).SingleValue)) == 0l)
				work.Type = EMPTY;
			break;
		}

		Entity.push_back(work);

		scope ++;
	}
}

Array::~Array(void)
{
	Clear();
}

bool Array::Clear(void)
{
	vector<tagValue>::iterator scope;
	
	scope = Entity.begin();
	while(scope != Entity.end())
	{
		switch((*scope).Type)
		{
		case ARRAY:
			delete (*scope).ArrayedValue;
			break;
		case VALUE:
			delete (*scope).SingleValue;
			break;
		}
		scope ++;
	}
	Entity.clear();
	return true;
}

bool Array::Grow(unsigned int required)
{
	if(required < Entity.size())
		return true;

	tagValue emptyvalue;

	emptyvalue.Type = EMPTY;
	for(required -= Entity.size(); required > 0; required --)
		Entity.push_back(emptyvalue);

	return true;
}

bool Array::Clear(tagValue * scope)
{
	if(scope == 0l)
		return false;

	switch(scope->Type)
	{
	case ARRAY:
		delete scope->ArrayedValue;
		break;
	case VALUE:
		delete (Valient *)scope->SingleValue;
		break;
	}
	scope->Type = EMPTY;
	return true;
}

bool Array::Set(unsigned int offset, const Valient & src)
{
	if( offset >= Entity.size() )
	{
		Grow(offset+1);
	}

	tagValue * scope = &Entity[offset];

	Clear(scope);
	scope->Type = VALUE;
	if((scope->SingleValue = new Valient(src)) == 0l)
	{
		scope->Type = EMPTY;
		return false;
	}

	return true;
}

bool Array::Set(unsigned int offset, Valient * src)
{
	if( offset >= Entity.size() )
	{
		Grow(offset+1);
	}

	tagValue * scope = &Entity[offset];

	Clear(scope);
	scope->Type = VALUE;
	scope->SingleValue = src;

	return true;
}

bool Array::Set(unsigned int offset, const Array & src)
{
	if( offset >= Entity.size() )
	{
		Grow(offset+1);
	}

	tagValue * scope = &Entity[offset];

	Clear(scope);
	scope->Type = ARRAY;
	if((scope->ArrayedValue = new Array(src)) == 0l)
	{
		scope->Type = EMPTY;
		return false;
	}

	return true;
}

bool Array::Set(unsigned int offset, Array * src)
{
	if( offset >= Entity.size() )
	{
		Grow(offset+1);
	}

	tagValue * scope = &Entity[offset];

	Clear(scope);
	scope->Type = ARRAY;
	scope->ArrayedValue = src;

	return true;
}

Valient * Array::GetValuePtr(unsigned int offset)
{
	if( offset > Entity.size() )
		return 0l;

	tagValue * scope = &Entity[offset];

	if( scope->Type != VALUE)
		return 0l;

	return scope->SingleValue;
}

Array * Array::GetArrayPtr(unsigned int offset)
{
	if( offset > Entity.size() )
		return 0l;

	tagValue * scope = &Entity[offset];

	if( scope->Type != ARRAY)
		return 0l;

	return scope->ArrayedValue;
}
