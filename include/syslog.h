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
 *  @(#) $Id: syslog.h,v 1.5 2001/10/08 01:46:03 hiro Exp $
 */

/*
 *	�����ƥ����ǽ
 *
 *  �����ƥ�������ӥ��ϡ������ƥ�Υ��������Ϥ��뤿��Υ����ӥ�
 *  �Ǥ��롥�����ͥ뤫��Υ�����ν��Ϥˤ��Ѥ��뤿�ᡤ�������Ԥ�����
 *  �ˤϤ��뤳�ȤϤʤ���
 *  ������ϡ������ͥ���Υ��Хåե��˽񤭹��फ�����٥��ʸ����
 *  �ϴؿ����Ѥ��ƽ��Ϥ��롥�ɤ����Ȥ����ϡ���ĥ�����ӥ���������ڤ�
 *  �����뤳�Ȥ��Ǥ��롥
 *  ���Хåե��ΰ褬�����Хե��������ˤϡ��Ť��������ä��ƾ�
 *  �񤭤��롥
 */

#ifndef _SYSLOG_H_
#define _SYSLOG_H_

#include <itron.h>

/*
 *  ������Υǡ�����¤
 */

#define TMAX_LOGINFO	6

typedef struct {
		UINT	logtype;		/* ������μ��� */
		SYSTIM	logtim;			/* ������ */
		VP_INT	loginfo[TMAX_LOGINFO];	/* ����¾�Υ����� */
	} SYSLOG;

/*
 *  ������ν����٤����
 */
#define LOG_EMERG	0		/* ����åȥ�������ͤ��륨�顼 */
#define LOG_ALERT	1
#define LOG_CRIT	2
#define LOG_ERR		3		/* �����ƥ२�顼 */
#define LOG_WARNING	4		/* �ٹ��å����� */
#define LOG_NOTICE	5
#define LOG_INFO	6
#define LOG_DEBUG	7		/* �ǥХå��ѥ�å����� */

/*
 *  ������ν����٤Υӥåȥޥåפ��뤿��Υޥ���
 */
#define LOG_MASK(prio)	(1 << (prio))
#define LOG_UPTO(prio)	((1 << ((prio) + 1)) - 1)

/*
 *  ������μ��̤����
 */
#define LOG_TYP_INTERRUPT	0x01	/* ����ߥϥ�ɥ� */
#define LOG_TYP_ISR		0x02	/* ����ߥ����ӥ��ϥ�ɥ� */
#define LOG_TYP_TIMERHDR	0x03	/* �����।�٥�ȥϥ�ɥ� */
#define LOG_TYP_CPUEXC		0x04	/* CPU�㳰�ϥ�ɥ� */
#define LOG_TYP_TSKEXC		0x05	/* �������㳰�����롼���� */
#define LOG_TYP_TSKSTAT		0x06	/* �����������Ѳ� */
#define LOG_TYP_DISPATCH	0x07	/* �ǥ����ѥå��� */
#define LOG_TYP_SVC		0x08	/* �����ӥ������� */
#define LOG_TYP_COMMENT		0x09	/* �����ȡ�ʸ����ΤߤΥ��� */
#define LOG_ENTER		0x00	/* ���������� */
#define LOG_LEAVE		0x80	/* �и�����λ */

/*
 *  ������ν���
 */
extern ER	syslog_write(UINT prio, SYSLOG *p_syslog);

/*
 *  ���Хåե�����Υ�������ɽФ�
 */
extern ER_UINT	syslog_read(SYSLOG *p_syslog);

/* 
 *  ���Ϥ��٤�������ν����٤�����
 */
extern ER	syslog_setmask(UINT logmask, UINT lowmask);

/*
 *  ���������Ϥ��뤿��Υޥ���
 *
 *  format ����Ӹ�³�ΰ����������������å������򡤽����� prio ��
 *  ������Ȥ��ƽ��Ϥ��뤿��Υޥ���arg1��argn �� VP_INT���˥���
 *  ���Ȥ��뤿�ᡤVP_INT���˷��Ѵ��Ǥ���Ǥ�դη��Ǥ褤��
 */

#define	syslog_0(prio, format)	_syslog_0(prio, format)

#define	syslog_1(prio, format, arg1) \
		_syslog_1(prio, format, (VP_INT)(arg1))

#define	syslog_2(prio, format, arg1, arg2) \
		_syslog_2(prio, format, (VP_INT)(arg1), (VP_INT)(arg2))

#define	syslog_3(prio, format, arg1, arg2, arg3) \
		_syslog_3(prio, format, (VP_INT)(arg1), (VP_INT)(arg2),	\
						(VP_INT)(arg3))

#define	syslog_4(prio, format, arg1, arg2, arg3, arg4) \
		_syslog_4(prio, format, (VP_INT)(arg1), (VP_INT)(arg2),	\
				(VP_INT)(arg3), (VP_INT)(arg4))

#define	syslog_5(prio, format, arg1, arg2, arg3, arg4, arg5) \
		_syslog_5(prio, format, (VP_INT)(arg1), (VP_INT)(arg2),	\
			(VP_INT)(arg3), (VP_INT)(arg4), (VP_INT)(arg5))

/*
 *  ���������Ϥ��뤿��Υ饤�֥��ؿ�
 */

Inline ER
_syslog_0(UINT prio, const char *format)
{
	SYSLOG	syslog;

	syslog.logtype = LOG_TYP_COMMENT;
	syslog.loginfo[0] = (VP_INT) format;
	return(syslog_write(prio, &syslog));
}

Inline ER
_syslog_1(UINT prio, const char *format, VP_INT arg1)
{
	SYSLOG	syslog;

	syslog.logtype = LOG_TYP_COMMENT;
	syslog.loginfo[0] = (VP_INT) format;
	syslog.loginfo[1] = arg1;
	return(syslog_write(prio, &syslog));
}

Inline ER
_syslog_2(UINT prio, const char *format, VP_INT arg1, VP_INT arg2)
{
	SYSLOG	syslog;

	syslog.logtype = LOG_TYP_COMMENT;
	syslog.loginfo[0] = (VP_INT) format;
	syslog.loginfo[1] = arg1;
	syslog.loginfo[2] = arg2;
	return(syslog_write(prio, &syslog));
}

Inline ER
_syslog_3(UINT prio, const char *format, VP_INT arg1,
				VP_INT arg2, VP_INT arg3)
{
	SYSLOG	syslog;

	syslog.logtype = LOG_TYP_COMMENT;
	syslog.loginfo[0] = (VP_INT) format;
	syslog.loginfo[1] = arg1;
	syslog.loginfo[2] = arg2;
	syslog.loginfo[3] = arg3;
	return(syslog_write(prio, &syslog));
}

Inline ER
_syslog_4(UINT prio, const char *format, VP_INT arg1, VP_INT arg2,
				VP_INT arg3, VP_INT arg4)
{
	SYSLOG	syslog;

	syslog.logtype = LOG_TYP_COMMENT;
	syslog.loginfo[0] = (VP_INT) format;
	syslog.loginfo[1] = arg1;
	syslog.loginfo[2] = arg2;
	syslog.loginfo[3] = arg3;
	syslog.loginfo[4] = arg4;
	return(syslog_write(prio, &syslog));
}

Inline ER
_syslog_5(UINT prio, const char *format, VP_INT arg1, VP_INT arg2,
				VP_INT arg3, VP_INT arg4, VP_INT arg5)
{
	SYSLOG	syslog;

	syslog.logtype = LOG_TYP_COMMENT;
	syslog.loginfo[0] = (VP_INT) format;
	syslog.loginfo[1] = arg1;
	syslog.loginfo[2] = arg2;
	syslog.loginfo[3] = arg3;
	syslog.loginfo[4] = arg4;
	syslog.loginfo[5] = arg5;
	return(syslog_write(prio, &syslog));
}

/*
 *  ���������Ϥ��뤿��Υ饤�֥��ؿ��ʲ��ѿ������ǡ�
 */
extern ER	syslog(UINT prio, const char *format, ...);

/* 
 *  ������Υե����ޥåȽ���
 */
extern void	syslog_printf(SYSLOG *p_syslog, void (*putc)(char));

#endif /* _SYSLOG_H_ */
