/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 *  �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 *  �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 *  ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 *  ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 *  �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 *  ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: cpu_config.h,v 1.9 2003/12/19 10:13:47 honda Exp $
 */

/*
 *	�ץ��å���¸�⥸�塼���SH1�ѡ�
 *���������������ͥ������ǻ��Ѥ������
 *�������������ǡ��������ޥ����ؿ��Υץ�ȥ��������
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

/*
 *  �����ͥ����������̾�Υ�͡���
 */
#include <cpu_rename.h>

/*
 *  SH1�ץ��å��������쥸���������
 */
#include <sh1.h>

/*
 *  �����ǽ�ʺǹ�ͥ����
 */
#ifdef GDB_STUB
#define MAX_IPM  0xe	/* �����֤���ξ���ͥ����14��CPU��å�   */
#else
#define MAX_IPM  0xf	/* �����֤ʤ��ξ��Ϻǹ�ͥ���٤�CPU��å� */
#endif /*  GDB_STUB  */

#define str_MAX_IPM  	TO_STRING(MAX_IPM)
#define str_intnest  	TO_STRING(_intnest)
#define str_reqflg  	TO_STRING(_reqflg)
#define str_ret_int  	TO_STRING(_ret_int)

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#ifndef _MACRO_ONLY
#include <cpu_insn.h>
#endif /* _MACRO_ONLY */


/*
 *  chg_ipm/get_ipm �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_CHG_IPM

/*
 *  vxget_tim �򥵥ݡ��Ȥ��뤫�ɤ��������
 */
#define	SUPPORT_VXGET_TIM

/*
 *  TCB ��Υե�����ɤΥӥå��������
 *
 *  cpu_context.h ��������������쥬��Ȥ��������Ȥΰ�¸���δط��ǡ�
 *  cpu_context.h �ˤ�������ʤ���
 */
#define	TBIT_TCB_TSTAT		8	/* tstat �ե�����ɤΥӥå��� */
#define	TBIT_TCB_PRIORITY	8	/* priority �ե�����ɤΥӥå��� */

#ifndef _MACRO_ONLY
/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
        VP	sp;             /* �����å��ݥ��� */
        FP	pc;             /* �ץ���५���� */
} CTXB;

/*
 *  ����ߥޥ������饤�֥��
 *
 *  ����ߥޥ�����intmask�ˤϡ�IPM��Interrupt Priority Mask�ˤ�4�ӥå�
 *  ���˥��եȤ�����ΤǤ��롥
 */

/*
 *  ���ߤγ���ߥޥ������ɽФ�
 */
Inline UW
current_intmask()
{
	return(current_sr() & 0x000000f0u);
}

/*
 *  ����ߥޥ���������
 */
Inline void
set_intmask(UW intmask)
{
	set_sr((current_sr() & ~0x000000f0u) | intmask);
}


/*
 *  ����ߡ�CPU�㳰�ͥ��ȥ�����
 */
extern UW	intnest;

/*
 *  �����ƥ���ֻ���
 */


/*
 *  ����ƥ����Ȼ���
 *
 *  ����ߥͥ��ȥ����󥿤��ɤ߽Ф���ľ��˳���ߤ�ȯ�����Ƥ⡢
 *  ��ä��Ȥ��ˤϥ���ƥ����Ȥ⸵����äƤ���
 */
Inline BOOL
sense_context()
{
	return(intnest > 0);
}

