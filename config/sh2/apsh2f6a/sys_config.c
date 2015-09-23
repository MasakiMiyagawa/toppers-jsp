/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Industrial Technology Institute,
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
 *  @(#) $Id: sys_config.c,v 1.3 2004/10/04 12:18:45 honda Exp $
 */

#include "jsp_kernel.h"
#include <sil.h>
#ifdef GDB_STUB
#include "sh7145sci0.h"
#else	/*  GDB_STUB  */
#include "sh7145sci1.h"
#endif	/*  GDB_STUB  */

/*
 *  �������åȥ����ƥ��¸�ν����
 */
/*
 *  ���ꥢ��I/O�ݡ��Ȥν���� banner���ϤΤ��ᥫ���ͥ�ν������̵�ط��˹Ԥ�
 */
Inline void
Sci_Initialize ()
{
#ifndef GDB_STUB
	sil_wrh_mem (PACRL2, sil_reh_mem (PACRL2) | (0x0100 | 0x0040));
#else	/*  GDB_STUB  */
	sil_wrh_mem (PACRL2, sil_reh_mem (PACRL2) | (0x0004 | 0x0001));
#endif	/*  GDB_STUB  */
	sil_wrb_mem (SCI_SDCR,0xf0);
	sil_wrb_mem (SCI_SCR,0x00);
	sil_wrb_mem (SCI_SMR, 0x00);
	sil_wrb_mem (SCI_BRR, (VB) BRR);
	sil_dly_nse (sh2sci_DELAY);
	sil_dly_nse (sh2sci_DELAY);
	sil_wrb_mem (SCI_SSR, sil_reb_mem (SCI_SSR) & ~(SSR_ORER | SSR_FER |SSR_PER));
	sil_wrb_mem (SCI_SCR, (VB) (SCI_RIE | SCI_TE | SCI_RE));
}

void
sys_initialize()
{
	Sci_Initialize ();

}

/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit()
{
	sh2_exit ();
}

/*
 *  �������åȥ����ƥ��ʸ������
 */
void
sys_putc(char c)
{
	if (c == '\n') {
		sh2_putc ('\r');
	}
	sh2_putc (c);
}

/* �ϡ��ɥ����������� */
#ifndef GDB_STUB
void
hardware_init_hook (void)
{
	sil_wrh_mem (MSTCR1, (VH)((VH)sil_reh_mem(MSTCR1)& ~0x0002));
	sil_wrh_mem (MSTCR2, (VH)((VH)sil_reh_mem(MSTCR2)& ~0x1000));
	sil_wrh_mem (BCR1, 0x202f);
	sil_wrh_mem (BCR2, 0x5500);
	sil_wrh_mem (WCR1, 0x0010);
	sil_wrh_mem (PACRH, 0x5000);
	sil_wrh_mem (PACRL1, 0x1540);
	sil_wrh_mem (PACRL2, 0x0140);
	sil_wrh_mem (PBCR1, 0x0002);
	sil_wrh_mem (PBCR2, 0xa005);
	sil_wrh_mem (PCCR, 0xfffc);
	sil_wrh_mem (PDCRH1, 0x5555);
	sil_wrh_mem (PDCRH2, 0x5555);
	sil_wrh_mem (PDCRL1, 0xffff);
	sil_wrh_mem (PDCRL2, 0x0000);
	sil_wrh_mem (PECRL1, 0x0000);
	sil_wrh_mem (PECRL2, 0x0000);
	sil_wrh_mem (PAIORL, 0x87e7);
	sil_wrh_mem (PBIOR, 0x023c);
	sil_wrh_mem (PEIORL, 0x8000);
}
#else	/*  GDB_STUB  */
void
hardware_init_hook (void)
{
	sil_wrh_mem (MSTCR1, (VH)((VH)sil_reh_mem(MSTCR1)& ~0x0001));
	sil_wrh_mem (MSTCR2, (VH)((VH)sil_reh_mem(MSTCR2)& ~0x1000));
	sil_wrh_mem (PEIORL, 0x8000);
}
#endif	/*  GDB_STUB  */

