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
 *  @(#) $Id: except.cpp,v 1.2 2002/04/05 08:48:31 takayuki Exp $
 */

// $Header: /home/CVS/configurator/except.cpp,v 1.2 2002/04/05 08:48:31 takayuki Exp $

#include "except.h"
#undef Throw

using namespace std;

unsigned long Message::current_codepage_index = 0;

unsigned long Message::codepage[NUM_SUPPORTLANGUAGE] =
{
	0x0000, /* Neutral language ( = English ) */
	0x0441  /* Japanese */
};

Message::Message(const char * msg, ...)
{
	va_list vl;
	va_start(vl, msg);
    initMessage(vl, msg);
}

void Message::initMessage(va_list vl, const char * msg)
{
    int count = current_codepage_index;

    while(count-- > 0)
        msg = va_arg(vl, const char *);

    message = msg;
}

Message::Message(Message & src)
{	message = src.message;	}


bool Message::selectCodepage(unsigned long _codepage)
{
	unsigned long i;

	for(i=0;i<NUM_SUPPORTLANGUAGE;i++)
		if(_codepage == codepage[i])
		{
			current_codepage_index = i;
			return true;
		}

	return false;
}
/*
Message & format(Message & str, ...)
{
	va_list vl;
	char buffer[1024];

	va_start(vl, str);
	vsprintf(buffer, (const char *)str, vl);

    str.message.assign(buffer);

	return str;
}
*/

ostream & operator << (ostream & out, const Message & msg)
{
    out << (const char *)msg;
    return out;
}

//------

Exception::Exception(int _code, const char * first, ...) : code(_code)
{
    va_list vl;

    if(first != 0)
    {
        va_start(vl, first);
        initMessage(vl, first);
    }else
        message = "Unknown Exception";
}

Exception::Exception(const char * first, ...) : code(FATAL), child(false)
{
    va_list vl;

    va_start(vl, first);
    initMessage(vl, first);
}

Exception::Exception(const Exception & exc)
{
    child = false;
    code = exc.code;
    message = exc.message;
}

Exception::Exception(const Exception * exc)
{
    child = true;
    code = exc->code;
    message = exc->message;
}

Exception::~Exception(void)
{
    if(!child)
    {
        this->Garbage::~Garbage();
        throw new Exception(this);
    }
}

bool Exception::isFatal(void) const
{   return code < 0;    }


Exception::operator int (void) const
{   return code;    }

//------

bool VerboseMessage::verboseControl = false;
std::ostream * VerboseMessage::outputStream = 0;

VerboseMessage::VerboseMessage(const char * msg, ...)
{
	va_list vl;
	va_start(vl, msg);
    initMessage(vl, msg);
}

VerboseMessage::~VerboseMessage(void)
{
    if(verboseControl && (outputStream != 0))
        *outputStream << message;
}
