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
 *  @(#) $Id: toppers.cpp,v 1.10 2000/11/14 15:56:26 takayuki Exp $
 */

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include "toppers.h"
#include "manager.h"
#include <stdlib.h>
#include <stdio.h>

	//Instanciate
Miscellanea misc;
Task task;
Semaphore semaphore;
EventFlag eventflag;
DataQueue dataqueue;
Mailbox mailbox;
FixedsizeMemoryPool fixedsizememorypool;
CyclicHandler cyclichandler;
InterruptHandler interrupthandler;
ExceptionHandler exceptionhandler;
InitializeHandler initializehandler;

void Manager::DeclareAPI(void)
{
	DeclareAPI(&misc.INCLUDE);
	DeclareAPI(&misc.DEFINE);

	DeclareAPI(&task.CRE_TSK);
	DeclareAPI(&task.DEF_TEX);

	DeclareAPI(&semaphore.CRE_SEM);

	DeclareAPI(&eventflag.CRE_FLG);

	DeclareAPI(&dataqueue.CRE_DTQ);

	DeclareAPI(&mailbox.CRE_MBX);

	DeclareAPI(&fixedsizememorypool.CRE_MPF);

	DeclareAPI(&cyclichandler.CRE_CYC);

	DeclareAPI(&interrupthandler.DEF_INH);

	DeclareAPI(&exceptionhandler.DEF_EXC);

	DeclareAPI(&initializehandler.ATT_INI);
}

void Manager::DeclareSerializer(void)
{
	DeclareSerializer(&misc);
	DeclareSerializer(&task);
	DeclareSerializer(&semaphore);
	DeclareSerializer(&eventflag);
	DeclareSerializer(&dataqueue);
	DeclareSerializer(&mailbox);
	DeclareSerializer(&fixedsizememorypool);
	DeclareSerializer(&cyclichandler);
	DeclareSerializer(&interrupthandler);
	DeclareSerializer(&exceptionhandler);
	DeclareSerializer(&initializehandler);
	DeclareSerializer(&misc);
}

ostream & operator <<(ostream & dest, Valient & val)
{
	switch((Valient::tagType)val)
	{
	case Valient::INTEGER:
		dest << val.GetInteger();
		break;
	case Valient::STRING:
		dest << val.GetString();
		break;
	case Valient::DOUBLE:
		dest << val.GetDouble();
		break;
	case Valient::POINTER:
		dest << val.GetPointer();
		break;
	}
	return dest;
}


void Miscellanea::API_INCLUDE::Body(Array & Parameter)
{
	CheckParameter(&Parameter,"s");
	misc.AddIncludeFile(string(Parameter[0].GetString()));
}

void Miscellanea::API_DEFINE::Body(Array & Parameter)
{
	CheckParameter(&Parameter,"s,-");
	CheckParameterCount(Parameter,2);
	misc.AddDefinition(string(Parameter[0].GetString()),Parameter[1]);
}

void Miscellanea::Body(MultiStream & dest)
{
	fstream * out;

	if(!secondpass)
	{
		{	//���󥯥롼�ɥե�����ν���
			out = dest[CFGFILE];
			set<string>::iterator scope = includefilename.begin();

			(*out) << "#include \"jsp_kernel.h\"" << endl << "#include \"" HEADERFILE "\"" << endl;
			while(scope != includefilename.end())
			{
				(*out) << "#include " << *scope << endl;
				scope ++;
			}
			(*out) << endl;
		}

			
		{	//�������ν���
			out = dest[HEADERFILE];
			map<string,Valient>::iterator scope;

			scope = define.begin();
			while(scope != define.end())
			{
				(*out) << "#define " << (*scope).first << " " << (*scope).second << endl;
				scope ++;
			}
			(*out) << endl;
		}
		secondpass = true;

			//�ü�����
		out = dest[CFGFILE];
		(*out) << "#ifdef _MSC_VER\n#define __ZERO(x,y) _declspec(naked) void y(void){}\n#else\n#define __ZERO(x,y) x y[0]\n#endif\n\n";
		return;
	}


	{	//2nd pass prosess
		set<string>::iterator scope;

		out = dest[CFGFILE];
		(*out) << "#include \"time_event.h\"" << endl << "TMEVTN	tmevt_heap[TNUM_TSKID + TNUM_CYCID];" << endl << endl;
		(*out) << "void object_initialize(void)" << endl << '{' << endl;
		
		scope = initializer.begin();
		while(scope != initializer.end())
		{
			(*out) << '\t' << *scope << "_initialize();" << endl;


			scope ++;
		}
		(*out) << '}' << endl;
		return;
	}
}


bool Miscellanea::IsDefined(const string & id)
{
	if(id.empty())
		return false;

	if(define.find(id) != define.end())
		return true;
	
	return false;
}

bool Miscellanea::AddIncludeFile(const string & filename)
{
	if(filename.empty())
		return false;

	includefilename.insert(filename);
	return true;
}

bool Miscellanea::AddInitializer(const string & name)
{
	if(name.empty())
		return false;

	initializer.insert(name);
	return true;
}

bool Miscellanea::AddDefinition(const string & id, const Valient & val)
{
	if(id.empty() || IsDefined(id))
		return false;
	
	define[id] = val;
	return true;
}

bool Miscellanea::GetDefinision(const string & id, Valient & val)
{
	if(id.empty() || !IsDefined(id))
		return false;

	val = define[id];
	return true;
}

Array * Object::LoadParameters(Array * src, int id, int start, int end, int offset)
{
	Array * dest;
	if(!Identifier.IsAssigned(id))
		return 0l;

	if(start > end)
		start ^= end, end ^= start, start ^= end;

	offset -= start;

	dest = &InitialParameter[id];
	if(src->Size() <= end + offset)
		throw Exception("�����ο������ʤ�");

	do
	{
		dest->Set(start,*src->GetValuePtr(start + offset));
		start ++;
	} while(start <= end);

	return dest;
}

int Object::AssignObjectID(Valient & src)
{
	int id;
	
	switch( (Valient::tagType) src)
	{
	case Valient::STRING:
		if(misc.IsDefined(string(src.GetString())))
			throw Exception("���֥�������̾�Ϥ��Ǥ����ѺѤ�");

		id = Identifier.GetNewID();
		misc.AddDefinition(string(src.GetString()),Valient(id));
		break;
	case Valient::INTEGER:
		id = src.GetInteger();
		if(Identifier.IsAssigned(id))
			throw Exception("���֥�������ID�Ϥ��Ǥ����ѺѤ�");
		break;
	default:
		throw Exception("�������ͤ����ꤵ�줿");
	}

	Identifier.Assign(id);
	return id;
}

int Object::GetAssignedObjectID(Valient & src)
{
	int id;
	Valient work;

	switch( (Valient::tagType) src)
	{
	case Valient::STRING:
		if(!misc.IsDefined(string(src.GetString())))
			throw Exception("���ꤵ�줿���֥�������̾��¸�ߤ��ʤ�");
	
		misc.GetDefinision(string(src.GetString()),work);
		if(!(work == Valient::INTEGER))
			throw Exception("���֥�������̾������");
		id = work.GetInteger();
		break;
	case Valient::INTEGER:
		id = src.GetInteger();
		break;
	default:
		throw Exception("��������");
	}

	if(!Identifier.IsAssigned(id))
		throw Exception("���֥������Ȥ�¸�ߤ��ʤ�");

	return id;
}

void Object::Check(bool & cont)
{
	if(!Identifier.IsAvailable())
		throw Exception("���֥�������ID������ [��Ϣ³, ���, �ϰϳ� �ʤ�]");
}

void Object::OutputHeaderBlock(ostream * dest, char * shortname, char * longname, char * sp)
{
	char lsname[16];
	char splsname[16];
	int i;

	for(i=0;*(shortname+i)!='\x0';i++)
		lsname[i] = *(shortname+i) - 'a' + 'A';
	lsname[i] = '\x0';

	if(sp == 0l)
		sp = shortname;

	(*dest) << "#include \"" << longname << ".h\"" << endl << endl;
	(*dest) << "#define TNUM_" << lsname << "ID " << Identifier.GetCount() << endl << endl;
	(*dest) << "const ID _kernel_tmax_" << shortname << "id = (TMIN_" << lsname << "ID + TNUM_" << lsname << "ID - 1);" << endl << endl;

	for(i=0;*(sp+i)!='\x0';i++)
		splsname[i] = *(sp+i) - 'a' + 'A';
	splsname[i] = '\x0';

	if(Identifier.GetCount() != 0)
	{
		
		(*dest) << "const " << splsname << "INIB _kernel_" << sp << "inib_table[TNUM_" << lsname << "ID] = {" << endl;
		misc.AddInitializer(string(longname));
	}else
		(*dest) << "__ZERO(const " << splsname << "INIB, _kernel_" << sp << "inib_table);" << endl;

};

void Object::OutputFooterBlock(ostream * dest, char * shortname, char * type)
{
	char lsname[16];
	char tlsname[16];
	int i;

	for(i=0;*(shortname+i)!='\x0';i++)
		lsname[i] = *(shortname+i) - 'a' + 'A';
	lsname[i] = '\x0';

	if(type == 0l)
		type = shortname;

	for(i=0; *(type+i)!='\x0'; i++)
		tlsname[i] = *(type+i) - 'a' + 'A';
	tlsname[i] = '\x0';

	if(Identifier.GetCount() != 0)
		(*dest) << "};" << endl << endl << tlsname << "CB _kernel_" << type << "cb_table[TNUM_" << lsname << "ID];";
	else
		(*dest) << "__ZERO(" << tlsname << "CB, _kernel_" << type << "cb_table);";
	
	(*dest) << endl << endl;
}

void Object::CreateBufferDefinition(ostream * out, int pos, char * type, char * prefix, int sizepos)
{
	map<int,Array>::iterator scope;
	Array * param;
	char buffer[128];

	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		if( string((*param)[pos].GetString()).compare("NULL") != 0)
			throw Exception("Non-NULL value assigned as object's buffer");

		sprintf(buffer,"_%s%d",prefix,(*scope).first);
		(*param)[pos] = buffer;
		(*out) << type << " " << (*param)[2];
		if(sizepos != -1)
		{
			(*out) << "[" << (*param)[sizepos] << "]";	
		}
		(*out) << ";" << endl;
		scope ++;
	}
}

