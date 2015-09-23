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
 *  @(#) $Id: valient.h,v 1.3 2000/11/14 16:57:33 takayuki Exp $
 */

//----------------------------------------------------------------
// class Valient - class definition
//

#ifndef __VALIENT_H
#define __VALIENT_H

class Valient
{
public:
	enum tagType
	{
		EMPTY, INTEGER, UNSIGNEDINTEGER, DOUBLE, STRING, POINTER
	};

protected:
	enum tagType Type;
	union
	{
		int Integer;
		unsigned int UnsignedInteger;
		double Double;
		struct
		{
			unsigned int Size;
			char * Entity;
		} String;
		void * Pointer;
	};

public:
	Valient(void);
	Valient(int);
	explicit Valient(unsigned int);
	Valient(double);
	explicit Valient(char *);
	Valient(void *);
	Valient(const Valient &);

	virtual ~Valient(void);

	bool Set(int);
	bool Set(unsigned int);
	bool Set(double);
	bool Set(char *);
	bool Set(void *);

	int GetInteger(int =0);
	char * GetString(char * =0l);
	double GetDouble(double =0.0);
	void * GetPointer(void * =0l);

	bool Clear(void);

	enum tagType GetType(void);

	bool operator ==(enum tagType);
	char * operator =(char *);
	Valient & operator =(const Valient &);

	operator const enum tagType(void)
	{	return Type;	};
};

inline Valient::Valient(void)
{	Type=EMPTY;	}

inline Valient::Valient(int src)
{	Type=EMPTY;	this->Set(src);	}

inline Valient::Valient(unsigned int src)
{	Type=EMPTY;	this->Set(src);	}

inline Valient::Valient(double src)
{	Type=EMPTY;	this->Set(src);	}

inline Valient::Valient(char * src)
{	Type=EMPTY;	this->Set(src);	}

inline Valient::Valient(void * src)
{	Type=EMPTY;	this->Set(src);	}

inline bool Valient::operator ==(enum tagType src)
{	return Type == src;	}

inline char * Valient::operator =(char * src)
{
	Set(src);
	return src;
}

inline int Valient::GetInteger(int def)
{
	if(Type != INTEGER)
		return def;
	return Integer;
}

inline char * Valient::GetString(char * def)
{
	if(Type != STRING)
		return def;
	return String.Entity;
}

inline double Valient::GetDouble(double def)
{
	if(Type != DOUBLE)
		return def;
	return Double;
}

inline void * Valient::GetPointer(void * def)
{
	if(Type != POINTER)
		return def;
	return Pointer;
}

inline enum Valient::tagType Valient::GetType(void)
{	return Type;	}

#endif

//--------
// Designed and Programmed by S.D.F.