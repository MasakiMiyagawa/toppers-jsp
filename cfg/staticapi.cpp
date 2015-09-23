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
 *  @(#) $Id: staticapi.cpp,v 1.3 2000/11/14 16:57:33 takayuki Exp $
 */

#include "staticapi.h"

char * StaticAPI::CheckParameter_Primitive(Array * param, char * format)
{
	int position;
	Valient * work;
	unsigned int flag;

	position = 0;
	flag = 0;
	while(true)
	{
		switch(*format)
		{
		case '{':
			if(!param->IsArray(position))
				throw Exception("Given parameter did not match the prototype.");

			if((format = CheckParameter_Primitive(param->GetArrayPtr(position),format+1)) == '\x0')
				throw Exception("Internal: Parameter descriptor syntax error (Unsuitable parenthesis)");

			if(*format == '\x0')
				return 0l;
			position ++;
			break;
		
		case '}':
		case ',':
		case '\x0':
			work = param->GetValuePtr(position);
			if(work == 0l)
				throw Exception("Geven parameter is too few.");
			
			if((flag & (1 << (int)work->GetType())) == 0)
				throw Exception("Given parameter did not match the prototype.");
			
			if( *format == '}' )
				return format+1;
			if( *format == '\x0' )
				return 0l;

			flag = 0;
			position ++;
			break;

		case '-':
			flag |= ~0;
			break;

		case 'S':
		case 's':
			flag |= 1 << Valient::STRING;
			break;
		case 'I':
		case 'i':
			flag |= 1 << Valient::INTEGER;
			break;
		case 'D':
		case 'd':
			flag |= 1 << Valient::DOUBLE;
			break;
		case 'U':
		case 'u':
			flag |= 1 << Valient::UNSIGNEDINTEGER;
			break;
		case 'P':
		case 'p':
			flag |= 1 << Valient::POINTER;
			break;
		default:
			throw Exception("Internal: Parameter descriptor syntax error (Illegal character)");
		}

		format ++;
	}
}
