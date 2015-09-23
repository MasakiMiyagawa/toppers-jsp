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
 *  @(#) $Id: msg-j.h,v 1.2 2001/03/24 08:22:56 takayuki Exp $
 */

#ifndef __MESSAGE_H
#define __MESSAGE_H

#define MSG_INTERNAL			"�������顼"
#define MSG_OR					" �⤷���� "

#define MSG_NULLAPIASSIGNMENT	"NULL����ŪAPI����Ͽ����褦�Ȥ��ޤ���"
#define MSG_NULLSERASSIGNMENT	"NULL�Υ��ꥢ�饤������Ͽ����褦�Ȥ��ޤ���"

#define MSG_UNKNOWN				"���������Υ��顼"

#define MSG_ILLEGALPRAMDESC		"�������ʥѥ�᡼������Ҥλ���"
#define MSG_SYNTAXERROR			"�ѥ�᡼������Ҥ�ʸˡ���Ǥ�"
#define MSG_COULDNOTOPEN		"�ե����뤬�����ޤ���Ǥ���"
#define MSG_FATALONAPI			"��ŪAPI�ν�������̿Ū�ʥ��顼��ȯ�����ޤ���"
#define MSG_FATALONOUTPUT		"���Ͻ�����˥��顼��ȯ�����ޤ���"
#define MSG_APINOTEXIST			"������ŪAPI�Ϥ���ޤ���"
#define MSG_VALIDATIONFAIL		"������Ƚ��Ǽ��Ԥ��ޤ���"
#define MSG_VALIDATIONDEADLOCK	"������Ƚ�꤬�ǥåɥ�å��򵯤����ޤ���"
#define MSG_COULDNOTCREATE		"�ե����뤬���ޤ���Ǥ���"
#define MSG_ILLEGALTYPE			"�ѥ�᡼���η����ۤʤ�ޤ�"
#define MSG_TOOMANYPARAM		"�ѥ�᡼���ο���¿�����ޤ�"
#define MSG_TOOFEWPARAM 		"�ѥ�᡼���ο������ʤ����ޤ�"
#define MSG_ALREADYEXISTED		"���Υ��֥������ȤϤ��Ǥ�¸�ߤ��Ƥ��ޤ�"
#define MSG_ALREADYASSIGNED		"����ID�ͤϤ��Ǥ˳�����Ƥ��Ƥ��ޤ�"
#define MSG_ILLEGALIDENTIFIER	"���֥������Ȥμ��̻Ҥ������Ǥ�"
#define MSG_NOTEXIST			"���֥������Ȥ�¸�ߤ��ޤ���"
#define MSG_ILLEGALIDENTIFIER2	"\n  (��Ϣ³�����͡��ϰϳ��ʤɤʤ�)"
#define MSG_NONNULLASSIGNED		"���֥������ȤΥХåե���NULL�ʳ����ͤ����ꤵ��ޤ���"
#define MSG_UNKNOWNOPTION		"�����ʥ��ץ����[%s]�����ꤵ��Ƥ��ޤ�"
#define MSG_ALREADYGIVENSRCFILE	"�������ե�����̾�Ϥ��Ǥ�Ϳ�����Ƥ���"
#endif
