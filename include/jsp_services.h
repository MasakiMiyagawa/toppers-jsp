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
 *  @(#) $Id: jsp_services.h,v 1.2 2001/09/11 03:52:27 hiro Exp $
 */

/*
 *	���ץꥱ��������� ɸ�।�󥯥롼�ɥե�����
 *
 *  JSP�����ͥ���ư���ץ���बɸ��Ū�˥��󥯥롼�ɤ��٤��ե�
 *  ���롥ɸ��Ū�ʥ����ƥॵ���ӥ���Ȥ�����Υ��󥯥롼�ɥե�������
 *  �ࡥ
 */

#ifndef _JSP_SERVICES_H_
#define _JSP_SERVICES_H_

/*
 *  JSP�����ͥ��ƤӽФ������ɬ�פʥ��󥯥롼�ɥե�����
 */
#include <jsp_stddef.h>
#include <kernel.h>

/*
 *  �����ͥ�ν�λ����
 */
extern void	kernel_exit(void);

/*
 *  ���ꥢ�륤�󥿥ե������⥸�塼��
 */
#include <serial.h>

/*
 *  �����ƥ�������ӥ�
 */
#include <syslog.h>

/*
 *  syscall�ޥ���_syscall �ޥ�������
 */

extern void	jsp_perror(const char *file, int line,
				const char *expr, ER ercd);
extern void	jsp_panic(const char *file, int line,
				const char *expr, ER ercd);

Inline ER
_jsp_perror(const char *file, int line, const char *expr, ER ercd)
{
	if (MERCD(ercd) < 0) {
		jsp_perror(file, line, expr, ercd);
	}
	return(ercd);
}

Inline ER
_jsp_panic(const char *file, int line, const char *expr, ER ercd)
{
	if (MERCD(ercd) < 0) {
		jsp_panic(file, line, expr, ercd);
	}
	return(ercd);
}

#define	syscall(s)	_jsp_perror(__FILE__, __LINE__, #s, (s));
#define	_syscall(s)	_jsp_panic(__FILE__, __LINE__, #s, (s));

#endif /* _JSP_SERVICES_H_ */