Inline BOOL
sense_lock()
{
	return(current_intmask() == MAX_IPM << 4);
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 *  task_intmask �ϡ�chg_ipm �򥵥ݡ��Ȥ��뤿����ѿ���chg_ipm �򥵥ݡ�
 *  �Ȥ��ʤ����ˤϡ�task_intmask ����� 0 �ˤʤäƤ���ȹͤ���Ф褤��
 */

#ifdef SUPPORT_CHG_IPM
extern UW	task_intmask;	/* ����������ƥ����ȤǤγ���ߥޥ��� */
#endif /* SUPPORT_CHG_IPM */

Inline void
t_lock_cpu()
{
	disint();		/*  cpu_insn.h  */
}

Inline void
t_unlock_cpu()
{
#ifdef SUPPORT_CHG_IPM
	/*
	 *  t_unlock_cpu ���ƤӽФ����Τ� CPU��å����֤ΤߤǤ��뤿
	 *  �ᡤ����������� task_intmask ���񤭴���뤳�ȤϤʤ���
	 */
	set_intmask(task_intmask);
#else /* SUPPORT_CHG_IPM */
	enaint();		/*  cpu_insn.h  */
#endif /* SUPPORT_CHG_IPM */
}

/*
 *  CPU��å��Ȥ��β�����󥿥�������ƥ������ѡ�
 */

extern UW	int_intmask;	/* �󥿥�������ƥ����ȤǤγ���ߥޥ��� */

Inline void
i_lock_cpu()
{
	UW	intmask;

	/*
	 *  ����ѿ� intmask ��ȤäƤ���Τϡ�current_intmask() ���
	 *  ���ľ��˳���ߤ�ȯ��������ư���줿����ߥϥ�ɥ����
	 *  int_intmask ���ѹ�������ǽ�������뤿��Ǥ��롥
	 */
	intmask = current_intmask();
	disint();
	int_intmask = intmask;
}

Inline void
i_unlock_cpu()
{
	set_intmask(int_intmask);
}

/*
 *  �������ǥ����ѥå���
 */

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���cpu_support.S��
 *
 *  dispatch �ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ����������
 *  ��ǡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	dispatch(void);

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���cpu_support.S��
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void	exit_and_dispatch(void);

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ������
 */

/*
 *  �㳰�٥����ơ��֥�ι�¤�����
 */
typedef struct exc_vector_entry {
	FP	exchdr;			/* �㳰�ϥ�ɥ�ε�ư���� */
} EXCVE;

#define EXCVT_SIZE	256

#ifndef CQ_SH1_DEB

extern EXCVE BASE_VBR[EXCVT_SIZE];

#define EXCVT_KERNEL	BASE_VBR
#define EXCVT_ORIG	0

#endif /* CQ_SH1_DEB */

/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 */
Inline void
define_inh(INHNO inhno, FP inthdr)
{
	EXCVE	*excvt;

#ifdef EXCVT_KERNEL
	/*
	 *  EXCVT_KERNEL ���������Ƥ�����ϡ��������������� VBR ��
	 *  EXCVT_KERNEL �����ꤹ��Τǡ�EXCVT_KERNEL ��Ȥ���
	 */
	excvt = (EXCVE *) EXCVT_KERNEL;
	excvt[inhno].exchdr = inthdr;
#else /* EXCVT_KERNEL */
	excvt = (EXCVE *) current_vbr();

#ifdef CQ_SH1_DEB	/*  ���ꥢ������ߤ��򤱤�  */
	if ((inhno != RXI0) && (inhno != TXI0))
#endif /* CQ_SH1_DEB */
		excvt[inhno].exchdr = inthdr;


#endif /* EXCVT_KERNEL */



#ifdef GDB_STUB	/*  �����ָƤӽФ�  */


#endif	/*  GDB_STUB  */
}

/*
 *  CPU�㳰�ϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� excno ��CPU�㳰�ϥ�ɥ�ε�ư���Ϥ� exchdr �����ꤹ�롥
 */
Inline void
define_exc(EXCNO excno, FP exchdr)
{
	/*  SH1�ϳ���ߤ�CPU�㳰��Ʊ������  */
	define_inh((INHNO)excno, exchdr);
}

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ�ν���������
 */

/*  C����롼����δؿ�̾�������������Υ�٥������  
 *     kernel_cfg.c�ǻ���
 */
#define	INT_ENTRY(inthdr)	_kernel_##inthdr##_entry
#define	EXC_ENTRY(exchdr)	_kernel_##exchdr##_entry

/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 *
 *  CPU�㳰�ϥ�ɥ�ϡ��󥿥�������ƥ����ȤǼ¹Ԥ��롥���Τ��ᡤCPU��
 *  ���ϥ�ɥ��ƤӽФ����˳���ߥ⡼�ɤ˰ܹԤ����꥿���󤷤Ƥ������
 *  ���Υ⡼�ɤ��᤹�����Υ⡼�ɤ��᤹����ˡ�����ߥ⡼�ɤ˰ܹԤ�����
 *  �� SR �����ߥ����å������¸���롥CPU�㳰������������ƥ����Ȥ�
 *  ȯ������reqflg �� TRUE �ˤʤä����ˡ�ret_exc ��ʬ�����롥
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 */

/*
 *  ����ߥϥ�ɥ顿CPU�㳰�ϥ�ɥ����������
 *
 *	SH1�Ǥϡ�����ߤ�CPU�㳰�ΰ������ۤȤ��Ʊ���ʤΤǡ�
 *	���������Υޥ���ⶦ�̤�������Ƥ���
 *
 *	����ߤ�CPU�㳰�������
 *	������CPU�㳰�ϥ�ɥ�˰�����Ϳ����
 *	������CPU�㳰�Ǥϡ��㳰ȯ������IPM��Ʊ���ͤǳ���ߤ���Ĥ���
 *		��CPU�㳰�ˤ�ꡢIPM���Ѳ������ʤ���
 *
 *	entry�����������Υ�٥�
 *	inthdr��C����롼�������Ƭ���ɥ쥹
 *	set_exchdr_arg1��
 *	set_exchdr_arg2��
 *		CPU�㳰�ϥ�ɥ�ΰ��������Ѥ�̿��
 *
 */
#define	_INTHDR_ENTRY(entry, inthdr, 					   \
			set_exchdr_arg1, set_exchdr_arg2) 		   \
