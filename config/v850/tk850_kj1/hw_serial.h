/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  Copyright (C) 2005 by Freelines CO.,Ltd
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: hw_serial.h,v 1.2 2005/12/12 09:08:16 honda Exp $
 */

/*
 * �������åȰ�¸���ꥢ��I/O�⥸�塼���V850/KJ1+ ��¢��Ʊ�����ꥢ��ch0/ch1�ѡ�
 *   �ܡ��졼�������SERIAL_COMPAREVALUE���ѹ����롣
 *   �ǡ����ե����ޥåȤ�8bit data, non-parity, 1stop-bit����
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include <s_services.h>

/*
 *  ���ꥢ��ݡ��Ȥν�����֥��å�
 */

typedef struct sio_port_initialization_block {
} SIOPINIB;

/*
 *  ���ꥢ��ݡ��Ȥ�����֥��å�
 */
typedef struct sio_port_control_block {
	const SIOPINIB	*inib;		/* ������֥��å�	*/
	VP_INT		exinf;		/* ��ĥ����		*/
	BOOL		openflag;	/* �����ץ�Ѥߥե饰	*/
	int			port_id;	/* �ݡ����ֹ�(0��) */
} SIOPCB;

extern SIOPCB siopcb_table[TNUM_PORT];

/*
 *  SIO ID ��������֥��å��ؤ��Ѵ��ޥ���
 */

#define INDEX_SIO(sioid)	((UINT)((sioid) - 1))
#define get_siopcb(sioid)	(&(siopcb_table[INDEX_SIO(sioid)]))

/*
 *  ������Хå��롼����μ����ֹ�
 */

#define SIO_ERDY_SND		1u			/* ������ǽ������Хå�			*/
#define SIO_ERDY_RCV		2u			/* �������Υ�����Хå�			*/

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 */

#define SERIAL_PORT				(CONSOLE_PORTID-1)		/* �����ƥ�Υݡ����ֹ� */
#define SERIAL_INT_PRIORITY		1	/* ������ͥ���� */
#define SERIAL_CLKDIV			3	/* clk = fxx/8     */
#define SERIAL_COMPAREVALUE		11	/* 9600bps=130, 19200bps=65, 38400bps=33, 57600bps=22, 115200bps=11 */

/* ���ꥢ���Ϣ�쥸���� */
#define ASIM(x)  (ASIM0 + ((x) * 0x10))
#define ASIS(x)  (ASIS0 + ((x) * 0x10))
#define ASIF(x)  (ASIF0 + ((x) * 0x10))
#define RXB(x)   (RXB0  + ((x) * 0x10))
#define TXB(x)   (TXB0  + ((x) * 0x10))
#define CKSR(x)  (CKSR0 + ((x) * 0x10))
#define BRGC(x)  (BRGC0 + ((x) * 0x10))
#define SRIC(x)  (SRIC0 + ((x) * 8))
#define STIC(x)  (STIC0 + ((x) * 8))

#define FLG_RECEIVED 1

static unsigned int _serial_flag[TNUM_PORT] = { 0 };

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL_IN		(0x19 + (SERIAL_PORT * 3))
#define INHNO_SERIAL_OUT	(0x1a + (SERIAL_PORT * 3))

/*
 *  ���٥�ݡ��Ⱦ�������֥��å��ν����
 */

