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
 *  @(#) $Id: msg-e.h,v 1.2 2001/02/23 22:10:55 takayuki Exp $
 */

#ifndef __MESSAGE_H
#define __MESSAGE_H

#define MSG_INTERNAL			"Internal error"
#define MSG_OR					" or "

#define MSG_UNKNOWN				"Unknown error"

#define MSG_NULLAPIASSIGNMENT	"Assigning a Static API with NULL pointer"
#define MSG_NULLSERASSIGNMENT	"Assigning a Serializer with NULL pointer"
#define MSG_ILLEGALPRAMDESC		"Illegal parameter descriptor (Unterminated descriptor)"
#define MSG_SYNTAXERROR			"Parameter descriptor syntax error"
#define MSG_APINOTEXIST			"That static API does not exist"
#define MSG_FATALONAPI			"Fatal error occured during Static API processing"
#define MSG_VALIDATIONFAIL		"Fatal error occured during validation checking"
#define MSG_FATALONOUTPUT		"Fatal error occured during output"
#define MSG_VALIDATIONDEADLOCK	"Validation step comes to a deadlock"
#define MSG_COULDNOTOPEN		"Specified file could not open"
#define MSG_COULDNOTCREATE		"Specified file could not create"
#define MSG_ILLEGALTYPE			"Type of the parameter given is not match the specification"
#define MSG_TOOMANYPARAM		"Too many parameters"
#define MSG_TOOFEWPARAM 		"Too few parameters"
#define MSG_ALREADYEXISTED		"The object you specified has already existed"
#define MSG_ALREADYASSIGNED		"The ID is already assigned for the other object"
#define MSG_ILLEGALIDENTIFIER	"Illegal identifier specified"
#define MSG_NOTEXIST			"There is no object specified"
#define MSG_ILLEGALIDENTIFIER2	"\n  (discontinuance, negative value, out of range, and so on)"
#define MSG_NONNULLASSIGNED		"Non-NULL pointer specified as a buffer of the object"

#endif
