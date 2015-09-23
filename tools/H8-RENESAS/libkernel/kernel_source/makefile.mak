#
#  TOPPERS/JSP Kernel
#      Toyohashi Open Platform for Embedded Real-Time Systems/
#      Just Standard Profile Kernel
# 
#  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
#                              Toyohashi Univ. of Technology, JAPAN
#  Copyright (C) 2005 by Industrial Technology Institute,
#                              Miyagi Prefectural Government, JAPAN
# 
#  ��L���쌠�҂́C�ȉ��� (1)�`(4) �̏������CFree Software Foundation 
#  �ɂ���Č��\����Ă��� GNU General Public License �� Version 2 �ɋL
#  �q����Ă�������𖞂����ꍇ�Ɍ���C�{�\�t�g�E�F�A�i�{�\�t�g�E�F�A
#  �����ς������̂��܂ށD�ȉ������j���g�p�E�����E���ρE�Ĕz�z�i�ȉ��C
#  ���p�ƌĂԁj���邱�Ƃ𖳏��ŋ�������D
#  (1) �{�\�t�g�E�F�A���\�[�X�R�[�h�̌`�ŗ��p����ꍇ�ɂ́C��L�̒���
#      ���\���C���̗��p��������щ��L�̖��ۏ؋K�肪�C���̂܂܂̌`�Ń\�[
#      �X�R�[�h���Ɋ܂܂�Ă��邱�ƁD
#  (2) �{�\�t�g�E�F�A���C���C�u�����`���ȂǁC���̃\�t�g�E�F�A�J���Ɏg
#      �p�ł���`�ōĔz�z����ꍇ�ɂ́C�Ĕz�z�ɔ����h�L�������g�i���p
#      �҃}�j���A���Ȃǁj�ɁC��L�̒��쌠�\���C���̗��p��������щ��L
#      �̖��ۏ؋K����f�ڂ��邱�ƁD
#  (3) �{�\�t�g�E�F�A���C�@��ɑg�ݍ��ނȂǁC���̃\�t�g�E�F�A�J���Ɏg
#      �p�ł��Ȃ��`�ōĔz�z����ꍇ�ɂ́C���̂����ꂩ�̏����𖞂�����
#      �ƁD
#    (a) �Ĕz�z�ɔ����h�L�������g�i���p�҃}�j���A���Ȃǁj�ɁC��L�̒�
#        �쌠�\���C���̗��p��������щ��L�̖��ۏ؋K����f�ڂ��邱�ƁD
#    (b) �Ĕz�z�̌`�Ԃ��C�ʂɒ�߂���@�ɂ���āCTOPPERS�v���W�F�N�g��
#        �񍐂��邱�ƁD
#  (4) �{�\�t�g�E�F�A�̗��p�ɂ�蒼�ړI�܂��͊ԐړI�ɐ����邢���Ȃ鑹
#      �Q������C��L���쌠�҂����TOPPERS�v���W�F�N�g��Ɛӂ��邱�ƁD
# 
#  �{�\�t�g�E�F�A�́C���ۏ؂Œ񋟂���Ă�����̂ł���D��L���쌠�҂�
#  ���TOPPERS�v���W�F�N�g�́C�{�\�t�g�E�F�A�Ɋւ��āC���̓K�p�\����
#  �܂߂āC�����Ȃ�ۏ؂��s��Ȃ��D�܂��C�{�\�t�g�E�F�A�̗��p�ɂ�蒼
#  �ړI�܂��͊ԐړI�ɐ����������Ȃ鑹�Q�Ɋւ��Ă��C���̐ӔC�𕉂�Ȃ��D
#

#
#  �O���c�[���Ăяo���pMakefile
#�@�@����Makefile�ł͈ȉ��̍�Ƃ��s�����߂̐ݒ���L�q����B
#�@�@�@�E�J�[�l���E���C�u�����\�z�̂��߂̃t�@�C������
#�@�@�@�ETCB�\���̂̃I�t�Z�b�g�Z�o
#


#######################################################################
#
#  ���[�U�[���ݒ肷��ϐ�
#
#######################################################################

#
#  �z�X�g�}�V���̊��Ɉˑ������`
#�@�@�ȉ��̕ϐ��̓z�X�g�}�V���̊��ɍ��킹�āA��`����B

