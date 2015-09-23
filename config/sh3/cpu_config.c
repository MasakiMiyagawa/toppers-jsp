/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cpu_config.c,v 1.1 2000/11/14 16:29:53 honda Exp $
 */


#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

#include "sh3.h"

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
FP  int_table[0x99];
VW  int_plevel_table[0x99];

/*
 * CPU�㳰�ϥ�ɥ�ε����ơ��֥�
 */
FP	exc_table[0x1E];

/*
 *  �ץ��å���¸�ν����
 */
void
cpu_initialize()
{
    INT i;

    /*
     *  ����������ƥ����ȤǤγ���ߥޥ����ν����
     */
#ifdef SUPPORT_CHG_IPM
    task_intmask = 0x0000;    
#endif /* SUPPORT_CHG_IPM */

#ifndef WITH_STUB
    /*
     * �����ߥ���ȥ���ν���� 
     */
    *ICR0 = 0x0000;     
    *ICR1 = 0x0000;
    *ICR2 = 0x0000;     
    *PINTER = 0x0000;     
    *IPRA = 0x0000;     
    *IPRB = 0x0000;
    *IPRC = 0x0000;
    *IPRD = 0x0000;
    *IPRE = 0x0000;
    *IRR0 = 0x0000;   
    *IRR1 = 0x0000;
    *IRR2 = 0x0000;
    
    /*
     *  �٥����١����쥸�������ν����
     */
    set_vbr(BASE_VBR);
#endif

    /*
     *  �����ߥϥ�ɥ�/ͥ���ٵ����ơ��֥�ν����
     */
    for(i = 0; i < 0x99; i++){
        int_table[0x99] = 0;
        int_plevel_table[0x99]  = 0;
    }
    
    /*
     *  CPU�㳰�����٥����ơ��֥�ν����
     */
    for(i = 0; i < 0x1E; i++){
        exc_table[i] = 0;
    }
    
}



/*
 *  �ץ��å���¸�ν�λ����
 */
void
cpu_terminate()
{
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


            
/*
 * Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
void cpu_expevt(VW expevt,VW spc,VW ssr,VW pr)
{
    syslog(LOG_EMERG, "Expevt error occurs.");

    syslog(LOG_EMERG, "Expevt = %08x SPC = %08x SR = %08x PR=%08X",expevt,spc,
             ssr,pr);
    while(1);
    exit();
}



#endif /* SUPPORT_CHG_IPM */








