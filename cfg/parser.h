/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
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
 *  @(#) $Id: parser.h,v 1.9 2002/04/11 07:26:37 takayuki Exp $
 */

// $Header: /home/CVS/configurator/parser.h,v 1.9 2002/04/11 07:26:37 takayuki Exp $

#ifndef __PARSER_H
#define __PARSER_H

#include "except.h"

#include "directorymap.h"
#include "component.h"

#include <stdarg.h>
#include <iostream>
#include <list>
#include <string>
#include <fstream>

#ifdef assert
#undef assert
#endif

class Token : public std::string
{
        //���Фα��äϤ��ʤ�
public:
	enum tagTokenType
	{
		IDENTIFIER		= 0x01,
		INTEGER			= 0x02,
		STRINGLITERAL	= 0x03,
        STRING          = 0x04,
		OPERATOR		= 0x05,
		PUNCTUATOR		= 0x06,
		RESERVEDWORD	= 0x07,
		SPECIAL			= 0x80,
		SPACE			= 0x81,
		UNKNOWN			= 0xfd,
		ERROR			= 0xfe,
        EOS             = 0xff      //End of Stream
	};

	enum tagTokenType type;
	long value;
    unsigned int line;

	Token(void)			        { type = UNKNOWN;  value = 0;	};
	Token(const Token & src)	{ (*this) = src; };
	Token(enum tagTokenType, const char *);

	operator const enum tagTokenType (void) const { return type; };

	Token & operator =(const Token & src);
	bool operator == (const Token & src) const;

	Token & trim(void);
    Token & chopLiteral(void);
	void    assert(const char *) const;
};

class Parser
{
protected:
	struct tagFile
	{
		std::string    identifier;
		std::istream * stream;
		unsigned int   line;
	};

	static const char * Punctuator;
	static const char * Operator;
	static Token        lastErrorToken;
	Directory *         Container;

	tagFile *             current;
	std::list<Token>      TokenStack;
	std::list<tagFile *>  fileStack;

	bool getIdentifier(Token &, int);
	bool getWhitespace(Token &, int, bool);
	bool getInteger(Token &, int);
	bool getStringLiteral(Token &, int);
	bool getOperator(Token &, int);

    int  getChar(void);
    void putBack(int);

public:
	Parser(Directory & cnt) { Container = &cnt; current = 0; };
	Parser(Directory * cnt) { Container =  cnt; current = 0; };
	~Parser(void);

	void pushStream(const std::string & filename, std::string = "");
	void pushStdStream(std::string = "Standard Input");

	void setStreamIdentifier(const std::string & id) { current->identifier = id; };
	void setCurrentLine(unsigned int pos) { current->line = pos; };
    unsigned int getCurrentLine(void);
	const char * getStreamIdentifier(void);
	std::string getStreamLocation(void);

    enum Token::tagTokenType getToken(Token &,bool = false);
	void getToken(Token &,enum Token::tagTokenType, const char * = NULL);
	void getToken(const char *, const char * = 0, ...);

    void putBack(Token &);

	static const Token & getLastErrorToken(void) { return lastErrorToken; };
};


//---

class ParseUnit
{
protected:
	static Token & parseParameter(Parser &);
	static int     parseParameters(Parser &, Directory *, int, int=0);
	static int     parseParameters(Parser &, Directory *, const char *);

public:
	ParseUnit(void *, const char *);

    const char * getIdentifier(void) const;
    virtual void body(const std::string &, Directory &, Parser &, const std::string &) =0;

    static void printList(void * container);
};

#define __DECLARE_PARSEUNIT(x,y,z) class x##_##y : public x { public: x##_##y(void) : x(z) {}; protected: virtual void body(const std::string &, Directory &, Parser &, const std::string &); } instance_of_##x##_##y; void x##_##y::body(const std::string & identifier, Directory & container, Parser & p, const std::string & domain)

//---

class StaticAPI : public ParseUnit
{
protected:
	static Directory * last;
	Directory * allocate(Directory &, const Token &, const char *, bool = true);
	Directory * find    (Directory &, const Token &, const char *);
public:
    static std::map<std::string, class ParseUnit *> container;
	StaticAPI(const char * name) : ParseUnit(&container, name) {};
    static void printList(void) { ParseUnit::printList(&container); }
	static void dropLastObject(void);
};

#define DECLARE_API(x,y) __DECLARE_PARSEUNIT(StaticAPI,x,y)

//---

class Directive : public ParseUnit
{
public:
    static std::map<std::string, class ParseUnit *> container;
	Directive(const char * name) : ParseUnit(&container, name) {};
    static void printList(void) { ParseUnit::printList(&container); }
};

#define DECLARE_DIRECTIVE(x,y) __DECLARE_PARSEUNIT(Directive,x,y)

//---

class ParserComponent : public Component
{
protected:
    int failCount;

    virtual void parseOption(Directory &);    
    virtual void body(Directory &);

    bool parseStaticAPI(Parser & p, Directory & container, Token token, const std::string = "");

	virtual bool parse(Parser & p, Directory & container) = 0;

public:
    ParserComponent(void);
    virtual ~ParserComponent(void);
};

//---

inline void Parser::pushStdStream(std::string strid)
{
	if(current != 0)
		fileStack.push_front(current);

	current = new tagFile;
	current->stream     = &std::cin;
	current->identifier = strid;
	current->line       = 1;
}

inline Token::Token(enum tagTokenType type, const char * term)
{
	type = type;
	value = 0;
	assign(term);
}

inline Token & Token::operator =(const Token & src)
{	
	type = src.type; 
	value = src.value; 
    line = src.line;
	assign(src); 
	return *this;	
}

inline bool Token::operator ==(const Token & src) const
{
	if(type != src.type)
		return false;
	if(type == Token::INTEGER && value != src.value)
		return false;
	else
		if(compare(src) != 0)
			return false;

	return true;
}

inline void Token::assert(const char * str) const
{
	if(compare(str) != 0)
		Exception("Illegal token (%s) appears during parse process.","������Ϥ�����������ʥȡ�����(%s)���и����ޤ���").format(str);
}

inline void Parser::getToken(Token & token, enum Token::tagTokenType type, const char * term)
{
	getToken(token, type == Token::SPACE);

    if(type == Token::STRING && token == Token::STRINGLITERAL)
        token.chopLiteral();

	if((type != token) || (term != NULL && token.compare(term) != 0))
	{
		lastErrorToken = token;
		Exception("Parse error on reading [%s]","������ϤΥ��顼 [%s]").format(token.c_str());
	}
}

inline void Parser::putBack(Token & token)
{	TokenStack.push_front(token);	}

inline Directory * StaticAPI::find(Directory & container, const Token & token, const char * id)
{
	Directory * node;

	node = container.findChild(id,token.c_str(),NULL);
	if(node == 0)
		Exception("The object %s(%s) does not exist.","���֥�������%s(%s)��̤����Ǥ�").format(token.c_str(),id);

	return node;
}

inline void StaticAPI::dropLastObject(void)
{
	if(last != NULL)
	{
		last->erase();
		last = NULL;
	}
}

#endif