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
 *  @(#) $Id: array.h,v 1.2 2000/11/14 15:56:26 takayuki Exp $
 */

//----------------------------------------------------------------
// class array - class definition
//

#ifndef __ARRAY_H
#define __ARRAY_H

#include <vector>
#include "valient.h"

class Array
{
public:
	enum tagType
	{
		EMPTY, ARRAY, VALUE
	};

protected:
	struct tagValue
	{
		enum tagType Type;
		union
		{
			Array * ArrayedValue;
			Valient * SingleValue;
		};
	};

	std::vector<tagValue> Entity;

	bool Grow(unsigned int);
	bool Clear(tagValue *);

public:
	Array(void);
	Array(const Array &);
	virtual ~Array(void);

		//�����Ϥ��ϥ��ԡ����뤬���ݥ����Ϥ��Ϥ����ͤ�Ȥ�
	bool Set(unsigned int,const Valient &);
	bool Set(unsigned int,Valient *);
	bool Set(unsigned int,const Array &);
	bool Set(unsigned int,Array *);

	Valient * GetValuePtr(unsigned int);
	Array * GetArrayPtr(unsigned int);
	tagType GetType(unsigned int);

	Valient & operator [](unsigned int);

	bool IsArray(unsigned int);
	unsigned int Size(void);

	bool Clear(void);
};

//------------------------------------------------------------
// Inline function declaration

inline Valient & Array::operator [](unsigned int offset)
{
	return *(Entity[offset].SingleValue);
}

inline bool Array::IsArray(unsigned int offset)
{
	if( offset > Entity.size() )
		return false;

	return (Entity[offset].Type == ARRAY);
}

inline unsigned int Array::Size(void)
{	return Entity.size();	}

#endif

//--------
// Designed and Programmed by S.D.F.