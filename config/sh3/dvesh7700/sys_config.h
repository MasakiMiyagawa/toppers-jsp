/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ�
 *  �եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�����
 *  �ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�������Х��ʥꥳ���ɤη��ޤ��ϵ�����Ȥ߹����������
 *      �Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (3) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: sys_config.h,v 1.2 2001/02/23 21:14:08 honda Exp $
 */


#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_


/*
 *  ��ư��å������Υ������å�̾
 */
#define	TARGET_NAME	"DVESH7700"

/*
 *  vxget_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_VXGET_TIM

/*
 *  ����å���⡼�ɤ�����
 *  P0,U0,P1�饤�ȥ��롼�⡼��
 */
#define CCR_MODE      0x00000003  


/*
 *  JSP�����ͥ�ư����Υ���ޥå� 
 *      0c000000 - 0c000fff     stub������ꥢ
 *      0c001000 - 0c080000     �������ΰ�(��0.5MB)
 *      0c080000 -              �ǡ����ΰ�(��0.5MB)
 *               - 0c0fffff     ��������Ω���ѥ����å� ���꽪λ
 *
 */

/*
 *   �����å��ΰ�����
 */
#define STACKTOP    0x0c100000    /* ��������Ω���ѥ����å��ν���� */   

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
 *  �ץ��å����̤Τ�����ѿ��ʥޥ���ץ��å��б���
 */
extern INT	board_id;	/* �ܡ���ID */
extern INT	board_addr;	/* ������������Ƭ���ɥ쥹 */



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
 *
 */

extern void sys_putc(char c);



/*
 *  SCIF,SCI,TMU��������
 *  Not yet!
 */

#ifdef CONFIG_30MHZ

/*
 *  16MHz / (3 + 1) /32 = 115200bps
 */
#define SCI_BPS_VALUE 3

#else  /* CONFIG_60MHZ */

/*
 * 30MHz / (7 + 1) /32 = 115200bps
 */
#define SCI_BPS_VALUE 7

#endif


/*
 *  DVESH7700�� 
 *  �⡼��7 I:B:P 1:1:1/2 ��ư��
 *  �������ͤ�����ɽ���� msec ñ�̤Ȥ��Ѵ�
 *  P = 15Mhz I = 30MHz
 *  /4:  3.75Mhz       tick 3750   0.266 ��sec 
 *  /16: 0.9375Mhz     tick 938    1.066 ��sec  X
 *  /64: 0.234375Mhz   tick 234    4.266 ��sec
 *  /256:0.0585Mhz     tick 58     17.09 ��sec
 *
 *  P = 30MHz I = 30MHz
 *  /4:  7.5Mhz     tick 7500   0.133 ��sec 
 *  /16: 1.875Mhz   tick 1875   0.533 ��sec X
 *  /64: 0.469Mhz   tick 469    2.133 ��sec
 *  /256:0.117Mhz   tick 117    8.545 ��sec
 *
 *
 * YDC DU
 *  P = 7.5MHz I = 15MHz
 *  /4:   1.875Mhz      tick 1875   0.532 ��sec X
 *  /16:  0.468Mhz      tick 468    2.132 ��sec
 *  /64:  0.117Mhz      tick 117    8.532 ��sec
 *  /256: 0.029Mhz      tick 29     34.18 ��sec
 *
 * YDC DU
 *  P = 3.75MHz I = 15MHz
 *  /4:   0.937Mhz       tick 937   1.067 ��sec X
 *  /16:  0.234Mhz       tick 234   4.273 ��sec
 *  /64:  0.0585Mhz      tick 59    17.09 ��sec
 *  /256: 0.0146Mhz      tick 15    68.49 ��sec
 *
 *  TMU�Υ���å��ξ�¤�2Mhz�ʤΤ�/16��ư����?
 */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */

#ifdef CONFIG_15MHZ

/*
 *   P/4�ǥ������
 */
#define TCR0_TPSC   0x0000
#define TIMER_CLOCK 937

#elif CONFIG_30MHZ

/*
 *   P/16�ǥ������
 */
#define TCR0_TPSC   0x0001
#define TIMER_CLOCK 1875

#elif CONFIG_60MHZ

/*
 *   P/16�ǥ������
 */
#define TCR0_TPSC   0x0001
#define TIMER_CLOCK 1875

#endif


#endif /* _MACRO_ONLY */
#endif /* _SYS_CONFIG_H_ */