void Task::API_CRE_TSK::Body(Array & parameter)
{
	int taskid;
	Array * dest;

	CheckParameter(&parameter,"si,{si,si,si,si,si,si}");

	taskid = task.AssignObjectID(parameter[0]);
	dest = task.LoadParameters(parameter.GetArrayPtr(1),taskid,TYPE,STACK);

	dest->Set(TEXTYPE, Valient("TA_NULL"));
	dest->Set(TEXFUNC, Valient("NULL"));
}

void Task::API_DEF_TEX::Body(Array & Parameter)
{
	int tskid;

	CheckParameter(&Parameter,"si,{si,si}");
	tskid = task.GetAssignedObjectID(Parameter[0]);
	task.LoadParameters(Parameter.GetArrayPtr(1),tskid,TEXTYPE,TEXFUNC);
}

void Task::Body(MultiStream & dest)
{
	ostream * out;
	map<int, Array>::iterator scope;
	Array * param;
	char buffer[128];

	out = dest[CFGFILE];
	(*out) << "\t//��������Ϣ" << endl;

		//�ѿ����
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;

			//�����å�
		if(string(((*param)[STACK]).GetString()).compare("NULL") != 0)
			throw Exception("Non-NULL value assigned as task stack");

		sprintf(buffer,"_stack%d",(*scope).first);
		(*param)[STACK] = buffer;

		(*out) << "VB " << (*param)[STACK] << "[" << (*param)[STACKSIZE] << "];" << endl;

		/*
			//����
		(*out) << "extern FP " << (*param)[TASK] << ";" << endl;

			//�������㳰�ϥ�ɥ�
		if(string(((*param)[TEXFUNC]).GetString()).compare("NULL") != 0)
			(*out) << "extern FP " << (*param)[TEXFUNC] << ';'<< endl;
		*/

		scope ++;
	}
	(*out) << endl;

	OutputHeaderBlock(out,"tsk","task","t");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;

		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';

		(*out) << '{' << (*param)[TYPE] << ", " << (*param)[EXINF] << ", " << (*param)[TASK]
			<< ", INT_PRIORITY(" << (*param)[PRIORITY] << "), "<< (*param)[STACKSIZE] << ", "
			<< (*param)[STACK] << ", " << (*param)[TEXTYPE] << ", " << (*param)[TEXFUNC] << '}' << endl;

		scope ++;
	}
	OutputFooterBlock(out,"tsk","t");
}


