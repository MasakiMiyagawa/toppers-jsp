/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: toppers.h,v 1.5 2001/11/13 11:58:17 takayuki Exp $
 */

/*
 * ���Υե�����ϲ���Ū�ʤ�ΤǤ��ꡤ���ΥС������ǤϺ��������ǽ��������
 *  (�ä˥ץ�ƥ������ɥᥤ��˴ؤ�����ʬ)
 */

#ifndef __TOPPERS_H
#define __TOPPERS_H

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <string>
#include <vector>
#include <map>
#include <set>

#include "../manager.h"
#include "../domain.h"
#include "../staticapi.h"
#include "../serializer.h"
#include "../garbage.h"
#include "../id.h"
#include "../value.h"

	//�Ǥ��Ф��ե������̾��
#define ORTIFILE "toppers_info.odl"
#define CFGFILE "kernel_cfg.c"
#define DOMAINCFGPREFIX "_cfg.c"
#define SHAREDOMFILE "shared_cfg.c"
#define HEADER "kernel_id.h"
#define LDSCRIPT "ld.script"
#define CHECKER "kernel_chk.c"

	//�����ޥ���
#define DECLARE_API(x) class API_##x : public StaticAPI { public: class BaseObject * Parent; const char * GetAPIName(void) { return #x; }; void Body(Manager *, Array *); } x; friend class x;
#define DECLARE_PAPI(x) class API_##x : public StaticAPI { const char * GetAPIName(void) { return #x; }; void Body(Manager *, Array *); } x; friend class x;
#define INIT_API(x) x##.Parent = this;
#define DECLARE_OBJECT(x,y) class x : public BaseObject { public: DECLARE_API(y); x(void) { INIT_API(y); }; };

enum tagOption
{
	ORTISUPPORT,
	DOMAINSUPPORT,
	VERBOSE,
	FORCEDOMAINSUPPORT,
	CHECKERFILE
};

class BaseObject
{
public:
	std::map<std::string, int> ObjectID;
	ID Identifier;
	Array Parameter;

	void InitializeParameter(int, int);
	bool LoadParameter(int, Array *, const char *,const char ** = NULL);
	void SetParameter(int, int, Value *);
	Value * GetParameter(int, int);

	int AssignNewObjectID(Manager *, int);
	int AssignObjectID(Manager *,Value *,int);
	int GetObjectID(Value *);

	void Serialization(Manager *, MultiStream &, const char *, const char *, const char * = NULL);
	void CreateBuffer(Manager *, MultiStream &, const char *, int, int, const char *, const char *);
};


	//���������֥�������
class Task : public BaseObject
{
public:
	enum tagPart
	{	TYPE=0, EXINF, TASK, PRIORITY, STACKSIZE, STACK, TEXTYPE, TEXFUNC};

	DECLARE_API(CRE_TSK);
	DECLARE_API(DEF_TEX);
	Task(void) 
	{ 
		INIT_API(CRE_TSK); 
		INIT_API(DEF_TEX);
	};
};

	//�ҤȤĤ���API���ʤ�ͭ��̵�ݤɤ�
DECLARE_OBJECT(Semaphore, CRE_SEM);
DECLARE_OBJECT(EventFlag, CRE_FLG);
DECLARE_OBJECT(DataQueue, CRE_DTQ);
DECLARE_OBJECT(Mailbox,   CRE_MBX);
DECLARE_OBJECT(CyclicHandler, CRE_CYC);

class FixedsizeMemoryPool : public BaseObject
{
public:
	FixedsizeMemoryPool(void) { INIT_API(CRE_MPF); };

	DECLARE_API(CRE_MPF);
	void Serialization(Manager *, MultiStream &, const char *, const char *, const char * = NULL);
};

	//����ߥϥ�ɥ�
class InterruptHandler : public BaseObject
{
public:
	InterruptHandler(void) { INIT_API(DEF_INH); };

	DECLARE_API(DEF_INH);

	void Serialization(Manager *, MultiStream &);
};

	//�㳰�ϥ�ɥ�
class ExceptionHandler : public BaseObject
{
public:
	ExceptionHandler(void) { INIT_API(DEF_EXC); };

	DECLARE_API(DEF_EXC);

	void Serialization(Manager *, MultiStream &);
};

	//������ϥ�ɥ饪�֥�������
class InitializeHandler : public BaseObject
{
protected:
	std::list<std::string> HandlerList;

public:
	InitializeHandler(void) { INIT_API(ATT_INI); };
	
	DECLARE_API(ATT_INI);

	void Serialization(Manager *, MultiStream &);
};
	

	//����JSP�Ǥ��ݸ�ɥᥤ��򥵥ݡ��Ȥ��Ƥ��ʤ��Τǡ�
	//�����ƥ����ñ�� (���ץ����ǳ����뤱�ɸ��̤ʤ�)
class ToppersDomain : public ProtectionDomain, public Serializer, public Garbage
{
protected:
	ProtectionDomain * CreateNewDomain(Manager *);
public:
	typedef std::set<int> set_int;
	std::map<BaseObject *, set_int> Object;

	void Parse(class Manager *, Parser *);
	bool Validation(Manager *);
	void Serialization(Manager *, MultiStream &);
};

/*
 * TOPPERS/JSP�����ͥ륳��ե�����졼�� ����
 */
class ToppersManager : public Manager, public Serializer
{
protected:
	std::string filename;

public:
	std::list<std::string> IncludeFile;
	std::list<std::string> Initializer;
	
	Task task;
	Semaphore semaphore;
	EventFlag eventflag;
	DataQueue dataqueue;
	Mailbox mailbox;
	FixedsizeMemoryPool fmempool;
	CyclicHandler cyclic;
	InterruptHandler inthdr;
	ExceptionHandler exchdr;
	InitializeHandler inihdr;

	ToppersManager(void);
	~ToppersManager(void) {};

	const char * GetKernelName(void) { return "TOPPERS/JSP kernel ver.1.1 (patchlevel=1)"; };
	bool ParseOption(int, char *[]);
	void Body(void);
	void Serialization(Manager *, MultiStream &);

	DECLARE_PAPI(INCLUDE);
};

#endif