asm(".text								\n"\
"	.align 2							\n"\
"	.global _"#entry"						\n"\
"_"#entry ":								\n"\
			/*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */	   \
"	mov.l	r0,@-r15						\n"\
				/*  ����߶ػߤ�SR�����ν���  		*/ \
		/*  ����ߥϥ�ɥ�ξ��				*/ \
		/*  	����߼��ջ��˥ϡ��ɥ�������IPM�����ꤹ��	*/ \
		/*  	����ߵ��ĤˤϤ���IPM���ͤ��Ѥ���		*/ \
		/*  CPU�㳰�ϥ�ɥ�ξ��				*/ \
		/*  	CPU�㳰���ջ���IPM���ͤ��Ѳ����ʤ�		*/ \
		/*  	����ߵ��Ĥˤ�CPU�㳰ȯ������IPM���ͤ��Ѥ���	*/ \
"	mov.l	r1,@-r15						\n"\
				/*  sr��r1�˥��ԡ�			*/ \
"	stc	sr,r1							\n"\
				/*  ����߶ػ�  			*/ \
"	mov.l	_mask_ipm_"#inthdr",r0					\n"\
"	ldc	r0,sr							\n"\
				/*  r2�򥹥��å�������  		*/ \
"	mov.l	r2,@-r15						\n"\
			/*  ����ߡ�CPU�㳰�ͥ��ȥ����󥿤Υ����å� 	*/ \
"	mov.l	_intnest_k_"#inthdr", r0				\n"\
"	mov.l	@r0,r2							\n"\
				/* �����ȯ�����Υ���ƥ����Ȥ�Ƚ��  	*/ \
"	tst     r2,r2   						\n"\
				/*  ����ߥͥ��ȥ����󥿤򥤥󥯥����*/ \
"	add	#0x1,r2							\n"\
				/*  add̿��Ǥ�sr��T�ӥåȤ��Ѳ����ʤ�	*/ \
"	mov.l	r2,@r0							\n"\
				/* ¿�ų���ߤʤ饸����   		*/ \
"	bf	_interrupt_from_int_"#inthdr"				\n"\
	/*  �ٱ䥹��åȤʤ�  */					   \
				/* �����å������ؤ�����			*/ \
				/* �����������å��ݥ��󥿤���¸        	*/ \
"	mov     r15,r2							\n"\
				/* ����ߥ����å����ڤ��ؤ�		*/ \
"	mov.l   _stacktop_k_"#inthdr",r15				\n"\
				/*  ����ߵ���  */			   \
"	ldc  	r1,sr							\n"\
				/*  �Ĥ�Υ�����å��쥸��������¸  	*/ \
				/*  	r2:�����������å��ݥ���  	*/ \
"	mov.l   r3,@-r2							\n"\
"	mov.l   r4,@-r2							\n"\
"	mov.l   r5,@-r2							\n"\
"	mov.l   r6,@-r2							\n"\
"	mov.l   r7,@-r2							\n"\
"	sts.l	pr,@-r2							\n"\
	set_exchdr_arg1		/*  CPU�㳰�ξ��ΰ�������  		*/ \
				/*  C����롼����ƤӽФ�		*/ \
"	mov.l	_c_routine_"#inthdr",r1					\n"\
"	jsr	@r1							\n"\
"	mov.l	r2,@-r15 \n"	/*  �ٱ䥹��åȡ�  			*/ \
				/*  �����������å��ݥ��󥿤�		*/ \
				/*  ����ߥ����å����Ѥ�  		*/ \
									   \
				/*  ����߶ػ�		*/		   \
"	mov.l	_mask_ipm_"#inthdr",r0					\n"\
"	ldc	r0,sr							\n"\
				/* ����ߡ�CPU�㳰�ͥ��ȥ����󥿤򥯥ꥢ*/ \
"	mov.l	_intnest_k_"#inthdr",r0				  	\n"\
"	mov	#0x0,r1							\n"\
"	mov.l	r1,@r0							\n"\
				/* �����å����ؤ�  			*/ \
"	mov.l	@r15,r15						\n"\
				/* reqflg�Υ����å�                    	*/ \
"	mov.l	_reqflg_k_"#inthdr",r4					\n"\
"       mov.l	@r4,r1							\n"\
			/* reqflg��FALSE�ʤ�ret_to_task_int������ 	*/ \
"	tst	r1,r1							\n"\
"	bt   	_ret_to_task_int_"#inthdr"				\n"\
	/*  �ٱ䥹��åȤʤ�  */					   \
"	mov	#0x0,r0							\n"\
"	mov.l	ret_int_"#inthdr",r1					\n"\
				/*  ret_int�إ�����  			*/ \
"	jmp	@r1							\n"\
				/*  �ٱ䥹��å� reqflg�򥯥ꥢ        	*/ \
"	mov.l	r0,@r4							\n"\
									   \
									   \
/*   ¿�ų���ߤν��� 							*/ \
/* 	�����ȯ�����Υ���ƥ����Ȥ�Ƚ�̸塢 				*/ \
/*   		����߶ػ� 						*/ \
/*   		r1������߼��ջ���sr�Υ��ԡ� 				*/ \
/* 	�ξ��֤Ǥ���������Ǥ��� 					*/ \
/* 	�ʳ���ߥͥ��ȥ����󥿤Υ��󥯥���ȤϺѤ�Ǥ���� 		*/ \
									   \
"_interrupt_from_int_"#inthdr":						\n"\
				/* ����ߵ���  				*/ \
"	ldc	r1,sr							\n"\
			/*  �Ĥ�Υ�����å��쥸�����򥹥��å����Ѥࡡ	*/ \
"	mov.l	r3,@-r15						\n"\
"	mov.l	r4,@-r15						\n"\
"	mov.l	r5,@-r15						\n"\
"	mov.l	r6,@-r15						\n"\
"	mov.l	r7,@-r15						\n"\
"	sts.l	pr,@-r15						\n"\
	set_exchdr_arg2			/*  CPU�㳰�ξ��ΰ�������  	*/ \
					/*  C����롼����ƤӽФ� 	*/ \
"	mov.l	_c_routine_"#inthdr",r1					\n"\
"	jsr	@r1							\n"\
"	nop			\n"	/*  �ٱ䥹��åȡ� 		*/ \
									   \
					/*  ����߶ػ�			*/ \
"	mov.l	_mask_ipm_"#inthdr",r0					\n"\
"	ldc	r0,sr							\n"\
		/* ����ߡ�CPU�㳰�ͥ��ȥ����󥿤�ǥ��������	*/ \
"	mov.l	_intnest_k_"#inthdr",r0					\n"\
"	mov.l	@r0,r2							\n"\
"	add	#-1,r2							\n"\
"	mov.l	r2,@r0							\n"\
									   \
									   \
/*   reqflg��FALSE�ξ��ν��� 						*/ \
/*    									*/ \
/*   	���ǥ����ѥå��⥿�����㳰������ɬ�פʤ� 			*/ \
/* 	��chg_ipm()�ν�����ɬ�פʤ� 					*/ \
/* 	�����󥿥�������ƥ����ȤǤϡ�chg_ipm()�ϻ����Բġ� 		*/ \
									   \
"_ret_to_task_int_"#inthdr": \n"					   \
"	lds.l	@r15+,pr    \n"	/*  �쥸��������  			*/ \
"	mov.l	@r15+,r7    \n"						   \
"	mov.l	@r15+,r6    \n"						   \
"	mov.l	@r15+,r5    \n"						   \
"	mov.l	@r15+,r4    \n"						   \
"	mov.l	@r15+,r3    \n"						   \
"	mov.l	@r15+,r2    \n"						   \
"	mov.l	@r15+,r1    \n"						   \
"	mov.l	@r15+,r0    \n"						   \
"	rte		    \n"	/*  ����߸������  			*/ \
"	nop		    \n"						   \
									   \
"	.align  4	    \n"						   \
"_stacktop_k_"#inthdr":     \n"	/* ��������Ω���Υ����å��ν����  	*/ \
"	.long  "str_STACKTOP" \n"					   \
"_intnest_k_"#inthdr":	    \n"	/*  ����ߡ�CPU�㳰�ͥ��ȥ�����  	*/ \
"	.long  __kernel_intnest	    \n"				  	   \
"_reqflg_k_"#inthdr":	    \n"						   \
"	.long  __kernel_reqflg \n"					   \
"_mask_ipm_"#inthdr":	    \n"	/*  ����߶ػ��ѥޥ���  		*/ \
"	.long  "str_MAX_IPM" << 4 \n"	/*  ipm�ʳ��ΥӥåȤϥ�����ɤ�	*/ \
"_c_routine_"#inthdr":	    \n"						   \
"	.long  _"#inthdr"   \n" /*  C����롼�������Ƭ���ɥ쥹  	*/ \
"ret_int_"#inthdr":	    \n"	/*  �и�����ret_int�Υ��ɥ쥹  		*/ \
"	.long  __kernel_ret_int \n"			  		   \
)
/*  _INTHDR_ENTRY()�ޥ��������ޤ�  */




