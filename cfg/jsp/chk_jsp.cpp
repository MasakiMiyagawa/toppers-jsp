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
 *  @(#) $Id: chk_jsp.cpp,v 1.2 2001/11/12 04:48:18 takayuki Exp $
 */

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include "chk_jsp.h"
#include <stdio.h>
#include <map>
#include <string>

using namespace std;

unsigned int error_count = 0;

enum tagOptionList
{
	VERBOSE = 1,
	HELP    = 2
};

map<int, bool> option_container;
string modulename;
string symbolfilename;

void print_usage(void)
{
	printf(Message(" Usage : chk [options] module_file [checker_file]\n\n"," �Ȥ��� : chk [���ץ����] �⥸�塼��ե����� [�����å����ե�����]\n\n"));
	printf(Message(" Option list\n"," ���ץ����\n"));
	printf("   -v --verbose    : %s\n",(const char *)Message("Verbose mode","�ܺ�ɽ����Ԥ�"));
	printf("   -le --english   : %s\n",(const char *)Message("Shows all messages in English","��å�������Ѹ�ˤ���"));
	printf("   -lj --japansese : %s\n",(const char *)Message("Shows all messages in Japanese","��å����������ܸ�ˤ���"));
	printf("\n");
	printf(Message(" Module file\n"," �⥸�塼��ե�����\n"));
	printf(Message("   \"Module file\" is the path of the target module file.\n\n","   �оݤȤʤ�⥸�塼��ؤΥѥ�����ꤷ�ޤ�\n\n"));
	printf(Message(" Checker file\n"," �����å����ե�����\n"));
	printf(Message("   \"Checker file\" is the path of checker file \n   that contains some informations of the corresponding target module.\n   If omitted, checker uses the path to target module\n   which replaced extensions by \".chk\" instead of the checker file path.","   �⥸�塼����б���������å����ե�����Υѥ�����ꤷ�ޤ���\n   ��ά�������ϥ⥸�塼��̾�γ�ĥ�Ҥ�.chk�ˤ����ե������\n   ���ꤷ����ΤȤ��ޤ���\n"));

	printf("\n\n");
}


bool parse_option(int argc, char * argv [])
{
	int i;
	string work;
	Message UnknownOption("Unknown Option [","�����ʥ��ץ���� [");

	for(i=1;i<argc;i++)
	{
		if(*argv[i] == '-')
		{
			switch(*(argv[i]+1))
			{
			case 'v': option_container[VERBOSE] = true; break;
			case 'h': option_container[HELP] = true;    break;
			case '?': option_container[HELP] = true;    break;

			case 'l':
				if(*(argv[i]+2) == 'j')
					Message::SelectCodePage(0x411);
				else
					Message::SelectCodePage();
				break;

			case '-':
				work = argv[i]+2;

				if(work.compare("english")==0)
				{
					Message::SelectCodePage();
					break;
				}

				if(work.compare("japanese")==0)
				{
					Message::SelectCodePage(0x411);
					break;
				}

				if(work.compare("verbose")==0)
				{
					option_container[VERBOSE] = true;
					break;
				}

				if(work.compare("help")==0)
				{
					option_container[HELP] = true;
					break;
				}

				throw Exception(string(UnknownOption) + argv[i] + "]");

			default:
				break;
			}
		}else
		{
			if(!modulename.empty())
			{
				if(!symbolfilename.empty())
					throw Exception(string(UnknownOption) + argv[i] + "]");
				else
					symbolfilename = argv[i];
			}else
				modulename = argv[i];
		}
	}

	return true;
}




#define LoadVal(x,y,z) x = 0; container->load_variable(&x, sizeof(x), y, z)
#define Load(x,y) container->load_variable(&(x), sizeof(x), y)

void print_header(Message & object, const char * type, int id, bool error = true)
{
	string work;
	string objectname;

	work = "    [";
	work += object;
	work += " (";

	objectname = container->get_objectname(id, type);
	if(objectname.empty())
	{
		char buffer[32];
		sprintf(buffer, "id = %d", id);
		work += buffer;
	}else
		work += objectname;
	work += ")]: ";

	printf(work.c_str());

	if(error)
		error_count ++;
}


bool check_taskblock(void)
{
	unsigned int id;
	unsigned int maxpri;
	unsigned int minpri;
	unsigned int work;
	unsigned int num;
	struct variable_information tinib_table;
	unsigned int old_error_count = error_count;
	Message object("Task","������");

	Load(num, "_kernel_tmax_tskid");
	tinib_table = container->get_variable_information("_kernel_tinib_table");
	maxpri = container->get_variable_information("TMAX_TPRI").value;
	minpri = container->get_variable_information("TMIN_TPRI").value;

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//°�������å�
		LoadVal(work, tinib_table.address, "task_initialization_block::tskatr");
		if((work & ~0x3) != 0)
		{
			print_header(object, "TASK", id);
			printf(Message("Illegal task attribute (It should be ((TA_HLNG||TA_ASM)|TA_ACT))\n","�����ʥ�����°�� ((TA_HLNG||TA_ASM)|TA_ACT)�ʳ�\n"));
		}
			//ͥ���٥����å�
		LoadVal(work, tinib_table.address, "task_initialization_block::ipriority");
		if(work < minpri)
		{
			print_header(object, "TASK", id);
			printf(Message("Initial priority is less than minimum priority (%d).\n","���ͥ���٤�����ͥ����(%d)��Ķ���Ƥ���\n"),minpri);
		}
		if(work > maxpri)
		{
			print_header(object, "TASK", id);
			printf(Message("Initial priority is greater than maximum priority (%d).\n","���ͥ���٤�����ͥ����(%d)��Ķ���Ƥ���\n"),maxpri);
		}
		tinib_table.address += tinib_table.size;
	}

	return old_error_count == error_count;
}

