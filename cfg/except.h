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
 *  @(#) $Id: except.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $
 */

// $Header: /home/CVS/configurator/except.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $

#ifndef __EXCEPT
#define __EXCEPT

#ifdef _MSC_VER
	#pragma warning(disable:4786)
#endif

#include <string>
#include <stdarg.h>
#include <stdio.h>

#include <iostream>
#include <list>

#include "garbage.h"

#define NUM_SUPPORTLANGUAGE 2
#define MESSAGE_BUFFERSIZE  1024

/*
 * ���顼���ʤɤˤ������å������ϡ��ƤӽФ��ޤǤ����ݤ��Ȥ����������̤����äƤ����Τǡ�
 * �Ǥ���¤��ñ���������褦�ˤ��Ƥ��������Τ����ǥ����С��إåɤ������Ƥ��ޤäƤ⡢
 * �ɤ����ۥ��Ȥ�ư���Τ�̵�롥
 */

/*
 * Message : ʣ�����å��������ݻ����뤿��δ��ܥ��饹
 */

class Message
{
private:
	static unsigned long current_codepage_index;
	static unsigned long codepage[NUM_SUPPORTLANGUAGE];

protected:
	std::string message;

    Message(void) {};
    void initMessage(va_list, const char * = 0);

public:
	Message(const char *, ...);
	Message(Message &);

	operator const char * (void) const;
	operator const std::string & (void) const;

	static bool selectCodepage(unsigned long = 0x0000);

    template<class T>
    inline Message & format(const T first, ...)
    {
        va_list vl;
        char buffer[MESSAGE_BUFFERSIZE];

        va_start(vl, first);
        vl = (va_list)((char *)vl - sizeof(first));
        vsprintf(buffer, message.c_str(), vl);
        message.assign(buffer);

        return *this;
    }

    friend Message & format(Message &, ...);
    friend std::ostream & operator << (std::ostream &, const Message &);
};

inline Message::operator const char *(void) const
{	return message.c_str();	}

inline Message::operator const std::string & (void) const
{	return message;	}


//------

/*
 * VerboseMessage : �������椬�Ĥ��Ƥ�����̥�å�����
 */

class VerboseMessage : public Message
{
private:
    static std::ostream * outputStream;
    static bool verboseControl;

public:
    VerboseMessage(const char *, ...);
    ~VerboseMessage(void);

    static inline void setStream(std::ostream * out)
    {   outputStream = out; };

    static inline void setVerbose(bool mode)
    {   verboseControl = mode;  };


	static inline bool getVerbose(void)
	{	return verboseControl && (outputStream != 0);	}
    
	template<class T>
    static inline void print(T msg)
    {
        if(getVerbose())
            (*outputStream) << msg;
    };
 
    template<class T>
    inline VerboseMessage & format(const T first, ...)
    {
        va_list vl;
        char buffer[MESSAGE_BUFFERSIZE];

        va_start(vl, first);
        vl = (va_list)((char *)vl - sizeof(first));
        vsprintf(buffer, message.c_str(), vl);
        message.assign(buffer);

        return *this;
    };
};

//------


//------

/*
 * Exception : ��̿Ū�ʻ��ݤ��Ф����������å�����
 */

class Exception : public Message, public Garbage
{
protected:
    int  code;
    bool child;

    explicit Exception(const Exception *);
public:
    enum 
    {
        FATAL = 0x80000000 
    };

    Exception(int, const char * = 0, ...);
    Exception(const char *, ...);
    Exception(const Exception &);
    virtual ~Exception(void);

    bool isFatal(void) const;
    operator int (void) const;

    template<class T>
    inline Exception & format(const T first, ...)
    {
        va_list vl;
        char buffer[MESSAGE_BUFFERSIZE];

        va_start(vl, first);
        vl = (va_list)((char *)vl - sizeof(first));
        vsprintf(buffer, message.c_str(), vl);
        message.assign(buffer);

        return *this;
    }
};

#endif
