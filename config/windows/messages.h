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
 *  @(#) $Id: messages.h,v 1.3 2002/04/10 11:20:09 takayuki Exp $
 */


/*
 * �ǥХ������ߥ�졼����󥵥ݡ��� ��å������Τ�����
 */

#ifndef __MESSAGES_H
#define __MESSAGES_H

#define MSG_TYP_DEVICE 0x40
#define MSG_TYP_REQUEST 0x80

	//���ζ��̤Υ�å�����
#define MSG_ACK 0
#define MSG_NAK 1

	//�ޥ͡����㤫��ǥХ����ؤΥ�å�����
#define MSG_DEVREP_INITIALIZE 0x82
#define MSG_DEVREP_KERNELSTART 0x83
#define MSG_DEVREP_READ 0x84
#define MSG_DEVREP_WRITE 0x85
#define MSG_DEVREP_FINALIZE 0x06
#define MSG_DEVREP_KERNELEXIT 0x07

	//�ǥХ�������ޥ͡�����ؤΥ�å�����
#define MSG_DEVREQ_ADD 0xc2
#define MSG_DEVREQ_DELETE 0xc3
#define MSG_DEVREQ_READ 0xc4
#define MSG_DEVREQ_WRITE 0xc5
#define MSG_DEVREQ_INTERRUPT 0xc6
#define MSG_DEVREQ_MAPPING 0xc7
#define MSG_DEVREQ_UNMAPPING 0xc8

	//�ޥ͡����㤫�饫���ͥ��
#define MSG_KERREP_INTERRUPT 0x86

	//�����ͥ뤫��ޥ͡������
#define MSG_KERREQ_KERNELSTART 0x82
#define MSG_KERREQ_KERNELEXIT 0x83
#define MSG_KERREQ_READ 0x84
#define MSG_KERREQ_WRITE 0x85

#endif