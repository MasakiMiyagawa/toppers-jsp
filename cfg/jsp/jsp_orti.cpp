#include "jsp_classes.h"
#include <string>
#include <iostream>

using namespace std;

void OrtiDescriptionFileGenerator::parseOption(Directory & container)
{
	string work;
	mpstrstream * stream;

	if(findOption(container,"h","help"))
	{
		cout << Message(
			"OSEK RunTime Interface(ORTI) Description File Generation\n"
			"  -odl [filename]  :  Generate an ORTI file with specifying its name of file\n",
			"OSEK RunTime Interface(ORTI) ���ҥե���������\n"
			"  -odl [filename]  :  ̾������ꤷ��ORTI�ե�������������ޤ�\n");
		return;
	}

	if(findOption(container,"odl","odl",&work))
	{
		if(work.empty())
			work.assign("ortidesc.odl");
		stream = new mpstrstream(work);
		stream->createpart("version","template","definition",NULL);

		container["/file/orti"] = stream;

		activateComponent(false);
	}

}

static void createDefinition(Directory & container, mpstrstream * out, const char * category)
{
	string work;
	Directory * scope;
	
	scope = container(category)->getFirstChild();
	while(scope != 0)
	{
		(*out) << "TEMPLATE t_" << category << '\t';

		work = scope->getKey();
		if(work[0] >= '0' && work[1] <= '9')
			(*out) << category << '_' << scope->toInteger();
		else
			(*out) << scope->getKey();
		(*out) << "(\"" << scope->toInteger() << "\");\n";

		scope = scope->getNext();
	}
}

void OrtiDescriptionFileGenerator::body(Directory & container)
{
	mpstrstream * out;

	out = reinterpret_cast<mpstrstream *>(container["/file/orti"].toPointer());

	out->moveto("definition");
	createDefinition(container,out,TASK);
	createDefinition(container,out,SEMAPHORE);
	createDefinition(container,out,EVENTFLAG);
	createDefinition(container,out,DATAQUEUE);
	createDefinition(container,out,MAILBOX);
	createDefinition(container,out,FIXEDSIZEMEMORYPOOL);
	createDefinition(container,out,CYCLICHANDLER);

	VerboseMessage("ORTI Description file generation finished successfully.\n","ORTI���ҥե��������Ϥ��ޤ���");
}