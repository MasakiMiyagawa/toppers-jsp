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
 *  @(#) $Id: manager.cpp,v 1.4 2000/11/24 09:14:47 takayuki Exp $
 */

#include "manager.h"
#include "staticapi.h"
#include "serializer.h"
#include "parser.h"
#include "multistream.h"
#include "exception.h"

#include <fstream>
#include <stdlib.h>
#include <stdio.h>

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

using namespace std;

Manager::Manager(Parser * src)
{
	Source = src;
}

Manager::~Manager(void)
{
	API.clear();
	SerializeUnit.clear();
}

bool Manager::Body(char * filename)
{
	DeclareAPI();
	DeclareSerializer();

	{
		map<string,StaticAPI *>::iterator func;
		istream * in;
		fstream infile;
		string api;
		Array param;
		
		if(filename != 0l)
		{
			infile.open(filename,ios::in);
			if(!infile.is_open())
				throw Exception(string("Configurator failed to open the source file [") + filename + "]");
			in = static_cast<istream *>(&infile);
		}else
			in = static_cast<istream *>(&cin);
		
		Source->SetStream(in);
		while(Source->GetNextStatement(api,param))
		{
			if((func = API.find(api)) == API.end())
			{
				char buffer[1024];
				sprintf(buffer,"%s(%d) : Static API [%s] does not exist",filename,Source->GetPreviousLinePosition(),api.c_str());
				throw Exception(buffer);
			}

			try
			{
				(*func).second->Body(param);
			}
			catch(Exception e)
			{
				char buffer[1024];
				sprintf(buffer,"%s(%d) : Fatal error on Static API[%s] (%s)",filename,Source->GetPreviousLinePosition(),api.c_str(),e.GetReason().c_str());
				throw Exception(buffer);
			}

			param.Clear();
		}

		if(infile.is_open())
			infile.close();
	}

	{
		bool cont;
		list<Serializer *> Checkers;
		list<Serializer *>::iterator scope;
		unsigned int LastCheckersCount;

		scope = SerializeUnit.begin();
		while(scope != SerializeUnit.end())
		{
			Checkers.push_back(*scope);
			scope ++;
		}

		do
		{
			LastCheckersCount = Checkers.size();
			scope = Checkers.begin();
			while(scope != Checkers.end())
			{
				try
				{
					cont = false;
					(*scope)->Check(cont);
					if(!cont)
						scope = Checkers.erase(scope);
					else
						scope ++;
				}
				catch(Exception e)
				{
					char buffer[1024];
					sprintf(buffer,"Fatal error on validation step (%s)",e.GetReason().c_str());
					throw Exception(buffer);
				}
			}
		}while(Checkers.begin() != Checkers.end() && LastCheckersCount != Checkers.size());

		if(Checkers.begin() != Checkers.end())
			throw Exception("Validation step comes to a deadlock");
	}

	{
		list<Serializer *>::iterator scope;
		MultiStream outfile;

		scope = SerializeUnit.begin();
		while(scope != SerializeUnit.end())
		{
			try
			{
				(*scope)->Body(outfile);
			}
			catch(Exception e)
			{
				char buffer[1024];
				sprintf(buffer,"Configurator failed on Output step (%s)",e.GetReason().c_str());
				throw Exception(buffer);
			}
			scope ++;
		}

		outfile.CloseAllStream();
	}

	return true;
}

void Manager::DeclareAPI(StaticAPI * api)
{
	if(api == 0l)
		throw Exception("Fatal: Assigning a Static API with NULL pointer");
	
	API[string(api->GetAPIName())] = api;
}

void Manager::DeclareSerializer(Serializer * sel)
{
	if(sel == 0l)
		throw Exception("Fatal: Assigning a Serializer with NULL pointer");

	SerializeUnit.push_back(sel);
}
