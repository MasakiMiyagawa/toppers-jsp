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
 *  @(#) $Id: directorymap.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $
 */

// $Header: /home/CVS/configurator/directorymap.h,v 1.2 2002/04/05 08:48:31 takayuki Exp $

#ifndef __DirectoryMAP_H
#define __DirectoryMAP_H

#ifdef _MSC_VER
	#pragma warning(disable:4786)
#endif

#include "except.h"
#include "garbage.h"

#include <string>
#include <map>
#include <iostream>

class Directory : public std::map<std::string, Directory *>
{
public:
	enum tagtype
	{
		UNKNOWN,
		POINTER,
		INTEGER,
		LITERAL,
		CONSTLITERAL,
		OBJECT
	};

	enum tagflag
	{
		NOTHING  = 0,
		DESTRUCT = 1,
		UNSIGNED = 2
	};

protected:
	static int defaultflag;

	enum tagtype type;
	int flag;

	Directory * parent;
	std::map<std::string, Directory *>::iterator myself;

	union
	{
		void * pointer;
		long value;
		const char * const_literal;
		std::string * literal;
		class Garbage * instance;
	} content;

    Directory(const Directory &);
    void _init(void);
	void _clear(void);
	void _erase(void);
    Directory * _find(bool, const std::string &);
    Directory * _find(bool automatic_creation, const char * key, va_list vl);

public:
	Directory(void);
    Directory(int);
    Directory(long);
    Directory(const std::string &);
    Directory(void *);
    explicit Directory(const char *);
    explicit Directory(Garbage *);
	~Directory(void);

	Directory & operator =(void *);
	Directory & operator =(long);
	Directory & operator =(const char *);
	Directory & operator =(const std::string &);
	Directory & operator =(Garbage *);

    bool operator == (enum tagtype _type)
    {   return type == _type;   };

	Directory * operator ()(const std::string & src)
	{	return findChild(src);	};
	Directory * operator ()(const char * src)
	{	return findChild(src);	};

	Directory & operator [](const std::string & src)
	{	return *openChild(src);	};
	Directory & operator [](const char * src)
	{	return *openChild(std::string(src));	};

	enum tagtype getType(void) const { return type; };
	Directory *  getParent(void) const { return parent; };
    Directory *  getParent(int) const;
	Directory *  getNext(void) const;
	Directory *  getPrev(void) const;
    Directory *  getFirstChild(void) const;
    Directory *  getLastChild(void) const;
    Directory *  findChild(const std::string &);
    Directory *  findChild(const char *);
    Directory *  findChild(const char *, const char * , ... );
    Directory *  findDescandant(const std::string &, unsigned int = 0xffffffff) const;
    Directory *  openChild(const std::string &);
    Directory *  openChild(const char *);
    Directory *  openChild(const char *, const char *, ... );

	void * operator new(size_t);
	void * operator * (void) const;
	operator const long (void) const;

	operator const unsigned long (void) const;
	operator const int (void) const;
	operator const unsigned int (void) const;
	operator const char (void) const;
	operator const unsigned char (void) const;
    operator const char * (void);
    operator const std::string & (void) const;
    operator const Garbage * (void) const;
    operator const void * (void) const;

	void * toPointer(const void * _default = 0) const;
	long toInteger(const long _default = 0) const;
	std::string toString(const std::string & _default = "") const;

	bool operator == (int) const;
	bool operator == (const std::string &) const;
	bool operator == (const char *) const;

	template<class T>
	bool operator != (T src) const
	{	return !(this->operator ==(src));	};


	Directory * addChild(const std::string &, Directory * = 0);
	Directory * addChild(const char *, Directory * = 0);
	Directory * addChild(const std::string &, Directory &);
	Directory * addChild(const char *, Directory &);
	Directory * addChild(Directory &);
	Directory * addChild(Directory * = 0);

    void erase(void);
	iterator erase(iterator);
	void disconnect(void);
    void copyTo(Directory *, int = 0x7fffffff);

	const std::string getKey(void) const;
	bool changeKey(const std::string &);
	bool changeKey(const char *);

    void Load(std::istream *);
    void Store(std::ostream *);

	void drawTree(std::ostream * = &std::cout, int = 0, std::string * = 0);

	std::string format(const char *);
	std::string format(const std::string &);
};


//------

inline void Directory::_init(void)
{
    parent = 0;
    type = UNKNOWN;
    flag = defaultflag;
    content.pointer = 0;
    defaultflag &= ~DESTRUCT;
}

inline Directory::Directory(void)
{   _init();    }

inline Directory::Directory(long val)
{
    _init();
    *this = val;
}

inline Directory::Directory(int val)
{
    _init();
    *this = (long)val;
}

inline Directory::Directory(void * val)
{
    _init();
    *this = val;
}

inline Directory::Directory(const std::string & val)
{
    _init();
    *this = val;
}

inline Directory::Directory(const char * val)
{
    _init();
    *this = val;
}

inline Directory::Directory(Garbage * val)
{
    _init();
    *this = val;
}

inline Directory * Directory::addChild(const std::string & key, Directory * node)
{
	iterator scope;

    if(node == 0)
        node = new Directory;
    else
    	if(node->parent != 0)
	    	node->disconnect();

	node->parent = this;
	if((scope = find(key)) != end())
	{
		(*scope).second->_erase();
		(*scope).second = node;
		node->myself = scope;
	}else
	{
		std::pair<iterator, bool> work;

		work = insert(value_type(key, node));
		node->myself = work.first;
	}
	return node;
}

inline Directory * Directory::addChild(const char * key, Directory * node)
{	return addChild(std::string(key), node);	}

inline Directory * Directory::addChild(const std::string & key, Directory & node)
{	return addChild(key, &node);	}

inline Directory * Directory::addChild(const char * key, Directory & node)
{	return addChild(std::string(key), &node);	}

inline Directory * Directory::addChild(Directory & node)
{	return addChild(&node);	}

	//����addChild���ɲä������Ǥϡ���������뤫���ä��ƤϤ����ʤ�
inline Directory * Directory::addChild(Directory * node)
{
	char buffer[32];
	::sprintf(buffer,"%03d", size());
	return addChild(buffer, node);
}

inline bool Directory::changeKey(const char * _key)
{	return changeKey(std::string(_key));	}

inline const std::string Directory::getKey(void) const
{
	if(parent == 0)
		return std::string("/");
	return (*myself).first;
}

inline Directory::operator const unsigned long (void) const
{   return static_cast<const unsigned long>(this->operator const long());  }

inline Directory::operator const int (void) const
{   return static_cast<const int>(this->operator const long());  }

inline Directory::operator const unsigned int (void) const
{   return static_cast<const unsigned int>(this->operator const long());  }

inline Directory::operator const char (void) const
{   return static_cast<const char>(this->operator const long());  }

inline Directory::operator const unsigned char (void) const
{   return static_cast<const unsigned char>(this->operator const long());  }

inline Directory::operator const char * (void)
{
    if(type == CONSTLITERAL)
        return content.const_literal;
    if(type == LITERAL)
        return content.literal->c_str();
    Exception("Bad cast exception raised","�������㥹���㳰");
    return 0;
}

inline Directory::operator const std::string &(void) const
{
    if(type == LITERAL)
        return *content.literal;
    Exception("Bad cast exception raised","�������㥹���㳰");
	return *(std::string *)0;
}

inline Directory::operator const Garbage * (void) const
{
    if(type == OBJECT)
        return content.instance;
    Exception("Bad cast exception raised","�������㥹���㳰");
    return 0;
}

inline Directory::operator const void * (void) const
{   return **this;  }

inline void Directory::erase(void)
{
    disconnect();
    _erase();
}

inline Directory * Directory::findChild(const std::string & path)
{   return _find(false, path);  }

inline Directory * Directory::openChild(const std::string & path)
{   return _find(true, path);  }

inline Directory * Directory::getParent(int level) const
{
    const Directory * node = this;
    while(level-- > 0 && node != 0)
        node = node->parent;
    return const_cast<Directory *>(node);
}

inline Directory * Directory::getFirstChild(void) const
{
    if(this == 0 || size()== 0)
	    return 0;
	return (*begin()).second;
}

inline Directory * Directory::getLastChild(void) const
{
    if(this == 0 || size()== 0)
	    return 0;
	return (*rbegin()).second;
}

inline bool Directory::operator == (int src) const
{	return type == INTEGER && content.value == src;	}

inline bool Directory::operator == (const std::string & src) const
{	return (type == LITERAL && src.compare(*content.literal) == 0) || (type == CONSTLITERAL && src.compare(content.const_literal) == 0);	}

inline bool Directory::operator == (const char * src) const
{	return (type == LITERAL && content.literal->compare(src) == 0) || (type == CONSTLITERAL && strcmp(content.const_literal, src)== 0);	}

inline std::string Directory::format(const char * src)
{	return format(std::string(src));	}

#endif