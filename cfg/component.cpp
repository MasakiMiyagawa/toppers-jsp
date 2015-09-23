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
 *  @(#) $Id: component.cpp,v 1.4 2002/04/11 07:26:37 takayuki Exp $
 */

// $Header: /home/CVS/configurator/component.cpp,v 1.4 2002/04/11 07:26:37 takayuki Exp $

#include "component.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

list<Component *> Component::componentList;
list<Component *> Component::activatedComponentList;
int Component::barrierFlag = 0;

Component::~Component(void)
{
    list<Component *>::iterator scope;

	scope = componentList.begin();
	while(scope != componentList.end())
	{
		if(*scope == this)
		{
	        componentList.erase(scope);
			break;
		}
		scope ++;
	}
}

void Component::activateComponent(bool allow_multiinstance)
{
    if(allow_multiinstance || (find(activatedComponentList.begin(),activatedComponentList.end(), this) == activatedComponentList.end()))
        activatedComponentList.push_back(this);  
}

Directory * Component::getOption(Directory & container, const char * id, const char * longId)
{
    Directory * param;
    Directory * scope;
    string identifier;

    param = container.findChild("Parameter");

    if( ((id != 0) && ((scope = param->findChild(id)) != 0)) ||
        ((longId != 0) && ((scope = param->findChild(string("-") + longId)) != 0)) )
    {
		return scope;
    }

    return NULL;
}

Directory * Component::mergeOption(Directory & container, const char * to, const char * from)
{
	Directory * src;
	Directory * dest;
	Directory * node;

	src  = container.findChild("Parameter",to,NULL);
	dest = container.findChild(string("Parameter/") + from);

	if(dest == 0)
		return src;

	if(src == 0)
		src = container.openChild("Parameter",to,NULL);

	node = dest->getFirstChild();
	while(node != 0)
	{
		src->addChild(new Directory(node->toString()));
		node = node->getNext();
	}

	dest->erase();

	return src;
}

 
static void addOptionItem(Directory * parameter, const string & key, const string & item)
{
    Directory * node;
    char buffer[32];

    node = parameter->findChild(key);

    if(item.empty())
    {
        if(node == 0)
            parameter->addChild(key, new Directory(""));
        else
            *node = "";
    }else
    {
        if(node != 0)
        {
            sprintf(buffer,"%03d", node->size());
            node->addChild(buffer, item.empty() ? new Directory("") : new Directory(item));
            *node = item;
        }else
            parameter->addChild(key, new Directory(item))->addChild("000", new Directory(item));
    }
}

void Component::parseOption(int argc, char ** argv, Directory & container)
{
    list<Component *>::iterator scope;
    Directory * parameter;
	string work;
	string prevparam;
	string::size_type i,j;
 
    try{
        parameter = container.addChild("Parameter");

		for(i=1;*(argv+i)!=0;i++)
		{
			work += *(argv+i);
			work += ' ';
		}
		(*parameter)["#cmdline"] = work.substr(0,work.size()-1);
		
		
            //�ѥ�᡼����ѡ�������
		prevparam = DEFAULT_PARAMETER;
	    while(*(++argv) != 0)
	    {
		    work.assign(*argv);
		    if(work[0] == '-')
		    {
			    i = work.find_first_of('=');
			    j = work.find_first_not_of('-');
			    if(i == j || j == string::npos)
                    Exception(Exception::FATAL,"Wrong option [%s]","�����ʥ��ץ���� [%s]").format(work.c_str());

			    if(i != string::npos)
				{
					prevparam = DEFAULT_PARAMETER;
                    addOptionItem(parameter, work.substr(1, i-1), work.substr(i+1));
				}
			    else
				{
					prevparam = work.substr(1);
                    addOptionItem(parameter, prevparam, string(""));
				}
		    }else
                addOptionItem(parameter, prevparam, work);
	    }

		if(argc == 1)
			parameter->addChild("h");

        {       //�����Х�ʥ��ץ������������

				//�ǥХå�����
			if(findOption(container, "debug","debug"))
			{
				cout << "\n[debug-info] : Parameter" << endl;
				container.findChild("Parameter")->drawTree(&cout);
			}

				//����Ϥϥ��顼��å������˱ƶ�����Τǰ��ֺǽ�˽�������
            if(findOption(container,"lj","japanese"))
                Message::selectCodepage(0x441);

            if(findOption(container,"le","english"))
                Message::selectCodepage(0);

            if(findOption(container, "debug","debug"))
                container.addChild("Debug");

            if(findOption(container,"h","help"))
                cout << '\n' << Message(
					"Global option\n"
					"  -lj, --japanese         : Use Japanese as display language\n"
					"  -le, --english          : Use English as display language(default)\n"
					"  -v, --verbose           : Display verbose messages\n"
					"  -ext, --extension       : Enable extensions\n"
					"  -no-ext, --no-extension : Restrict use of extensions (Override -ext)\n",
                    "���ΤΥ��ץ����\n"
					"  -lj, --japanese         : ���ܸ��ɽ�����ޤ�\n"
					"  -le, --english          : �Ѹ��ɽ�����ޤ�\n"
                    "  -v,  --verbose          : ����в�ʤɤ�ɽ�����ޤ�\n"
					"  -ext, --extension       : ��ĥ��ǽ��ͭ���ˤ��ޤ�\n"
					"  -no-ext, --no-extension : ��ĥ��ǽ��̵���ˤ��ޤ�\n");

			if(findOption(container,"ext","extension"))
				enable(EXTENSION);

			if(findOption(container,"no-ext","no-extension"))
				disable(EXTENSION);

            if(findOption(container,"v","verbose"))
                VerboseMessage::setVerbose(true);
        }

            //����ݡ��ͥ�Ȥˤ��ѥ�᡼������
        scope = componentList.begin();
        while(scope != componentList.end())
        {
//			VerboseMessage("Option parsing [%s]\n","���ץ������� [%s]\n").format((*scope)->getIdentifier());
            (*scope)->parseOption(container);
            scope++;
        }
    }
    catch(Exception * e)
    {
        Exception(Exception::FATAL, "Fatal error occured during command line parsing.\n  %s","���ޥ�ɥ饤�󥪥ץ����β��������̿Ū�ʥ��顼�����Ĥ���ޤ���\n  %s").format((const char *)*e);
    }
}

void Component::dumpContainerSnapshot(Directory & container, bool forcedly)
{
	string dump;

	if(forcedly || findOption(container, "D", "dump", &dump) || findOption(container,"debug","debug"))
	{
		if(dump.empty())
			dump.assign("container.txt");

		fstream f(dump.c_str(), ios::out);
		if(f.is_open())
		{
			f << "Last configuration was finished successfully\n\n";
			container.drawTree(&f);
			f.close();
		}
	}
}

void Component::executeComponents(Directory & container)
{
    Component * cmp;

    while(!activatedComponentList.empty())
    {
        cmp = *activatedComponentList.begin();
        activatedComponentList.pop_front();
        try{
            cmp->body(container);
        }
		catch(Exception * e)
        {
			dumpContainerSnapshot(container);

            if(e->isFatal())
                throw e;
            cerr << *e << Message("(continue...)","(³�Ԥ��ޤ�...)") <<  endl;
        }
    }

	dumpContainerSnapshot(container);
}