/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INTHDR_ENTRY(inthdr)					\
	extern void _kernel_##inthdr##_entry(void);		\
	_INTHDR_ENTRY(_kernel_##inthdr##_entry, inthdr, "", "")


/*
 *  CPU�㳰�ξ��ΰ��������ѥޥ���
 *
 *�������������������å��ݥ��󥿤򥳥ԡ�
 *�����������ʥ����å���Ƭ����40�Х��Ȳ���sr���Ѥޤ�Ƥ����
 */
#define	SET_EXCHDR_ARG(sp)						\
"	mov	"#sp",r4						\n"\
"	add	#40,r4							\n"


/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 *  ��
 *  	��������̿��ξ���������Ϥ�2�Х��ȿʤ��ɬ�פ����뤬
 *	�б����Ƥ��ʤ�
 *	��GDB stub���֥졼���ݥ���ȤȤ��ƻ��Ѥ��롣��
 */
#define	EXCHDR_ENTRY(exchdr)  						\
	extern void _kernel_##exchdr##_entry(VP sp);			\
	_INTHDR_ENTRY(_kernel_##exchdr##_entry, exchdr,			\
			SET_EXCHDR_ARG(r2), SET_EXCHDR_ARG(r15))


/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
	/* ������Ӥ���Τϡ����߼¹����CPU�㳰��ʬ 		*/
	/*  ����ߥͥ��ȥ����󥿤����󥯥���Ȥ���Ƥ��뤿�� 	*/
	return(intnest > 1);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
	UW sr = *(UW *)p_excinf; 
	return((sr& 0x00000f0u) == MAX_IPM << 4);
}

/*
 *  �ץ��å���¸�ν����
 */
extern void	cpu_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void	cpu_terminate(void);

/*
 * �ץ��å���¸���ꥢ�����
 */
extern void     cpu_putc(char c);


/*
 *  �����Υ����ϻ��Υ����å���¤�����
 */
typedef struct exc_stack {
	VW	r0;
	VW	r1;
	VW	r2;
	VW	r3;
	VW	r4;
	VW	r5;
	VW	r6;
	VW	r7;
	VW	r8;
	VW	r9;
	VW	r10;
	VW	r11;
	VW	r12;
	VW	r13;
	VW	r14;
	VW	r15;
	VW	pr;	/*  �ץ������㡦�쥸����  	*/
	VW	pc;	/*  �ץ���ࡦ������  	*/
	VW	sr;	/*  ���ơ��������쥸����  	*/
} EXCSTACK;


/*
 * �㳰ȯ�����Υ����� (cpu_config.c, cpu_support.S)
 */
extern void     cpu_experr(EXCSTACK *);

#endif /* _MACRO_ONLY */
#endif /* _CPU_CONFIG_H_ */
