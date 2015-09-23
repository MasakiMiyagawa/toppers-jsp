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
 *  @(#) $Id: parser.h,v 1.5 2001/11/12 14:59:27 takayuki Exp $
 */


#ifndef __PARSER_H
#define __PARSER_H

#include <iostream>
#include <list>
#include <string>

class Token : public std::string
{
public:
	enum tagTokenType
	{
		IDENTIFIER		= 0x01,
		INTEGER			= 0x02,
		STRINGLITERAL	= 0x03,
		OPERATOR		= 0x04,
		PUNCTUATOR		= 0x05,
		RESERVEDWORD	= 0x06,
		SPECIAL			= 0x80,
		SPACE			= 0x81,
		UNKNOWN			= 0xfe,
		ERROR			= 0xff
	};

	enum tagTokenType Type;
	long Value;

	Token(void)			{ Type = UNKNOWN;  Value = 0;	};
	Token(enum tagTokenType, const char *);
	Token(const Token & src)	{ (*this) = src; };

	operator const enum tagTokenType (void) const { return Type; };

	Token & operator =(const Token & src);
	bool operator == (const Token & src) const;

	Token & Trim(void);
};

class Parser
{
protected:
	std::istream * in;
	static const char * Punctuator;
	static const char * Operator;
	std::list<Token> TokenStack;

	bool GetIdentifier(Token &, int);
	bool GetWhitespace(Token &, int);
	bool GetInteger(Token &, int);
	bool GetStringLiteral(Token &, int);
	bool GetOperator(Token &, int);

public:
	Parser(void);
	~Parser(void) {};

	std::istream * SetStream(std::istream *);
	enum Token::tagTokenType GetToken(Token &,bool = false);
	void GetToken(Token &,enum Token::tagTokenType, const char * = NULL);
	void PutBack(Token &);
};

class ParserComponent
{
public:
	virtual void Parse(class Manager *, Parser *) =0;
};

inline std::istream * Parser::SetStream(std::istream * _in)
{
	std::istream * old = in;
	in = _in;
	return old;
}

inline Token::Token(enum tagTokenType type, const char * term)
{
	Type = type;
	Value = 0;
	assign(term);
}

inline Token & Token::operator =(const Token & src)
{	
	Type = src.Type; 
	Value = src.Value; 
	assign(src); 
	return *this;	
}

inline bool Token::operator ==(const Token & src) const
{
	if(Type != src.Type)
		return false;
	if(Type == Token::INTEGER && Value != src.Value)
		return false;
	else
		if(compare(src) != 0)
			return false;

	return true;
}

inline void Parser::PutBack(Token & token)
{	TokenStack.push_front(token);	}

#endif