void Semaphore::API_CRE_SEM::Body(Array & param)
{
	CheckParameter(&param,"si,{si,si,si}");
	semaphore.LoadParameters(param.GetArrayPtr(1),semaphore.AssignObjectID(param[0]),ATR,MAXCNT);
}

void Semaphore::Body(MultiStream & dest)
{
	ostream * out;
	Array * param;
	map<int,Array>::iterator scope;

	out = dest[CFGFILE];
	(*out) << "\t//���ޥե���Ϣ" << endl;
	OutputHeaderBlock(out,"sem","semaphore");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[0] << ',' << (*param)[1] << ',' << (*param)[2] << '}' << endl;
		scope ++;
	}
	OutputFooterBlock(out,"sem");
}

void EventFlag::API_CRE_FLG::Body(Array & param)
{
	CheckParameter(&param,"si,{si,si}");
	eventflag.LoadParameters(param.GetArrayPtr(1),eventflag.AssignObjectID(param[0]),ATR,FLGPTN);
}

void EventFlag::Body(MultiStream & dest)
{
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//�ե饰��Ϣ" << endl;

	OutputHeaderBlock(out,"flg","eventflag");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[0] << ',' << (*param)[1] << '}' << endl;
		scope ++;
	}
	OutputFooterBlock(out,"flg");
}

