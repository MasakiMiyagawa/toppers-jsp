/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: sys_config.h,v 1.2 2001/10/22 02:16:43 imai Exp $
 */


#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#ifndef OMIT_RENAME

#define board_id		_kernel_board_id
#define board_addr		_kernel_board_addr

#ifdef LABEL_ASM

#define _board_id		__kernel_board_id
#define _board_addr		__kernel_board_addr

#endif /* LABEL_ASM */
#endif /* OMIT_RENAME */

/*
 *  ��ư��å������Υ������å�̾
 */
#define	TARGET_NAME	"KMC KZ-SH1-01"

/*
 *  vxget_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_VXGET_TIM

/*
 *  JSP�����ͥ�ư����Υ���ޥå�
 *      0x0000,0000 - 0x0004,0000  �������ΰ�(256KB)
 *      0x0a00,0000 -              �ǡ����ΰ�(256KB)
 *                  - 0x0a03,ffff  ��������Ω���ѥ����å� ���꽪λ
 *
 */

/*
 *   �����å��ΰ�����
 *	��������Ω���ѥ����å��ν����
 */


#define STACKTOP    	 0x0a03fffc
#define str_STACKTOP	_TO_STRING(STACKTOP)


/*
 *  ���ꥢ������ߤ�����/���Ϥǰۤʤ뤫�ɤ��������
 *  	���Υޥ�������������������ǳ���ߥϥ�ɥ餬�ۤʤ�
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
 *  �����ƥ��λ������˻Ȥ���
 */
extern void	sys_exit(void);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����
 *
 */

extern void sys_putc(char c);



/*
 *  SCI������
 *  	���ԥޥ�������ԥ塼��KZ-SH1-01�Υ���å����ȿ���20MHz
 *  	CQ���� RISCɾ�����å� SH-1�Υ���å����ȿ���19.6608MHz
 */

/*
 *  ʬ����ȥӥåȥ졼�Ȥ�����
 *
 *  ����å�	��19.6608MHz
 *  �ӥåȥ졼�ȡ�9600bps
 *
 *  ��N = CLOCK*10^6 / (64*2^(2n-1)*BPS) - 1
 *  ���
 *  ��n=0(ʬ�����ʤ��ΤǤ��Τޤ�)
 *  ��N=63�Ǹ�0%
 *  ��äơ�
 *  �����ꥢ��⡼�ɥ쥸����SMR�Υ���å����쥯�ȥӥå�CKS=00
 *  ���ӥåȥ졼�ȥ쥸����BRR=63
 */
#ifdef CONFIG_19MHZ
#define SMR_CKS 	0x0	/*  ʬ����  		*/
#define SCI_BRR 	63	/*  �ӥåȥ졼��  	*/
#endif

/*
 *  ����å�	��20MHz�ξ��
 *  �ӥåȥ졼�ȡ�9600bps
 *
 *  ��n=0(ʬ�����ʤ��ΤǤ��Τޤ�)
 *  ��N=64�Ǹ�0.16%
 *  ��äơ�
 *  �����ꥢ��⡼�ɥ쥸����SMR�Υ���å����쥯�ȥӥå�CKS=00
 *  ���ӥåȥ졼�ȥ쥸����BRR=64
 */
#ifdef CONFIG_20MHZ
#define SMR_CKS 	0x0	/*  ʬ����  		*/
#define SCI_BRR 	64	/*  �ӥåȥ졼��  	*/
#endif


/*
 *  �ǽ��1�ӥå�ʬ���Ԥ����֤�����
 *  ����å�20MHz�ξ����ͤ�ή��
 *  �롼��1����դ�5̿��ʡ�5����å���
 *  ��N = CLOCK*10^6 / (5*BPS)
 *  ���
 *  ��N=417��
 *  �ޡ�����������
 *  ��N=450��
 */
#define WAIT_TIME 	450


/*
 *  ITU������
 */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */

/*
 *   �����ޤؤ����ϥ���å���ʬ��������
 *   	f/8�ǥ������
 */
#define TCR_TPSC	0x3

/*
 *   �����ޤ˶��뤵��륯��å����ȿ�[kHz]
 *   	19.6608MHz/8 =2.4576MHz =2457.6kHz
 */
#ifdef CONFIG_19MHZ
#define TIMER_CLOCK	2458
#endif

/*   	20MHz/8 =2.5MHz =2500kHz	*/
#ifdef CONFIG_20MHZ
#define TIMER_CLOCK	2500
#endif


#endif /* _MACRO_ONLY */
#endif /* _SYS_CONFIG_H_ */
