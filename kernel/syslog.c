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
 *  @(#) $Id: syslog.c,v 1.5 2002/03/26 08:19:38 hiro Exp $
 */

/*
 *  �����ƥ����ǽ
 */

#include "jsp_kernel.h"
#include "time_event.h"

/*
 *  ���Хåե��Ȥ���˥����������뤿��Υݥ���
 */

#define TCNT_SYSLOG_BUFFER	32

static SYSLOG	syslog_buffer[TCNT_SYSLOG_BUFFER];
static UINT	syslog_count;
static UINT	syslog_head;
static UINT	syslog_tail;
static UINT	syslog_lost;

/*
 *  ���Ϥ��٤�������ν����١ʥӥåȥޥåס�
 */
static UINT	syslog_logmask;		/* ��Ͽ�����Ϥ��٤������� */
static UINT	syslog_lowmask;		/* ���٥���Ϥ��٤������� */

/*
 *  ����ƥ����Ȥ˰ͤ�ʤ�CPU��å�����å����
 */
#define	lock_cpu()	(sense_context() ? i_lock_cpu() : t_lock_cpu())
#define	unlock_cpu()	(sense_context() ? i_unlock_cpu() : t_unlock_cpu())

/*
 *  �����ƥ����ǽ�ν����
 */
void
syslog_initialize()
{
	syslog_count = 0;
	syslog_head = syslog_tail = 0;
	syslog_lost = 0;

	syslog_logmask = LOG_UPTO(LOG_NOTICE);
	syslog_lowmask = LOG_UPTO(LOG_NOTICE);
}     

/* 
 *  ������ν���
 */
ER
syslog_write(UINT prio, SYSLOG *p_syslog)
{
	BOOL	locked;

	p_syslog->logtim = systim_offset + current_time;
	if ((syslog_logmask & LOG_MASK(prio)) != 0) {
		/*
		 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���
		 *  �褦�ˤ��롥
		 */
		locked = sense_lock();
		if (!locked) {
			lock_cpu();
		}
		if ((syslog_lowmask & LOG_MASK(prio)) != 0) {
			/*
			 *  ���٥���Ϥؤν�Ф�
			 */
			syslog_printf(p_syslog, sys_putc);
			sys_putc('\n');
		}
		else {
			/*
			 *  ���Хåե��ؤν����
			 */
			syslog_buffer[syslog_tail] = *p_syslog;
			syslog_tail++;
			if (syslog_tail >= TCNT_SYSLOG_BUFFER) {
				syslog_tail = 0;
			}
			if (syslog_count < TCNT_SYSLOG_BUFFER) {
				syslog_count++;
			}
			else {
				syslog_head = syslog_tail;
				syslog_lost++;
			}
		}
		if (!locked) {
			unlock_cpu();
		}
	}
	return(E_OK);
}

/*
 *  ���Хåե�������ɽФ�
 */
ER_UINT
syslog_read(SYSLOG *p_syslog)
{
	BOOL	locked;
	INT	n;

	/*
	 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���褦�ˤ�
	 *  �롥
	 */
	locked = sense_lock();
	if (!locked) {
		lock_cpu();
	}
	if (syslog_count > 0) {
		*p_syslog = syslog_buffer[syslog_head];
		syslog_count--;
		syslog_head++;
		if (syslog_head >= TCNT_SYSLOG_BUFFER) {
			syslog_head = 0;
		}
		n = syslog_lost;
		syslog_lost = 0;
	}
	else {
		n = E_OBJ;
	}
	if (!locked) {
		unlock_cpu();
	}
	return(n);
}

/* 
 *  ���Ϥ��٤�������ν����٤�����
 */
ER
syslog_setmask(UINT logmask, UINT lowmask)
{
	syslog_logmask = logmask;
	syslog_lowmask = lowmask;
	return(E_OK);
}

/* 
 *  �����ƥ����ǽ�ν�λ����
 *
 *  ���Хåե��˵�Ͽ���줿����������٥���ϵ�ǽ���Ѥ��ƽ��Ϥ�
 *  �롥
 */
void
syslog_terminate()
{
	SYSLOG	syslog, lostlog;
	char	*bufmsg = "-- buffered messages --";
	char	*lostmsg = "%d messages are lost.";
	INT	n;

	lostlog.loginfo[0] = (VP_INT) bufmsg;
	syslog_printf(&lostlog, sys_putc);
	sys_putc('\n');
	while ((n = syslog_read(&syslog)) >= 0) {
		if (n > 0) {
			lostlog.loginfo[0] = (VP_INT) lostmsg;
			lostlog.loginfo[1] = (VP_INT) n;
			syslog_printf(&lostlog, sys_putc);
			sys_putc('\n');
		}
		syslog_printf(&syslog, sys_putc);
		sys_putc('\n');
	}
	sys_putc('\n');
}

/*
 *  ���ͤ�ʸ������Ѵ�
 */
static void
convert(unsigned int val, int radix, const char *radchar, int width,
		int minus, int padzero, void (*putc)(char))
{
	char	buf[12];
	int	i, j;

	i = 0;
	do {
		buf[i++] = radchar[val % radix];
		val /= radix;
	} while (val != 0);

	width -= minus;
	if (minus > 0 && padzero > 0) {
		(*putc)('-');
	}
	for (j = i; j < width; j++) {
		(*putc)((char)(padzero > 0 ? '0' : ' '));
	}
	if (minus > 0 && padzero <= 0) {
		(*putc)('-');
	}
	while (i > 0) {
		(*putc)(buf[--i]);
	}
}

/*
 *  ������ե����ޥå��ѥ饤�֥��ؿ�
 */
static char const raddec[] = "0123456789";
static char const radhex[] = "0123456789abcdef";
static char const radHEX[] = "0123456789ABCDEF";

void
syslog_printf(SYSLOG *p_syslog, void (*putc)(char))
{
	char	*format;
	int	argno;
	int	c;
	int	width;
	int	padzero;
	int	val;
	char	*str;

	format = (char *)(p_syslog->loginfo[0]);
	argno = 1;

	while ((c = *format++) != '\0') {
		if (c != '%') {
			(*putc)((char) c);
			continue;
		}

		width = padzero = 0;
		if ((c = *format++) == '0') {
			padzero = 1;
			c = *format++;
		}
		while ('0' <= c && c <= '9') {
			width = width*10 + c - '0';
			c = *format++;
		}
		switch (c) {
		case 'd':
			val = (int)(p_syslog->loginfo[argno++]);
			if (val >= 0) {
				convert(val, 10, raddec, width,
						0, padzero, putc);
			}
			else {
				convert(-val, 10, raddec, width,
						1, padzero, putc);
			}
			break;
		case 'u':
			val = (int)(p_syslog->loginfo[argno++]);
			convert(val, 10, raddec, width, 0, padzero, putc);
			break;
		case 'x':
			val = (int)(p_syslog->loginfo[argno++]);
			convert(val, 16, radhex, width, 0, padzero, putc);
			break;
		case 'X':
			val = (int)(p_syslog->loginfo[argno++]);
			convert(val, 16, radHEX, width, 0, padzero, putc);
			break;
		case 'c':
			(*putc)((char)(int)(p_syslog->loginfo[argno++]));
			break;
		case 's':
			str = (char *)(p_syslog->loginfo[argno++]);
			while ((c = *str++) != '\0') {
				(*putc)((char) c);
			}
			break;
		case '%':
			(*putc)('%');
			break;
		case '\0':
			format--;
			break;
		default:
			break;
		}
	}
}
