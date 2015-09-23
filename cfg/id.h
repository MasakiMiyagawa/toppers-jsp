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
 *  @(#) $Id: id.h,v 1.3 2000/11/14 16:57:33 takayuki Exp $
 */

//------------------------------------------------------------
// ID - class definition
//
//   class ID is a type for managing objects' identifier and
//		assigning suitable identifier automatically for new
//		object.

#ifndef __ID_H

#include <set>

class ID
{
protected:
	long LowerBound;	//IDs which equal upper or lower bound are available
	long UpperBound;	
	std::set<long> AssignedIdentifier;

public:
	ID(const long Size = 255);
	explicit ID(long Lower, unsigned long Size = 255);
	explicit ID(long Lower, long Upper = 255);

	operator const bool(void);				//Availability check
	operator const unsigned long(void);	//Count of items
	bool operator [](long);							//Status of each item

	bool Assign(long);
	bool Resign(long);
	
	bool IsAssigned(long);
	long GetMaxID(void);
	long GetMinID(void);
	unsigned long GetCount(void);

	long GetNewID(void);		//Method GetNewID reports a suitable new identifier, but never reserves one.

	bool IsAvailable(void);		//This method checks up on the availablity of these IDs with ITRON ID numbering policy.
};

inline ID::operator const bool (void)
{	return this->IsAvailable();	}

inline ID::operator const unsigned long(void)
{	return this->AssignedIdentifier.size();	}

inline bool ID::operator [] (long value)
{	return this->AssignedIdentifier.find(value) != this->AssignedIdentifier.end();	}

inline bool ID::IsAssigned (long value)
{	return this->AssignedIdentifier.find(value) != this->AssignedIdentifier.end();	}

inline unsigned long ID::GetCount(void)
{	return AssignedIdentifier.size();	}

#endif

//---
// Degined and Programmed by S.D.F. in Oct,2000