#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */
Inline BOOL
hw_port_initialize(int port_id)
{
	if( (sil_reb_mem((VP)ASIM(port_id)) & 0x80) == 0 )
	{
	    	/* ��Ʊ�����ꥢ���̿�ϩ�ν���� */

		/* �ݡ��Ȥ򳫤��� */
		if (port_id == 0) {
			sil_wrh_mem((VP)PMC3, sil_reh_mem((VP)PMC3) | 0x0003);
		} else {
			sil_wrh_mem((VP)PFC8, 0);
			sil_wrh_mem((VP)PMC8, 3);
		}
		/* �ܡ��졼��ȯ����ν���� */
		sil_wrb_mem((VP)CKSR(port_id), SERIAL_CLKDIV);
		sil_wrb_mem((VP)BRGC(port_id), SERIAL_COMPAREVALUE);
		sil_wrb_mem((VP)ASIM(port_id), sil_reb_mem((VP)ASIM(port_id)) | 0x80);	/* enable ASIO */

		__asm("nop; nop");

		sil_wrb_mem((VP)ASIM(port_id), sil_reb_mem((VP)ASIM(port_id)) | 0x04);	/* 8bit length */

		__asm("nop; nop");

		sil_wrb_mem((VP)ASIM(port_id), sil_reb_mem((VP)ASIM(port_id)) | 0x60);	/* Tx, Rx enable */

		/* ��������� */
		sil_wrb_mem((VP)SRIC(port_id), SERIAL_INT_PRIORITY);
		sil_wrb_mem((VP)STIC(port_id), SERIAL_INT_PRIORITY);
	}
	return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥν�λ
 */
Inline void
hw_port_terminate(int port_id)
{
}

/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */
extern void	serial_handler_in(int portid);
extern void	serial_handler_out(int portid);

/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(int port_id)
{
	return (_serial_flag[port_id] & FLG_RECEIVED) != 0 ? TRUE : FALSE;
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(int port_id)
{
	return (sil_reb_mem((VP)ASIF(port_id)) & 0x2) != 0 ? FALSE : TRUE;
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline unsigned char
hw_port_getchar(int port_id)
{
	_serial_flag[port_id] &= FLG_RECEIVED;
	sil_wrb_mem((VP)SRIC(port_id), sil_reb_mem((VP)SRIC(port_id)) & 0x7f);
	return sil_reb_mem((VP)RXB(port_id));
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(int port_id, unsigned char c)
{
	sil_wrb_mem((VP)TXB(port_id), c);
}

/*
 *  ��������ʸ���ν񤭹��ߡ�������ǽ�ˤʤ�ޤ��Ԥġ�
 */
Inline void
hw_port_wait_putchar(int port_id, unsigned char c)
{
	while( !hw_port_putready(port_id) ) ;
	hw_port_putchar(port_id, c);
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(int port_id)
{
}

Inline void
hw_port_sendstop(int port_id)
{
}

extern void	sio_ierdy_rcv(VP_INT exinf);
extern void	sio_ierdy_snd(VP_INT exinf);

Inline void
hw_port_handler_in(int port_id)
{
	_serial_flag[port_id] |= FLG_RECEIVED;
    sio_ierdy_rcv(siopcb_table[port_id].exinf);
}

Inline void
hw_port_handler_out(int port_id)
{
	sio_ierdy_snd(siopcb_table[port_id].exinf);
}

/***********************************************************************************/

/*
 *  sio_initialize -- ���ꥢ��ݡ��ȥɥ饤�Фν����
 */
Inline void
sio_initialize (void)
{
	int ix;

	/* SIO �����֥��å��ν���� */
	for (ix = TNUM_PORT; ix -- > 0; ) {
		siopcb_table[ix].openflag = FALSE;
	}
}

/*
 *  sio_opn_por -- �ݡ��ȤΥ����ץ�
 */
Inline SIOPCB *
sio_opn_por(ID sioid, VP_INT exinf)
{
	SIOPCB	*pcb;

	pcb = get_siopcb(sioid);
	pcb->inib     = NULL;
	pcb->exinf    = exinf;
	pcb->openflag = TRUE;
	pcb->port_id  = sioid-1;
	hw_port_initialize(pcb->port_id);
	return pcb;
}

/*
 *  sio_snd_chr -- ʸ������
 */
Inline BOOL
sio_snd_chr(SIOPCB *pcb, INT chr)
{
	if (hw_port_putready(pcb->port_id)) {
		hw_port_putchar(pcb->port_id, (UB)chr);
		return TRUE;
		}
	else
		return FALSE;
}

/*
 *  sio_rcv_chr -- ʸ������
 */
Inline INT
sio_rcv_chr(SIOPCB *pcb)
{
	if (hw_port_getready(pcb->port_id))
		return hw_port_getchar(pcb->port_id);
	else
		return -1;
}

/*
 *  sio_ena_cbr -- ���ꥢ�� I/O ����Υ�����Хå��ε���
 */
Inline void
sio_ena_cbr(SIOPCB *pcb, UINT cbrtn)
{
}

/*
 *  sio_dis_cbr -- ���ꥢ�� I/O ����Υ�����Хå��ζػ�
 */
Inline void
sio_dis_cbr(SIOPCB *pcb, UINT cbrtn)
{
}

/*
 *  sio_cls_por -- �ݡ��ȤΥ�������
 */
Inline void
sio_cls_por(SIOPCB *pcb)
{
	sio_dis_cbr(pcb, SIO_ERDY_SND);
	sio_dis_cbr(pcb, SIO_ERDY_RCV);
	pcb->openflag = FALSE;
}

Inline void
sio_in_handler(void)
{
	hw_port_handler_in(0);
}

Inline void
sio_out_handler(void)
{
	hw_port_handler_out(0);
}

#if TNUM_PORT > 1
Inline void
sio_in_handler2(void)
{
	hw_port_handler_in(1);
}

Inline void
sio_out_handler2(void)
{
	hw_port_handler_out(1);
}
#endif

#endif /* _HW_SERIAL_H_ */