bool check_semaphoreblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;
	unsigned int work2;
	unsigned int old_error_count = error_count;

	struct variable_information seminib;
	Message object("Semaphore","���ޥե�");

	Load(num, "_kernel_tmax_semid");
	seminib = container->get_variable_information("_kernel_seminib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, seminib.address, "semaphore_initialization_block::sematr");
		if((work & ~0x1) != 0)
		{
			print_header(object, "SEM", id);
			printf(Message("Illegal attribute (It should be (TA_TFIFO||TA_TPRI)).\n","(TA_TFIFO||TA_TPRI)�ʳ���°�������ꤵ��Ƥ���\n"));
		}

			//maxcnt < isemcnt
		LoadVal(work, seminib.address, "semaphore_initialization_block::maxsem");
		LoadVal(work2,seminib.address, "semaphore_initialization_block::isemcnt");
		if(work < work2)
		{
			print_header(object, "SEM", id);
			printf(Message("Initial count[%d] is greater than the maximum count[%d] of this semaphore\n","�����[%d]��������[%d]��Ķ���Ƥ���\n"),work2,work);
		}
	
		seminib.address += seminib.size;
	}

	return old_error_count == error_count;
}


bool check_eventflagblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Event flag","���٥�ȥե饰");

	Load(num, "_kernel_tmax_flgid");
	inib = container->get_variable_information("_kernel_flginib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "eventflag_initialization_block::flgatr");
		if((work & ~0x7) != 0)
		{
						print_header(object, "FLG", id);
			printf(Message("Illegal attribute value [0x%x]\n","��������°���� [0x%x]\n"),(work & ~0x7));
		}
		if((work & 0x2) != 0)
		{
						print_header(object, "FLG", id);
			printf(Message("Attribute TA_WMUL is not supported in current version.\n","TA_WMUL�ϥ��ݡ��ȳ�\n"),(work & ~0x7));
		}
	
		inib.address += inib.size;
	}

	return old_error_count == error_count;
}


bool check_dataqueueblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Data queue","�ǡ������塼");

	Load(num, "_kernel_tmax_dtqid");
	inib = container->get_variable_information("_kernel_dtqinib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "dataqueue_initialization_block::dtqatr");
		if((work & ~0x1) != 0)
		{
			print_header(object, "DTQ", id);
			printf(Message("Illegal attribute value [0x%x]\n","��������°���� [0x%x]\n"),(work & ~0x1));
		}
	
		inib.address += inib.size;
	}

	return old_error_count == error_count;
}


bool check_mailboxblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Mailbox","�᡼��ܥå���");

	Load(num, "_kernel_tmax_mbxid");
	inib = container->get_variable_information("_kernel_mbxinib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "mailbox_initialization_block::mbxatr");
		if((work & ~0x3) != 0)
		{
			print_header(object, "MBX", id);
			printf(Message("Illegal attribute value [0x%x]\n","��������°���� [0x%x]\n"),(work & ~0x3));
		}
	
			//mailbox message priority check
		LoadVal(work, inib.address, "mailbox_initialization_block::maxmpri");
		if( container->get_variable_information("mailbox_initialization_block::maxmpri").size == 2)
			work <<= 16;
		if((signed)work < 0)
		{
			print_header(object, "MBX", id);
			printf(Message("Priority must not be a negative number.\n","ͥ���٤�����\n"),(work & ~0x1));
		}

		inib.address += inib.size;
	}

	return old_error_count == error_count;
}

