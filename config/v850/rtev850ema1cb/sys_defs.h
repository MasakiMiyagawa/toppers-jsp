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
 *  @(#) $Id: sys_defs.h,v 1.2 2001/11/15 13:18:32 takayuki Exp $
 */

/*
 *	�������åȥ����ƥ�˰�¸�������
 *    RTE-V850E/MA1-CB uPD70F3107 50MHz
 */

#include "sys_config.h"

#ifndef _SYS_DEFS_H_
#define _SYS_DEFS_H_

#define RTEV850EMA1CB

/*
 * ����ޥåץɥ쥸����
 */

#define ISPR  0xfffff1fa

#define PHCMD 0x0ffff800
#define CKC   0x0ffff822

#define IMR0  0x0ffff100
#define IMR1  0x0ffff102
#define IMR2  0x0ffff104
#define IMR3  0x0ffff106

#define SRIC0 0x0ffff15c
#define STIC0 0x0ffff15e
#define ASIM0 0x0ffffa00
#define RXB0  0x0ffffa02
#define ASIS0 0x0ffffa03
#define TXB0  0x0ffffa04
#define ASIF0 0x0ffffa05
#define CKSR0 0x0ffffa06
#define BRGC0 0x0ffffa07

#define LED1  0x07802000
#define LED2  0x07802001

#define BCT0  0x0ffff480
#define BCT1  0x0ffff482
#define DWC0  0x0ffff484
#define DWC1  0x0ffff486
#define BCC   0x0ffff488
#define VSWC  0x0ffff06e
#define BCP   0x0ffff48c
#define ASC   0x0ffff48a
#define CSC0  0x0ffff060
#define CSC1  0x0ffff062
#define BSC   0x0ffff066
#define BEC   0x0ffff068
#define SCR1  0x0ffff4a4
#define RFS1  0x0ffff4a6

#define PMC4  0x0ffff448
#define PFC4  0x0ffff468

	/* �����޴�Ϣ�쥸���� */
#define TMD(x)   (0x0ffff540 + ((x) * 0x10))
#define CMD(x)   (0x0ffff540 + ((x) * 0x10) + 2)
#define TMCD(x)  (0x0ffff540 + ((x) * 0x10) + 4)
#define CMICD(x) (0x0ffff148 + ((x) * 2))

	/* ���ꥢ���Ϣ�쥸���� */
#define ASIM(x)  (0x0ffffa00 + ((x) * 0x10))
#define ASIS(x)  (0x0ffffa00 + ((x) * 0x10) + 3)
#define ASIF(x)  (0x0ffffa00 + ((x) * 0x10) + 5)
#define RXB(x)   (0x0ffffa00 + ((x) * 0x10) + 2)
#define TXB(x)   (0x0ffffa00 + ((x) * 0x10) + 4)
#define CKSR(x)  (0x0ffffa00 + ((x) * 0x10) + 6)
#define BRGC(x)  (0x0ffffa00 + ((x) * 0x10) + 7)
#define SRIC(x)  (0x0ffff15c + ((x) * 8))
#define STIC(x)  (0x0ffff15c + ((x) * 8) + 1)

/*
 *  INTNO���ȳ���ߤζػ�/����
 */
#ifndef _MACRO_ONLY

typedef	UINT		INTNO;		/* ������ֹ� */

extern ER	dis_int(INTNO intno);
extern ER	ena_int(INTNO intno);

#endif /* _MACRO_ONLY */

/*
 *  �������åȥ����ƥ��¸�Υ����ӥ�������
 */
#ifndef _MACRO_ONLY

typedef	UD		SYSUTIM;	/* ��ǽɾ���ѥ����ƥ���� */

extern ER	vxget_tim(SYSUTIM *pk_sysutim);

#endif /* _MACRO_ONLY */

/*
 *  ������ƥ��å������
 */
#define	TIC_NUME	1		/* ������ƥ��å��μ�����ʬ�� */
#define	TIC_DENO	1		/* ������ƥ��å��μ�����ʬ�� */

#endif /* _SYS_DEFS_H_ */
