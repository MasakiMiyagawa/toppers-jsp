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
 *  @(#) $Id: parser.cpp,v 1.8 2001/11/14 11:58:17 takayuki Exp $
 */


#include "parser.h"
#include "exception.h"
#include "message.h"


Message MSG_WRONGTOKEN("Wrong token appeared","ͽ�����̥ȡ�������ɤ߹��ߤޤ���");

using namespace std;

Token & Token::Trim(void)
{
	string::iterator scope;

	scope = begin();
	while(*scope == ' ' || *scope == '\t' || *scope == '\r' || *scope == '\n')
		scope ++;
	erase(begin(), scope);

	if(!empty())
	{
		scope = end();
		do {
			scope --;
		} while(*scope == ' ' || *scope == '\t' || *scope == '\r' || *scope == '\n');
		scope ++;
		erase(scope, end());
	}
	return *this;
}

const char * Parser::Punctuator =
	",:;(){}";

const char * Parser::Operator =
	"+-*/&|%^~!?[]=";

Parser::Parser(void)
{	in = NULL;	}

bool Parser::GetIdentifier(Token & token,int ch)
{
	token.Value = 0;

	do {
		token.Value ++;
		token += static_cast<char>(ch);
		ch = in->get();
	} while( (ch >='a' && ch <= 'z') || (ch >='A' && ch <= 'Z') || (ch == '_') || (ch >= '0' && ch <= '9') );

	if(ch != -1)
		in->putback(static_cast<char>(ch));

	token.Type = Token::IDENTIFIER;
	return true;
}

bool Parser::GetWhitespace(Token & token, int ch)
{
	int prev;

	switch(ch)
	{
	case '/':
		ch = in->get();

		switch(ch)
		{
		case '*':
			token += "/*";
			prev = '\x0';
			while( ((ch = in->get()) != '/') || (prev!='*'))
			{
				token += static_cast<char>(ch);
				prev = ch;
			}
			token += static_cast<char>(ch);
			break;
		case '/':
			token += '/';
			do {
				token += static_cast<char>(ch);
			} while( (ch = in->get()) != '\n' );
			break;
		default:
			in->putback(ch);
			return false;
		}
		break;

	case '#':
		do {
			token += static_cast<char>(ch);
		} while( (ch = in->get()) != '\n' );
		break;

	case ' ':
	case '\t':
	case '\n':
	case '\r':
		do {
			token += static_cast<char>(ch);
			ch = in->get();
		} while((ch == ' ') || (ch == '\n') || (ch == '\r') || (ch == '\t'));
		in->putback(static_cast<char>(ch));
		break;
	}

	token.Type = Token::SPACE;
	return true;
}

bool Parser::GetInteger(Token & token, int ch)
{
	bool minus = false; 

	if(ch == '-')
	{
		minus = true;
		ch = in->get();
		if(ch < '0' || ch >'9')
		{
			in->putback(static_cast<char>(ch));
			return false;
		}
		token += "-";
	}

	token.Type = Token::INTEGER;
	token.Value = 0;


	if(ch == '0')
	{
		token += static_cast<char>(ch);
		ch = in->get();
		if(ch == 'x' || ch == 'X')
		{
			token += static_cast<char>(ch);
			ch = in->get();
			while((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F'))
			{
				token += static_cast<char>(ch);
				if((ch -= '0') >= 10)
					if((ch -= 'A' - '0' + 10) >= 16)
						ch -= 'a' - 'A';
				token.Value = token.Value * 16 + ch;
				ch = in->get();
			}
		}else
		{
			while(ch >= '0' && ch <= '7')
			{
				token += static_cast<char>(ch);
				token.Value = token.Value * 8 + ch - '0';
				ch = in->get();
			}
		}
	}else
	{
		do {
			token += static_cast<char>(ch);
			token.Value = token.Value * 10 + ch - '0';
			ch = in->get();
		} while(ch >= '0' && ch <= '9');
	}

	if(minus)
		token.Value = - token.Value;

	if(ch != -1)
		in->putback(static_cast<char>(ch));

	return true;
}

bool Parser::GetOperator(Token & token, int ch)
{
		//����äȼ�ȴ������
	const char * work;

	for(work = Operator;*work != '\x0' && *work != ch;work++);

	if(*work == '\x0')
		return false;

	do {
		token += static_cast<char>(ch);
		ch = in->get();
		for(work = Operator;*work != '\x0' && *work != ch;work++);
	} while(*work != '\x0');

	in->putback(ch);
	token.Type = Token::OPERATOR;
	return true;
}

bool Parser::GetStringLiteral(Token & token, int ch)
{
	int prev;

	token.Value = 0;
	token.Type = Token::STRINGLITERAL;

	prev = 0;
	ch = in->get();
	while(!(ch == '"' && prev != '\\'))
	{
		if(prev == '\\')
		{
			switch(ch)
			{
			case 'n': token += '\n'; break;
			case 't': token += '\t'; break;
			case 'r': token += '\r'; break;
			case 'b': token += '\b'; break;
			default:
				token += static_cast<char>(ch);
			}
			prev = 0;
		}else
		{
			if(prev != 0)
				token += static_cast<char>(prev);
			prev = ch;
		}

		ch = in->get();
	}

	if(prev != 0)
		token += static_cast<char>(prev);


	return true;
}

enum Token::tagTokenType Parser::GetToken(Token & token, bool allow_space)
{
	int ch;
	const char * work;

	if(!TokenStack.empty())
	{
		do {
			token = TokenStack.front();
			TokenStack.pop_front();
		} while(!TokenStack.empty() && !allow_space && token.Type == Token::SPACE);

		if(!allow_space && token.Type != Token::SPACE)
			return token.Type;
	}

	token.erase();
	token.Type = Token::ERROR;
	token.Value = 0;
	if(in == NULL || in->bad() || in->eof())
		return Token::ERROR;


	// �Ƕ��PC�ʤ�׻���®���Τǡ��ϥå���ơ��֥�����������ľ�˥����ǥ��󥰤���
	ch = in->get();

		//First(whitespaces) is [ \n\t\r/#]
	while( (ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '\r') || (ch == '/') || (ch == '#'))
	{
		if(GetWhitespace(token, ch))
		{
			if(allow_space)
				return Token::SPACE;	
			else{
				token.erase();
				token.Type = Token::ERROR;
				token.Value = 0;
				ch = in->get();
			}
		}
	}

	if(in == NULL || in->bad() || in->eof())
		return Token::ERROR;

		//First(identifier) is [a-zA-Z_]
	if(	(ch >='a' && ch <= 'z') || (ch >='A' && ch <= 'Z') || (ch == '_') )
		if(GetIdentifier(token, ch))
			return Token::IDENTIFIER;

		//First(integer) is [\-0-9]
	if( (ch >='0' && ch <='9') || (ch == '-') )
		if(GetInteger(token,ch))
			return Token::INTEGER;

		//First(string) is ["]
	if( ch == '"' )
		if(GetStringLiteral(token,ch))
			return Token::STRINGLITERAL;

		//Operator
	if(GetOperator(token,ch))
		return Token::OPERATOR;

		//Punctuator
	work = Punctuator;
	while(*work != '\x0')
		if( *(work++) == ch )
		{
			token += static_cast<char>(ch);
			return (token.Type = Token::PUNCTUATOR);
		}

	token += static_cast<char>(ch);
	token.Type = Token::UNKNOWN;
	return Token::UNKNOWN;
}

void Parser::GetToken(Token & token, enum Token::tagTokenType type, const char * term)
{
	GetToken(token, type == Token::SPACE);

	if((type != token) || (term != NULL && token.compare(term) != 0))
		throw Exception(string(MSG_WRONGTOKEN) + "[" + token + "]");
}

ostream & operator << (ostream & out, Token & src)
{
	switch(src.Type)
	{
	case Token::IDENTIFIER:
		out << "<IDENTIFIER:["; break;
	case Token::INTEGER:
		out << "<INTEGER:["; break;
	case Token::STRINGLITERAL:
		out << "<STRINGLITERAL:["; break;
	case Token::OPERATOR:
		out << "<OPERATOR:["; break;
	case Token::PUNCTUATOR:
		out << "<PUNCTUATOR:["; break;
	case Token::RESERVEDWORD:
		out << "<RESERVEDWORD:["; break;
	case Token::SPECIAL:
		out << "<SPECIAL:["; break;
	case Token::SPACE:
		out << "<SPACE:["; break;
	case Token::UNKNOWN:
		out << "<UNKNOWN>"; return out;
	case Token::ERROR:
		out << "<ERROR>"; return out;
	default:
		out << "<???:[";
	}

	return out << static_cast<string &>(src) << "]("<<src.Value<<")>";
}

