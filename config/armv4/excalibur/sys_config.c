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
 *  @(#) $Id: sys_config.c,v 1.6 2003/12/11 00:44:27 honda Exp $
 */

/*
 *    �������åȥ����ƥ��¸�⥸�塼���Excalibur-ARM�ѡ�
 */

#include "jsp_kernel.h"
#include <excalibur.h>



/*
 * ����ߥϥ�ɥ���Ͽ�ѥơ��֥�
 */
FP   int_table[MAX_INT_NUM];
UW   int_mask_table[MAX_INT_NUM];

/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
    int i;
  
    /*
     *  ����ߥơ��֥�ν����
     */
    for(i = 0; i < MAX_INT_NUM; i++){
        int_table[i] = 0x00;        /* �ꥻ�å� */
        int_mask_table[i] = 0x1ffff;   /* ������߶ػ� */
    }

    /*
     *  ARM�Υ٥����ơ��֥�س���ߥϥ�ɥ����Ͽ
     */
    arm_install_handler(IRQ_Number,IRQ_Handler);
  
    /*
     *  ����ߥ���ȥ���ν����
     */
    sil_wrw_mem((VP)INT_MASK_CLEAR,0x1ffff);     /* ���Ƥγ���ߤ�ػ� */
    sil_wrw_mem((VP)INT_MODE,INT_MODE_SII);      /* ����ߥ⡼�ɤ����� */
 
    /*
     *  sys_putc ����ǽ�ˤʤ�褦��UART������
     */
    uart_init();
}


/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit(void)
{
#ifdef GDB_STUB
    stub_exit();
#else  /* WITH_OUT_GDB_STUB */
    syslog(LOG_EMERG, "End Kernel.....!");
    while(1);
#endif /* GDB_STUB */  
}




/*
 *  �������åȥ����ƥ��ʸ������
 */
void
sys_putc(char c)
{
#ifdef GDB_STUB  
    if (c == '\n') {
        stub_putc('\r');
    }
    stub_putc(c);
#else
    if (c == '\n') {
        uart_putc('\r');
    }
  uart_putc(c);  
#endif /* GDB_STUB */  
}


/*
 *  ����ߥϥ�ɥ������
 *
 *  ������ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
void
define_inh(INHNO inhno, FP inthdr)
{
    assert(inhno < MAX_INT_NUM);
    int_table[inhno] = inthdr;
#ifdef GDB_STUB  
    /*  
     * GDB Stub����Ͽ���ơ�������ȯ�����˸ƤФ��褦�ˤ��롥
     */
    stub_set_inh(inhno,IRQ_Handler);
#endif /* GDB_STUB */  
}


/*
 * ����ߥϥ�ɥ鵯ư���˳���ߥ���ȥ��顼�˥��åȤ���ޥ����ͤ����ꡥ
 */
void
define_inh_mask(INHNO inhno, UW mask)
{
    assert(inhno < MAX_INT_NUM);
    int_mask_table[inhno] = mask;
}


/*
 *  ̤����γ���ߤ����ä����ν���
 */
void
undef_interrupt(){
    syslog(LOG_EMERG, "Unregistered Interrupt occurs.");
    while(1);
}
