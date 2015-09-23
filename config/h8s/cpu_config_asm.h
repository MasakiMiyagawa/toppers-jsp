 ;/*
 ;*  TOPPERS/JSP Kernel
 ;*      Toyohashi Open Platform for Embedded Real-Time Systems/
 ;*      Just Standard Profile Kernel
 ;*
 ;*  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 ;*                              Toyohashi Univ. of Technology, JAPAN
 ;*  Copyright (C) 2001,2002 by Dep. of Computer Science and Engineering
 ;*                   Tomakomai National College of Technology, JAPAN
 ;*  Copyright (C) 2001,2002 by Industrial Technology Institute,
 ;*                              Miyagi Prefectural Government, JAPAN
 ;*
 ;*  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ���
 ;*  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 ;*  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
 ;*  ������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 ;*  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 ;*  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 ;*      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 ;*      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 ;*  (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ�������֥륪��
 ;*      �������ȥե������饤�֥��ʤɡˤη������Ѥ�����ˤϡ�����
 ;*      ��ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ����
 ;*      �������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 ;*  (3) �ܥ��եȥ�������������Բ�ǽ�ʥХ��ʥꥳ���ɤη��ޤ��ϵ������
 ;*      �߹�����������Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 ;*    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 ;*        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 ;*    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 ;*        ���ȡ�
 ;*  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 ;*      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 ;*
 ;*  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 ;*  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 ;*  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 ;*  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 ;*
 ;*  @(#) $Id: cpu_config_asm.h,v 1.2 2002/04/13 13:14:45 imai Exp $
 ;*/

;/*
; *  �ץ��å���¸�⥸�塼��(H8S��)
; */

	.AIFDEF _CPU_CONFIG_H_
	.AELSE
_CPU_CONFIG_H_: .DEFINE " "

;/*
; *  �����ͥ����������̾�Υ�͡���
; */
	.AIFDEF OMIT_RENAME
	.AELSE

activate_r: 	.DEFINE 		"_kernel_activate_r"
ret_int: 	.DEFINE 		"_kernel_ret_int"
ret_exc: 	.DEFINE 		"_kernel_ret_exc"
task_intmask: 	.DEFINE 		"_kernel_task_intmask"
int_intmask: 	.DEFINE 		"_kernel_int_intmask"

	.AIFDEF LABEL_ASM

_activate_r: 	.DEFINE 		"__kernel_activate_r"
_ret_int: 	.DEFINE 		"__kernel_ret_int"
_ret_exc: 	.DEFINE 		"__kernel_ret_exc"
_task_intmask: 	.DEFINE 		"__kernel_task_intmask"
_int_intmask: 	.DEFINE 		"__kernel_int_intmask"

	.AENDI ;/* LABEL_ASM */
	.AENDI ;/* OMIT_RENAME */




;/*  �����ǽ�ʺǹ�ͥ����  */
MAX_IPM: .DEFINE  	"H'7"
MAX_IPM_CCR: .DEFINE	"H'80"



;/*
; *  chg_ipm/get_ipm �򥵥ݡ��Ȥ��뤫�ɤ��������
; */
SUPPORT_CHG_IPM: .DEFINE ""


	.AENDI ;/* _CPU_CONFIG_H_ */
