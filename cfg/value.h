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
 *  @(#) $Id: value.h,v 1.2 2001/11/12 14:59:27 takayuki Exp $
 */


#ifndef __VALUE_H
#define __VALUE_H

#include <vector>
#include <string>
#include <iostream>

class Value
{
public:
	enum tagType
	{
		UNKNOWN = 0,
		INTEGER,
		STRING,
		FLOAT,
		ARRAY
	};

	Value(void) {}
	virtual ~Value(void){};

	virtual operator enum tagType (void) const = 0;

	virtual Value * Duplicate(void) = 0;
	virtual void Serialize(std::ostream &) const = 0;
};

class Integer : public Value
{
protected:
	int value;

public:
	Integer(long src=0) { value = src; };
	Integer(const Integer & src) { value = src.value; };
	virtual ~Integer(void) {};

	virtual operator enum tagType (void) const { return INTEGER; };
	
	operator const int (void) const;
	operator int & (void);

	virtual Value * Duplicate(void);
	virtual void Serialize(std::ostream &) const;
};

class String : public Value, public std::string
{
public:
	String(void) {};
	String(const char *);
	String(std::string &);
	String(const String & src);
	virtual ~String(void) {};
	virtual operator enum tagType (void) const { return STRING; };
	virtual Value * Duplicate(void);
	virtual void Serialize(std::ostream &) const;
};

class Array : public Value, public std::vector<Value *>
{
public:
	Array(void) {};
	Array(const Array &);
	virtual ~Array(void);

	virtual operator enum tagType (void) const { return ARRAY; };
	Array & operator =(const Array &);

	void clear();
	
	virtual Value * Duplicate(void);
	virtual void Serialize(std::ostream &) const;
};


//--- Inline functions

inline Integer::operator const int (void) const
{	return value;	}

inline Integer::operator int & (void)
{	return value;	}

inline Value * Integer::Duplicate(void)
{	return new Integer(value);	}

inline void Integer::Serialize(std::ostream & out) const
{	out << value;	}

inline String::String(const char * str)
{	assign(str);	}

inline String::String(std::string & str)
{	assign(str.c_str());	}

inline String::String(const String & src)
{	assign(src);	}

inline Value * String::Duplicate(void)
{	return static_cast<Value *>(new String(*this));	}

inline void String::Serialize(std::ostream & out) const
{	out << static_cast<std::string>(*this);	}


inline Value * Array::Duplicate(void)
{	return new Array(*this);	}

//--- Related functions

inline std::ostream & operator <<(std::ostream & out, Value & val)
{
	val.Serialize(out);
	return out;
}

inline std::ostream & operator <<(std::ostream & out, Value * val)
{
	if(val != NULL)
		val->Serialize(out);
	else
		out << "<null>";
	return out;
}

#endif