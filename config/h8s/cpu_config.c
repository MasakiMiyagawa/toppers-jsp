/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
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
 *  @(#) $Id: cpu_config.c,v 1.2 2002/04/13 13:14:45 imai Exp $
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

/*
 * �ץ��å���¸�⥸�塼��(H8S��)
 */

/*
 *  ����������ƥ����ȤǤγ���ߥޥ���
 */
#ifdef SUPPORT_CHG_IPM
IPM	task_intmask;   /* IPM -> UB�����̵��8�ӥå� */
#endif /* SUPPORT_CHG_IPM */


/*
 * �󥿥�������ƥ����ȤǤγ���ߥޥ���
 */

IPM	int_intmask;

/*
 *  ����ߥͥ��ȥ�����
 */

UW	intnest;

/*
 *  �ץ��å���¸�ν����
 */

void
cpu_initialize()
{
/*
 *  ����������ƥ����ȤǤγ���ߥޥ����ν����
 */
#ifdef SUPPORT_CHG_IPM
	task_intmask = 0x00;
#endif /* SUPPORT_CHG_IPM */

	/*
	 *  ����ߡ�CPU�㳰�ͥ��ȥ����󥿤ν����
	 */
       intnest = 1;

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
	task_intmask = ipm;
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
	*p_ipm = task_intmask;
	t_unlock_cpu();
	return(E_OK);
}


#endif /* SUPPORT_CHG_IPM */



/*
 * ��Ͽ����Ƥ��ʤ������ߤ�ȯ������ȸƤӽФ����
 */

void cpu_experr(EXCSTACK *sp)
{
    syslog(LOG_EMERG, "Unexpected interrupt.");
    syslog(LOG_EMERG, "PC  = %08x SP  = %08x", sp->pc, sp - 32);
    syslog(LOG_EMERG, "ER0 = %08x ER1 = %08x ER2 = %08x ER3 = %08x",
                       sp->er0, sp->er1, sp->er2, sp->er3);
    syslog(LOG_EMERG, "ER4 = %08x ER5 = %08x ER6 = %08x",
                       sp->er4, sp->er5, sp->er6);
    while(1);
}