void DataQueue::API_CRE_DTQ::Body(Array & param)
{
	CheckParameter(&param,"si,{si,si,si}");
	dataqueue.LoadParameters(param.GetArrayPtr(1),dataqueue.AssignObjectID(param[0]),ATR,DTQ);
}

void DataQueue::Body(MultiStream & dest)
{
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//�ǡ������塼��Ϣ" << endl;
	CreateBufferDefinition(out,DTQ,"VP_INT","_dtq",CNT);
	(*out) << endl;

	OutputHeaderBlock(out,"dtq","dataqueue");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[0] << ',' << (*param)[1] << ',' << (*param)[2] <<  '}' << endl;
		scope ++;
	}
	OutputFooterBlock(out,"dtq");
}

void Mailbox::API_CRE_MBX::Body(Array & param)
{
	CheckParameter(&param,"si,{si,si,si}");
	mailbox.LoadParameters(param.GetArrayPtr(1),mailbox.AssignObjectID(param[0]),ATR,HD);
}

void Mailbox::Body(MultiStream & dest)
{
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//�᡼��ܥå�����Ϣ" << endl;

	OutputHeaderBlock(out,"mbx","mailbox");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[0] << ',' << (*param)[1] << '}' << endl;
		scope ++;
	}
	OutputFooterBlock(out,"mbx");
}

void FixedsizeMemoryPool::API_CRE_MPF::Body(Array & param)
{
	CheckParameter(&param,"si,{si,si,si,si}");
	fixedsizememorypool.LoadParameters(param.GetArrayPtr(1),fixedsizememorypool.AssignObjectID(param[0]),ATR,MPF);
}

void FixedsizeMemoryPool::Body(MultiStream & dest)
{
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];
	char buffer[128];

	(*out) << "\t//����Ĺ����ס����Ϣ" << endl;

		//�Хåե�����
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		if(string((*param)[MPF].GetString()).compare("NULL") != 0)
			throw Exception("Non-NULL value assigned as buffer of memory pool");

		sprintf(buffer,"_mpf%d",(*scope).first);
		(*param)[MPF] = buffer;
		(*out) << "VP " << (*param)[MPF] << "[TCOUNT_VP(" << (*param)[SZ] << ") * (" << (*param)[CNT] << ")];" << endl;		
		scope ++;
	}

	OutputHeaderBlock(out,"mpf","mempfix");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[ATR] << ",TCOUNT_VP(" << (*param)[SZ] << ")," << (*param)[MPF] << "(VP)(((VB *)" << (*param)[MPF] << ") + sizeof(" << (*param)[MPF] << "))}" << endl;
		scope ++;
	}
	OutputFooterBlock(out,"mpf");
}

void CyclicHandler::API_CRE_CYC::Body(Array & param)
{
	CheckParameter(&param,"si,{si,si,si,si,si}");
	cyclichandler.LoadParameters(param.GetArrayPtr(1),cyclichandler.AssignObjectID(param[0]),ATR,PHS);
}

void CyclicHandler::Body(MultiStream & dest)
{
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//������ư�ϥ�ɥ��Ϣ" << endl;

	OutputHeaderBlock(out,"cyc","cyclic");
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[0] << ',' << (*param)[1] << ',' << (*param)[2] << ',' << (*param)[3] << ',' << (*param)[4] << '}' << endl;
		scope ++;
	}
	OutputFooterBlock(out,"cyc");
}

