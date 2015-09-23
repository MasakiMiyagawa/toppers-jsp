#! /usr/bin/perl
#
#  TOPPERS/JSP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      Just Standard Profile Kernel
# 
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2004 by Embedded and Real-Time Systems Laboratory
#              Graduate School of Information Science, Nagoya Univ., JAPAN
#  Copyright (C) 2005 by Industrial Technology Institute,
#                              Miyagi Prefectural Government, JAPAN
# 
#  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
#  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
#  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
#  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
#  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
#  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
#      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
#      ����������˴ޤޤ�Ƥ��뤳�ȡ�
#  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
#      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
#      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
#  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
#      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
#      �ȡ�
#    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
#        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
#    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
#        ��𤹤뤳�ȡ�
#  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
#      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
# 
#  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
#  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
#  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
#  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
# 
#  @(#) $Id: genvector.pl,v 1.4 2005/12/07 01:49:24 honda Exp $
# 


#
#  �٥����ơ��֥�����������ץ�
#  ��make depend�������������tmp_script.pl���ɤ߹��ळ�Ȥˤ�ä�
#  ���¹ԤǤ���褦�ˤʤ�

require "getopt.pl";

#  ���ץ��������
#
#  -s <vector size>	�٥������ơ��֥�Υ�����

#
#  ���ץ����ν���
#
do Getopt("s");

$vector_size = $opt_s;

for ($i=0; $i<$vector_size; $i++) {
	$vector_table[$i] = "_no_reg_exception";
}

# �ꥻ�åȥ٥��������
$vector_table[0] = "_start";

# ��ư�������줿������ץȤ��ɤ߹���
require "./tmp_script.pl";

# �٥����ơ��֥�ν���
for ($i=0; $i<$vector_size; $i++) {
	if ($vector_table[$i] =~ /(_start)|(_no_reg_exception)/) {
		printf "\t.DATA.L %s\t;  %d, 0x%02x\n", $vector_table[$i] , $i, $i;
	} else {
		printf "\t.DATA.L __kernel_%s_entry\t;  %d, 0x%02x\n", 
							$vector_table[$i] , $i, $i;
	}
}

#
# ����ߤ����������ν���
#
print <<INTENTRY

;
;  ����ߤ��������������
;    ���Υե�����ˤϥ桼��������γ���ߥϥ�ɥ��C����롼�����̾��
;    ���Ҥ���
;
        .SECTION P, CODE, ALIGN=2

;
;    ����ߤ�������������������ޥ���λȤ���
;      �ʳ�����װ���˰ۤʤ���ʬ��
;
;    �ޥ���INTHDR_ENTRY C_ROUTINE, INTMASK
;      �ѥ�᡼��
;          C_ROUTINE��C����롼����δؿ�̾����Ƭ��'_'���դ��ʤ���
;          INTMASK��  ����ߵ��Ļ��˳���ߥޥ��������ꤹ����
;                      IPM_LEVEL1��IPM_LEVEL2�Τ����줫�ˤ��뤳��
;                      ��ʬ��Ʊ����٥�γ���ߤ�ޥ������뤿�ᡢ
;                      IPM�ˤϣ��ľ�Υ�٥�����ꤹ�롣
;

INTENTRY
;

for ($i=0; $i<$vector_size; $i++) {
	if ($vector_table[$i] !~ /(_start)|(_no_reg_exception)/) {
		printf " INTHDR_ENTRY %s, %s_intmask\n", 
				$vector_table[$i] , $vector_table[$i];
	}
}


print "\n .END\n";

