/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Kunihiko Ohnaka
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
 *  @(#) $Id: sys_config.h,v 1.2 2002/04/11 11:55:11 hiro Exp $
 */

#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

#include "h8_3067f.h"

/*
 *  ��ư��å������Υ������å�̾
 */

#define	TARGET_NAME	"AKI-H8/3067F"

/*
 *  vgxet_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */

#define	SUPPORT_VXGET_TIM

/*
 *   �����å��ΰ�����
 */

#define STACKTOP    	0x00ffff20		/* ��������Ω���ѥ����å��ν���� */
#define str_STACKTOP	_TO_STRING(STACKTOP)

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

extern void cpu_putc(char c);

Inline void
sys_putc(char c)
{
	cpu_putc(c);
	};

#endif /* _MACRO_ONLY */

/*
 *  (1) ���ꥢ��ݡ��Ȥ�����
 *  (2) �����ޡ�������
 *  (3) �������ɥ쥹��������
 */
 
/*
 *  ���ꥢ������ߤ�����/���Ϥǰۤʤ뤫�ɤ��������
 */

#define SEPARATE_SIO_INT

/*
 *  ���ݡ��Ȥ��륷�ꥢ��ǥ��Х����ο�
 *  ���� 3����������JSP �����ͥ�� 2 �ݡ��ȤޤǤ���
 *  ���ݡ��Ȥ��Ƥ��ʤ���
 */

#define NUM_PORT	2

#define SYSTEM_SCI		H8SCI1

#define SYSTEM_SCI_IPR		H8IPRB
#define SYSTEM_SCI_IP_BIT	H8IPR_SCI1_BIT

#define BAUD_RATE		19200			/* bps */

#define H8SMR_CKS		(H8SMR_CKS1|H8SMR_CKS0)	/* clock / 8 */

#define H8BRR_RATE		((UB)((CPU_CLOCK/(32*(BAUD_RATE)))-1))
#define SCI_SETUP_COUNT		((CPU_CLOCK)/(BAUD_RATE)/5)

#define	CONSOLE_PORTID		SYSTEM_PORTID	/* ���󥽡�����Ѥ��륷�ꥢ��ݡ����ֹ�     */
#define	LOGTASK_PORTID		SYSTEM_PORTID	/* �����ƥ������Ϥ��륷�ꥢ��ݡ����ֹ� */

#if NUM_PORT == 1

#define	SYSTEM_PORTID		PORT_ID1

#define HWPORT1_ADDR		SYSTEM_SCI

#define INHNO_SERIAL_ERROR	IRQ_ERI1
#define INHNO_SERIAL_IN		IRQ_RXI1
#define INHNO_SERIAL_OUT	IRQ_TXI1

#elif NUM_PORT == 2	/* of #if NUM_PORT == 1 */

#define USER_SCI		H8SCI0

#define USER_SCI_IPR		H8IPRB
#define USER_SCI_IP_BIT		H8IPR_SCI0_BIT

#define	USER_PORTID		PORT_ID1
#define	SYSTEM_PORTID		PORT_ID2

#define HWPORT1_ADDR		USER_SCI
#define HWPORT2_ADDR		SYSTEM_SCI

#define INHNO_SERIAL_ERROR	IRQ_ERI0
#define INHNO_SERIAL_IN		IRQ_RXI0
#define INHNO_SERIAL_OUT	IRQ_TXI0

#define INHNO_SERIAL_ERROR2	IRQ_ERI1
#define INHNO_SERIAL_IN2	IRQ_RXI1
#define INHNO_SERIAL_OUT2	IRQ_TXI1

#else	/* of #if NUM_PORT == 1 */

#error NUM_PORT <= 2

#endif	/* of #if NUM_PORT == 1 */

/*
 *  �����ޤ�����
 */

#define SYSTEM_TIMER		H816TU0

#define SYSTEM_TIMER_CNT	(SYSTEM_TIMER + H8TCNT)
#define SYSTEM_TIMER_TCR	(SYSTEM_TIMER + H8TCR)
#define SYSTEM_TIMER_TIOR	(SYSTEM_TIMER + H8TIOR)
#define SYSTEM_TIMER_IER	H816TU_TISRA
#define SYSTEM_TIMER_IFR	H816TU_TISRA
#define SYSTEM_TIMER_TSTR	H816TU_TSTR
#define SYSTEM_TIMER_GR		(SYSTEM_TIMER + H8GRA)

#define SYSTEM_TIMER_STR	H8TSTR_STR0
#define SYSTEM_TIMER_STR_BIT	H8TSTR_STR0_BIT
#define SYSTEM_TIMER_IE		H8TISRA_IMIEA0		/* interrupt mask */
#define SYSTEM_TIMER_IE_BIT	H8TISRA_IMIEA0_BIT
#define SYSTEM_TIMER_IF		H8TISRA_IMFA0		/* match flag */
#define SYSTEM_TIMER_IF_BIT	H8TISRA_IMFA0_BIT

#define INHNO_TIMER		IRQ_IMIA0

#define SYSTEM_TIMER_TCR_BIT	(H8TCR_CCLR0 | H8TCR_TPSC1 | H8TCR_TPSC0)
#define SYSTEM_TIMER_TIOR_BIT	(0)

#define TIMER_CLOCK		((CPU_CLOCK)/8000)	/* 20MHz / 8 = 2.5MHz = 2500KHz */

/*
 *  �������ɥ쥹��������
 */

#define	ENABLE_P8_CS		(H8P8DDR_CS0|H8P8DDR_CS1|H8P8DDR_CS2|H8P8DDR_CS3)

#if 0

#define	ENABLE_LOWER_DATA
#define	ENABLE_PB_CS		(H8PADDR_CS4|H8PADDR_CS5|H8PADDR_CS6|H8PBDDR_CS7)

#endif	/* of #if 0 */

#endif /* _SYS_CONFIG_H_ */
