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
 *  @(#) $Id: cpu_config.c,v 1.13 2001/11/05 13:31:13 honda Exp $
 */


#include "jsp_kernel.h"
#include "check.h"
#include "task.h"
#include "sys_defs.h"

#if defined(SH7750)
#include "sh4.h"
#else   
#include "sh3.h"
#endif /* SH7750 */
/*
 *  �ץ��å���¸�⥸�塼���SH3�ѡ�
 */

/*
 *  ����������ƥ����ȤǤγ���ߥޥ���
 */
#ifdef SUPPORT_CHG_IPM
UW	task_intmask;
#endif /* SUPPORT_CHG_IPM */

/*
 *  �󥿥�������ƥ����ȤǤγ���ߥޥ���
 */
UW	int_intmask;


/*
 * �����ߥϥ�ɥ�/ͥ���٤ε����ơ��֥�
 */
FP  int_table[0x50];
VW  int_plevel_table[0x50];

/*
 * CPU�㳰�ϥ�ɥ�ε����ơ��֥�
 */
FP	exc_table[(0x1E0 >> 5) + 1];

/*
 *  �ץ��å���¸�ν����
 */
void
cpu_initialize()
{
    int i;
    
    /*
     *  ����������ƥ����ȤǤγ���ߥޥ����ν����
     */
#ifdef SUPPORT_CHG_IPM
    task_intmask = 0x0000;    
#endif /* SUPPORT_CHG_IPM */
    
    /*
     * int_table[],int_plevel_table[]�ν����
     * ̤��Ͽ�γ����ȯ������cpu_interrup()���ƤӽФ����褦��
     * no_reg_interrup()����Ͽ����
     */
    for(i = 0; i < 0x50; i++){
        int_table[i] = no_reg_interrupt;
        int_plevel_table[i] = 0x400000f0;
    }
    
#ifndef GDB_STUB
    /*
     * �����ߥ���ȥ���ν���� 
     */
#if defined(SH7750)
    *ICR  = 0x0000;
    *IPRA = 0x0000;
    *IPRB = 0x0000;
    *IPRC = 0x0000;
#else /* SH7708 || SH7709 || SH7709A */   
    *ICR0 = 0x0000;
    *IPRA = 0x0000;     
    *IPRB = 0x0000;
#if defined(SH7709) || (SH7709A)    
    *ICR1 = 0x4000;
    *ICR2 = 0x0000;     
    *PINTER = 0x0000;
    *IPRC = 0x0000;
    *IPRD = 0x0000;
    *IPRE = 0x0000;
    *IRR0 = 0x0000;   
    *IRR1 = 0x0000;
    *IRR2 = 0x0000;
#endif /* SH7709 || SH7709A  */   
#endif /* SH7750 */
    
    /*
     *  �٥����١����쥸�������ν����
     */
    set_vbr(BASE_VBR);
    
#endif /* GDB_STUB */

    
}



/*
 *  �ץ��å���¸�ν�λ����
 */
void
cpu_terminate()
{
}


/*
 * Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
void
cpu_expevt(VW expevt,VW spc,VW ssr,VW pr)
{
    syslog(LOG_EMERG, "Unregistered Expevt error occurs.");
    syslog(LOG_EMERG, "Expevt = %08x SPC = %08x SR = %08x PR=%08X",
           expevt,spc,ssr,pr);
    while(1);
}

/*
 * ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
void
cpu_interrupt(VW intevt, VW intevt2,VW spc,VW ssr)
{
    syslog(LOG_EMERG, "Unregistered Interrupt occurs.");
#if defined(SH7709) || defined(SH7709A)
    syslog(LOG_EMERG, "INTEVT = %08x INTEVT2 = %08x SPC = %08x SR = %08x ",
           intevt,intevt2,spc,ssr);
#else    
    syslog(LOG_EMERG, "INTEVT = %08x  SPC = %08x SR = %08x ",intevt,spc,ssr);
#endif    
    while(1);
}



#ifdef SUPPORT_CHG_IPM

/*
 *  ����ߥޥ������ѹ�
 *
 *  chg_ipm ��Ȥä� IPM �� MAX_IPM ��NMI �����֥�⡼�ȥ֥졼�� �ʳ�
 *  �Τ��٤Ƥγ���ߤ�ػߡ˰ʾ���ѹ����뤳�ȤϤǤ��ʤ���NMI �����֥�
 *  �⡼�ȥ֥졼���ʳ��Τ��٤Ƥγ���ߤ�ػߤ��������ˤϡ�loc_cpu ��
 *  ���CPU��å����֤ˤ���Ф褤��IPM �� 0 �ʳ��λ��ˤ⡤�������ǥ���
 *  �ѥå�����α����ʤ���IPM �ϡ��������ǥ����ѥå��ˤ�äơ���������
 *  �Ծ��֤ˤʤä��������ذ����Ѥ���롥���Τ��ᡤ���������¹���ˡ���
 *  �Υ������ˤ�ä� IPM ���ѹ�������礬���롥JSP�����ͥ�Ǥϡ�IPM
 *  ���ѹ��ϥ������㳰�����롼����ˤ�äƤⵯ����Τǡ�����ˤ�äư�
 *  �����񤷤��ʤ�����Ͼ��ʤ��Ȼפ��롥IPM ���ͤˤ�äƥ������ǥ���
 *  �ѥå���ػߤ��������ˤϡ�dis_dsp ��ʻ�Ѥ���Ф褤��
 */

SYSCALL ER
chg_ipm(IPM ipm)
{
	CHECK_TSKCTX_UNL();
	CHECK_PAR(0 <= ipm && ipm <= MAX_IPM - 1);

	t_lock_cpu();
	task_intmask = (ipm << 4);
	t_unlock_cpu();
	return(E_OK);
}

/*
 *  ����ߥޥ����λ���
 */
SYSCALL ER
get_ipm(IPM *p_ipm)
{
	CHECK_TSKCTX_UNL();

	t_lock_cpu();
	*p_ipm = (task_intmask >> 4);
	t_unlock_cpu();
	return(E_OK);
}


            



#endif /* SUPPORT_CHG_IPM */








