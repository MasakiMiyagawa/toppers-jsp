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
 *  @(#) $Id: toppers.h,v 1.2 2000/11/14 15:56:26 takayuki Exp $
 */

#ifndef __TOPPERS_H
#define __TOPPERS_H

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include "serializer.h"
#include "staticapi.h"
#include "id.h"
#include "multistream.h"

#include <map>
#include <list>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

#define DECLARE_API(x) class API_##x : public StaticAPI { public: char * GetAPIName(void) { return #x; }; void Body(Array &); } x; friend class API_##x; 

#define HEADERFILE "kernel_id.h"
#define CFGFILE "kernel_cfg.c"

//-----------------------------------------------------------------
// Miscellanea : ���󥯥롼�ɤ��������ʤ�
//

class Miscellanea : public Serializer
{
protected:
	set<string> includefilename;
	map<string, Valient> define;
	set<string> initializer;
	bool secondpass;

public:
	DECLARE_API(INCLUDE);
	DECLARE_API(DEFINE);

		//include
	bool AddIncludeFile(const string & file);

		//define
	bool IsDefined(const string & id);
	bool AddDefinition(const string & id, const Valient & val);
	bool GetDefinision(const string & id, Valient & val);

	bool AddInitializer(const string &);

	void Check(void) { secondpass = false; };
	void Body(MultiStream & dest);
};


class Object : public Serializer
{
protected:
	ID Identifier;
	map<int, Array> InitialParameter;

	void OutputHeaderBlock(ostream *,char *, char *, char * =0l);
	void OutputFooterBlock(ostream *,char *, char * =0l);

	void CreateBufferDefinition(ostream *, int,char *,char *,int =-1);
public:
	Array * LoadParameters(Array *, int, int, int,int =0);
	int AssignObjectID(Valient &);
	int GetAssignedObjectID(Valient &);
	Array * GetInitialParameterArray(int);

	virtual void Check(bool &);
};

inline Array * Object::GetInitialParameterArray(int offset)
{
	if(!Identifier.IsAssigned(offset))
		return 0l;
	return &InitialParameter[offset];
}


//-----------------------------------------------------------------
// Task : ��������Ϣ��������
//

class Task : public Object
{
protected:
	enum tagPart
	{	TYPE=0, EXINF, TASK, PRIORITY, STACKSIZE, STACK,TEXTYPE, TEXFUNC	};


public:
	DECLARE_API(CRE_TSK)
	DECLARE_API(DEF_TEX)

	void Body(MultiStream & src);
};

//-----------------------------------------------------------------
// Semaphore : ���ޥե���Ϣ��������
//


class Semaphore : public Object
{
protected:
	enum tagPart
	{	ATR=0, ISEMCNT, MAXCNT	};

public:
	DECLARE_API(CRE_SEM)

	void Body(MultiStream & src);
};

class EventFlag : public Object
{
protected:
	enum tagPart { ATR=0, FLGPTN };
public:
	DECLARE_API(CRE_FLG)

	void Body(MultiStream &);
};

class DataQueue : public Object
{
protected:
	enum tagPart { ATR=0, CNT, DTQ };
public:
	DECLARE_API(CRE_DTQ)

	void Body(MultiStream &);
};

class Mailbox : public Object
{
protected:
	enum tagPart { ATR = 0, MPRI, HD };
public:
	DECLARE_API(CRE_MBX)

	void Body(MultiStream &);
};

class FixedsizeMemoryPool : public Object
{
protected:
	enum tagPart { ATR=0, CNT, SZ, MPF };
public:
	DECLARE_API(CRE_MPF)

	void Body(MultiStream &);
};

class CyclicHandler : public Object
{
protected:
	enum tagPart { ATR=0, EXINF, HDR, TIM, PHS };
public:
	DECLARE_API(CRE_CYC)

	void Body(MultiStream &);
};

class InterruptHandler : public Object
{
protected:
	enum tagPart { ATR=0, HDR, NO };
public:
	DECLARE_API(DEF_INH)

	void Check(bool & cont) {};
	void Body(MultiStream &);
};

class ExceptionHandler : public Object
{
protected:
	enum tagPart { ATR=0, HDR, NO };
public:
	DECLARE_API(DEF_EXC)

	virtual void Check(bool & cont) {};
	void Body(MultiStream &);
};

class InitializeHandler : public Object
{
protected:
	enum tagPart { ATR=0, EXINF, RTN};
public:
	DECLARE_API(ATT_INI)

	virtual void Check(bool & cont) {};
	void Body(MultiStream &);
};

#endif