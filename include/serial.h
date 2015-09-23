/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: serial.h,v 1.3 2002/04/08 05:29:20 hiro Exp $
 */

/*
 *	���ꥢ�륤�󥿥ե������ɥ饤��
 */

#ifndef _SERIAL_H_
#define _SERIAL_H_

#include <itron.h>
#include "hw_serial.h"

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фε�ư
 *
 *  �����ͥ�˽�����롼����Ȥ�����Ͽ���뤳�Ȥ����ꤷ�Ƥ��롥exinf ��
 *  �ϡ���ư���������ꥢ��ݡ��Ȥ�ID�ֹ���Ϥ���
 */
extern void	serial_initialize(VP_INT portid);

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фγ���ߥϥ�ɥ�
 */
#ifdef SIO_INT_SEPARATE
extern void	serial_in_handler(void);
extern void	serial_out_handler(void);
#else /* SIO_INT_SEPARATE */
extern void	serial_handler(void);
#endif /* SIO_INT_SEPARATE */

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Ф�ư�������ѤΤ�������
 *
 *  �ʲ�������ϡ��ӥå���������¤�Ȥä��Ѥ��롥
 */
#define	IOCTL_NULL	0		/* ����ʤ� */
#define	IOCTL_ECHO	0x0001		/* ���Ϥ���ʸ���򥨥����Хå� */
#define	IOCTL_CRLF	0x0010		/* LF ����Ϥ���ݤ� CR ���ղ� */
#define	IOCTL_RAW	0x0100		/* 1ʸ��ñ�̤����� */
#define	IOCTL_CANONICAL	0x0200		/* LF �����ޤ����� */
#define	IOCTL_IXON	0x1000		/* ���Ϥ��Ф��� XON/XOFF ���� */
#define	IOCTL_IXANY	0x2000		/* �ɤΤ褦��ʸ���Ǥ���ϳ��� */
#define	IOCTL_IXOFF	0x4000		/* ���Ϥ��Ф��� XON/XOFF ���� */

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�ФΥ����ӥ�������
 */
extern ER	serial_open(ID portid);
extern ER	serial_close(ID portid, BOOL flush);
extern ER_UINT	serial_read(ID portid, char *buf, UINT len);
extern ER_UINT	serial_write(ID portid, char *buf, UINT len);
extern ER	serial_ioctl(ID portid, UINT ioctl);

#endif /* _SERIAL_H_ */
