/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cpu_config.c,v 1.5 2002/04/10 11:08:18 hiro Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���M68040�ѡ�
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

/*
 *  ����������ƥ����ȤǤγ���ߥޥ���
 */
#ifdef SUPPORT_CHG_IPM
UH	task_intmask;
#endif /* SUPPORT_CHG_IPM */

/*
 *  �󥿥�������ƥ����ȤǤγ���ߥޥ���
 */
UH	int_intmask;

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
	 *  �㳰�٥����ơ��֥�ν����
	 */
#ifdef EXCVT_KERNEL
	memcpy(EXCVT_KERNEL, EXCVT_ORIG, EXCVT_LEN);
	set_vbr(EXCVT_KERNEL);
#endif /* EXCVT_KERNEL */
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
 *  chg_ipm ��Ȥä� IPM �� 7��NMI �ʳ��Τ��٤Ƥγ���ߤ�ػߡˤ��ѹ�
 *  ���뤳�ȤϤǤ��ʤ���NMI �ʳ��Τ��٤Ƥγ���ߤ�ػߤ��������ˤϡ�
 *  loc_cpu �ˤ��CPU��å����֤ˤ���Ф褤��
 *  IPM �� 0 �ʳ��λ��ˤ⡤�������ǥ����ѥå�����α����ʤ���IPM �ϡ�
 *  �������ǥ����ѥå��ˤ�äơ��������¹Ծ��֤ˤʤä��������ذ����Ѥ�
 *  ��롥���Τ��ᡤ���������¹���ˡ��̤Υ������ˤ�ä� IPM ���ѹ���
 *  ����礬���롥JSP�����ͥ�Ǥϡ�IPM ���ѹ��ϥ������㳰�����롼��
 *  ��ˤ�äƤⵯ����Τǡ�����ˤ�äư������񤷤��ʤ�����Ͼ��ʤ���
 *  �פ��롥IPM ���ͤˤ�äƥ������ǥ����ѥå���ػߤ��������ˤϡ�
 *  dis_dsp ��ʻ�Ѥ���Ф褤��
 */
SYSCALL ER
chg_ipm(IPM ipm)
{
	CHECK_TSKCTX_UNL();
	CHECK_PAR(0 <= ipm && ipm <= 6);

	t_lock_cpu();
	task_intmask = (ipm << 8);
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
	*p_ipm = (task_intmask >> 8);
	t_unlock_cpu();
	return(E_OK);
}

#endif /* SUPPORT_CHG_IPM */
