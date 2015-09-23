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
 *  @(#) $Id: syslog.c,v 1.1 2000/11/14 14:44:25 hiro Exp $
 */

/*
 *  �����ƥ�������ӥ�
 */

#include "../kernel/jsp_kernel.h"
#include <jsp_services.h>

/*
 *  �����ƥ���ѤΥ�󥰥Хåե��Ȥ���˥����������뤿��Υݥ���
 */

#define	SYSLOG_BUFSZ	1024

static char	syslog_buffer[SYSLOG_BUFSZ];
static int	syslog_write_ptr;
static int	syslog_read_ptr;
static int	syslog_mode;
static int	syslog_mask;

/*
 *  �����ƥ�������ӥ��ν����
 */
void
syslog_initialize()
{
	syslog_write_ptr = syslog_read_ptr = 0;
	syslog_mode = 0;
	syslog_mask = LOG_UPTO(LOG_NOTICE);
}     

/*
 *  �����ƥ���ؤ�1ʸ������
 */
static void
syslog_putc(char c)
{
	switch (syslog_mode) {
	default:
		sys_putc(c);
		break;
	case 1:
		syslog_buffer[syslog_write_ptr] = c;
		if (++syslog_write_ptr >= SYSLOG_BUFSZ) {
			syslog_write_ptr = 0;
		}
		if (syslog_read_ptr == syslog_write_ptr) {
			if (++syslog_read_ptr >= SYSLOG_BUFSZ) {
				syslog_read_ptr = 0;
			}
		}
		break;
	}
}

/*
 *  �����ƥ�������Ѵʰ��� vprintf�饤�֥��
 *
 *  LONG_TYPE ���������Ƥ���ȡ�"l" �λ���� LONG_TYPE ��������줿
 *  ���ǿ��ͤ���Ф���LONGLONG_TYPE ���������Ƥ���ȡ�"ll" �λ���� 
 *  LONGLONG_TYPE ��������줿���ǿ��ͤ���Ф���
 */

/*
 *  �����٤��Ǥ�Ĺ���������� LONGEST������դ��ˤ� ULONGEST�����̵����
 *  �˷�������롥
 */
#ifdef LONGLONG_TYPE
typedef LONGLONG_TYPE		LONGEST;
typedef unsigned LONGLONG_TYPE	ULONGEST;
#else /* LONGLONG_TYPE */
#ifdef LONG_TYPE
typedef LONG_TYPE		LONGEST;
typedef unsigned LONG_TYPE	ULONGEST;
#else /* LONG_TYPE */
typedef int			LONGEST;
typedef unsigned int		ULONGEST;
#endif /* LONG_TYPE */
#endif /* LONGLONG_TYPE */

/*
 *  ���ͤ�ʸ������Ѵ�
 */
static void
convert(ULONGEST val, int radix, const char *radchar,
		int width, int minus, int padzero)
{
	char	buf[24];
	int	i, j;

	i = 0;
	do {
		buf[i++] = radchar[val % radix];
		val /= radix;
	} while (val != 0);
	if (minus) {
		buf[i++] = '-';
	}

	for (j = i; j < width; j++) {
		syslog_putc((char)(padzero ? '0' : ' '));
	}
	while (i > 0) {
		syslog_putc(buf[--i]);
	}
}

static char const raddec[] = "0123456789";
static char const radhex[] = "0123456789abcdef";
static char const radHEX[] = "0123456789ABCDEF";

/*
 *  ��������Ф�����Υޥ���
 */
#ifdef LONGLONG_TYPE
#ifdef LONG_TYPE
#define GET_ARG	((longflag > 1) ? va_arg(ap, LONGLONG_TYPE) \
			(longflag ? va_arg(ap, LONG_TYPE) : va_arg(ap, int)))
#else /* LONG_TYPE */
#define GET_ARG	((longflag > 1) ? va_arg(ap, LONGLONG_TYPE) : va_arg(ap, int))
#endif /* LONG_TYPE */
#else /* LONGLONG_TYPE */
#ifdef LONG_TYPE
#define GET_ARG	(longflag ? va_arg(ap, LONG_TYPE) : va_arg(ap, int))
#else /* LONG_TYPE */
#define GET_ARG	(va_arg(ap, int))
#endif /* LONG_TYPE */
#endif /* LONGLONG_TYPE */

