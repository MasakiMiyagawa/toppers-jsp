;
;   TOPPERS/JSP Kernel
;       Toyohashi Open Platform for Embedded Real-Time Systems/
;       Just Standard Profile Kernel
;
;   Copyright (C) 2006 by Witz Corporation, JAPAN
;
;   �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
;   �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
;   �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
;   ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
;   ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
;   (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
;       ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
;       ����������˴ޤޤ�Ƥ��뤳�ȡ�
;   (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
;       �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
;       �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
;       ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
;   (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
;       �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
;       �ȡ�
;     (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
;         �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
;     (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
;         ��𤹤뤳�ȡ�
;   (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
;       ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
;
;   �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
;   ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
;   �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
;   ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
;
;   @(#) $Id: sys_support.app,v 1.1 2006/04/10 08:19:25 honda Exp $
;

	$MAXIMUM
	module sys_support_app

;
;	�������åȥ����ƥ��¸�⥸�塼�� ������֥������
;	��Zup-F16��ĥ�ܡ����ѡ�
;

#include "jsp_rename.h"
#include "cpu_rename.h"
#include "sys_rename.h"
#include "tmp91cy22.h"

f_code section code large align=1,1

;
; �������åȥϡ��ɥ������˰�¸����ɬ�פʽ����������������
;
	public hardware_init_hook
hardware_init_hook:
; ư���å�����(��®����å�1ʬ����4���ܤ�1/2)��6.144*(1/1)*4*(1/2)=12.288��
	ldb		(TADR_SFR_SYSCR0), 0xa0
	ldb		(TADR_SFR_SYSCR1), 0x00
	ldb		(TADR_SFR_SYSCR2), 0x2c ; halt̿��ˤ�IDLE2������
	ldb		(TADR_SFR_DFMCR1), 0x0b
	ldb		(TADR_SFR_DFMCR0), 0x40
lockup:			; ��å����å��Ԥ�
	bit		5, (TADR_SFR_DFMCR0)
	jr		nz, lockup
	ldb		(TADR_SFR_DFMCR0), 0x80

; �������ɥ쥹����2̵��
	ldb		(TADR_SFR_B2CS), 0x00
; �������ɥ쥹����1ͭ��(1MByteSRAM)
	ldb		(TADR_SFR_P1CR), 0x00
	ldb		(TADR_SFR_P1FC), 0xff	; AD0��AD15�����
	ldb		(TADR_SFR_P2CR), 0xff
	ldb		(TADR_SFR_P2FC), 0x0f	; A16��A19�����(�Ĥ�ϥݡ���)
	ldb		(TADR_SFR_P2), 0xff
	ldb		(TADR_SFR_P3), 0x78
	ldb		(TADR_SFR_P3CR), 0x7f
	ldb		(TADR_SFR_P3FC), 0x07	; RD/WR/HWR�����
	ldb		(TADR_SFR_P4FC), 0x02	; CS1�����
	ldb		(TADR_SFR_P4CR), 0x0e
	ldb		(TADR_SFR_MSAR1), 0x10	; 0x00100000��
	ldb		(TADR_SFR_MAMR1), 0x3f	; 0x001fffff
	ldb		(TADR_SFR_B1CS), 0x83	; 0��������/16bitDataBus

; WDT���
	ldb		(TADR_SFR_WDMOD), 0x00
	ldb		(TADR_SFR_WDCR), 0xb1

	ret

;
;  ���������Ԥ�
;
	public _sil_dly_nse
_sil_dly_nse:
	ld	WA, (XSP+0x4)
	sub	WA, 3173
	ret	le
	nop
sil_dly_nse1:
	sub	WA, 732
	jr	gt, sil_dly_nse1
	ret


	end


