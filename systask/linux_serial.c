/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  $B>e5-Cx:n8"<T$O!$0J2<$N>r7o$rK~$?$9>l9g$K8B$j!$K\%=%U%H%&%'%"!JK\%=(B
 *  $B%U%H%&%'%"$r2~JQ$7$?$b$N$r4^$`!%0J2<F1$8!K$r;HMQ!&J#@=!&2~JQ!&:FG[(B
 *  $BI[!J0J2<!$MxMQ$H8F$V!K$9$k$3$H$rL5=~$G5vBz$9$k!%(B
 *  (1) $BK\%=%U%H%&%'%"$r%=!<%9%3!<%I$N7A$GMxMQ$9$k>l9g$K$O!$>e5-$NCx:n(B
 *      $B8"I=<(!$$3$NMxMQ>r7o$*$h$S2<5-$NL5J]>Z5,Dj$,!$$=$N$^$^$N7A$G%=!<(B
 *      $B%9%3!<%ICf$K4^$^$l$F$$$k$3$H!%(B
 *  (2) $BK\%=%U%H%&%'%"$r%P%$%J%j%3!<%I$N7A$^$?$O5!4o$KAH$_9~$s$@7A$GMx(B
 *      $BMQ$9$k>l9g$K$O!$<!$N$$$:$l$+$N>r7o$rK~$?$9$3$H!%(B
 *    (a) $BMxMQ$KH<$&%I%-%e%a%s%H!JMxMQ<T%^%K%e%"%k$J$I!K$K!$>e5-$NCx:n(B
 *        $B8"I=<(!$$3$NMxMQ>r7o$*$h$S2<5-$NL5J]>Z5,Dj$r7G:\$9$k$3$H!%(B
 *    (b) $BMxMQ$N7ABV$r!$JL$KDj$a$kJ}K!$K$h$C$F!$>e5-Cx:n8"<T$KJs9p$9$k(B
 *        $B$3$H!%(B
 *  (3) $BK\%=%U%H%&%'%"$NMxMQ$K$h$jD>@\E*$^$?$O4V@\E*$K@8$8$k$$$+$J$kB;(B
 *      $B32$+$i$b!$>e5-Cx:n8"<T$rLH@U$9$k$3$H!%(B
 * 
 *  $BK\%=%U%H%&%'%"$O!$L5J]>Z$GDs6!$5$l$F$$$k$b$N$G$"$k!%>e5-Cx:n8"<T$O!$(B
 *  $BK\%=%U%H%&%'%"$K4X$7$F!$$=$NE,MQ2DG=@-$b4^$a$F!$$$$+$J$kJ]>Z$b9T$o(B
 *  $B$J$$!%$^$?!$K\%=%U%H%&%'%"$NMxMQ$K$h$jD>@\E*$^$?$O4V@\E*$K@8$8$?$$(B
 *  $B$+$J$kB;32$K4X$7$F$b!$$=$N@UG$$rIi$o$J$$!%(B
 * 
 *  @(#) $Id: linux_serial.c,v 1.1 2000/11/14 16:27:57 honda Exp $
 */

#define _LINX_SERIAL_
#include <jsp_services.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux_sigio.h>
#include "kernel_id.h"
#include "sys_config.h"




/*
 *  $B%7%j%"%k%]!<%H$NDc%l%Y%kDj5A(B
 */

typedef struct hardware_serial_port_descripter {
	char   *path;		            /* UNIX $B>e$G$N%U%!%$%kL>(B */
	int	   fd;		                /* $B%U%!%$%k%G%#%9%/%j%W%?(B */
	struct termios	current_term;	/* $BC<Kv@)8f>pJs(B */
	struct termios	saved_term;    
} HWPORT;

#define NUM_PORT	1

#define RAWPORT1	{ 0 }

/*
 *  UNIX $B%l%Y%k$N%]!<%H=i4|2=(B/$B%7%c%C%H%@%&%s=hM}(B
 *
 *  $B8=:_$N<BAu$G$O!$C<Kv$r;H$&%1!<%9$7$+9M$($F$$$J$$!%K\Mh$O!$(Bopen $B$7(B
 *  $B$?$N$,C<Kv$+$I$&$+$G=hM}$rJQ$($k$Y$-!%(B
 */

Inline void
hw_port_initialize(HWPORT *p)
{
	if (p->path) {
		p->fd = open(p->path, O_RDWR|O_NDELAY);
	}
	else {
		p->fd = 0;			/* $BI8=`F~=PNO$r;H$&(B */
	}
	fcntl(p->fd, F_SETOWN, getpid());
	fcntl(p->fd, F_SETFL, FASYNC|FNDELAY);
    
    
    tcgetattr(p->fd, &(p->saved_term));
    
	p->current_term = p->saved_term;
    p->current_term.c_lflag &= ~(ECHO);
    p->current_term.c_lflag &= ~(ICANON);
    p->current_term.c_cc[VMIN] = 1;
    p->current_term.c_cc[VTIME] = 0;
    
    tcsetattr(p->fd, TCSAFLUSH, &(p->current_term));
}

Inline void
hw_port_terminate(HWPORT *p)
{
    tcsetattr(p->fd, TCSAFLUSH, &(p->saved_term));
	fcntl(p->fd, F_SETFL, 0);
	if (p->path) {
		close(p->fd);
	}
}


/*
 *  $B%7%j%"%k%$%s%?%U%'!<%9%I%i%$%PMQ$N(B SIGIO $BDLCN%$%Y%s%H%V%m%C%/(B
 */

static SIGIOEB	serial_sigioeb;


/*
 *  $B%7%j%"%k%]!<%H4IM}%V%m%C%/$NDj5A(B
 */

typedef struct ioctl_descripter {
	int	echo;
	int	input;
	int	newline;
	int	flowc;
} IOCTL;

#define	SERIAL_BUFSZ	256	/* $B%7%j%"%k%$%s%?%U%'!<%9MQ%P%C%U%!$N%5%$%:(B */

#define	inc(x)		(((x)+1 < SERIAL_BUFSZ) ? (x)+1 : 0)
#define	INC(x)		((x) = inc(x))


typedef struct serial_port_control_block {
	BOOL	init_flag;	/* $B=i4|2=:Q$+!)(B */
	HWPORT	hwport;		/* $B%O!<%I%&%'%"0MB8>pJs(B */
	ID	in_semid;	/* $B<u?.%P%C%U%!4IM}MQ%;%^%U%)$N(B ID */
	ID	out_semid;	/* $BAw?.%P%C%U%!4IM}MQ%;%^%U%)$N(B ID */

	int	in_read_ptr;	/* $B<u?.%P%C%U%!FI$_=P$7%]%$%s%?(B */
	int	in_write_ptr;	/* $B<u?.%P%C%U%!=q$-9~$_%]%$%s%?(B */
	int	out_read_ptr;	/* $BAw?.%P%C%U%!FI$_=P$7%]%$%s%?(B */
	int	out_write_ptr;	/* $BAw?.%P%C%U%!=q$-9~$_%]%$%s%?(B */
	UINT	ioctl;		/* ioctl $B$K$h$k@_DjFbMF(B */
	BOOL	send_enabled;	/* $BAw?.$r%$%M!<%V%k$7$F$"$k$+!)(B */
	BOOL	ixon_stopped;	/* STOP $B$r<u$1<h$C$?>uBV$+!)(B */
	BOOL	ixoff_stopped;	/* $BAj<j$K(B STOP $B$rAw$C$?>uBV$+!)(B */
	char	ixoff_send;	/* $BAj<j$K(B START/STOP $B$rAw$k$+!)(B */

	char	in_buffer[SERIAL_BUFSZ];	/* $B<u?.%P%C%U%!%(%j%"(B */
	char	out_buffer[SERIAL_BUFSZ];	/* $B<u?.%P%C%U%!%(%j%"(B */
} SPCB;


#define	IN_BUFFER_EMPTY(spcb) \
		((spcb)->in_read_ptr == (spcb)->in_write_ptr)
#define	IN_BUFFER_FULL(spcb) \
		((spcb)->in_read_ptr == inc((spcb)->in_write_ptr))
#define	OUT_BUFFER_FULL(spcb) \
		((spcb)->out_read_ptr == inc((spcb)->out_write_ptr))

/*
 *  $B%b%8%e!<%kFb$G;H$&4X?t(B
 */
static void	sigint_handler();
static BOOL	serial_getc(SPCB *spcb, char *c);
static BOOL	serial_putc(SPCB *spcb, char c);


/*
 *  $B%7%j%"%k%]!<%H4IM}%V%m%C%/$NDj5A$H=i4|2=(B
 */

SPCB spcb_table[NUM_PORT] = {
    {0, RAWPORT1, SEM_SERIAL1_IN, SEM_SERIAL1_OUT }
};

#define get_spcb(portid)	(&(spcb_table[(portid)-1]))
#define get_spcb_def(portid)	get_spcb((portid) ? (portid) : CONSOLE_PORTID)


/*
 *  $B%]!<%H$N=i4|2=(B
 */
int
serial_open(ID portid)
{

    SPCB	*spcb;
	ER	ercd = E_OK;;

	if (!(1 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);
	}
	spcb = get_spcb(portid);

	/*
	 *  $BJ#?t$N%?%9%/$,F1;~$K(B serial_open $B$r8F$V>u67$K$OBP1~$7$F$$(B
	 *  $B$J$$!%(B
	 */
	if (spcb->init_flag) {		/* $B=i4|2=:Q$+$N%A%'%C%/(B */
		return(E_OK);
	}

	/*
	 *  $BJQ?t$N=i4|2=(B
	 */
	spcb->in_read_ptr = spcb->in_write_ptr = 0;
	spcb->out_read_ptr = spcb->out_write_ptr = 0;
	spcb->ixon_stopped = spcb->ixoff_stopped = FALSE;
	spcb->ixoff_send = 0;

	/*
	 *  $B%O!<%I%&%'%"0MB8$N=i4|2=(B
	 */
	hw_port_initialize(&(spcb->hwport));
        
	/*
 	 *  $B%W%m%;%9$r=*N;$5$;$k%7%0%J%k$rJa$^$($k(B
         *  sigaction()$B$G=q$-D>$7$?J}$,$$$$$N$+(B?
	 */
	signal(SIGHUP, sigint_handler);
	signal(SIGINT, sigint_handler);
	signal(SIGTERM, sigint_handler);
        
    spcb->init_flag = TRUE;
	spcb->send_enabled = FALSE;
	return(ercd);
}

/*
 *  $B%]!<%H$N%7%c%C%H%@%&%s(B
 *
 *  flush $B$,(B TRUE $B$N>l9g$O!$%7%j%"%k%]!<%H$X$NAw?.%P%C%U%!$,6u$K$J$k$^(B
 *  $B$GBT$D!%(B
 */

#define	MAX_FLUSH_LOOP	1000000

int
serial_close(ID portid, int flush)
{
	SPCB	*spcb;
	int	i;

	if (!(1 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* $B%]!<%HHV9f$N%A%'%C%/(B */
	}

	spcb = get_spcb(portid);
	if (!(spcb->init_flag)) {	/* $B=i4|2=:Q$+$N%A%'%C%/(B */
		return(E_OBJ);
	}

	/*
	 *  $B%P%C%U%!$N%U%i%C%7%e=hM}(B
	 */
	if (flush) {
		for (i = 0; i < MAX_FLUSH_LOOP; i++) {
			if (spcb->out_write_ptr == spcb->out_read_ptr) {
				break;
			}
		}
	}

	/*
	 *  $B%O!<%I%&%'%"0MB8$N%7%c%C%H%@%&%s=hM}(B
	 */
	syscall(loc_cpu());
	hw_port_terminate(&(spcb->hwport));
	syscall(unl_cpu());

	spcb->init_flag = FALSE;
	return(E_OK);
}

/*
 *  $B%W%m%;%9$r=*N;$5$;$k%7%0%J%k$KBP$9$k%O%s%I%i(B
 */
void
sigint_handler()
{
	SPCB	*spcb;
	int	i;

	for (i = 1; i <= NUM_PORT; i++) {
		spcb = get_spcb(i);
		if (spcb->init_flag) {
			hw_port_terminate(&(spcb->hwport));
		}
	}
	exit(0);
}

/*
 *  $B%U%m!<%3%s%H%m!<%k4X78$NDj5A(B
 */
#define	STOP	'\023'		/* Control-S */
#define	START	'\021'		/* Control-Q */

#define	IXOFF_STOP	64	/* buffer area size to send STOP */
#define	IXOFF_START	128	/* buffer area size to send START */

#define	in_buf_area(p)							\
		((spcb->in_read_ptr >= spcb->in_write_ptr) ?		\
		 (spcb->in_read_ptr - spcb->in_write_ptr) :		\
		 (spcb->in_read_ptr + SERIAL_BUFSZ - spcb->in_write_ptr))
/*
 *  $B%f!<%F%#%j%F%#%k!<%A%s(B
 */

Inline BOOL
read_char(SPCB *spcb, char *c)
{
	int	n;

	if ((n = read(spcb->hwport.fd, c, 1)) == 1) {
		return(1);
	}
	assert(n < 0 && errno == EWOULDBLOCK);
	return(0);
}

Inline BOOL
write_char(SPCB *spcb, char c)
{
	int	n;

	if ((n = write(spcb->hwport.fd, &c, 1)) == 1) {
		return(1);
	}
	assert(n < 0 && errno == EWOULDBLOCK);
	return(0);
}

/*
 *  $B%7%j%"%k%]!<%H$+$i$N<u?.(B
 */

static BOOL
serial_getc(SPCB *spcb, char *c)
{
	BOOL	buffer_empty;

	syscall(loc_cpu());
	*c = spcb->in_buffer[spcb->in_read_ptr];
        if (inc(spcb->in_write_ptr) == spcb->in_read_ptr) {
            /*
             *  $B%P%C%U%!%U%k>uBV$,2r=|$5$l$?$i!"3d$j9~$_$,F~$C$?$N$H(B
             *  $BF1$8?6$kIq$$$r$5$;$k!#(B
             */
            kill(getpid(), SIGIO);
        }
        
	INC(spcb->in_read_ptr);

    if (*c == '\r' && (spcb->ioctl & IOCTL_RAW) == 0) {
		*c = '\n';
	}

	if (spcb->ixoff_stopped && (in_buf_area(spcb) > IXOFF_START)) {
		if (!write_char(spcb, START)) {
			spcb->ixoff_send = START;
		}
		spcb->ixoff_stopped = FALSE;
	}
	buffer_empty = IN_BUFFER_EMPTY(spcb);
	syscall(unl_cpu());
	return(buffer_empty);
}

int
serial_read(int portid, char *buf, unsigned int len)
{
    	SPCB	*spcb;
	BOOL	buffer_empty;
	char	c;
	int	i;


	if (sns_dpn()) {		/* $B%3%s%F%-%9%H$N%A%'%C%/(B */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* $B%]!<%HHV9f$N%A%'%C%/(B */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* $B=i4|2=:Q$+$N%A%'%C%/(B */
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
 * $B%7%j%"%k%]!<%H$X$NAw?.(B
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
	if (!(spcb->ixon_stopped) && write_char(spcb, c)) {
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
serial_write(ID portid, char *buf, unsigned int len)
{
	SPCB	*spcb;
	BOOL	buffer_full;
	int	i;

	if (sns_dpn()) {		/* $B%3%s%F%-%9%H$N%A%'%C%/(B */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* $B%]!<%HHV9f$N%A%'%C%/(B */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* $B=i4|2=:Q$+$N%A%'%C%/(B */
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
 *  $B%7%j%"%k%]!<%H$N@)8f(B
 */

int
serial_ioctl(ID portid, UINT ioctl)
{
	SPCB	*spcb;

	if (sns_ctx()) {		/* $B%3%s%F%-%9%H$N%A%'%C%/(B */
		return(E_CTX);
	}
	if (!(0 <= portid && portid <= NUM_PORT)) {
		return(E_PAR);		/* $B%]!<%HHV9f$N%A%'%C%/(B */
	}

	spcb = get_spcb_def(portid);
	if (!(spcb->init_flag)) {	/* $B=i4|2=:Q$+$N%A%'%C%/(B */
		return(E_OBJ);
	}

    spcb->ioctl = ioctl;
    return(E_OK);
}


/*
 *  $B%7%j%"%k%]!<%H3d9~$_%O%s%I%i(B
 */

static BOOL
serial_int_handler(ID portid)
{
	SPCB	*spcb;
	BOOL	flag;
	char	c;

	spcb = get_spcb(portid);
	flag = 0;

	/*
	 *  1$BJ8;z<u?.=hM}(B
	 *
	 *  $B$^$:!$%P%C%U%!%U%k$G$J$$>l9g$K!$(B1$BJ8;zFI$s$G$_$k!%FI$a$l$P!$(B
	 *  $B$=$l$K1~$8$?=hM}$r9T$&!%(B
	 */
	if (inc(spcb->in_write_ptr) != spcb->in_read_ptr
            && read_char(spcb, &c)) {
		if ((spcb->ioctl & IOCTL_IXON) != 0 && c == STOP) {
			spcb->ixon_stopped = TRUE;
		}
        else if (((spcb->ioctl & IOCTL_IXON) != 0 || spcb->ixon_stopped)
                                 && (c == START || (spcb->ioctl & IOCTL_IXANY) != 0)) {
			spcb->ixon_stopped = FALSE;
		}
		else {
			spcb->in_buffer[spcb->in_write_ptr] = c;
                        if(spcb->in_read_ptr == spcb->in_write_ptr){
                            syscall(sig_sem(spcb->in_semid));
                        }
                        
			INC(spcb->in_write_ptr);
                        
			if ((spcb->ioctl & IOCTL_IXOFF) != 0 && !(spcb->ixoff_stopped)
					&& (in_buf_area(p) < IXOFF_STOP)) {
				spcb->ixoff_stopped = TRUE;
				spcb->ixoff_send = STOP;
			}
		}
		flag = 1;
	}

	/*
	 *  1$BJ8;zAw?.=hM}(B
	 */
	if (spcb->ixoff_send) {
		if (write_char(spcb, spcb->ixoff_send)) {
			spcb->ixoff_send = 0;
			flag = 1;
		}
	}
	else if (!(spcb->ixon_stopped)
                      && spcb->out_read_ptr != spcb->out_write_ptr) {
		if (write_char(spcb, spcb->out_buffer[spcb->out_read_ptr])) {
                    if(OUT_BUFFER_FULL(spcb)){
			syscall(isig_sem(spcb->out_semid));
                    }
                    INC(spcb->out_read_ptr);                        
                    flag = 1;
		}
	}
	return(flag);
}



/*
 *  SIGIO $B%3!<%k%P%C%/%k!<%A%s(B
 */

static BOOL
serial_sigio_callback(VP arg)
{
	BOOL	flag;

	do {
		syscall(loc_cpu());
		flag = serial_int_handler(1);
		syscall(unl_cpu());
	} while (flag);
	return(0);
}



/*
 *  $B%7%j%"%k%$%s%?%U%'!<%9%I%i%$%P$N5/F0(B
 */

void
serial_initialize(VP_INT portid)
{

	syscall(serial_open((ID) portid));

	serial_sigioeb.callback = serial_sigio_callback;
	serial_sigioeb.arg = (VP) 0;
	syscall(enqueue_sigioeb_initialize(&serial_sigioeb));
	syslog(LOG_NOTICE, "Serial driver service starts on port %d.\r",
		 portid);
}






