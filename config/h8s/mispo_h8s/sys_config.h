/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: sys_config.h,v 1.2 2002/04/13 13:15:41 imai Exp $
 */

#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

#include "h8S_2350.h"

/*
 *  ��ư��å������Υ������å�̾
 */

#define	TARGET_NAME	"MISPO-H8S/2350 EVA"

/*
 *  vgxet_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */

#define	SUPPORT_VXGET_TIM

/*
 *  JSP�����ͥ�ư����Υ���ޥå�
 *      0x000000 - 0x01ffff     �������ΰ�(128kB)
 *      0x200000 -              �ǡ����ΰ�(128kB)
 *               - 0x21ffff     ��������Ω���ѥ����å������꽪λ
 */

/*
 *   �����å��ΰ�����
 */

#define STACKTOP    	0x21fffc		/* ��������Ω���ѥ����å��ν���� */
#define str_STACKTOP	_TO_STRING(STACKTOP)
 
/*
 *  ���ꥢ������ߤ�����/���Ϥǰۤʤ뤫�ɤ��������
 */

#define SEPARATE_SIO_INT

/*
 *  �����ƥॿ�����˴ؤ������
 */

#define	CONSOLE_PORTID	1	/* ���󥽡����Ѥ��Ѥ��륷�ꥢ��ݡ����ֹ� */
#define	LOGTASK_PORTID	1	/* �����ƥ������Ϥ��륷�ꥢ��ݡ����ֹ� */

/*
 *  �����ƥॿ���������Ѥ���饤�֥��˴ؤ������
 */

#define NEWLIB			/* newlib ���Ѥ��� */

#ifndef _MACRO_ONLY

/*
 *  �������åȥ����ƥ��¸�ν����
 */

extern void	sys_initialize(void);

/*
 *  �������åȥ����ƥ�ν�λ
 *
 *  �����ƥ��λ������˻Ȥ���ROM��˥��ƽФ��Ǽ¸����뤳�Ȥ����ꤷ
 *  �Ƥ��롥
 */

extern void	sys_exit(void);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����ROM��˥��ƽФ��Ǽ¸����뤳
 *  �Ȥ����ꤷ�Ƥ��롥
 */

extern void sys_putc(char c);

#endif /* _MACRO_ONLY */

/*
 *  (1) CPU �Υ���å����ȿ�
 *  (2) SCI ������
 *  (3) ITU ������
 *  (4) �������ɥ쥹��������
 */

#ifdef CONFIG_20MHz

#define CPU_CLOCK	20000000		/* MHz */

#endif	/* of #ifdef CONFIG_20MHz */

/*
 *  ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI) ������
 */

/*   ����å�20(MHz)
 *�� �ӥåȥ졼��9600(bps)
 *   
 *�� n=0��ʬ���ʤ���
 *�� N=64����0.16(%)
 *   ���äơ����ꥢ��⡼�ɥ쥸����(SMR)�Υ���å����쥯�ȥӥå�
 *�� CKS1=0��CKS0=0
 *�� �ӥåȥ졼�ȥ쥸����BRR=64
 */

#define SYSTEM_SCI		H8SSCI0
#define SYSTEM_SCI_IPR		H8SIPRJ
/*  �ʲ���2���ܤ�H8�ǤǤ�������Ƥ��ʤ���  */
#define SCI_INTLVL		3   	/*  SCI����ͥ�0�γ����ߥ�٥�  */
#define SCI_BIT_SHIFT		0       /*  ����ߥ�٥������쥸��������������Ȥ��Υ��եȿ�  */

#define BAUD_RATE		9600			/* bps */

#define INHNO_SERIAL_IN		IRQ_RXI0
#define INHNO_SERIAL_OUT	IRQ_TXI0

#define H8SSMR_CKS		(H8SSMR_CKS0)  /*  ����  */

#define H8SBRR_RATE		64	/*  N=64  */

/*  
 *  �ǽ�Σ��ӥå�ʬ���Ԥ����֤�����
 *������å�20MHz�ξ����ͤ�ή��
 *���롼��1����դ�5̿��(=5����å�)
 */

#define SCI_SETUP_COUNT		((CPU_CLOCK)/(BAUD_RATE)/5) 
/*
 *  �����ޥѥ륹��˥å�(TPU) ������
 */

#define SYSTEM_TPU		H8STPU0
#define SYSTEM_STR		H8STSTR_CST0
#define SYSTEM_STR_BIT		H8STSTR_CST0_BIT
#define SYSTEM_GR		H8STGRA
#define SYSTEM_TPU_IE		H8STIER_TGIEA		/* interrupt mask */
#define SYSTEM_TPU_IE_BIT	H8STIER_TGIEA_BIT
#define SYSTEM_TPU_IF		H8STSR_TGFA		/* match flag */
#define SYSTEM_TPU_IF_BIT	H8STSR_TGFA_BIT

#define SYSTEM_TPU_IPR		H8SIPRF  /*  TPU����ͥ�0��IPR  */
/*  H8�ǤǤϰʲ���2���ܤ�����Ϥʤ�  */
 				/*��TPU����ͥ�0�γ����ߥ�٥롡*/
#define TPU_INTLVL		5
#define LEVEL0			0
				 /*  ����ߥ�٥������쥸��������������Ȥ��Υ��եȿ�  */
#define TPU_BIT_SHIFT		4

#define INHNO_TIMER		IRQ_TGI0A

#define H8STCR_CCLR		H8STCR_CCLR0		/* clear on GRA */
#define H8STCR_CKEG		(0)			/* positive edge */
							/* clock / 4 */
#define H8STCR_TPSC		(H8STCR_TPSC0)
#define H8STIOR_IOB		(0)			/* no output */
#define H8STIOR_IOA		(0)			/* no output */
#define H8STIOR_IOC		(0)			/* no output */
#define H8STIOR_IOD		(0)			/* no output */

#define TIMER_CLOCK		((CPU_CLOCK)/4000)	/* 20MHz / 4 = 5MHz = 5000KHz */

/*
 *  �������ɥ쥹��������
 */

#if 0

#define	ENABLE_LOWER_DATA

#define	ENABLE_P8_CS		(H8P8DDR_CS0_BIT|H8P8DDR_CS1_BIT|H8P8DDR_CS2_BIT|H8P8DDR_CS3_BIT)
#define	ENABLE_PA_CS		(H8PADDR_CS4_BIT|H8PADDR_CS5_BIT|H8PADDR_CS6_BIT)
#define ENABLE_PB_CS		 H8PBDDR_CS7_BIT

#endif	/* of #if 0 */

#endif /* _SYS_CONFIG_H_ */