#
#  �c�[���`�F�[�����C���g�[������Ă���f�B���N�g��
#
TC=C:\Hew3\Tools\Renesas\H8\6_1_0

#
#  perl�̎��s�t�@�C�����t���p�X�Ŏw�肷��B
#
PERL = C:\Perl\bin\perl.exe

#######################################################################


#
#  �^�[�Q�b�g���̒�`
#
CPU = h8
SYS = hsb8f3048bf25
TOOL = renesas

#
#  �\�[�X�t�@�C���̃f�B���N�g���̒�`
#
SRCDIR = ..\..\..\..
KERNELDIR = $(SRCDIR)\kernel
INCLUDEDIR = $(SRCDIR)\include
CPUDIR = $(SRCDIR)\config\$(CPU)-$(TOOL)
SYSDIR = $(CPUDIR)\$(SYS)

#
#  �C���N���[�h�t�@�C���̃T�[�`�p�X�̒�`
#
INCLUDE = .,$(INCLUDEDIR),$(SYSDIR),$(CPUDIR),$(KERNELDIR)

#
#  �R���p�C���ɗ^����I�v�V�����̒�`
#�@�@HEW�Ŏw�肷��I�v�V�����Ƃ��낦�Ȃ��Ɛ���ɓ��삵�Ȃ��̂Œ���
#
CC_OPT = -cpu=300HA -nologo -nolist -op=0 -nomessage=0006,0008,0010,1400 \
 -debug  -def=LABEL_ASM -def=E10T -I=$(INCLUDE)

#
#  �c�[���̒�`
#
CC = $(TC)\Bin\ch38.exe
COPY = copyfile.bat

#
#  �ˑ��t�@�C���̒�`
#
KERNEL_DEP_FILES = $(INCLUDEDIR)\itron.h $(INCLUDEDIR)\kernel.h \
 $(INCLUDEDIR)\kernel_cfg.h $(INCLUDEDIR)\kernel_debug.h \
 $(INCLUDEDIR)\logtask.h $(INCLUDEDIR)\s_services.h $(INCLUDEDIR)\serial.h \
 $(INCLUDEDIR)\sil.h $(INCLUDEDIR)\t_config.h $(INCLUDEDIR)\t_services.h \
 $(INCLUDEDIR)\t_stddef.h $(INCLUDEDIR)\t_syslog.h $(INCLUDEDIR)\timer.h \
 $(KERNELDIR)\check.h $(KERNELDIR)\cyclic.h $(KERNELDIR)\dataqueue.h \
 $(KERNELDIR)\eventflag.h $(KERNELDIR)\exception.h $(KERNELDIR)\interrupt.h \
 $(KERNELDIR)\jsp_kernel.h $(KERNELDIR)\jsp_rename.h $(KERNELDIR)\jsp_unrename.h \
 $(KERNELDIR)\mailbox.h $(KERNELDIR)\mempfix.h $(KERNELDIR)\queue.h \
 $(KERNELDIR)\semaphore.h $(KERNELDIR)\syslog.h $(KERNELDIR)\task.h \
 $(KERNELDIR)\time_event.h $(KERNELDIR)\wait.h

CPU_DEP_FILES = $(CPUDIR)\h8_3048f.h \
 $(CPUDIR)\cpu_config.h $(CPUDIR)\cpu_context.h \
 $(CPUDIR)\cpu_defs.h $(CPUDIR)\cpu_insn.h $(CPUDIR)\cpu_rename.h \
 $(CPUDIR)\cpu_unrename.h $(CPUDIR)\h8.h $(CPUDIR)\hw_serial.h \
 $(CPUDIR)\hw_timer.h $(CPUDIR)\tool_config.h $(CPUDIR)\tool_defs.h \
 $(CPUDIR)\util.h

SYS_DEP_FILES = $(SYSDIR)\sys_config.h $(SYSDIR)\sys_defs.h \
 $(SYSDIR)\user_config.h $(SYSDIR)\sys_rename.h $(SYSDIR)\sys_unrename.h 

DEP_FILES = $(KERNEL_DEP_FILES) $(CPU_DEP_FILES) $(SYS_DEP_FILES)

#
#  �e�\�[�X�t�@�C�����琶�������I�u�W�F�N�g�t�@�C���̒�`
#
TASK = tskini.c tsksched.c tskrun.c tsknrun.c \
		tskdmt.c tskact.c tskext.c tskpri.c tskrot.c tsktex.c

