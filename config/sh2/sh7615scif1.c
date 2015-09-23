/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2000-2003 by Industrial Technology Institute,
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
 *  @(#) $Id: sh7615scif1.c,v 1.1 2004/09/03 15:52:38 honda Exp $
 */

/*
 *   SH2��¢���ꥢ�륳�ߥ�˥�������󥤥󥿥ե�����SCI�� �ʰץɥ饤��
 */

#include <s_services.h>
#ifndef GDB_STUB
#include "sh7615scif1.h"
#else	/*  GDB_STUB  */
#include "sh7615scif2.h"
#endif	/*  GDB_STUB  */

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 *  ��2ch���ݡ��Ȥ˳�ĥ������Ͻ�����ѤΥǡ�����ޤ��
 */
struct sio_port_control_block
{
	VP_INT exinf;				/* ��ĥ���� */
	BOOL openflag;				/* �����ץ�Ѥߥե饰 */
};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 *  ����ID = 1 ��SCI0���б������Ƥ��롥
 */
SIOPCB siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)	((UINT)((siopid) - 1))
#define get_siopcb(siopid)	(&(siopcb_table[INDEX_SIOP(siopid)]))

/*
 *  ʸ��������Ǥ��뤫��
 */
Inline BOOL
sh2scif1_getready (SIOPCB * siopcb)
{
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ����å�  */
	return (sil_reh_mem (SCIF_SC1SSR1) & SC1SSR_RDRF);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
sh2scif1_putready (SIOPCB * siopcb)
{
	/*  �ȥ�󥹥ߥå�FIFO�ǡ����쥸��������ץƥ����ե饰�Υ����å� */
	return (sil_reh_mem (SCIF_SC1SSR1) & SC1SSR_TDFE);
}

/*
 *  ��������ʸ���μ�Ф�
 */
Inline char
sh2scif1_getchar (SIOPCB * siopcb)
{
	VB data;

	data = sil_reb_mem (SCIF_SCFRDR1);
	/*  �쥷���֥ǡ����쥸�����ե롦�ե饰�Υ��ꥢ  */
	//SCIF_SC1SSR1 &= ~SC1SSR_RDRF ;
	sil_wrh_mem (SCIF_SC1SSR1, sil_reh_mem (SCIF_SC1SSR1) & ~SC1SSR_RDRF);
	return data;
}

/*
 *  ��������ʸ���ν����
 */
Inline void
sh2scif1_putchar (SIOPCB * siopcb, char c)
{
	sil_wrb_mem (SCIF_SCFTDR1, c);
	/*  �ȥ�󥹥ߥå�FIFO�ǡ����쥸��������ץƥ����ե饰�Υ��ꥢ */
	sil_wrh_mem (SCIF_SC1SSR1, sil_reh_mem (SCIF_SC1SSR1) & ~SC1SSR_TDFE);
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
void
sh2scif1_initialize ()
{
	SIOPCB *siopcb;
	UINT i;

	/*
	 *  ���륢��I/O�ݡ��ȴ����֥�å��ν����
	 */
	for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
		siopcb->openflag = FALSE;
	}
}

/*
 *  �����ץ󤷤Ƥ���ݡ��Ȥ����뤫��
 */
BOOL
sh2scif1_openflag (void)
{
#if TNUM_SIOP < 2
	return (siopcb_table[0].openflag);
#else /* TNUM_SIOP < 2 */
	return (siopcb_table[0].openflag || siopcb_table[1].openflag);
#endif /* TNUM_SIOP < 2 */
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
sh2scif1_opn_por (ID siopid, VP_INT exinf)
{
	SIOPCB *siopcb;

	siopcb = get_siopcb (siopid);

	/*  ���������  */
	sil_wrh_mem (SCIF_SCSCR1,
				 sil_reh_mem (SCIF_SCSCR1) & ~(SCSCR_TE | SCSCR_RE));

	/*  SCIF1�ǡ��������ϥݡ��Ȥ�����  */
#ifndef GDB_STUB
	sil_wrh_mem (PBCR, sil_reh_mem (PBCR) | (PBCR_TXD1 | PBCR_RXD1));
#else	/*  GDB_STUB  */
	sil_wrh_mem (PBCR2, sil_reh_mem (PBCR2) | (PBCR_TXD2 | PBCR_RXD2));
#endif	/*  GDB_STUB  */

	/*  FIFO�ν����  */
	sil_wrb_mem (SCIF_SCFCR1, (VB) (SCFCR_TFRST | SCFCR_RFRST));

	/*  �������ե����ޥå�  */
	sil_wrb_mem (SCIF_SCSMR1, 0x00);
	/*  Ĵ��Ʊ����  */
	/*  8�ӥåȡ��ѥ�ƥ��ʤ�  */
	/*  ���ȥåץӥåȥ�󥰥���1   */
	/*  ����å����쥯�� */

	sil_wrb_mem (SCIF_SCBRR1, (VB) SCI_BRR);	/*  �ܡ��졼������      */


	/*
	 * �ܡ��졼�Ȥ�����塢1�������ʬ�Ԥ��ʤ���Фʤ�ʤ���
	 */
	sil_dly_nse (sh2scif1_DELAY);	/* �ͤϣ�裱��Ʊ�� */

	/*  FIFO������  */
	sil_wrb_mem (SCIF_SCFCR1, 0x00);

	/* ���顼�ե饰�򥯥ꥢ */
	sil_wrb_mem (SCIF_SC2SSR1, sil_reb_mem (SCIF_SC2SSR1) & ~SC2SSR_ORER);
	sil_wrh_mem (SCIF_SC1SSR1,
				 sil_reh_mem (SCIF_SC1SSR1) & ~(SC1SSR_ER | SC1SSR_FER |
												SC1SSR_PER));

	sil_wrb_mem (SCIF_SCSCR1, (VB) (SCSCR_RIE | SCSCR_TE | SCSCR_RE));

	siopcb->exinf = exinf;
	siopcb->openflag = TRUE;
	return (siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
sh2scif1_cls_por (SIOPCB * siopcb)
{
	/*  ��������ߡ�����߶ػ�  */
	sil_wrb_mem (SCIF_SCSCR1,
				 (VB) ~ (SCSCR_TIE | SCSCR_RIE | SCSCR_TE | SCSCR_RE));

	siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
sh2scif1_snd_chr (SIOPCB * siopcb, char c)
{
	if (sh2scif1_putready (siopcb)) {
		sh2scif1_putchar (siopcb, c);
		return (TRUE);
	}
	return (FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
sh2scif1_rcv_chr (SIOPCB * siopcb)
{
	if (sh2scif1_getready (siopcb)) {
		return ((INT) (UB) sh2scif1_getchar (siopcb));
	}
	return (-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
sh2scif1_ena_cbr (SIOPCB * siopcb, UINT cbrtn)
{
	switch (cbrtn) {
	case SIO_ERDY_SND:			/* �����������׵����� */
		sil_wrb_mem (SCIF_SCSCR1, sil_reb_mem (SCIF_SCSCR1) | SCSCR_TIE);
		break;
	case SIO_ERDY_RCV:			/* �����������׵����� */
		sil_wrb_mem (SCIF_SCSCR1, sil_reb_mem (SCIF_SCSCR1) | SCSCR_RIE);
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
sh2scif1_dis_cbr (SIOPCB * siopcb, UINT cbrtn)
{
	switch (cbrtn) {
	case SIO_ERDY_SND:			/* �����������׵��ػ� */
		sil_wrb_mem (SCIF_SCSCR1, sil_reb_mem (SCIF_SCSCR1) & ~SCSCR_TIE);
		break;
	case SIO_ERDY_RCV:			/* �����������׵��ػ� */
		sil_wrb_mem (SCIF_SCSCR1, sil_reb_mem (SCIF_SCSCR1) & ~SCSCR_RIE);
		break;
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф�����������߽���
 */
Inline void
sh2scif1_isr_siop_out (SIOPCB * siopcb)
{
	VB scr0 = sil_reb_mem (SCIF_SCSCR1);

	if ((scr0 & SCSCR_TIE) != 0 && sh2scif1_putready (siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		sh2scif1_ierdy_snd (siopcb->exinf);
	}
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф����������߽���
 */
Inline void
sh2scif1_isr_siop_in (SIOPCB * siopcb)
{
	VB scr0 = sil_reb_mem (SCIF_SCSCR1);

	if ((scr0 & SCSCR_RIE) != 0 && sh2scif1_getready (siopcb)) {
		/*
		 *  �������Υ�����Хå��롼�����ƤӽФ���
		 */
		sh2scif1_ierdy_rcv (siopcb->exinf);
	}
}

/*
 *  SIO��������ߥ����ӥ��롼���� ��裱��Ʊ��
 *  
 *  ��SH1��¢��SCI�Ǥϳ�����ֹ椬�������̡�����ͥ��̤�ʬ����Ƥ���Τǡ�
 *  ��SCI0����������߰ʳ��Ǥ��Υ롼���󤬸ƤФ�뤳�ȤϤʤ�
 *  
 */
void
sh2scif1_isr_out ()
{
	if (siopcb_table[0].openflag) {
		sh2scif1_isr_siop_out (&(siopcb_table[0]));
	}
}

/*
 *  SIO��������ߥ����ӥ��롼���󡡣�裱��Ʊ��
 *  
 *  ��SH1��¢��SCI�Ǥϳ�����ֹ椬�������̡�����ͥ��̤�ʬ����Ƥ���Τǡ�
 *  ��SCI0�μ�������߰ʳ��Ǥ��Υ롼���󤬸ƤФ�뤳�ȤϤʤ�
 *  
 */
void
sh2scif1_isr_in ()
{
	if (siopcb_table[0].openflag) {
		sh2scif1_isr_siop_in (&(siopcb_table[0]));
	}
}

/*
 *  SIO�������顼����ߥ����ӥ��롼���󡡣�裱��Ʊ��
 *  
 *  ��SH1��¢��SCI�Ǥϳ�����ֹ椬����ͥ��̤�ʬ����Ƥ���Τǡ�
 *  ��SCI0�μ������顼����߰ʳ��Ǥ��Υ롼���󤬸ƤФ�뤳�ȤϤʤ�
 *  ��
 *  �����顼�������Τϥ��顼�ե饰�Υ��ꥢ�ΤߤˤȤɤ�Ƥ��롣
 *  �������������С���󥨥顼
 *  ���������ե졼�ߥ󥰥��顼
 *  ���������ѥ�ƥ����顼
 */
void
sh2scif1_isr_error (void)
{

	if (siopcb_table[0].openflag) {
		sil_wrb_mem (SCIF_SC2SSR1, sil_reb_mem (SCIF_SC2SSR1) & ~SC2SSR_ORER);
		sil_wrh_mem (SCIF_SC1SSR1,
					 sil_reh_mem (SCIF_SC1SSR1) & ~(SC1SSR_ER | SC1SSR_FER |
													SC1SSR_PER));
	}
}

/*
 * �ݡ���󥰤ˤ��ʸ��������
 */
void
sh2scif1_putc_pol (char c)
{
	while (!sh2scif1_putready (&siopcb_table[0]));
	sh2scif1_putchar (&siopcb_table[0], c);
}
