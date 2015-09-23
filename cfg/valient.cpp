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
 *  @(#) $Id: valient.cpp,v 1.3 2000/11/14 16:57:33 takayuki Exp $
 */

#include "valient.h"

Valient::Valient(const Valient & src)
{
	switch(src.Type)
	{
	case STRING:
		Type = EMPTY;
		this->Set(src.String.Entity);
		break;

	default:
		Type = src.Type;
		Double = src.Double;
	}
}

Valient::~Valient(void)
{	Clear();	}

bool Valient::Set(int src)
{
	Clear();
	Type = INTEGER;
	Integer = src;
	return true;
}

bool Valient::Set(unsigned int src)
{
	Clear();
	Type = UNSIGNEDINTEGER;
	UnsignedInteger = src;
	return true;
}

bool Valient::Set(double src)
{
	Clear();
	Type = DOUBLE;
	Double = src;
	return true;
}

bool Valient::Set(char * src)
{
	unsigned int i,j;

	Clear();
	Type = STRING;
	
	for(i=0;*(src+i)!='\x0';i++);

	String.Size = i;
	String.Entity = new char [i+1];
	for(j=0;j<=i;j++)
		*(String.Entity+j)=*(src+j);

	return true;
}

bool Valient::Set(void * src)
{
	Clear();
	Type = POINTER;
	Pointer = src;
	return true;
}

bool Valient::Clear(void)
{
	switch(Type)
	{
	case STRING:
		if(String.Entity != 0l)
			delete [] String.Entity;
		String.Entity = 0l;
		break;
	}
	Type = EMPTY;
	return true;
}

Valient & Valient::operator =(const Valient & src)
{
	Clear();
	
	Type = src.Type;
	if(src.Type == STRING)
	{
		unsigned int i;
		String.Entity = new char[src.String.Size+1];
		for(i=0;i<=src.String.Size;i++)
			*(String.Entity+i) = *(src.String.Entity+i);
		String.Size = src.String.Size;
	}else
		Double = src.Double;

	return *this;
}