void InterruptHandler::API_DEF_INH::Body(Array & param)
{
	int id;
	Array * inip;
	CheckParameter(&param,"si,{si,s}");
	
	id = interrupthandler.Identifier.GetNewID();
	interrupthandler.Identifier.Assign(id);
	inip = interrupthandler.LoadParameters(param.GetArrayPtr(1),id,ATR,HDR);
	inip->Set(NO,param[0]);
}

void InterruptHandler::Body(MultiStream & dest)
{
	set<string> entry;
	set<string>::iterator entry_scope;

	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//�����ߥϥ�ɥ��Ϣ" << endl;
	(*out) << "#include \"interrupt.h\"" << endl;
	(*out) << "#define TNUM_INHNO " << Identifier.GetCount() << endl;
	(*out) << "const ID _kernel_tnum_inhno = TNUM_INHNO;" << endl << endl;

	if(Identifier.GetCount() == 0)
	{
		(*out) << "__ZERO(const INHINIB, _kernel_inhinib_table);" << endl << endl;
		return;
	}

	entry.clear();
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		entry.insert((*scope).second[HDR].GetString());
		scope ++;
	}

	entry_scope = entry.begin();
	while(entry_scope != entry.end())
	{
		(*out) << "INTHDR_ENTRY(ENTRY(" << (*entry_scope) << ")," << (*entry_scope) << ");" << endl;
		entry_scope ++;
	}

	(*out) << endl << "const INHINIB _kernel_inhinib_table[TNUM_INHNO] = {" << endl;
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[NO] << ',' << (*param)[ATR] << ",ENTRY(" << (*param)[HDR] << ")}" << endl;
		scope ++;
	}
	(*out) << "};" << endl << endl;
	misc.AddInitializer(string("interrupt"));
}

void ExceptionHandler::API_DEF_EXC::Body(Array & param)
{
	int id;
	Array * inip;
	CheckParameter(&param,"si,{si,si}");
	
	id = exceptionhandler.Identifier.GetNewID();
	exceptionhandler.Identifier.Assign(id);
	inip = exceptionhandler.LoadParameters(param.GetArrayPtr(1),id,ATR,HDR);
	inip->Set(NO,param[0]);
}

void ExceptionHandler::Body(MultiStream & dest)
{
	set<string> entry;
	set<string>::iterator entry_scope;
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//CPU�㳰�ϥ�ɥ��Ϣ" << endl;
	(*out) << "#include \"exception.h\"" << endl;
	(*out) << "#define TNUM_EXCNO " << Identifier.GetCount() << endl;
	(*out) << "const ID _kernel_tnum_excno = TNUM_EXCNO;" << endl << endl;

	if(Identifier.GetCount() == 0)
	{
		(*out) << "__ZERO(const EXCINIB, _kernel_excinib_table);" << endl;
		return;
	}

	entry.clear();
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		entry.insert((*scope).second[HDR].GetString());
		scope ++;
	}

	entry_scope = entry.begin();
	while(entry_scope != entry.end())
	{
		(*out) << "EXCHDR_ENTRY(ENTRY(" << (*entry_scope) << ")," << (*entry_scope) << ");" << endl;
		entry_scope ++;
	}

	(*out) << endl << "const EXCINIB _kernel_excinib_table[TNUM_EXCNO] = {" << endl;
	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t';
		if(scope != InitialParameter.begin())
			(*out) << ',';
		(*out) << '{' << (*param)[NO] << ',' << (*param)[ATR] << ",ENTRY(" << (*param)[HDR] << ")}" << endl;
		scope ++;
	}
	(*out) << "};" << endl << endl;
	misc.AddInitializer(string("exception"));
}

void InitializeHandler::API_ATT_INI::Body(Array & param)
{
	int id;
	CheckParameter(&param,"{si,si,si}");
	id = initializehandler.Identifier.GetNewID();
	initializehandler.Identifier.Assign(id);
	initializehandler.LoadParameters(param.GetArrayPtr(0),id,ATR,RTN);
}

void InitializeHandler::Body(MultiStream & dest)
{
	map<int,Array>::iterator scope;
	Array * param;
	ostream * out = dest[CFGFILE];

	(*out) << "\t//������롼�����Ϣ" << endl;
	(*out) << "void call_inirtn(void)" << endl << '{' << endl;

	scope = InitialParameter.begin();
	while(scope != InitialParameter.end())
	{
		param = &(*scope).second;
		(*out) << '\t' << (*param)[RTN] << "((VP_INT)(" << (*param)[EXINF] << "));" << endl;
		scope ++;
	}
	(*out) << "}" << endl << endl;
}
