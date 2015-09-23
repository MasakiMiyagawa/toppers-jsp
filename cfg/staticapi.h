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
 *  @(#) $Id: staticapi.h,v 1.3 2000/11/24 09:14:47 takayuki Exp $
 */

//------------------------------------------------------------
// StaticAPI - class definition
//

#ifndef __STATICAPI_H
#define __STATICAPI_H

#include "array.h"
#include "exception.h"

class StaticAPI
{
private:
	char * CheckParameter_Primitive(Array *,char *);
protected:
	void CheckParameter(Array *, char *);
	void CheckParameterCount(Array &,unsigned int, unsigned int=0);
	void CheckParameterType(Array &,unsigned int,Valient::tagType);
	void CheckParameterType(Array &,unsigned int,Array::tagType);

public:
	StaticAPI(void) {};
	virtual ~StaticAPI(void) {};

	virtual char * GetAPIName(void) =0;
	virtual void Body(Array & Parameter) =0;
};

inline void StaticAPI::CheckParameterCount(Array & param,unsigned int start, unsigned int end)
{
	if((param.Size() < start) || (end != 0 && param.Size() > end))
		throw Exception("Too few or Too much parameters");
}

inline void StaticAPI::CheckParameterType(Array & param,unsigned int offset, Valient::tagType type)
{
	if(param.Size() > offset || param.GetValuePtr(offset) == 0l || !(param[offset] == type))
		throw Exception("Parameter type is not match");
}

inline void StaticAPI::CheckParameterType(Array & param,unsigned int offset, Array::tagType type)
{
	if((type != Array::EMPTY) && param.IsArray(offset) != (type == Array::ARRAY) ? true : false)
		throw Exception("Parameter type is not match");
}

inline void StaticAPI::CheckParameter(Array * param, char * format)
{
	if(CheckParameter_Primitive(param,format)!=0l)
		throw Exception("Internal error : Illegal parameter descriptor (Unterminated descriptor)");
}

#endif

//---
// Degined and Programmed by S.D.F. in Oct,2000
