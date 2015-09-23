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
 *  @(#) $Id: task.cpp,v 1.3 2000/11/14 16:57:33 takayuki Exp $
 */

#pragma warning(disable:4786)

#include "Serializer.h"
#include "staticapi.h"
#include "id.h"

#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

#define DECLARE_API(x) \
class API_##x : public StaticAPI { public: char * GetAPIName(void) { return #x; }; bool Body(Array &); } x; friend class API_##x; 

class Includer : public Serializer
{
protected:
	list<string> filename;

public:
	DECLARE_API(INCLUDE)

	bool Body(ostream & dest)
	{
		list<string>::iterator scope = filename.begin();

		while(scope != filename.end())
		{
			dest << "#include \"" << *scope << "\"" << endl;
			scope ++;
		}
		return true;
	}
} includer;

bool Includer::API_INCLUDE::Body(Array & Parameter)
{
	includer.filename.push_front(Parameter[0].GetString());
	return true;
}


class Definer : public Serializer
{
protected:
	struct tagValue
	{
		string Identifier;
		Valient Instance;
	};

	list<tagValue> define;

public:
	bool IsDefined(string & id)
	{
		list<tagValue>::iterator scope;

		scope = define.begin();
		while(scope != define.end())
		{
			if( (*scope).Identifier == id)
				return true;
			scope ++;
		}
		
		return false;
	}
	
	void Add(string & id, Valient & val)
	{
		tagValue work;
		work.Identifier = id;
		work.Instance = val;
		define.push_back(work);
	};

	bool Body(ostream & dest)
	{
		list<tagValue>::iterator scope;

		scope = define.begin();
		while(scope != define.end())
		{
			dest << "#define " << (*scope).Identifier << " " << (*scope).Instance << endl;
			scope ++;
		}
		return true;
	};
} definer;

class Task : public Serializer
{
protected:
	ID TaskID;

	enum tagPart
	{
		TYPE=0, EXINF, TASK, PRIORITY, STACKSIZE, STACK
	};

	map<int, Array> InitialParameter;

public:
	DECLARE_API(CRE_TSK)

	bool Body(ostream & src)
	{
		return true;
 	}
} task;


bool Task::API_CRE_TSK::Body(Array & parameter)
{
	int taskid;
	Valient work;

	Array * info;
	Array * subarray;

	work = parameter[0];
	if(work == Valient::STRING)
	{
		if(definer.IsDefined(string(work.GetString())))
		{
			//Already Defined
			return false;
		}
		taskid = task.TaskID.GetNewID();
		definer.Add(string(work.GetString()),Valient(taskid));
	}else
	{
		taskid = work.GetInteger();
		if(task.TaskID.IsAssigned(taskid))
			return false;
	}

	task.TaskID.Assign(taskid);
	info = &task.InitialParameter[taskid];
	subarray = parameter.GetArrayPtr(1);
	info->Set(TYPE, (*subarray)[0]);
	info->Set(EXINF, (*subarray)[1]);
	info->Set(TASK, (*subarray)[2]);
	info->Set(PRIORITY, (*subarray)[3]);
	info->Set(STACKSIZE, (*subarray)[4]);
	info->Set(STACK, (*subarray)[5]);

	return true;
}


#include "manager.h"

void Manager::DeclareAPI(void)
{
	DeclareAPI(&task.CRE_TSK);
	DeclareAPI(&includer.INCLUDE);
}

void Manager::DeclareSerializer(void)
{
	DeclareSerializer(&includer);
	DeclareSerializer(&definer);
	DeclareSerializer(&task);
}
