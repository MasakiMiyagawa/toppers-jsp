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
 *  @(#) $Id: simpleparser.cpp,v 1.5 2000/11/14 16:57:33 takayuki Exp $
 */

#include "simpleparser.h"

using namespace std;

SimpleParser::SimpleParser(void)
{
	in = 0l;
	CurrentLinePos = 1;
	PreviousLinePos = 1;
}

SimpleParser::~SimpleParser(void)
{}


bool SimpleParser::SetStream(istream * source)
{
	if(in != 0l)
		delete in;

	in = source;
	return true;
}

bool SimpleParser::GetArrayedParameter(Array & param, bool parenthesis = false)
{
	char buffer[1024];
	int pos;
	int ch;
	int offset;

	if(in == 0l)
		return false;

	offset = 0;

	do
	{
		if(in->eof())
			return false;

		do{
			ch = in->get();
			if(ch == '\n')
				CurrentLinePos++;
		}while(ch == ' ' || ch == '\t' || ch == '\n' || ch=='\r');

		if(parenthesis)
		{
			if(ch == '(')
				ch = '{';
			if(ch == ')')
				ch = '}';
		}

		switch(ch)
		{
		case ',':
			break;
		case '{':
			{
				Array * newarray = new Array;
				param.Set(offset,newarray);
				offset++;
				if(!GetArrayedParameter(*newarray))
					return false;
				break;
			}
		case '}':
			return true;

		case '"':
			pos = 0;
			do{
				if((ch = in->get()) == '"')
					break;
				if(ch == '\\')
					ch = in->get();
				buffer[pos++] = ch;
			}while(true);
			buffer[pos] = '\0';
			param.Set(offset,new Valient(buffer));
			offset ++;
			break;

		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			{
				int work = ch - '0';

				ch = in->get();
				while( ch>='0' && ch<='9' )
				{
					work = work * 10 + ch - '0';
					ch = in->get();
				}
				in->putback(ch);

				param.Set(offset++,new Valient(work));
				break;
			}

		default:
			buffer[0] = ch;
			pos = 1;
			do{
				buffer[pos++] = in->get();
			}while(buffer[pos-1] != ',' && !(parenthesis && buffer[pos-1] == ')') && buffer[pos-1] != '}');
			in->putback(buffer[pos-1]);
			buffer[pos-1] = '\0';
			param.Set(offset,new Valient(TrimString(buffer)));
			offset ++;
			break;
		}

	}while(true);

	return false;
}

bool SimpleParser::GetNextStatement(string & api,Array & param)
{
	char buffer[32];
	int pos;
	int ch;

	if(in == 0l)
		return false;

	pos = 0;

	if((ch = in->get()) == '#')
	{
		do
		{
			ch = in->get();
		}while(ch != '\xa' && !in->eof());
	}

	while( ch != '(' && !in->eof() )
	{
		if(ch == '\xa')
		{
			CurrentLinePos++;
			if((ch = in->get()) == '#')
			{
				do
				{
					ch = in->get();
				}while(ch != '\xa' && !in->eof());
			}else
				if( ch == '\xa')
					in->putback(ch);
		}

		if(ch != '\n' && ch != '\r' && ch != ' ' && ch != '\t')
			buffer[pos++] = ch;
		ch = in->get();
	}

	if(in->eof())
		return false;

	PreviousLinePos = CurrentLinePos;

	buffer[pos] = '\0';
	api = TrimString(buffer);

	if(!GetArrayedParameter(param,true))
		return false;

	do
	{
		if(in->eof())
			return false;

		ch = in->get();
		if(ch == '\n')
			CurrentLinePos++;
	}while(ch != ';');

	return true;
}
