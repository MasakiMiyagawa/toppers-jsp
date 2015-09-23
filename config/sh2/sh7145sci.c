/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2002-2004 by Hokkaido Industrial Research Institute, JAPAN
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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: sh7145sci.c,v 1.1 2004/10/04 12:23:39 honda Exp $
 */

/*
 *   SH2��¢���ꥢ�륳�ߥ�˥�������󥤥󥿥ե�����SCI�� �ʰץɥ饤��
 */

#include <s_services.h>
#ifdef GDB_STUB
#include "sh7145sci0.h"
#else	/*  GDB_STUB  */
#include "sh7145sci1.h"
#endif	/*  GDB_STUB  */

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
struct sio_port_control_block {
	VP_INT		exinf;		/* ��ĥ���� */
	BOOL		openflag;	/* �����ץ�Ѥߥե饰 */
};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
static SIOPCB	siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
				/*  �ݡ���ID����ǥХ����ֹ�����ޥ���  */
#define INDEX_SIOP(siopid)	((UINT)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  ʸ��������Ǥ��뤫��
 */
Inline BOOL
sh2sci_getready(SIOPCB *siopcb)
{
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ����å�  */
	return (sil_reb_mem (SCI_SSR) & SSR_RDRF);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
sh2sci_putready(SIOPCB *siopcb)
{
	/*  �ȥ�󥹥ߥåȥǡ����쥸��������ץƥ����ե饰�Υ����å� */
	return (sil_reb_mem (SCI_SSR) & SSR_TDRE);
}

/*
 *  ��������ʸ���μ�Ф�
 */
Inline char
sh2sci_getchar(SIOPCB *siopcb)
{
	char data;

	data = sil_reb_mem (SCI_RDR);
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ��ꥢ  */
	sil_wrb_mem (SCI_SSR, sil_reb_mem (SCI_SSR) & ~SSR_RDRF);
	return data;
}

/*
 *  ��������ʸ���ν����
 */
Inline void
sh2sci_putchar(SIOPCB *siopcb, char c)
{
#ifdef GDB_STUB
	//gdb_stub_putc( c );
	sil_wrb_mem (SCI_TDR, c);
	/*  �ȥ�󥹥ߥå�FIFO�ǡ����쥸��������ץƥ����ե饰�Υ��ꥢ */
	sil_wrb_mem (SCI_SSR, sil_reb_mem (SCI_SSR) & ~SSR_TDRE);
#else
	sil_wrb_mem (SCI_TDR, c);
	/*  �ȥ�󥹥ߥå�FIFO�ǡ����쥸��������ץƥ����ե饰�Υ��ꥢ */
	sil_wrb_mem (SCI_SSR, sil_reb_mem (SCI_SSR) & ~SSR_TDRE);
#endif
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
void
sh2sci_initialize()
{
	SIOPCB	*siopcb;
	UINT	i;

	/*
	 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
	 */
	for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
		siopcb->openflag = FALSE;
	}
}

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
BOOL
sh2sci_openflag(void)
{
#if TNUM_SIOP < 2
	return(siopcb_table[0].openflag);
#else /* TNUM_SIOP < 2 */
	return(siopcb_table[0].openflag || siopcb_table[1].openflag);
#endif /* TNUM_SIOP < 2 */
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
sh2sci_opn_por(ID siopid, VP_INT exinf)
{
	SIOPCB *siopcb = get_siopcb(siopid);

#ifdef GDB_STUB
	sil_wrh_mem (MSTCR1, (VH)((VH)sil_reh_mem(MSTCR1)& ~0x0001));
#else	/*  GDB_STUB  */
	sil_wrh_mem (MSTCR1, (VH)((VH)sil_reh_mem(MSTCR1)& ~0x0002));
#endif	/*  GDB_STUB  */
	sil_wrb_mem (SCI_SDCR,0xf0);

	/*  ���������  */
	sil_wrb_mem (SCI_SCR,0x00);

	/*  SCI�ǡ��������ϥݡ��Ȥ�����  */
	sil_wrh_mem (PACRL2, sil_reh_mem (PACRL2) | (PFC_TXD | PFC_RXD));

	/*  �ԥ󥢥�����
	 *     ���ꥢ��ǥХ������Τλ���ǤϤʤ��Τ�
	 *     ����Ϥ��Υե�����˵��Ҥ���ΤϤդ��路���ʤ�����
	 *     hw_serial.c���Ѱդ���Τ��ѻ��ʤΤǻ���Ū�ˤ���������Ƥ��롣
	 */

	/*  �������ե����ޥå�  */
	sil_wrb_mem (SCI_SMR, 0x00);
	/*  Ĵ��Ʊ����  */
	/*  8�ӥåȡ��ѥ�ƥ��ʤ�  */
	/*  ���ȥåץӥåȥ�󥰥���1   */
	/*  ����å����쥯�� */

	sil_wrb_mem (SCI_BRR, (VB) BRR);

	/*
	 * �ܡ��졼�Ȥ�����塢1�������ʬ�Ԥ��ʤ���Фʤ�ʤ���
	 */
	sil_dly_nse (sh2sci_DELAY);	/* �ͤϣ�裱��Ʊ�� */

	/* ���顼�ե饰�򥯥ꥢ */
	sil_wrb_mem (SCI_SSR, sil_reb_mem (SCI_SSR) & ~(SSR_ORER | SSR_FER |SSR_PER));
	//���������ġ����������ߵ���
	sil_wrb_mem (SCI_SCR, (VB) (SCI_RIE | SCI_TE | SCI_RE));

	siopcb->exinf = exinf;
	siopcb->openflag = TRUE;
	return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
sh2sci_cls_por(SIOPCB *siopcb)
{
	/*  ��������ߡ�����߶ػ�  */
	sil_wrb_mem (SCI_SCR,sil_reb_mem (SCI_SCR) & (VB) ~ (SCI_TIE | SCI_RIE | SCI_TE | SCI_RE));
#ifdef GDB_STUB
	sil_wrh_mem (MSTCR1, (VH)((VH)sil_reh_mem(MSTCR1) | 0x0001));
#else	/*  GDB_STUB  */
	sil_wrh_mem (MSTCR1, (VH)((VH)sil_reh_mem(MSTCR1) | 0x0002));
#endif	/*  GDB_STUB  */
	siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
sh2sci_snd_chr(SIOPCB *siopcb, char c)
{
	if (sh2sci_putready(siopcb)) {
		sh2sci_putchar(siopcb, c);
		return(TRUE);
	}
	return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
sh2sci_rcv_chr(SIOPCB *siopcb)
{
	if (sh2sci_getready(siopcb)) {
		return((INT)(UB) sh2sci_getchar(siopcb));
		/*  (UB)�ǥ��㥹�Ȥ���Τϥ����ĥ�ˤ��뤿��  */
	}
	return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
sh2sci_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	switch (cbrtn) {
	case SIO_ERDY_SND:	/* �����������׵����� */
		sil_wrb_mem (SCI_SCR, sil_reb_mem (SCI_SCR) | SCI_TIE);
		break;
	case SIO_ERDY_RCV:	/* �����������׵����� */
		sil_wrb_mem (SCI_SCR, sil_reb_mem (SCI_SCR) | SCI_RIE);
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
sh2sci_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
	switch (cbrtn) {
	case SIO_ERDY_SND:	/* �����������׵��ػ� */
		sil_wrb_mem (SCI_SCR, sil_reb_mem (SCI_SCR) & ~SCI_TIE);
		break;
	case SIO_ERDY_RCV:	/* �����������׵��ػ� */
		sil_wrb_mem (SCI_SCR, sil_reb_mem (SCI_SCR) & ~SCI_RIE);
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф�����������߽���
 */
Inline void
sh2sci_isr_siop_out(SIOPCB *siopcb)
{
	VB scr0 = sil_reb_mem (SCI_SCR);
	
	if ((scr0 & SCI_TIE) != 0 && sh2sci_putready(siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		sh2sci_ierdy_snd(siopcb->exinf);
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф����������߽���
 */
Inline void
sh2sci_isr_siop_in(SIOPCB *siopcb)
{
	VB scr0 = sil_reb_mem (SCI_SCR);

	if ((scr0 & SCI_RIE) != 0 && sh2sci_getready(siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		sh2sci_ierdy_rcv(siopcb->exinf);
	}
}

/*
 *  SCI��������ߥ����ӥ��롼����
 *  
 */
void
sh2sci_isr_out(void)
{
	if (siopcb_table[0].openflag) {
		sh2sci_isr_siop_out(get_siopcb(1));
	}
}

/*
 *  SIO��������ߥ����ӥ��롼����
 *  
 */
void
sh2sci_isr_in(void)
{
	if (siopcb_table[0].openflag) {
		sh2sci_isr_siop_in(get_siopcb(1));
	}
}

/*
 *  SIO�������顼����ߥ����ӥ��롼����
 */
void
sh2sci_isr_error(void)
{
	if (siopcb_table[0].openflag) {
	sil_wrb_mem (SCI_SSR, sil_reb_mem (SCI_SSR) & ~(SSR_ORER | SSR_FER |SSR_PER));
	}
}

/*
 * �ݡ���󥰤ˤ��ʸ��������
 */
void
sh2sci_putc_pol(char c)
{
	while(!sh2sci_putready(&siopcb_table[0]));
	sh2sci_putchar(&siopcb_table[0], c);
}
