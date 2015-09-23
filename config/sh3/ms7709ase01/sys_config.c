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
 *  @(#) $Id: sys_config.c,v 1.11 2002/04/05 07:43:51 honda Exp $
 */


#include "jsp_kernel.h"
#include "ms7709ase01.h"
#include "sh3.h"


/*
 *  SMSC Super I/O (FDC37C935A)�ν����
 */
void
smsc_init()
{
    /*
     * Enter Config mode 
     */
    *SMSC_CONFIG_PORT = 0x55 << 8;
    *SMSC_CONFIG_PORT = 0x55 << 8;


    /*
     * Init SCI0
     */
    /* Power on */
    smsc_config_write(0x22, (smsc_config_read(0x22) | 0x10));
    /* Select SCI0 */
    smsc_config_write(0x07, 0x04);
    /* Enable SCI0 */
    smsc_config_write(0x30, 0x01);
    /* Set SCI0 Base Address */
    smsc_config_write(0x60, (SMSC_SCI0_BASE_ADDR & 0xff00) >> 8);
    smsc_config_write(0x61, (SMSC_SCI0_BASE_ADDR & 0xff));    
    /* IRQ4 */
    smsc_config_write(0x70, 0x04);

    

    /*
     *  Exit Config mode
     */
    *SMSC_CONFIG_PORT = 0xAA << 8;
}



/*
 *  �������åȥ����ƥ��¸ ������롼����
 */
void
sys_initialize()
{
    /* Enable IRL Interrupt */
    *ICR1 = 0x5000;

    /* Init Super I/O */
    smsc_init();

#ifndef GDB_STUB
    SCIF.SCSCR2 = 0;  /* SCIF�����,����P����å���Ȥ� */
    SCIF.SCFCR2 = SCFCR2_TFRST | SCFCR2_RFRST; /* ��������FIFO�򥯥ꥢ */
    SCIF.SCSMR2 = 0;         /* Async,8data,1stop,no parity */
    SCIF.SCBRR2 = SCIF_BPS_VALUE; /* �ܡ��졼�Ȥ����� */

    /*
     * �ܡ��졼�Ȥ�����塢1�������ʬ�Ԥ��ʤ���Фʤ�ʤ���
     * �Х����ơ��ȥ���ȥ���Υ�ե�å��奫���󥿤�Ȥ�
     * 1�������ʬ�Ԥ�
     */
    *RFCR = RFCR_CLEAR;
    while( *RFCR < WAIT_RFCR_FOR_SCI);
    
    SCIF.SCFCR2 = 0x30;           /* R-FIFO=1,T-FIFO=1 �ȥꥬ������ */
    SCIF.SCSSR2 = 0x0060;         /* ���顼�ե饰�򥯥ꥢ */
    SCIF.SCSCR2 = 0x30;           /* Start TE = 1 RE = 1  */
#endif /* GDB_STUB */
}


/*
 *  �������åȥ����ƥ�ν�λ�롼����
 *
 *  �����ƥ��λ������˻Ȥ����̾�ϥ�˥��ƤӽФ��Ǽ¸����롥
 *  
 */
void
sys_exit(void)
{
  Asm("trapa #0xff"::);
}

/*
 *   �����ƥ�ʸ��������λ���
 */

#ifdef GDB_STUB
#define SYS_PUT_CHAR(c) stub_putc(c)
#elif defined(PARTNER_J)
#define SYS_PUT_CHAR(c) partner_putc(c)
#else  /* ����¾ */
#define SYS_PUT_CHAR(c) scif_putc(c)
#endif 


void
sys_putc(char c)
{
    if (c == '\n') {
        SYS_PUT_CHAR('\r');
    }
    SYS_PUT_CHAR(c);
}

#ifdef PARTNER_J
char
partner_syscall(int callno, char put_char)
{
    char get_char = 0x00;
    Asm("mov %1, r0;\n"
        "mov %2, r2;\n"
        ".global _sysc_et;\n"
        "_sysc_et:;\n"
        "nop;\n"
        "mov r0,%0\n"
        : "=r"(get_char)
        : "r"(callno),"r"(put_char)
        : "r0","r2");
    return get_char;
}

void
partner_putc(char c)
{
    partner_syscall(PARTNER_OUT,c);
}
#endif /* PARTNER_J */


