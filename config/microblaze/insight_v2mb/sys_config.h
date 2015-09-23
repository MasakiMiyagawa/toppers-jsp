/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: sys_config.h,v 1.1 2002/04/05 08:47:14 honda Exp $
 */

/*
 *	�������åȥ����ƥ��¸�⥸�塼���Insight VirtexII�ѡ�
 */

#ifndef _SYS_CONFIG_H_
#define _SYS_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#ifndef OMIT_RENAME

#ifdef LABEL_ASM

#endif /* LABEL_ASM */
#endif /* OMIT_RENAME */

/*
 *  ��ư��å������Υ������å�̾
 */
#define	TARGET_NAME	"INSIGHT VIRTEXII(Microblaze)"

/*
 *  ����ե�����졼������¸�����
 */
/*
 *  JSP�����ͥ�ư����Υ���ޥå�
 *  ������¡�Υ֥�å�RAM 
 *      0x0400 - 0x7fff   �������ΰ�(��32KB)
 *      0x8000 -          �ǡ����ΰ�(32KB)
 *             - 0xffff   ��������Ω���ѥ����å�
 *             - 0x10000  ���꽪λ
 *
 */

/*
 *   �����å��ΰ�����
 */                 
#define STACKTOP    0x10000    /* ��������Ω���ѥ����å��ν���� */

/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK		24000

/*
 *  INTC �Υ١������ɥ쥹
 */
#define INTC_BASE 0xFFFF1000

/*
 *  TIMER �Υ١������ɥ쥹
 */
#define TIMER_BASE 0xFFFF0000   

/*
 * �����ͥ�ǻ��Ѥ��� UART �Υ١������ɥ쥹
 */
#define UART_BASE 0xFFFF8100


/*
 *  TIM ����ߤγ�����ֹ�
 */
#define TIMINTLVL        1


/*
 * UART ����ߤγ�����ֹ�
 */
#define UARTINTLVL 2



/*
 *  �����ƥॿ�����˴ؤ������
 */
#define	CONSOLE_PORTID	1	/* ���󥽡����Ѥ��Ѥ��륷�ꥢ��ݡ����ֹ� */
#define	LOGTASK_PORTID	1	/* �����ƥ������Ϥ��륷�ꥢ��ݡ����ֹ� */


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
                        
/*
 *  LCD�ɥ饤��
 */
extern void lcd_init(void);
extern void lcd_write_string(char *string);
extern BOOL lcd_set_cur_posi(int row, int col);

#endif /* _MACRO_ONLY */
#endif /* _SYS_CONFIG_H_ */




