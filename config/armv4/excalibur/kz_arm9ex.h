/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: kz_arm9ex.h,v 1.4 2003/12/01 06:29:15 honda Exp $
 */

/*
 *   ���ԥޥ�������ԥ塼����KZ-ARM9EX�Ѥ����
 *   sys_config.h���饤�󥯥롼�ɤ����
 */

#ifndef _KZ_ARM9EX_H_
#define _KZ_ARM9EX_H_

/*
 *  ��ư��å������Υ������åȥ����ƥ�̾
 */
#define    TARGET_NAME    "KZ-ARM9EX, Excalibur-ARM(ARM922T)"


/*
 *  JSP�����ͥ�ư����Υ���ޥåפȴ�Ϣ�������
 *
 *  �����ƥ����ޥå�
 *
 *  SRAM0   : 0x00000000 - 0x0000ffff   (64kbyte)
 *  SRAM1   : 0x00010000 - 0x0001ffff   (64kbyte)
 *  DPSRAM0 : 0x00100000 - 0x00107fff   (32kbyte)
 *  DPSRAM1 : 0x00108000 - 0x0010ffff   (32kbyte)
 *  SDRAM0  : 0x10000000 - 0x0bffffff   (64Mbye)
 *
 *  JSP�Ǥγ������
 *  0x00000000 - 0x0000ffff �������ΰ�(64Kbyte)
 *  0x00010000 -            �ǡ����ΰ�(64Kbyte)
 *             - 0x0001ffff ��������Ω�������å�
 *  0x10000000 -            PLD����ե�����졼�����ǡ���(��1Mbyte)
 */

#define   STACKTOP 0x00020000   /* �󥿥�������ƥ������ѤΥ����å��ν���� */

/*
 *  ���꡼�ޥåפ������Ԥ���
 */
//#define EXCALIBUR_MEMMAP_INIT

/*
 *  Memmory Map Control Registe ��������
 */
#define MMAP_SRAM0_VAL    0x00000781
#define MMAP_SRAM1_VAL    0x00010781
#define MMAP_DPSRAM0_VAL  0x00100701
#define MMAP_DPSRAM1_VAL  0x00108701
//#define MMAP_SDRAM0_VAL   
//#define MMAP_SDRAM1_VAL
#define MMAP_EVI0_VAL     0x40000A83
#define MMAP_EVI1_VAL     0x50000c03
//#define MMAP_EVI2_VAL
//#define MMAP_EVI3_VAL
//#define MMAP_PLD0_VAL
//#define MMAP_PLD1_VAL
//#define MMAP_PLD2_VAL
//#define MMAP_PLD3_VAL



/*
 * PLL�ν������Ԥ���
 */
#define EXCALIBUR_PLL_INIT

/*
 * PLL��Ϣ��������
 */
#define CLK_PLL1_NCNT_VAL   0x40000
#define CLK_PLL1_MCNT_VAL   0x20404
#define CLK_PLL1_KCNT_VAL   0x40000
#define CLK_PLL2_NCNT_VAL   0x40000
#define CLK_PLL2_MCNT_VAL   0x10807
#define CLK_PLL2_KCNT_VAL   0x10201

/* 
 * ����ե�����졼����󥯥�å�����
 * AHB2_CLOCK /( X * 2 )
 * 16Mhz�ʲ��ˤʤ�褦�����ꤹ�롥
 */
#define CONFIG_CLOCK_DATA  4
//#define CONFIG_CLOCK_DATA  3


/*
 *   CPU�˶��뤹�륯��å����ԡ���(sys_config.S��PLL�ν�����Ȥ��碌�롥)
 */
#define AHB1_CLK             132000000

/*
 *    Stripe�Υ١������ɥ쥹
 */
#define EXCALIBUR_DEV_BASE   0x7fffc000

/*
 * UART�γ����ߥ�٥�
 */
#define INTLV_UART        5

/*
 *  UART�Υܡ��졼��
 */
#define UART_BPS      115200

/*
 *  UART�Υǡ����ե����ޥåȡ�UART_MC�ؤ������͡�
 */
#define UART_DATA_FOMAT 0x03

/*
 *  �����ޡ��γ����ߥ�٥�
 */
#define INTLV_TIM0        4


/*
 *  �������ͤ�����ɽ���ȥߥ���ñ�̤Ȥ��Ѵ�
 */
#define TIMER_CLOCK          66000


/*
 *  ����å����Ϣ������
 */

/* 
 * ����å�������� CP5 No.1 �˽񤭹����� 
 * ICache �Τ�ON
 */
#define CP5_NO1_VAL         0x1078


/*
 *  �ץ��å��Υ���ǥ�����
 */
#define SIL_ENDIAN  SIL_ENDIAN_LITTLE  /* ��ȥ륨��ǥ����� */

#endif /* _KZ_ARM9EX_H_ */



 