bool check_fixed_memorypoolblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Fixed size memory pool","����Ĺ����ס���");

	Load(num, "_kernel_tmax_mpfid");
	inib = container->get_variable_information("_kernel_mpfinib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "fixed_memorypool_initialization_block::mpfatr");
		if((work & ~0x1) != 0)
		{
			print_header(object, "MPF", id);
			printf(Message("Illegal attribute value [0x%x]\n","��������°���� [0x%x]\n"),(work & ~0x1));
		}

		inib.address += inib.size;
	}

	return old_error_count == error_count;
}


bool check_cyclic_handlerblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Cyclic handler","�����ϥ�ɥ�");

	Load(num, "_kernel_tmax_cycid");
	inib = container->get_variable_information("_kernel_cycinib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "cyclic_handler_initialization_block::cycatr");
		if((work & ~0x7) != 0)
		{
						print_header(object, "CYC", id);
			printf(Message("Illegal attribute value [0x%x]\n","��������°���� [0x%x]\n"),(work & ~0x1));
		}
		if( (work & 0x1) != 0 || (work & 0x4) != 0)
		{
						print_header(object, "CYC", id);
			printf(Message("TA_ASM and TA_PHS are not supported in this kernel.\n","TA_ASM��TA_PHS�ϥ��ݡ��ȳ�"));
		}

		inib.address += inib.size;
	}

	return old_error_count == error_count;
}

bool check_interrupt_handlerblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Interrupt handler","����ߥϥ�ɥ�");

	Load(num, "_kernel_tnum_inhno");
	inib = container->get_variable_information("_kernel_inhinib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "interrupt_handler_initialization_block::inhatr");
		if(work != 0)
		{
						print_header(object, "INT", id);
			printf(Message("The attribute can take only TA_HLNG\n","TA_HNLG�ʳ���°��������Ǥ��ޤ���\n"));
		}
		inib.address += inib.size;
	}

	return old_error_count == error_count;
}

bool check_exception_handlerblock(void)
{
	unsigned int id;
	unsigned int num;
	unsigned int work;

	unsigned int old_error_count = error_count;
	struct variable_information inib;
	Message object("Exception handler","�㳰�ϥ�ɥ�");

	Load(num, "_kernel_tnum_excno");
	inib = container->get_variable_information("_kernel_excinib_table");

	if(option_container[VERBOSE] && num != 0)
		printf(string(string("  ") + (const char *)object + (const char *)Message(" object","���֥�������") + " : %d items\n").c_str(), num);

	for(id = 1; id <= num; id++)
	{
			//attribute validation check
		LoadVal(work, inib.address, "exception_handler_initialization_block::excatr");
		if(work != 0)
		{
						print_header(object, "EXC", id);
			printf(Message("The attribute can take only TA_HLNG\n","TA_HNLG�ʳ���°��������Ǥ��ޤ���\n"));
		}
		inib.address += inib.size;
	}

	return old_error_count == error_count;
}

bool check_body(void)
{
	bool result = true;
	
	if(option_container[HELP])
	{
		print_usage();
		return true;
	}

	if(modulename.empty())
	{
		printf(Message(" Failure : Requires path for the target module\n\n","  ���顼 : �оݥ⥸�塼��̾����ꤷ�Ƥ�������\n\n"));
		print_usage();
		return false;
	}

	if(symbolfilename.empty())
		symbolfilename = modulename.substr(0, modulename.find_last_of('.')) + ".chk";

	container->attach_module(modulename.c_str());
	container->attach_infofile(symbolfilename.c_str());
	printf("  Target architecture : %s\n",container->get_architecture());

	result &= check_taskblock();
	result &= check_semaphoreblock();
	result &= check_eventflagblock();
	result &= check_dataqueueblock();
	result &= check_mailboxblock();
	result &= check_fixed_memorypoolblock();
	result &= check_cyclic_handlerblock();
	result &= check_interrupt_handlerblock();
	result &= check_exception_handlerblock();

	if(result)
		printf(Message("No error found in current configuration\n","�����˰۾�Ϥ���ޤ���Ǥ���\n"));
	else
		printf(Message("Total %d errors found in current configuration.\n","������%d�ĤΥ��顼�����Ф���ޤ���\n"),error_count);

	return result;
}