/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: cpu_config.c,v 1.5 2002/04/11 11:30:20 imai Exp $
 */


#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

#include "sh1.h"

/*
 *  �ץ��å���¸�⥸�塼���SH1�ѡ�
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
 *  ����ߡ�CPU�㳰�ͥ��ȥ�����
 */
UW	intnest;


/*
 *  �㳰�٥����ơ��֥�
 */
#ifdef EXCVT_KERNEL
EXCVE BASE_VBR[EXCVT_SIZE];
#endif	/*  EXCVT_KERNEL  */


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
	task_intmask = 0x0000;
#endif /* SUPPORT_CHG_IPM */

	/*
	 *  ����ߡ�CPU�㳰�ͥ��ȥ����󥿤ν����
	 */
	intnest = 1;

#ifndef WITH_STUB

	/*
	 * �����ߥ���ȥ���ν����
	 */
	*IPRA = 0x0000;
	*IPRB = 0x0000;
	*IPRC = 0x0000;
	*IPRD = 0x0000;
	*IPRE = 0x0000;

#endif	/*  WITH_STUB  */

#ifndef CQ_SH1_DEB
#ifdef EXCVT_KERNEL
	/*
	 *  �٥����ơ��֥�ν����
	 */
	memcpy(EXCVT_KERNEL, EXCVT_ORIG, EXCVT_SIZE*sizeof(VP));
	
	/*
	 *  �٥����١����쥸�����ν����
	 */
	set_vbr(EXCVT_KERNEL);
#endif /* EXCVT_KERNEL */
#endif /* CQ_SH1_DEB */

}



/*
 *  �ץ��å���¸�ν�λ����
 */
void
cpu_terminate()
{
#ifdef EXCVT_KERNEL
	set_vbr(EXCVT_ORIG);
#endif /* EXCVT_KERNEL */
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


/*
 * ��Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
void cpu_experr(EXCSTACK *sp)
{
    syslog(LOG_EMERG, "Exception error occurs.");

    syslog(LOG_EMERG, "PC = %08x SR = %08x PR = %08x",
    			sp->pc, sp->sr, sp->pr);

    syslog(LOG_EMERG, "r0 = %08x r1 = %08x r2 = %08x",
    			sp->r0, sp->r1, sp->r2);
    syslog(LOG_EMERG, "r3 = %08x r4 = %08x r5 = %08x",
    			sp->r3, sp->r4, sp->r5);
    syslog(LOG_EMERG, "r6 = %08x r7 = %08x r8 = %08x",
    			sp->r6, sp->r7, sp->r8);
    syslog(LOG_EMERG, "r9 = %08x r10 = %08x r11 = %08x",
    			sp->r9, sp->r10, sp->r11);
    syslog(LOG_EMERG, "r12 = %08x r13 = %08x r14 = %08x",
    			sp->r12, sp->r13, sp->r14);
    			/*  �㳰ȯ��ľ���Υ����å��ݥ��󥿤���  */
    syslog(LOG_EMERG, "r15 = %08x", (sp->r15)+19*4);

    while(1);
}


/*
 *  ����֥�å����饤�֥��
 *	(ItIs�����ή��)
 *
 *  �ؿ��λ��ͤϡ�ANSI C �饤�֥��λ��ͤ�Ʊ����ɸ��饤�֥��Τ�Τ�
 *  �Ȥä�������Ψ���ɤ���ǽ�������롥
 *
 */
VP
_dummy_memcpy(VP dest, VP src, UINT len)
{
	VB	*d = dest;
	VB	*s = src;

	while (len-- > 0) {
		*d++ = *s++;
	}
	return(dest);
}