/*
 *  �����ƥ���ؤ� vprintf
 */
static void
syslog_vprintf(const char *format, va_list ap)
{
	int	c;
	LONGEST	val;
	int	width;
	int	padzero;
	int	longflag;
	char	*str;

	while ((c = *format++) != '\0') {
		if (c != '%') {
			syslog_putc((char) c);
			continue;
		}

		width = padzero = longflag = 0;

		if ((c = *format++) == '0') {
			padzero = 1;
			c = *format++;
		}
		while ('0' <= c && c <= '9') {
			width = width*10 + c - '0';
			c = *format++;
		}
		while (c == 'l') {
			longflag++;
			c = *format++;
		}
		switch (c) {
		case 'd':
			val = GET_ARG;
			if (val >= 0) {
				convert(val, 10, raddec, width, 0, padzero);
			}
			else {
				convert(-val, 10, raddec, width, 1, padzero);
			}
			break;
		case 'u':
			val = GET_ARG;
			convert(val, 10, raddec, width, 0, padzero);
			break;
		case 'x':
			val = GET_ARG;
			convert(val, 16, radhex, width, 0, padzero);
			break;
		case 'X':
			val = GET_ARG;
			convert(val, 16, radHEX, width, 0, padzero);
			break;
		case 'c':
			syslog_putc((char) va_arg(ap, int));
			break;
		case 's':
			str = va_arg(ap, char *);
			while ((c = *str++) != '\0') {
				syslog_putc((char) c);
			}
			break;
		case '%':
			syslog_putc('%');
			break;
		case 0:
			format--;
			break;
		default:
			break;
		}
	}
}

/* 
 *  �����ƥ�����ϴؿ�
 *
 *  �����ͥ��⤫���ƤӽФ���뤿�ᡤCPU��å����֤����ˤϡ�������
 *  ���ѤΥ롼������Ѥ��Ƥ��롥
 */
void
syslog(int priority, const char *format, ...)
{
	va_list	ap;

	if (syslog_mask & LOG_MASK(priority)) {
		/*
		 *  LOG_EMERG �ǸƤӽФ��줿��硤����������٥�ν�
		 *  �ϥ롼������ڤ��ؤ��롥
		 */
		if (priority == LOG_EMERG) {
			syslog_mode = 0;
		}

		/*
		 *  CPU��å����֤�¹ԥ���ƥ����Ȥˤ�餺ư��Ǥ���
		 *  �褦�ˤ��롥
		 */
		va_start(ap, format);
		if (sense_lock()) {
			syslog_vprintf(format, ap);
			syslog_putc('\n');
		}
		else if (sense_context()) {
			i_lock_cpu();
			syslog_vprintf(format, ap);
			syslog_putc('\n');
			i_unlock_cpu();
		}
		else {
			t_lock_cpu();
			syslog_vprintf(format, ap);
			syslog_putc('\n');
			t_unlock_cpu();
		}
		va_end(ap);
	}
}

/* 
 *  ���ޥ���������
 */
int
setlogmask(int maskpri)
{
	int	old_maskpri;

	old_maskpri = syslog_mask;
	syslog_mask = maskpri;
	return(old_maskpri);
}

/*
 *  ��󥰥Хåե�������ɤ߽Ф�
 */
int
syslog_read()
{
	int	c;

	if (sns_ctx() || sns_loc()) {
		return(-1);
	}

	loc_cpu();
	if (syslog_read_ptr == syslog_write_ptr) {
		c = -1;
	}
	else {
		c = (unsigned char) syslog_buffer[syslog_read_ptr];
		if (++syslog_read_ptr >= SYSLOG_BUFSZ) {
			syslog_read_ptr = 0;
		}
	}
	unl_cpu();
	return(c);
}

/* 
 *  ���⡼�ɤ��ѹ�
 */
int
setlogmode(int mode)
{
	int	old_mode;

	old_mode = syslog_mode;
	syslog_mode = mode;
	return(old_mode);
}
