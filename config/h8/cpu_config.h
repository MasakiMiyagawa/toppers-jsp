/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2004 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2004 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001-2004 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
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
 *  @(#) $Id: cpu_config.h,v 1.11 2004/09/03 15:39:07 honda Exp $
 */

/*
 *  �ץ��å���¸�⥸�塼���H8�ѡ�
 */

#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

#include <h8.h>

/*
 *  �����ͥ����������̾�Υ�͡���
 */

#include <cpu_rename.h>

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */

#ifndef _MACRO_ONLY
#include <cpu_insn.h>
#endif /* _MACRO_ONLY */

#ifndef _MACRO_ONLY

/*
 *  ����������ƥ����ȥ֥�å������
 */

typedef struct task_context_block {
	VP	sp;		/* �����å��ݥ��� */
	FP	pc;		/* �ץ���५���� */
} CTXB;

/*
 *  ����ߥޥ������饤�֥��
 */

/*
 *  ���ߤγ���ߥޥ������ɽФ�
 */

Inline UB
current_intmask()
{
	return(current_ccr() & H8INT_MASK_ALL);
}

/*
 *  ����ߥޥ���������
 */

Inline void
set_intmask(UB intmask)
{
	set_ccr((current_ccr() & ~H8INT_MASK_ALL) | intmask);
}

/*
 *  ����ߥͥ��ȥ�����
 */

extern UW	intnest;

/*
 *  ����ƥ����Ȼ���
 *
 *  ����ߥͥ��ȥ����󥿤��ɤ߽Ф���ľ��˳���ߤ�ȯ�����Ƥ⡢��ä���
 *  ���ˤϥ���ƥ����Ȥ⸵����äƤ���
 */

Inline BOOL
sense_context()
{
	return(intnest > 0);
}

Inline BOOL
sense_lock()
{
	return(current_ccr() & H8INT_MASK_ALL);
}

#define t_sense_lock	sense_lock
#define i_sense_lock	sense_lock

/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 */

Inline void
t_lock_cpu()
{
	disint();
}

Inline void
t_unlock_cpu()
{
	enaint();
}

/*
 *  CPU��å��Ȥ��β�����󥿥�������ƥ������ѡ�
 */

extern UB	int_intmask;	/* �󥿥�������ƥ����ȤǤγ���ߥޥ��� */

Inline void
i_lock_cpu()
{
	UB	intmask;

	/*
	 *  ����ѿ� intmask ��ȤäƤ���Τϡ�current_intmask()��Ƥ�
	 *  ��ľ��˳���ߤ�ȯ��������ư���줿����ߥϥ�ɥ����
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
 *
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 *
 */

Inline void
define_inh(INHNO inhno, FP inthdr)
{
	}

/*
 *   CPU�㳰�ϥ�ɥ������
 */

Inline void
define_exc(EXCNO excno, FP exchdr)
{
	}

/*
 *  ����ߥϥ�ɥ�ν���������
 *
 */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *		�ʼ������������
 *
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 *
 *
 */

/*  C����롼����δؿ�̾�������������Υ�٥������  */

#define	INT_ENTRY(inthdr)	inthdr##_entry
#define	EXC_ENTRY(exchdr)	exchdr##_entry

/*
 *  ����ߥϥ�ɥ����������
 *
 *	H8�Ǥϡ�����ߤ�CPU�㳰�ΰ�����Ʊ���ʤΤǡ�
 *	���������Υޥ���ⶦ�̤�������Ƥ���
 *
 *	entry�����������Υ�٥�
 *	inthdr��C����롼�������Ƭ���ɥ쥹
 *
 */

#define	_INTHDR_ENTRY(entry, inthdr) 					   \
asm(".text								\n"\
"	.align 2							\n"\
"	.global _"#entry"						\n"\
"_"#entry ":								\n"\
			/*  ɬ�׺Ǿ��¤Υ쥸�����򥹥��å�������  */	   \
"	push.l	er0							\n"\
"	push.l	er1							\n"\
			/*  ����ߥͥ��ȥ����󥿤Υ����å� 		*/ \
"	mov.l	@__kernel_intnest, er0					\n"\
"	mov.l	er0, er1   						\n"\
				/*  ����ߥͥ��ȥ����󥿤� +1 */	   \
"	inc.l	#1, er0							\n"\
"	mov.l	er0, @__kernel_intnest					\n"\
				/* �����ȯ�����Υ���ƥ����Ȥ�Ƚ��  	*/ \
"	or.l	er1, er1   						\n"\
				/* ¿�ų���ߤʤ饸����   		*/ \
"	bne	_interrupt_from_int_"#inthdr"				\n"\
				/*  ���̥ϡ��ɥ����������߶ػ� */	   \
"	jsr	@_"#inthdr"_disable_int					\n"\
				/* �����å������ؤ�����			*/ \
				/* �����������å��ݥ��󥿤���¸        	*/ \
"	mov.l	sp, er0							\n"\
				/* ����ߥ����å����ڤ��ؤ�		*/ \
"	mov.l	#"str_STACKTOP", sp					\n"\
				/* �����ߵ���				*/ \
"	andc	#"str_H8INT_ENA_ALL", ccr				\n"\
				/*  �Ĥ�Υ쥸��������¸ */		   \
"	mov.l	er2, @-er0						\n"\
"	mov.l	er3, @-er0						\n"\
"	mov.l	er4, @-er0						\n"\
"	mov.l	er5, @-er0						\n"\
"	mov.l	er6, @-er0						\n"\
"	push.l	er0							\n"\
"	jsr	@_"#inthdr"						\n"\
				/* �����߶ػ�				*/ \
"	orc	#"str_H8INT_DIS_ALL", ccr				\n"\
				/*  ���̥ϡ��ɥ����������ߵ��� */	   \
"	jsr	@_"#inthdr"_enable_int					\n"\
				/* ����ߥͥ��ȥ����󥿤�-1 */		   \
"	mov.l	@__kernel_intnest, er0				  	\n"\
"	dec.l	#1, er0							\n"\
"	mov.l	er0, @__kernel_intnest					\n"\
				/* �����å����ؤ�  			*/ \
"	mov.l	@sp, sp							\n"\
				/* reqflg�Υ����å�                    	*/ \
"       mov.l	@__kernel_reqflg, er0							\n"\
			/* reqflg��FALSE�ʤ�ret_to_task_int������ 	*/ \
"	or.l	er0, er0						\n"\
"	beq	_ret_to_task_int_"#inthdr"				\n"\
				/*  reqflg�򥯥ꥢ  		      	*/ \
"	sub.l	er0, er0						\n"\
"       mov.l	er0, @__kernel_reqflg					\n"\
				/*  ret_int�إ�����  			*/ \
"	jmp	@_kernel_ret_int					\n"\
									   \
									   \
/*   ¿�ų���ߤν��� 							*/ \
/* 	�����ȯ�����Υ���ƥ����Ȥ�Ƚ�̸塢�����߶ػ�		*/ \
/* 	�ξ��֤Ǥ���������Ǥ��� 					*/ \
/* 	�ʳ���ߥͥ��ȥ����󥿤Υ��󥯥���ȤϺѤ�Ǥ���� 		*/ \
									   \
"_interrupt_from_int_"#inthdr":						\n"\
				/*  ���̥ϡ��ɥ����������߶ػ� */	   \
"	jsr	@_"#inthdr"_disable_int					\n"\
				/* �����ߵ���				*/ \
"	andc	#"str_H8INT_ENA_ALL", ccr				\n"\
				/*  �Ĥ�Υ쥸��������¸	  	*/ \
"	push.l	er2							\n"\
"	push.l	er3							\n"\
"	push.l	er4							\n"\
"	push.l	er5							\n"\
"	push.l	er6							\n"\
"	jsr	@_"#inthdr"						\n"\
				/* �����߶ػ�				*/ \
"	orc	#"str_H8INT_DIS_ALL", ccr				\n"\
				/*  ���̥ϡ��ɥ����������ߵ��� */	   \
"	jsr	@_"#inthdr"_enable_int					\n"\
				/* ����ߥͥ��ȥ����󥿤� -1 */		   \
"	mov.l	@__kernel_intnest, er0				  	\n"\
"	dec.l	#1, er0							\n"\
"	mov.l	er0, @__kernel_intnest					\n"\
									   \
									   \
/*   reqflg��FALSE�ξ��ν��� 						*/ \
									   \
"_ret_to_task_int_"#inthdr": \n"					   \
"	pop.l	er6	\n"	/*  �쥸��������  			*/ \
"	pop.l	er5	\n"						   \
"	pop.l	er4	\n"						   \
"	pop.l	er3	\n"						   \
"	pop.l	er2	\n"						   \
"	pop.l	er1	\n"						   \
"	pop.l	er0	\n"						   \
"	rte		\n"	/*  ����߸������  			*/ \
)

/*  _INTHDR_ENTRY()�ޥ��������ޤ�  */

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */

#define INTHDR_ENTRY(inthdr)				\
	extern void inthdr##_entry(void);		\
	_INTHDR_ENTRY(inthdr##_entry, inthdr)

/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 */

#define	EXCHDR_ENTRY(exchdr)	INTHDR_ENTRY(exchdr)

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ�����Ƚ��
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
	return(*((UW *)p_excinf) & (((UW)H8INT_MASK_ALL) << 24));
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
 *  ̤��������ȯ�����Υ��顼���ϻ��Υ����å���¤�����
 */

typedef struct exc_stack {
	VW	er0;
	VW	er1;
	VW	er2;
	VW	er3;
	VW	er4;
	VW	er5;
	VW	er6;
	VW	pc;	/*  �ץ���ࡦ������  	*/
} EXCSTACK;

/*
 * ̤��������ȯ�����Υ��顼���� (cpu_config.c, cpu_support.S)
 */

extern void     cpu_experr(EXCSTACK *);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����ROM��˥��ƽФ��Ǽ¸����뤳
 *  �Ȥ����ꤷ�Ƥ��롥
 */

extern void cpu_putc(char c);

#endif /* _MACRO_ONLY_ */

#endif /* _CPU_CONFIG_H_ */
