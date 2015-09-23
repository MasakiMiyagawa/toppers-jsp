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
;   @(#) $Id: start.app,v 1.1 2006/04/10 08:19:25 honda Exp $
;

	$MAXIMUM
	module start_app

;
;	�����ͥ��ѤΥ������ȥ��åץ⥸�塼���TLCS-900�ѡ�
;
#include "jsp_rename.h"
#include "cpu_rename.h"
#include "sys_rename.h"
#include "tlcs900vec.inc"

; �������ȥ���ܥ����
	extern large	__StackTop
	extern large	__AreaRAM
	extern large	__AreaRAM_size
	extern large	__DataRAM
	extern large	__DataRAM_ini
	extern large	__DataRAM_size
	extern large	hardware_init_hook
	extern large	software_init_hook
	extern large	_kernel_start

f_code section code large align=1,1

	public _start
_start:
; ����߶ػ�
	di		; �ꥻ�åȻ���IFF��7�����ꤵ��뤿��DI���֤Ȥʤ�
			; �ϡ��ɥ������ꥻ�åȻ���di̿������
			; ���եȤˤ� jp _start �����ǽ�����θ�������ɤ�Ĥ�

; �����å������
	ld		xsp, __StackTop

; INTNEST�쥸���������
	ld		hl, 0
	ldc		intnest, hl

; hardware_init_hook ��ƽФ���0 �Ǥʤ�����
; �������åȥϡ��ɥ������˰�¸����ɬ�פʽ����������������
; �ϡ�hardware_init_hook �Ȥ����ؿ����Ѱդ��롥
	ld		xhl, hardware_init_hook
	cp		xhl, 0
	call	nz, hardware_init_hook

; �����̵��RAM�ΰ�Υ��ꥢ
	ld		xde, __AreaRAM			; ��Ƭ���Ϥȥ���������
	ld		xbc, __AreaRAM_size
	ld		ix, bc					; �ǲ���bit�ݻ�(��ǻ���)
	srl		1, xbc					; 2byteñ�̤ǽ������뤿�᥵����/2
	jr		z, area_clr_byte
	ld		xhl, xde				; ��Ƭ�����ݻ�(��ǻ���)
	ldw		(xde+), 0				; ��Ƭ���ϥ��ꥢ
	sub		xbc, 1					; �������ǥ������
	jr		z, area_clr_byte
	ldirw	(xde+), (xhl+)			; ��Ƭ����(����0����)���ͤ����Ϥ�...
									; �����Τ�BC�쥸����ʬ�֥�å�����
	cp		qbc, 0
	jr		eq, area_clr_byte			; ���16bit��0�ʤ齪λ
	ld		wa, qbc
area_clr_loop:						; ���16bit(0x10000ñ��)�Ǥν���
	ldirw	(xde+), (xhl+)			; 0x10000ʬ�֥�å�����
	djnz	wa, area_clr_loop
area_clr_byte:
	bit		0, ix					; �ΰ襵����������ʤ�1byte���ꥢ
	jr		z, area_clr_end
	ldb		(xde), 0
area_clr_end:

; �����ͭ��RAM�ΰ�ؤΥǡ�������
	ld		xde, __DataRAM			; ���ɸ������������Ϥȥ���������
	ld		xhl, __DataRAM_ini
	ld		xbc, __DataRAM_size
	or		xbc, xbc				; ������0�ʤ齪λ
	jr		z, data_ld_end
	ldirb	(xde+), (xhl+)			; BC�쥸����ʬ�֥�å�����
	cp		qbc, 0
	jr		eq, data_ld_end			; ���16bit��0�ʤ齪λ
	ld		wa, qbc
data_ld_loop:						; ���16bit(0x10000ñ��)�Ǥν���
	ldirb	(xde+), (xhl+)			; 0x10000ʬ�֥�å�����
	djnz	wa, data_ld_loop
data_ld_end:

; software_init_hook ��ƽФ���0 �Ǥʤ�����
; ���եȥ������Ķ����ä˥饤�֥��ˤ˰�¸����ɬ�פʽ������
; ����������ϡ�software_init_hook �Ȥ����ؿ����Ѱդ��롥
	ld		xhl, software_init_hook
	cp		xhl, 0
	call	nz, software_init_hook

; �����ͥ뵯ư
	jp		_kernel_start

; EXIT�롼��
exit:
	jr		exit

	end
