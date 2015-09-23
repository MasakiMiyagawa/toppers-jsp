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
 *  @(#) $Id: jsp_kernel.h,v 1.4 2002/03/26 08:19:38 hiro Exp $
 */

/*
 *	JSP�����ͥ� ɸ�।�󥯥롼�ɥե�����
 */

#ifndef _JSP_KERNEL_H_
#define _JSP_KERNEL_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#include "jsp_rename.h"

/*
 *  ���ץꥱ�������ȶ��̤Υ��󥯥롼�ɥե�����
 */
#include <jsp_stddef.h>
#include <kernel.h>

/*
 *  �����ƥ�������ӥ��Τ�������
 */
#ifndef _MACRO_ONLY
#include <syslog.h>
#endif /* _MACRO_ONLY */

/*
 *  �����ƥ��ץ��å��˰�¸�������
 */
#include "sys_config.h"
#include "cpu_config.h"

/*
 *  ���֥�������ID�κǾ��ͤ����
 */
#define	TMIN_TSKID	1	/* ������ID�κǾ��� */
#define	TMIN_SEMID	1	/* ���ޥե�ID�κǾ��� */
#define	TMIN_FLGID	1	/* �ե饰ID�κǾ��� */
#define	TMIN_DTQID	1	/* �ǡ������塼ID�κǾ��� */
#define	TMIN_MBXID	1	/* �᡼��ܥå���ID�κǾ��� */
#define	TMIN_MPFID	1	/* ����Ĺ����ס���ID�κǾ��� */
#define	TMIN_CYCID	1	/* �����ϥ�ɥ�ID�κǾ��� */

/*
 *  ͥ���٤��ʳ��������
 */
#define	TNUM_TPRI	(TMAX_TPRI - TMIN_TPRI + 1)
#define	TNUM_MPRI	(TMAX_MPRI - TMIN_MPRI + 1)

/*
 *  �����ͥ�����Ѥ���ޥ�������
 */
#define SYSCALL

/*
 *  �إå��ե����������ʤ��⥸�塼��δؿ������
 */
#ifndef _MACRO_ONLY

/*
 *  �����ƥ����ǽ�ν������syslog.c��
 */
extern void	syslog_initialize(void);

/*
 *  �����ƥ����ǽ�ν�λ������syslog.c��
 */
extern void	syslog_terminate(void);

/*
 *  �ƥ⥸�塼��ν������kernel_cfg.c��
 */
extern void	object_initialize(void);

/*
 *  ������롼����μ¹ԡ�kernel_cfg.c��
 */
extern void	call_inirtn(void);

/*
 *  ��ư��å�������ɽ����banner.c��
 */
extern void	print_banner(void);

/*
 *  �����ͥ�ν�λ������startup.c��
 */
extern void	kernel_exit(void);

#endif /* _MACRO_ONLY */
#endif /* _JSP_KERNEL_H_ */
