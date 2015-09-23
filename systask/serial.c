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
 *  @(#) $Id: serial.c,v 1.7 2001/11/12 13:23:22 hiro Exp $
 */

/*
 *	���ꥢ�륤�󥿥ե������ɥ饤��
 */

#include <jsp_services.h>
#include "kernel_id.h"

/*
 *  ���ꥢ�륤�󥿥ե������ɥ饤�Фε�ư
 */

static BOOL	in_inirtn = FALSE;	/* ������롼����¹���򼨤� */

void
serial_initialize(VP_INT portid)
{
	in_inirtn = TRUE;
	syscall(serial_open((ID) portid));
	in_inirtn = FALSE;
	syslog_1(LOG_NOTICE, "Serial driver service starts on port %d.",
							portid);
}

/*
 *  ���ꥢ��ݡ��ȴ����֥�å������
 */

#define	SERIAL_BUFSZ	256	/* ���ꥢ�륤�󥿥ե������ѥХåե��Υ����� */

#define	inc(x)		(((x)+1 < SERIAL_BUFSZ) ? (x)+1 : 0)
#define	INC(x)		((x) = inc(x))

typedef struct serial_port_control_block {
	BOOL	init_flag;	/* ������Ѥ��� */
	HWPORT	hwport;		/* �ϡ��ɥ�������¸���� */
	ID	in_semid;	/* �����Хåե������ѥ��ޥե��� ID */
	ID	out_semid;	/* �����Хåե������ѥ��ޥե��� ID */

	int	in_read_ptr;	/* �����Хåե��ɤ߽Ф��ݥ��� */
	int	in_write_ptr;	/* �����Хåե��񤭹��ߥݥ��� */
	int	out_read_ptr;	/* �����Хåե��ɤ߽Ф��ݥ��� */
	int	out_write_ptr;	/* �����Хåե��񤭹��ߥݥ��� */
	UINT	ioctl;		/* ioctl �ˤ���������� */
	BOOL	send_enabled;	/* �����򥤥͡��֥뤷�Ƥ��뤫�� */
	BOOL	ixon_stopped;	/* STOP �������ä����֤��� */
	BOOL	ixoff_stopped;	/* ���� STOP �����ä����֤��� */
	char	ixoff_send;	/* ���� START/STOP �����뤫�� */

	char	in_buffer[SERIAL_BUFSZ];	/* �����Хåե����ꥢ */
	char	out_buffer[SERIAL_BUFSZ];	/* �����Хåե����ꥢ */
} SPCB;

#define	IN_BUFFER_EMPTY(spcb) \
		((spcb)->in_read_ptr == (spcb)->in_write_ptr)
#define	IN_BUFFER_FULL(spcb) \
		((spcb)->in_read_ptr == inc((spcb)->in_write_ptr))
#define	OUT_BUFFER_FULL(spcb) \
		((spcb)->out_read_ptr == inc((spcb)->out_write_ptr))

/*
 *  �⥸�塼����ǻȤ��ؿ�
 */
static BOOL	serial_getc(SPCB *spcb, char *c);
static BOOL	serial_putc(SPCB *spcb, char c);

/*
 *  ���ꥢ��ݡ��ȴ����֥�å�������Ƚ����
 */

static SPCB spcb_table[NUM_PORT] = {
	{ 0, HWPORT1, SEM_SERIAL1_IN, SEM_SERIAL1_OUT },
#if NUM_PORT > 1
	{ 0, HWPORT2, SEM_SERIAL2_IN, SEM_SERIAL2_OUT },
#endif
};

#define get_spcb(portid)	(&(spcb_table[(portid)-1]))
#define get_spcb_def(portid)	get_spcb((portid) ? (portid) : CONSOLE_PORTID)

/*
 *  �ݡ��ȤΥ����ץ�
 *
 *  ʣ���Υ�������Ʊ���˸Ƥ־����ˤ��б����Ƥ��ʤ���
 */
ER
serial_open(ID portid)
{
	SPCB	*spcb;
	ER	ercd;

	if (!(1 <= portid && portid <= NUM_PORT)) {
		return(E_ID);
	}
	spcb = get_spcb(portid);

	if (spcb->init_flag) {		/* ������Ѥ��Υ����å� */
		return(E_OK);
	}

	/*
	 *  �ѿ��ν����
	 */
	spcb->in_read_ptr = spcb->in_write_ptr = 0;
	spcb->out_read_ptr = spcb->out_write_ptr = 0;
	spcb->ioctl = (IOCTL_ECHO | IOCTL_CRLF | IOCTL_CANONICAL
				| IOCTL_IXON | IOCTL_IXOFF);
	spcb->send_enabled = FALSE;
	spcb->ixon_stopped = spcb->ixoff_stopped = FALSE;
	spcb->ixoff_send = 0;

	/*
	 *  �ϡ��ɥ�������¸�ν����
	 */
	if (!in_inirtn) {
		syscall(loc_cpu());
	}
	if (hw_port_initialize(&(spcb->hwport))) {
		ercd = E_SYS;
	}
	else {
		spcb->init_flag = TRUE;
		ercd = E_OK;
	}
	if (!in_inirtn) {
		syscall(unl_cpu());
	}
	return(ercd);
}

/*
 *  �ݡ��ȤΥ�����
 *
 *  flush �� TRUE �ξ��ϡ����ꥢ��ݡ��Ȥؤ������Хåե������ˤʤ��
 *  ���Ԥġ�
 *  ʣ���Υ�������Ʊ���˸Ƥ־����ˤ��б����Ƥ��ʤ���
 */

#define	MAX_FLUSH_LOOP	1000000

ER
serial_close(ID portid, BOOL flush)
{
	SPCB	*spcb;
	int	i;

	if (!(1 <= portid && portid <= NUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}

	/*
	 *  �Хåե��Υե�å������
	 */
	if (flush) {
		for (i = 0; i < MAX_FLUSH_LOOP; i++) {
			if (spcb->out_write_ptr == spcb->out_read_ptr) {
				break;
			}
		}
	}

	/*
	 *  �ϡ��ɥ�������¸�Υ���åȥ��������
	 */
	syscall(loc_cpu());
	hw_port_terminate(&(spcb->hwport));
	syscall(unl_cpu());

	spcb->init_flag = FALSE;
	return(E_OK);
}

/*
 *  �ե�����ȥ���ط������
 */
#define	STOP	'\023'		/* ����ȥ���-S */
#define	START	'\021'		/* ����ȥ���-Q */

#define	IXOFF_STOP	64	/* STOP������Ĥ�Хåե����ꥢ */
#define	IXOFF_START	128	/* START������Ĥ�Хåե����ꥢ */

#define	in_buf_area(spcb)						\
		((spcb->in_read_ptr >= spcb->in_write_ptr) ?		\
		 (spcb->in_read_ptr - spcb->in_write_ptr) :		\
		 (spcb->in_read_ptr + SERIAL_BUFSZ - spcb->in_write_ptr))

/*
 *  �桼�ƥ���ƥ��롼����
 */

Inline BOOL
enable_send(SPCB *spcb, char c)
{
	if (!(spcb->send_enabled)) {
		hw_port_sendstart(&(spcb->hwport));
		spcb->send_enabled = TRUE;
		if (hw_port_putready(&(spcb->hwport))) {
			hw_port_putchar(&(spcb->hwport), c);
			return(TRUE);
		}
	}
	return(FALSE);
}

/*
 *  ���ꥢ��ݡ��Ȥ���μ���
 */

static BOOL
serial_getc(SPCB *spcb, char *c)
{
	BOOL	buffer_empty;

	syscall(loc_cpu());
	*c = spcb->in_buffer[spcb->in_read_ptr];
	INC(spcb->in_read_ptr);

	if (*c == '\r' && (spcb->ioctl & IOCTL_RAW) == 0) {
		*c = '\n';
	}

	if (spcb->ixoff_stopped && (in_buf_area(spcb) > IXOFF_START)) {
		if (!enable_send(spcb, START)) {
			spcb->ixoff_send = START;
		}
		spcb->ixoff_stopped = FALSE;
	}
	buffer_empty = IN_BUFFER_EMPTY(spcb);
	syscall(unl_cpu());
	return(buffer_empty);
}

ER_UINT
serial_read(ID portid, char *buf, UINT len)
{
	SPCB		*spcb;
	BOOL		buffer_empty;
	char		c;
	unsigned int	i;

	if (sns_dpn()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}
	if (len == 0) {
		return(len);
	}

	syscall(wai_sem(spcb->in_semid));
	buffer_empty = FALSE;
	for (i = 0; i < len; i++) {
		buffer_empty = serial_getc(spcb, &c);
		if ((spcb->ioctl & IOCTL_ECHO) != 0) {
			syscall(wai_sem(spcb->out_semid));
			if (!serial_putc(spcb, c)) {
				syscall(sig_sem(spcb->out_semid));
			}
		}
		*buf++ = c;
		if ((spcb->ioctl & IOCTL_RAW) != 0
				|| ((spcb->ioctl & IOCTL_CANONICAL) != 0
						&& c == '\n')) {
			len = i + 1;
			break;
		}
		if (buffer_empty && i < len - 1) {
			syscall(wai_sem(spcb->in_semid));
		}
	}
	if (!buffer_empty) {
		syscall(sig_sem(spcb->in_semid));
	}
	return(len);
}

/*
 *  ���ꥢ��ݡ��Ȥؤ�����
 */

static BOOL
serial_putc(SPCB *spcb, char c)
{
	BOOL	buffer_full;

	if (c == '\n' && (spcb->ioctl & IOCTL_CRLF) != 0) {
		if (serial_putc(spcb, '\r')) {
			syscall(wai_sem(spcb->out_semid));
		}
	}

	syscall(loc_cpu());
	if (!(spcb->ixon_stopped) && enable_send(spcb, c)) {
		buffer_full = FALSE;
	}
	else {
		spcb->out_buffer[spcb->out_write_ptr] = c;
		INC(spcb->out_write_ptr);
		buffer_full = OUT_BUFFER_FULL(spcb);
	}
	syscall(unl_cpu());
	return(buffer_full);
}

ER_UINT
serial_write(ID portid, char *buf, UINT len)
{
	SPCB		*spcb;
	BOOL		buffer_full;
	unsigned int	i;

	if (sns_dpn()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}

	syscall(wai_sem(spcb->out_semid));
	buffer_full = FALSE;
	for (i = 0; i < len; i++) {
		buffer_full = serial_putc(spcb, *buf++);
		if (buffer_full && i < len - 1) {
			syscall(wai_sem(spcb->out_semid));
		}
	}
	if (!buffer_full) {
		syscall(sig_sem(spcb->out_semid));
	}
	return(len);
}

/*
 *  ���ꥢ��ݡ��Ȥ�����
 */
ER
serial_ioctl(ID portid, UINT ioctl)
{
	SPCB	*spcb;

	if (sns_ctx()) {		/* ����ƥ����ȤΥ����å� */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_ID);		/* �ݡ����ֹ�Υ����å� */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* ������Ѥ��Υ����å� */
		return(E_OBJ);
	}

	spcb->ioctl = ioctl;
	return(E_OK);
}

/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼����
 */

void
serial_handler_in(ID portid)
{
	SPCB	*spcb;
	char	c;

	spcb = get_spcb(portid);
	if (hw_port_getready(&(spcb->hwport))) {
		c = hw_port_getchar(&(spcb->hwport));
		if ((spcb->ioctl & IOCTL_IXON) != 0 && c == STOP) {
			spcb->ixon_stopped = TRUE;
		}
		else if (((spcb->ioctl & IOCTL_IXON) != 0
					|| spcb->ixon_stopped)
				&& (c == START
					|| (spcb->ioctl & IOCTL_IXANY) != 0)) {
			spcb->ixon_stopped = FALSE;
			if (!(spcb->send_enabled)) {
				hw_port_sendstart(&(spcb->hwport));
				spcb->send_enabled = TRUE;
			}
		}
		else if (IN_BUFFER_FULL(spcb)) {
			/* �Хåե��ե�ξ�硤��������ʸ����ΤƤ롥*/
		}
		else {
			spcb->in_buffer[spcb->in_write_ptr] = c;
			if (spcb->in_read_ptr == spcb->in_write_ptr) {
				syscall(isig_sem(spcb->in_semid));
			}
			INC(spcb->in_write_ptr);

			if ((spcb->ioctl & IOCTL_IXOFF) != 0
					&& !(spcb->ixoff_stopped)
					&& (in_buf_area(spcb) < IXOFF_STOP)) {
				if (!enable_send(spcb, STOP)) {
					spcb->ixoff_send = STOP;
				}
				spcb->ixoff_stopped = TRUE;
			}
		}
	}
}

void
serial_handler_out(ID portid)
{
	SPCB	*spcb;

	spcb = get_spcb(portid);
	if (hw_port_putready(&(spcb->hwport))) {
		if (!spcb->send_enabled) {
			hw_port_sendstop(&(spcb->hwport));
		}
		else if (spcb->ixoff_send) {
			hw_port_putchar(&(spcb->hwport), spcb->ixoff_send);
			spcb->ixoff_send = 0;
		}
		else if (spcb->ixon_stopped
				|| spcb->out_read_ptr == spcb->out_write_ptr) {
			/* ������� */
			hw_port_sendstop(&(spcb->hwport));
			spcb->send_enabled = FALSE;
		}
		else {
			hw_port_putchar(&(spcb->hwport),
					spcb->out_buffer[spcb->out_read_ptr]);
			if (OUT_BUFFER_FULL(spcb)) {
				syscall(isig_sem(spcb->out_semid));
			}
			INC(spcb->out_read_ptr);
		}
	}
}

/*
 *  ����ߥϥ�ɥ�
 */

#ifdef SEPARATE_SIO_INT

void
serial_in_handler(void)
{
	hw_serial_handler_in();
}

void
serial_out_handler(void)
{
	hw_serial_handler_out();
}

#else /* SEPARATE_SIO_INT */

void
serial_handler(void)
{
	hw_serial_handler();
}

#endif /* SEPARATE_SIO_INT */
