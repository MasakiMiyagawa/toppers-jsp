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
 *  @(#) $Id: mpstrstream.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $
 */


// $Header: /home/CVS/configurator/mpstrstream.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $

#ifndef __MPFSTREAM
#define __MPFSTREAM

#ifdef _MSC_VER
  #pragma warning(disable:4786)
#endif

#include "except.h"
#include "garbage.h"

#include <fstream>
#include <strstream>
#include <list>
#include <string>

class mpstrstream : public Garbage
{
public:
	enum { DEFAULT = 0, NO_SERIALIZE = 1 };

protected:
	struct tagStreamPartInfo
	{
		std::string	    name;
		std::strstream  stream;
		int				flags;
	};

	std::string filename;

	std::list<struct tagStreamPartInfo *>           container;
	std::list<struct tagStreamPartInfo *>::iterator current;

	std::list<struct tagStreamPartInfo *>::iterator _find(const char * partname) const;

public:
	enum tagPosition { BEGIN, END };

	mpstrstream(void);
	mpstrstream(const std::string &);
	mpstrstream(const char * filename);
	~mpstrstream(void);

	bool             operator !  (void) const;
	std::strstream & operator *  (void) const;
	std::strstream & operator [] (const char *);
	std::strstream & operator [] (unsigned int);
	std::strstream & operator [] (enum tagPosition);
	std::strstream & operator ++ (void);
	std::strstream & operator -- (void);

	bool             is_valid(void)      const;
    const std::string &    getStreamName(void) const;
	const std::string &	 getPartName(void)   const;
	std::strstream & getStream(void)     const;

	std::strstream & moveto(const std::string & partname);
	std::strstream & moveto(const char * partname);
	std::strstream & moveto(unsigned int offset);
	std::strstream & moveto(enum tagPosition pos);
	std::strstream & movenext(void);
	std::strstream & moveprev(void);

	std::strstream & createpart(const char * partname, const char * second = 0, ... );
	std::strstream & insertpart(const char * partname, const char * successor = 0);
	void             erasepart(const char * partname);
	void             movepart(const char * partname, const char * successor = 0);

	void             assignFilename(const std::string &);
	void             assignFilename(const char *);
	void             serialize(void);
	std::ostream &   serialize(std::ostream &);

	int				 setf(const char * partname, int);
	int				 setf(int);

	template<class T>
	std::strstream & operator << (const T & src) { (*current)->stream << src; return (*current)->stream; };

};

inline mpstrstream::mpstrstream(void)
{	current = container.end();	}

inline mpstrstream::mpstrstream(const std::string & src)
{	current = container.end();	filename.assign(src);	}

inline mpstrstream::mpstrstream(const char * file)
{	current = container.end();	filename.assign(file);	}

inline const std::string & mpstrstream::getStreamName(void) const
{	return filename;	}

inline const std::string & mpstrstream::getPartName(void) const
{	return (*current)->name;	}

inline std::strstream & mpstrstream::getStream (void) const
{	return (*current)->stream;	}

inline std::strstream & mpstrstream::operator * (void) const
{	return getStream();	}

inline bool mpstrstream::is_valid(void) const
{	return !(container.end() == current);	}

inline bool mpstrstream::operator ! (void) const
{	return is_valid();	}

inline std::strstream & mpstrstream::operator [](const char * partname)
{	return moveto(partname);	}

inline std::strstream & mpstrstream::operator [](unsigned int offset)
{	return moveto(offset);	}

inline std::strstream & mpstrstream::operator [](enum tagPosition pos)
{	return moveto(pos);	}

inline std::strstream & mpstrstream::operator ++ (void)
{	return movenext();	}

inline std::strstream & mpstrstream::operator -- (void)
{	return moveprev();	}

inline std::strstream & mpstrstream::moveto(const std::string & partname)
{	return moveto(partname.c_str());	}

inline std::strstream & mpstrstream::movenext(void)
{	current++; return (*current)->stream;	}

inline std::strstream & mpstrstream::moveprev(void)
{	current--; return (*current)->stream;	}

inline void mpstrstream::assignFilename(const std::string & src)
{	filename.assign(src);	}

inline void mpstrstream::assignFilename(const char * src)
{	filename.assign(src);	}

inline int mpstrstream::setf(const char * partname, int flag)
{
	this->movepart(partname);
	return setf(flag);
}
#endif