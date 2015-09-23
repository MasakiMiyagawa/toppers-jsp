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
 *  (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ���������֥륪��
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
 *  @(#) $Id: cpu_config.c,v 1.5 2001/11/09 12:08:54 honda Exp $
 */

/*
 *	�ץ����å���¸�⥸�塼���ARM7TDMI�ѡ�
 */

#include "jsp_kernel.h"
#include "check.h"
#include "arm7tdmi.h"
#include "evaluator7t.h"

/*
 * �㳰�٥����˽񤭹��ޤ줿������̿�᤬���Ȥ��륢�ɥ쥹
 * 
 */
UW *arm_vector_add[8];


/*
 * �㳰�˱������ϥ�ɥ�ε�ư����
 */
UW arm_handler_add[8];


/*
 * �����ߤΥͥ��Ȳ���Υ������
 */
UW interrupt_count = 1;


/*
 * CPU/����ߥϥ�ɥ�ν����������ǰ��Ū�˻��Ѥ��륹���å�
 */
UW int_stack[INT_STACK_SIZE];


/*
 *  CPU�㳰�ϥ�ɥ������
 */

void
define_exc(EXCNO excno, FP exchdr)
{
    arm_install_handler(excno,exchdr);
}


/*
 *  �ץ����å���¸�ν����
 */
void
cpu_initialize()
{

    UW i,vector_value;
    /*
     * �㳰�٥�������Ͽ����Ƥ���̿�ᤫ�黲�Ȥ���륢�ɥ쥹�ȡ�
     *���Υ��ɥ쥹������(�ϥ�ɥ�μ¹���)����¸���롥
     */
    for(i = 0; i <=7; i++){
        vector_value = *(volatile UW *)(i*4);
        vector_value &= 0x00000fff;
        arm_vector_add[i] = (UW *)(vector_value + 8) + i;
        arm_handler_add[i] = *arm_vector_add[i];
    }
}


/*
 *  �ץ����å���¸�ν�λ����
 */
void
cpu_terminate()
{
    UW i;
    /*  �٥����ơ��֥�򸵤��᤹��*/
    for(i = 0; i <=7; i++)
        *arm_vector_add[i] = arm_handler_add[i];
}






    
    
    
    