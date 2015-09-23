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
 *  @(#) $Id: component.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $
 */

// $Header: /home/CVS/configurator/component.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $

#ifndef __COMPONENT
#define __COMPONENT

#ifdef _MSC_VER
	#pragma warning(disable:4786)
#endif

#include <list>
#include <map>
#include <string>

#include "except.h"
#include "directorymap.h"

#define DEFAULT_PARAMETER " "

//------

class Component
{
public:
	enum tagBarrier   { EXTENSION, IGNORE_UNKNOWN_API };

protected:
	static std::list<Component *> componentList;
	static std::list<Component *> activatedComponentList;
	static int barrierFlag;

    static Component * findComponent(const char *);
    static bool findOption(Directory &, const char *, const char * = 0, std::string * = 0);
	static Directory * getOption(Directory &, const char *, const char * = 0);
	static Directory * mergeOption(Directory &, const char *, const char *);

	static void enable(enum tagBarrier);
	static void disable(enum tagBarrier);

	static void dumpContainerSnapshot(Directory &, bool = false);
    
    virtual void parseOption(Directory &) {};    
    virtual void body(Directory &) {};

public:
	Component(void);
    virtual ~Component(void);

    void activateComponent(bool = true);

	static bool isEnabled(enum tagBarrier);
	static void barrier(enum tagBarrier, const Message & reason);

    static void parseOption(int, char **, Directory &);
    static void executeComponents(Directory &);
};

#include <iostream>

inline Component::Component(void)
{	componentList.push_back(this);	}

inline bool Component::findOption(Directory & container, const char * id, const char * longId, std::string * value)
{
	Directory * node = getOption(container, id, longId);
	if(node != 0)
	{
		if(value != 0)
			*value = node->toString();
		return true;
	}
	return false;
}

inline void Component::enable(enum tagBarrier bf)
{	barrierFlag |= 1 << (int)bf;	}

inline void Component::disable(enum tagBarrier bf)
{	barrierFlag &= ~(1 << (int)bf);	}

inline bool Component::isEnabled(enum tagBarrier bf)
{	return (barrierFlag & (1 << (int)bf)) != 0;	}

inline void Component::barrier(enum tagBarrier bf, const Message & reason)
{
	if((barrierFlag & (1 << (int)bf)) == 0)
		Exception("The operation detailed below is not permitted.\n %s\n","�������ϵ��Ĥ���Ƥ��ޤ���\n %s\n").format(((std::string &)reason).c_str());

	if(!((std::string &)reason).empty())
		VerboseMessage("Configurator allows the operation below\n %s\n","����������Ĥ��ޤ���\n %s\n").format(((std::string &)reason).c_str());
}

#endif