WAIT = waimake.c waicmp.c waitmo.c waitmook.c \
		waican.c wairel.c wobjwai.c wobjwaitmo.c wobjpri.c

TIME_EVENT = tmeini.c tmeup.c tmedown.c tmeins.c tmedel.c isig_tim.c

SYSLOG = logini.c vwri_log.c vrea_log.c vmsk_log.c logter.c

TASK_MANAGE = act_tsk.c iact_tsk.c can_act.c ext_tsk.c ter_tsk.c \
		chg_pri.c get_pri.c

TASK_SYNC = slp_tsk.c tslp_tsk.c wup_tsk.c iwup_tsk.c can_wup.c \
		rel_wai.c irel_wai.c sus_tsk.c rsm_tsk.c frsm_tsk.c dly_tsk.c

TASK_EXCEPT = ras_tex.c iras_tex.c dis_tex.c ena_tex.c sns_tex.c

SEMAPHORE = semini.c sig_sem.c isig_sem.c wai_sem.c pol_sem.c twai_sem.c

EVENTFLAG = flgini.c flgcnd.c set_flg.c iset_flg.c clr_flg.c \
		wai_flg.c pol_flg.c twai_flg.c

DATAQUEUE = dtqini.c dtqenq.c dtqfenq.c dtqdeq.c dtqsnd.c dtqrcv.c \
		snd_dtq.c psnd_dtq.c ipsnd_dtq.c tsnd_dtq.c \
		fsnd_dtq.c ifsnd_dtq.c rcv_dtq.c prcv_dtq.c trcv_dtq.c

MAILBOX = mbxini.c snd_mbx.c rcv_mbx.c prcv_mbx.c trcv_mbx.c

MEMPFIX = mpfini.c mpfget.c get_mpf.c pget_mpf.c tget_mpf.c rel_mpf.c

TIME_MANAGE = set_tim.c get_tim.c vxget_tim.c

CYCLIC = cycini.c cycenq.c sta_cyc.c stp_cyc.c cyccal.c

SYS_MANAGE = rot_rdq.c irot_rdq.c get_tid.c iget_tid.c \
		loc_cpu.c iloc_cpu.c unl_cpu.c iunl_cpu.c \
		dis_dsp.c ena_dsp.c sns_ctx.c sns_loc.c sns_dsp.c \
		sns_dpn.c vsns_ini.c

INTERRUPT = inhini.c

EXCEPTION = excini.c vxsns_ctx.c vxsns_loc.c \
		vxsns_dsp.c vxsns_dpn.c vxsns_tex.c


#
#  �S�̂̐����K��
#
ALL: SETENV offset.inc TASK WAIT TIME_EVENT SYSLOG TASK_MANAGE TASK_SYNC \
 TASK_EXCEPT SEMAPHORE EVENTFLAG DATAQUEUE MAILBOX MEMPFIX TIME_MANAGE \
 CYCLIC SYS_MANAGE INTERRUPT EXCEPTION

#
#  ���ϐ��̐ݒ�
#
SETENV:
	set CH38=$(TC)\Include
	set CH38TMP=$(TC)\Ctemp

#
#  offset.inc �̐����K���i�\���̓��̃I�t�Z�b�g�l�̎Z�o�j
#
MAKEOFFSET_C = $(CPUDIR)\makeoffset.c

offset.inc: $(MAKEOFFSET_C)
	$(CC) -code=asmcode $(CC_OPT) -I=$(INCLUDE) $(MAKEOFFSET_C)
	$(PERL) $(SRCDIR)\utils\h8-renesas\genoffset makeoffset.src > offset.inc

#
#  task.c�����̃��[��
#
TASK_C = $(KERNELDIR)\task.c

tskini.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskini -prep=tskini.p $(TASK_C)
	$(COPY) tskini.p tskini.c

tsksched.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tsksched -prep=tsksched.p $(TASK_C)
	$(COPY) tsksched.p tsksched.c

tskrun.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskrun -prep=tskrun.p $(TASK_C)
	$(COPY) tskrun.p tskrun.c

tsknrun.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tsknrun -prep=tsknrun.p $(TASK_C)
	$(COPY) tsknrun.p tsknrun.c

