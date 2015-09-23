/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: sys_config.h,v 1.1 2001/11/12 13:38:30 abe Exp $
 */

#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

#include "h8_3048f.h"

/*
 *  ��ư��å������Υ������å�̾
 */

#define	TARGET_NAME	"AKI-H8/3048F"

/*
 *  vgxet_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */

#define	SUPPORT_VXGET_TIM

/*
 *  JSP�����ͥ�ư����Υ���ޥå� (RAM �ǥХå���)
 *      00020000 - 0003ffff     �������ΰ衢�ǡ����ΰ�(384KB)
 *               - 00080000     ��������Ω���ѥ����å�
 *               - 00080000     ���꽪λ
 *
 */

/*
 *   �����å��ΰ�����
 */

#define STACKTOP    	0x000fff10		/* ��������Ω���ѥ����å��ν���� */
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

#ifdef CONFIG_16MHz

#define CPU_CLOCK	16000000		/* MHz */

#endif	/* of #ifdef CONFIG_16MHz */

/*
 *  SCI ������
 */

#define SYSTEM_SCI		H8SCI1

#define SYSTEM_SCI_IPR		H8IPRB
#define SYSTEM_SCI_IP_BIT	H8IPR_SCI1_BIT

#define BAUD_RATE		9600			/* bps */

#define INHNO_SERIAL_IN		IRQ_RXI1
#define INHNO_SERIAL_OUT	IRQ_TXI1

#define H8SMR_CKS		(H8SMR_CKS1|H8SMR_CKS0)	/* clock / 8 */

#define H8BRR_RATE		((UB)((CPU_CLOCK/(32*(BAUD_RATE)))-1))
#define SCI_SETUP_COUNT		((CPU_CLOCK)/(BAUD_RATE)/5)

/*
 *  ITU ������
 */

#define SYSTEM_ITU		H8ITU0
#define SYSTEM_STR		H8TSTR_STR0
#define SYSTEM_STR_BIT		H8TSTR_STR0_BIT
#define SYSTEM_GR		H8GRA
#define SYSTEM_ITU_IE		H8TIER_IMIEA		/* interrupt mask */
#define SYSTEM_ITU_IE_BIT	H8TIER_IMIEA_BIT
#define SYSTEM_ITU_IF		H8TSR_IMIFA		/* match flag */
#define SYSTEM_ITU_IF_BIT	H8TSR_IMIFA_BIT

#define INHNO_TIMER		IRQ_IMIA0

#define H8TCR_CCLR		H8TCR_CCLR0		/* clear on GRA */
#define H8TCR_CKEG		(0)			/* positive edge */
							/* clock / 8 */
#define H8TCR_TPSC		(H8TCR_TPSC1|H8TCR_TPSC0)
#define H8TIOR_IOB		(0)			/* no output */
#define H8TIOR_IOA		(0)			/* no output */

#define TIMER_CLOCK		((CPU_CLOCK)/8000)	/* 16MHz / 8 = 2MHz = 2000KHz */

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
