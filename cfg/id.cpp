/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ���ξ��Τ����줫�����������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
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
 *  @(#) $Id: id.cpp,v 1.6 2001/11/12 14:59:27 takayuki Exp $
 */


//------------------------------------------------------------
// ID - class implementation
//
//   class ID is a type for managing objects' identifier and
//		assigning suitable identifier automatically for new
//		object.

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include "id.h"
#include <algorithm>

using namespace std;

ID::ID(const long Size)
{
	LowerBound = 1;
	UpperBound = Size -1 + LowerBound;
	AssignedIdentifier.clear();
}

ID::ID(long Lower, unsigned long Size)
{
	LowerBound = Lower;
	UpperBound = Size -1 + LowerBound;
	AssignedIdentifier.clear();
}

ID::ID(long Lower, long Upper)
{
	if(Lower > Upper)
	{
		Lower ^= Upper;
		Upper ^= Lower;
		Lower ^= Upper;
	}
	LowerBound = Lower;
	UpperBound = Upper;
	AssignedIdentifier.clear();
}

bool ID::Assign(long value)
{
	if(value < LowerBound || value > UpperBound)
		return false;

	return (AssignedIdentifier.insert(value)).second;
}

	//METHOD Resign
	// value : The value of ID you want remove
	// Result: Execution status (True means success)
bool ID::Resign(long value)
{
	if(value < LowerBound || value > UpperBound)
		return false;

	AssignedIdentifier.erase(value);
	return true;
}

	//METHOD GetMinID
	// Result: Maximum value of ID existed
long ID::GetMaxID(void)
{
	set<long>::iterator maxvalue;

	maxvalue = max_element(AssignedIdentifier.begin(),AssignedIdentifier.end());
	if(maxvalue == AssignedIdentifier.end())
		return LowerBound -1;

	return *maxvalue;
}

	//METHOD GetMinID
	// Result: Minimum value of ID existed 
long ID::GetMinID(void)
{
	set<long>::iterator minvalue;

	minvalue = min_element(AssignedIdentifier.begin(),AssignedIdentifier.end());
	if(minvalue == AssignedIdentifier.end())
		return UpperBound + 1;

	return *minvalue;
}

	//METHOD GetNewID
	// Result: Suitable New ID
long ID::GetNewID(void)
{
	long prev;
	set<long>::iterator scope;

	if(AssignedIdentifier.size()==0)
		return LowerBound;

	scope = AssignedIdentifier.end();
	scope --;
	if(*scope-LowerBound+1 == (signed)AssignedIdentifier.size())
	{
		if(*scope+1>UpperBound)
			return LowerBound -1;
		else
			return *scope+1;
	}

	scope = AssignedIdentifier.begin();
	if(*scope != LowerBound)
		return LowerBound;
	
	prev = *scope;
	scope++;
	while(scope != AssignedIdentifier.end() )
	{
		if(prev+1<*scope)
			return prev+1;
		prev = *scope;
		scope++;
	}

	return LowerBound-1;
}

	//METHOD IsAvailable
	//  Result: Status whether this array is available or not
bool ID::IsAvailable(void)
{
	long prev;
	set<long>::iterator work;

		//Empty check (Empty ID set is not bad, so result should be true.)
	if(AssignedIdentifier.size() == 0)
		return true;

		//Smallest ID should be equal to lower bound
	work = AssignedIdentifier.begin();
	if(*work != LowerBound)
		return false;

		//The array of IDs must not include any cracks
	prev = *work;
	work ++;
	while(work != AssignedIdentifier.end() )
	{
		if(*work != prev +1)
			return false;
		
		prev = *work;
		work++;
	}

	return true;
}


//---
// Degined and Programmed by S.D.F. in Oct,2000