tskdmt.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskdmt -prep=tskdmt.p $(TASK_C)
	$(COPY) tskdmt.p tskdmt.c

tskact.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskact -prep=tskact.p $(TASK_C)
	$(COPY) tskact.p tskact.c

tskext.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskext -prep=tskext.p $(TASK_C)
	$(COPY) tskext.p tskext.c

tskpri.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskpri -prep=tskpri.p $(TASK_C)
	$(COPY) tskpri.p tskpri.c

tskrot.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tskrot -prep=tskrot.p $(TASK_C)
	$(COPY) tskrot.p tskrot.c

tsktex.c:$(TASK_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tsktex -prep=tsktex.p $(TASK_C)
	$(COPY) tsktex.p tsktex.c


#
#  wait.c�����̃��[��
#
WAIT_C = $(KERNELDIR)\wait.c

waimake.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__waimake -prep=waimake.p $(WAIT_C)
	$(COPY) waimake.p waimake.c

waicmp.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__waicmp -prep=waicmp.p $(WAIT_C)
	$(COPY) waicmp.p waicmp.c

waitmo.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__waitmo -prep=waitmo.p $(WAIT_C)
	$(COPY) waitmo.p waitmo.c

waitmook.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__waitmook -prep=waitmook.p $(WAIT_C)
	$(COPY) waitmook.p waitmook.c

waican.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__waican -prep=waican.p $(WAIT_C)
	$(COPY) waican.p waican.c

wairel.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wairel -prep=wairel.p $(WAIT_C)
	$(COPY) wairel.p wairel.c

wobjwai.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wobjwai -prep=wobjwai.p $(WAIT_C)
	$(COPY) wobjwai.p wobjwai.c

wobjwaitmo.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wobjwaitmo -prep=wobjwaitmo.p $(WAIT_C)
	$(COPY) wobjwaitmo.p wobjwaitmo.c

wobjpri.c:$(WAIT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wobjpri -prep=wobjpri.p $(WAIT_C)
	$(COPY) wobjpri.p wobjpri.c


#
#  time_event.c�����̃��[��
#
TIME_EVENT_C = $(KERNELDIR)\time_event.c

tmeini.c:$(TIME_EVENT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tmeini -prep=tmeini.p $(TIME_EVENT_C)
	$(COPY) tmeini.p tmeini.c

tmeup.c:$(TIME_EVENT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tmeup -prep=tmeup.p $(TIME_EVENT_C)
	$(COPY) tmeup.p tmeup.c

tmedown.c:$(TIME_EVENT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tmedown -prep=tmedown.p $(TIME_EVENT_C)
	$(COPY) tmedown.p tmedown.c

tmeins.c:$(TIME_EVENT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tmeins -prep=tmeins.p $(TIME_EVENT_C)
	$(COPY) tmeins.p tmeins.c

tmedel.c:$(TIME_EVENT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tmedel -prep=tmedel.p $(TIME_EVENT_C)
	$(COPY) tmedel.p tmedel.c

isig_tim.c:$(TIME_EVENT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__isig_tim -prep=isig_tim.p $(TIME_EVENT_C)
	$(COPY) isig_tim.p isig_tim.c


#
#  syslog.c�����̃��[��
#
SYSLOG_C = $(KERNELDIR)\syslog.c

logini.c:$(SYSLOG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__logini -prep=logini.p $(SYSLOG_C)
	$(COPY) logini.p logini.c

vwri_log.c:$(SYSLOG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vwri_log -prep=vwri_log.p $(SYSLOG_C)
	$(COPY) vwri_log.p vwri_log.c

vrea_log.c:$(SYSLOG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vrea_log -prep=vrea_log.p $(SYSLOG_C)
	$(COPY) vrea_log.p vrea_log.c

vmsk_log.c:$(SYSLOG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vmsk_log -prep=vmsk_log.p $(SYSLOG_C)
	$(COPY) vmsk_log.p vmsk_log.c

logter.c:$(SYSLOG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__logter -prep=logter.p $(SYSLOG_C)
	$(COPY) logter.p logter.c


#
#  task_manage.c�����̃��[��
#
TASK_MANAGE_C = $(KERNELDIR)\task_manage.c

act_tsk.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__act_tsk -prep=act_tsk.p $(TASK_MANAGE_C)
	$(COPY) act_tsk.p act_tsk.c

iact_tsk.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iact_tsk -prep=iact_tsk.p $(TASK_MANAGE_C)
	$(COPY) iact_tsk.p iact_tsk.c

can_act.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__can_act -prep=can_act.p $(TASK_MANAGE_C)
	$(COPY) can_act.p can_act.c

ext_tsk.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ext_tsk -prep=ext_tsk.p $(TASK_MANAGE_C)
	$(COPY) ext_tsk.p ext_tsk.c

ter_tsk.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ter_tsk -prep=ter_tsk.p $(TASK_MANAGE_C)
	$(COPY) ter_tsk.p ter_tsk.c

chg_pri.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__chg_pri -prep=chg_pri.p $(TASK_MANAGE_C)
	$(COPY) chg_pri.p chg_pri.c

get_pri.c:$(TASK_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__get_pri -prep=get_pri.p $(TASK_MANAGE_C)
	$(COPY) get_pri.p get_pri.c


#
#  task_sync.c�����̃��[��
#
TASK_SYNC_C = $(KERNELDIR)\task_sync.c

slp_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__slp_tsk -prep=slp_tsk.p $(TASK_SYNC_C)
	$(COPY) slp_tsk.p slp_tsk.c

tslp_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tslp_tsk -prep=tslp_tsk.p $(TASK_SYNC_C)
	$(COPY) tslp_tsk.p tslp_tsk.c

wup_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wup_tsk -prep=wup_tsk.p $(TASK_SYNC_C)
	$(COPY) wup_tsk.p wup_tsk.c

iwup_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iwup_tsk -prep=iwup_tsk.p $(TASK_SYNC_C)
	$(COPY) iwup_tsk.p iwup_tsk.c

can_wup.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__can_wup -prep=can_wup.p $(TASK_SYNC_C)
	$(COPY) can_wup.p can_wup.c

rel_wai.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__rel_wai -prep=rel_wai.p $(TASK_SYNC_C)
	$(COPY) rel_wai.p rel_wai.c

irel_wai.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__irel_wai -prep=irel_wai.p $(TASK_SYNC_C)
	$(COPY) irel_wai.p irel_wai.c

sus_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sus_tsk -prep=sus_tsk.p $(TASK_SYNC_C)
	$(COPY) sus_tsk.p sus_tsk.c

rsm_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__rsm_tsk -prep=rsm_tsk.p $(TASK_SYNC_C)
	$(COPY) rsm_tsk.p rsm_tsk.c

frsm_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__frsm_tsk -prep=frsm_tsk.p $(TASK_SYNC_C)
	$(COPY) frsm_tsk.p frsm_tsk.c

dly_tsk.c:$(TASK_SYNC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dly_tsk -prep=dly_tsk.p $(TASK_SYNC_C)
	$(COPY) dly_tsk.p dly_tsk.c


#
#  task_except.c�����̃��[��
#
TASK_EXCEPT_C = $(KERNELDIR)\task_except.c

ras_tex.c:$(TASK_EXCEPT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ras_tex -prep=ras_tex.p $(TASK_EXCEPT_C)
	$(COPY) ras_tex.p ras_tex.c

iras_tex.c:$(TASK_EXCEPT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iras_tex -prep=iras_tex.p $(TASK_EXCEPT_C)
	$(COPY) iras_tex.p iras_tex.c

dis_tex.c:$(TASK_EXCEPT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dis_tex -prep=dis_tex.p $(TASK_EXCEPT_C)
	$(COPY) dis_tex.p dis_tex.c

ena_tex.c:$(TASK_EXCEPT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ena_tex -prep=ena_tex.p $(TASK_EXCEPT_C)
	$(COPY) ena_tex.p ena_tex.c

sns_tex.c:$(TASK_EXCEPT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sns_tex -prep=sns_tex.p $(TASK_EXCEPT_C)
	$(COPY) sns_tex.p sns_tex.c


#
#  semaphore.c�����̃��[��
#
SEMAPHORE_C = $(KERNELDIR)\semaphore.c

semini.c:$(SEMAPHORE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__semini -prep=semini.p $(SEMAPHORE_C)
	$(COPY) semini.p semini.c

sig_sem.c:$(SEMAPHORE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sig_sem -prep=sig_sem.p $(SEMAPHORE_C)
	$(COPY) sig_sem.p sig_sem.c

isig_sem.c:$(SEMAPHORE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__isig_sem -prep=isig_sem.p $(SEMAPHORE_C)
	$(COPY) isig_sem.p isig_sem.c

wai_sem.c:$(SEMAPHORE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wai_sem -prep=wai_sem.p $(SEMAPHORE_C)
	$(COPY) wai_sem.p wai_sem.c

pol_sem.c:$(SEMAPHORE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__pol_sem -prep=pol_sem.p $(SEMAPHORE_C)
	$(COPY) pol_sem.p pol_sem.c

twai_sem.c:$(SEMAPHORE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__twai_sem -prep=twai_sem.p $(SEMAPHORE_C)
	$(COPY) twai_sem.p twai_sem.c


#
#  eventflag.c�����̃��[��
#
EVENTFLAG_C = $(KERNELDIR)\eventflag.c

flgini.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__flgini -prep=flgini.p $(EVENTFLAG_C)
	$(COPY) flgini.p flgini.c

flgcnd.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__flgcnd -prep=flgcnd.p $(EVENTFLAG_C)
	$(COPY) flgcnd.p flgcnd.c

set_flg.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__set_flg -prep=set_flg.p $(EVENTFLAG_C)
	$(COPY) set_flg.p set_flg.c

iset_flg.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iset_flg -prep=iset_flg.p $(EVENTFLAG_C)
	$(COPY) iset_flg.p iset_flg.c

clr_flg.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__clr_flg -prep=clr_flg.p $(EVENTFLAG_C)
	$(COPY) clr_flg.p clr_flg.c

wai_flg.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__wai_flg -prep=wai_flg.p $(EVENTFLAG_C)
	$(COPY) wai_flg.p wai_flg.c

pol_flg.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__pol_flg -prep=pol_flg.p $(EVENTFLAG_C)
	$(COPY) pol_flg.p pol_flg.c

twai_flg.c:$(EVENTFLAG_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__twai_flg -prep=twai_flg.p $(EVENTFLAG_C)
	$(COPY) twai_flg.p twai_flg.c


#
#  dataqueue.c�����̃��[��
#
DATAQUEUE_C = $(KERNELDIR)\dataqueue.c

dtqini.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dtqini -prep=dtqini.p $(DATAQUEUE_C)
	$(COPY) dtqini.p dtqini.c

dtqenq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dtqenq -prep=dtqenq.p $(DATAQUEUE_C)
	$(COPY) dtqenq.p dtqenq.c

dtqfenq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dtqfenq -prep=dtqfenq.p $(DATAQUEUE_C)
	$(COPY) dtqfenq.p dtqfenq.c

dtqdeq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dtqdeq -prep=dtqdeq.p $(DATAQUEUE_C)
	$(COPY) dtqdeq.p dtqdeq.c

dtqsnd.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dtqsnd -prep=dtqsnd.p $(DATAQUEUE_C)
	$(COPY) dtqsnd.p dtqsnd.c

dtqrcv.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dtqrcv -prep=dtqrcv.p $(DATAQUEUE_C)
	$(COPY) dtqrcv.p dtqrcv.c

snd_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__snd_dtq -prep=snd_dtq.p $(DATAQUEUE_C)
	$(COPY) snd_dtq.p snd_dtq.c

psnd_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__psnd_dtq -prep=psnd_dtq.p $(DATAQUEUE_C)
	$(COPY) psnd_dtq.p psnd_dtq.c

ipsnd_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ipsnd_dtq -prep=ipsnd_dtq.p $(DATAQUEUE_C)
	$(COPY) ipsnd_dtq.p ipsnd_dtq.c

tsnd_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tsnd_dtq -prep=tsnd_dtq.p $(DATAQUEUE_C)
	$(COPY) tsnd_dtq.p tsnd_dtq.c

fsnd_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__fsnd_dtq -prep=fsnd_dtq.p $(DATAQUEUE_C)
	$(COPY) fsnd_dtq.p fsnd_dtq.c

ifsnd_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ifsnd_dtq -prep=ifsnd_dtq.p $(DATAQUEUE_C)
	$(COPY) ifsnd_dtq.p ifsnd_dtq.c

rcv_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__rcv_dtq -prep=rcv_dtq.p $(DATAQUEUE_C)
	$(COPY) rcv_dtq.p rcv_dtq.c

prcv_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__prcv_dtq -prep=prcv_dtq.p $(DATAQUEUE_C)
	$(COPY) prcv_dtq.p prcv_dtq.c

trcv_dtq.c:$(DATAQUEUE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__trcv_dtq -prep=trcv_dtq.p $(DATAQUEUE_C)
	$(COPY) trcv_dtq.p trcv_dtq.c


#
#  mailbox.c�����̃��[��
#
MAILBOX_C = $(KERNELDIR)\mailbox.c

mbxini.c:$(MAILBOX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__mbxini -prep=mbxini.p $(MAILBOX_C)
	$(COPY) mbxini.p mbxini.c

snd_mbx.c:$(MAILBOX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__snd_mbx -prep=snd_mbx.p $(MAILBOX_C)
	$(COPY) snd_mbx.p snd_mbx.c

rcv_mbx.c:$(MAILBOX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__rcv_mbx -prep=rcv_mbx.p $(MAILBOX_C)
	$(COPY) rcv_mbx.p rcv_mbx.c

prcv_mbx.c:$(MAILBOX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__prcv_mbx -prep=prcv_mbx.p $(MAILBOX_C)
	$(COPY) prcv_mbx.p prcv_mbx.c

trcv_mbx.c:$(MAILBOX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__trcv_mbx -prep=trcv_mbx.p $(MAILBOX_C)
	$(COPY) trcv_mbx.p trcv_mbx.c


#
#  mempfix.c�����̃��[��
#
MEMPFIX_C = $(KERNELDIR)\mempfix.c

mpfini.c:$(MEMPFIX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__mpfini -prep=mpfini.p $(MEMPFIX_C)
	$(COPY) mpfini.p mpfini.c

mpfget.c:$(MEMPFIX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__mpfget -prep=mpfget.p $(MEMPFIX_C)
	$(COPY) mpfget.p mpfget.c

get_mpf.c:$(MEMPFIX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__get_mpf -prep=get_mpf.p $(MEMPFIX_C)
	$(COPY) get_mpf.p get_mpf.c

pget_mpf.c:$(MEMPFIX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__pget_mpf -prep=pget_mpf.p $(MEMPFIX_C)
	$(COPY) pget_mpf.p pget_mpf.c

tget_mpf.c:$(MEMPFIX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__tget_mpf -prep=tget_mpf.p $(MEMPFIX_C)
	$(COPY) tget_mpf.p tget_mpf.c

rel_mpf.c:$(MEMPFIX_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__rel_mpf -prep=rel_mpf.p $(MEMPFIX_C)
	$(COPY) rel_mpf.p rel_mpf.c


#
#  time_manage.c�����̃��[��
#
TIME_MANAGE_C = $(KERNELDIR)\time_manage.c

set_tim.c:$(TIME_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__set_tim -prep=set_tim.p $(TIME_MANAGE_C)
	$(COPY) set_tim.p set_tim.c

get_tim.c:$(TIME_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__get_tim -prep=get_tim.p $(TIME_MANAGE_C)
	$(COPY) get_tim.p get_tim.c

vxget_tim.c:$(TIME_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vxget_tim -prep=vxget_tim.p $(TIME_MANAGE_C)
	$(COPY) vxget_tim.p vxget_tim.c


#
#  cyclic.c�����̃��[��
#
CYCLIC_C = $(KERNELDIR)\cyclic.c

cycini.c:$(CYCLIC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__cycini -prep=cycini.p $(CYCLIC_C)
	$(COPY) cycini.p cycini.c

cycenq.c:$(CYCLIC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__cycenq -prep=cycenq.p $(CYCLIC_C)
	$(COPY) cycenq.p cycenq.c

sta_cyc.c:$(CYCLIC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sta_cyc -prep=sta_cyc.p $(CYCLIC_C)
	$(COPY) sta_cyc.p sta_cyc.c

stp_cyc.c:$(CYCLIC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__stp_cyc -prep=stp_cyc.p $(CYCLIC_C)
	$(COPY) stp_cyc.p stp_cyc.c

cyccal.c:$(CYCLIC_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__cyccal -prep=cyccal.p $(CYCLIC_C)
	$(COPY) cyccal.p cyccal.c


#
#  sys_manage.c�����̃��[��
#
SYS_MANAGE_C = $(KERNELDIR)\sys_manage.c

rot_rdq.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__rot_rdq -prep=rot_rdq.p $(SYS_MANAGE_C)
	$(COPY) rot_rdq.p rot_rdq.c

irot_rdq.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__irot_rdq -prep=irot_rdq.p $(SYS_MANAGE_C)
	$(COPY) irot_rdq.p irot_rdq.c

get_tid.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__get_tid -prep=get_tid.p $(SYS_MANAGE_C)
	$(COPY) get_tid.p get_tid.c

iget_tid.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iget_tid -prep=iget_tid.p $(SYS_MANAGE_C)
	$(COPY) iget_tid.p iget_tid.c

loc_cpu.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__loc_cpu -prep=loc_cpu.p $(SYS_MANAGE_C)
	$(COPY) loc_cpu.p loc_cpu.c

iloc_cpu.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iloc_cpu -prep=iloc_cpu.p $(SYS_MANAGE_C)
	$(COPY) iloc_cpu.p iloc_cpu.c

unl_cpu.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__unl_cpu -prep=unl_cpu.p $(SYS_MANAGE_C)
	$(COPY) unl_cpu.p unl_cpu.c

iunl_cpu.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__iunl_cpu -prep=iunl_cpu.p $(SYS_MANAGE_C)
	$(COPY) iunl_cpu.p iunl_cpu.c

dis_dsp.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__dis_dsp -prep=dis_dsp.p $(SYS_MANAGE_C)
	$(COPY) dis_dsp.p dis_dsp.c

ena_dsp.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__ena_dsp -prep=ena_dsp.p $(SYS_MANAGE_C)
	$(COPY) ena_dsp.p ena_dsp.c

sns_ctx.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sns_ctx -prep=sns_ctx.p $(SYS_MANAGE_C)
	$(COPY) sns_ctx.p sns_ctx.c

sns_loc.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sns_loc -prep=sns_loc.p $(SYS_MANAGE_C)
	$(COPY) sns_loc.p sns_loc.c

sns_dsp.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sns_dsp -prep=sns_dsp.p $(SYS_MANAGE_C)
	$(COPY) sns_dsp.p sns_dsp.c

sns_dpn.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__sns_dpn -prep=sns_dpn.p $(SYS_MANAGE_C)
	$(COPY) sns_dpn.p sns_dpn.c

vsns_ini.c:$(SYS_MANAGE_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vsns_ini -prep=vsns_ini.p $(SYS_MANAGE_C)
	$(COPY) vsns_ini.p vsns_ini.c


#
#  interrupt.c�����̃��[��
#
INTERRUPT_C = $(KERNELDIR)\interrupt.c
$(INTERRUPT):$(INTERRUPT_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__inhini -prep=inhini.p $(INTERRUPT_C)
	$(COPY) inhini.p inhini.c


#
#  exception.c�����̃��[��
#
EXCEPTION_C = $(KERNELDIR)\exception.c

excini.c:$(EXCEPTION_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__excini -prep=excini.p $(EXCEPTION_C)
	$(COPY) excini.p excini.c

vxsns_ctx.c:$(EXCEPTION_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vxsns_ctx -prep=vxsns_ctx.p $(EXCEPTION_C)
	$(COPY) vxsns_ctx.p vxsns_ctx.c

vxsns_loc.c:$(EXCEPTION_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vxsns_loc -prep=vxsns_loc.p $(EXCEPTION_C)
	$(COPY) vxsns_loc.p vxsns_loc.c

vxsns_dsp.c:$(EXCEPTION_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vxsns_dsp -prep=vxsns_dsp.p $(EXCEPTION_C)
	$(COPY) vxsns_dsp.p vxsns_dsp.c

vxsns_dpn.c:$(EXCEPTION_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vxsns_dpn -prep=vxsns_dpn.p $(EXCEPTION_C)
	$(COPY) vxsns_dpn.p vxsns_dpn.c

vxsns_tex.c:$(EXCEPTION_C) $(DEP_FILES)
	$(CC) $(CC_OPT) -def=__vxsns_tex -prep=vxsns_tex.p $(EXCEPTION_C)
	$(COPY) vxsns_tex.p vxsns_tex.c
