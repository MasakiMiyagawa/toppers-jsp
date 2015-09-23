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
 *  @(#) $Id: cpu_config.h,v 1.7 2005/12/07 01:44:56 honda Exp $
 */

/*
 *      �ץ��å���¸�⥸�塼���H8�ѡ�
 *���������������ͥ������ǻ��Ѥ������
 *�������������ǡ��������ޥ����ؿ��Υץ�ȥ��������
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�t_config.h �Τߤ��饤�󥯥롼�ɤ���롥
 *  ¾�Υե����뤫��ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
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

/*
 *  TCB ��Υե�����ɤΥӥå��������
 *
 *  cpu_context.h ��������������쥬��Ȥ��������Ȥΰ�¸���δط��ǡ�
 *  cpu_context.h �ˤ�������ʤ���
 */
#define TBIT_TCB_TSTAT          8       /* tstat �ե�����ɤΥӥå��� */
#define TBIT_TCB_PRIORITY       8       /* priority �ե�����ɤΥӥå��� */


#ifndef _MACRO_ONLY

/*
 *  ����������ƥ����ȥ֥�å������
 */

typedef struct task_context_block {
        VP      sp;             /* �����å��ݥ��� */
        FP      pc;             /* �ץ���५���� */
} CTXB;


/*
 *  ����饤��ؿ��Υץ�ȥ��������
 *  ������饤��ؿ���ץ�ȥ�����������ʤ��ȷٹ𤬽Ф뤿��
 *  �������ǤޤȤ��������Ƥ��롣
 */
Inline UB current_intmask(void);
Inline void set_intmask(UB intmask);
Inline BOOL sense_context(void);

Inline void t_lock_cpu(void);
Inline void t_unlock_cpu(void);
Inline void i_lock_cpu(void);
Inline void i_unlock_cpu(void);

Inline void define_inh(INHNO inhno, FP inthdr);
Inline void define_exc(EXCNO excno, FP exchdr);

Inline BOOL exc_sense_context(VP p_excinf);
Inline BOOL exc_sense_lock(VP p_excinf);

Inline void tmevtb_delete_top(void);    /*  time_event.c  */

Inline VB sil_reb_mem(VP mem);          /*  sil.h  */
Inline void sil_wrb_mem(VP mem, VB data);

Inline VH sil_reh_mem(VP mem);
Inline void sil_wrh_mem(VP mem, VH data);
Inline VH sil_reh_lem(VP mem);
Inline void sil_wrh_lem(VP mem, VH data);

Inline VW sil_rew_mem(VP mem);
Inline void sil_wrw_mem(VP mem, VW data);
Inline VW sil_rew_lem(VP mem);
Inline void sil_wrw_lem(VP mem, VW data);


/*
 *  ����ߥޥ������饤�֥��
 */

/*
 *  ���ߤγ���ߥޥ������ɽФ�
 */
Inline UB
current_intmask(void)
{
        return(current_ccr() & CCR_DISINT_ALL);
}

/*
 *  ����ߥޥ���������
 */
Inline void
set_intmask(UB intmask)
{
        UB ccr = current_ccr();
        
        /* ����ѥ���ηٹ���������뤿�ᡢ���㥹�Ȥ��Ƥ��롣 */
        ccr = (UB)((ccr & CCR_ENAINT_ALL) | intmask);
        set_ccr(ccr);
}

/*
 *  ����ߥͥ��ȥ�����
 */

extern volatile UB       intnest;

/*
 *  ����ƥ����Ȼ���
 *
 *  ����ߥͥ��ȥ����󥿤��ɤ߽Ф���ľ��˳���ߤ�ȯ�����Ƥ⡢��ä���
 *  ���ˤϥ���ƥ����Ȥ⸵����äƤ���
 */
Inline BOOL
sense_context(void)
{
	BOOL ret;
	
	ret = (intnest != 0) ? TRUE : FALSE;
	return(ret);
}

/*
 *  CPU��å����֤λ���
 */

/*
 *  CPU��å����֤�ɽ���ե饰
 */
extern volatile BOOL     iscpulocked;

#define sense_lock()    iscpulocked
#define t_sense_lock    sense_lock
#define i_sense_lock    sense_lock

/*
 *  CPU��å��Ȥ��β���ʥ���������ƥ������ѡ�
 *
 *  task_intmask �ϡ�chg_ipm �򥵥ݡ��Ȥ��뤿����ѿ���chg_ipm �򥵥ݡ���
 *  ���ʤ����ˤϡ�t_unlock_cpu ��� task_intmask �� 0 ���֤������Ƥ褤��
 */

#ifdef SUPPORT_CHG_IPM
extern volatile UB       task_intmask;   /* ����������ƥ����ȤǤγ���ߥޥ��� */
#endif /* SUPPORT_CHG_IPM */

Inline void
t_lock_cpu(void)
{
        disint();
        iscpulocked = TRUE;
}

Inline void
t_unlock_cpu(void)
{
        iscpulocked = FALSE;
#ifdef SUPPORT_CHG_IPM
        /*
         *  t_unlock_cpu ���ƤӽФ����Τ� CPU��å����֤ΤߤǤ��뤿�ᡣ
         *  ����������� task_intmask ���񤭴���뤳�ȤϤʤ���
         */
        set_intmask(task_intmask);
#else /* SUPPORT_CHG_IPM */
        enaint();               /* cpu_insn.h */
#endif /* SUPPORT_CHG_IPM */
}

/*
 *  CPU��å��Ȥ��β�����󥿥�������ƥ������ѡ�
 */

extern volatile UB       int_intmask;    /* �󥿥�������ƥ����ȤǤγ���ߥޥ��� */

Inline void
i_lock_cpu(void)
{
        UB      intmask = current_intmask();
        /*
         *  ����ѿ� intmask ��ȤäƤ���Τϡ�current_intmask()��Ƥ�
         *  ��ľ��˳���ߤ�ȯ��������ư���줿����ߥϥ�ɥ����
         *  int_intmask ���ѹ�������ǽ�������뤿��Ǥ��롥
         */

        disint();
        int_intmask = intmask;
        iscpulocked = TRUE;
}

Inline void
i_unlock_cpu(void)
{
        iscpulocked = FALSE;
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

extern void     dispatch(void);

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���cpu_support.S��
 *
 *  exit_and_dispatch �ϡ�CPU��å����֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */

extern void     exit_and_dispatch(void);

/*
 *
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ� inhno �γ���ߥϥ�ɥ�ε�ư���Ϥ� inthdr �����ꤹ�롥
 *
 *��H8�ǤǤϲ�������򤷤ʤ�
 *���ʥ٥����ơ��֥��ޥ˥奢����Խ������
 */
Inline void
define_inh(INHNO inhno, FP inthdr)
{
}

/*
 *  CPU�㳰�ϥ�ɥ������
 *����H8�ǤǤϻ��Ѥ���ʤ�
 */

Inline void
define_exc(EXCNO excno, FP exchdr)
{
}

/*
 *  ����ߥϥ�ɥ�ν���������
 *����H8C��H8��¸���Ǥϳ���ߤν����������򥢥���֥饽�������
 *�����������뤿�ᡢ�����C��������������ɬ�פ��ʤ���
 *���������Ǥ϶������ȤΥ��󥿡��ե��������碌�뤿�ᡢ
 *����ɬ�פʥޥ�������Τߤ��Ƥ��롣
 */

/*
 *  C����롼����δؿ�̾�������������Υ�٥������
 *����H8C��H8��¸���Ǥ�����������vector.src��Υ����롦����ܥ��
 *�����Ǥ���Τǡ������Х�˸�������ɬ�פ��ʤ���
 *���������Ǥ϶������ȤΥ��󥿡��ե��������碌�뤿�ᡢ
 *�������ߡ��Υ�٥��Ϳ���Ƥ��롣
 */
#define INT_ENTRY(inthdr) _kernel_common_interrupt_process
#define EXC_ENTRY(exchdr) _kernel_common_interrupt_process

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *������C�����ǤϤ��ޤ������Ǥ��ʤ����ᡢ������֥饽�������
 *�����������Ѱդ��롣
 */
#define INTHDR_ENTRY(inthdr) extern void INT_ENTRY(inthdr)(void) throw()

/*
 *  CPU�㳰�ϥ�ɥ�ν����������������ޥ���
 */
#define EXCHDR_ENTRY(exchdr) extern void EXC_ENTRY(exchdr)(void) throw()

/*
 *  CPU�㳰��ȯ���������Υ����ƥ���֤λ���
 */

/*
 *  CPU�㳰��ȯ���������Υ���ƥ�����Ƚ��
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
        /* H8�ǤǤϸƤФ�ʤ��� */
        return(TRUE);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
        /* H8�ǤǤϸƤФ�ʤ��� */
        return(TRUE);
}

/*
 *  �ץ��å���¸�ν����
 */

extern void     cpu_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */

extern void     cpu_terminate(void);

/*
 *  ̤��������ȯ�����Υ��顼���ϻ��Υ����å���¤�����
 */

typedef struct exc_stack {
	UW	er0;
	UW	er1;
	UW	er2;
	UW	er3;
	UW	er4;
	UW	er5;
	UW	er6;
	UW	pc;	/*  �ץ���ࡦ������  	*/
} EXCSTACK;

/*
 * ̤��������ȯ�����Υ��顼���� (cpu_config.c, cpu_support.S)
 */

extern void     cpu_experr(EXCSTACK *sp);

/*
 *  �������åȥ����ƥ��ʸ������
 *
 *  �����ƥ�����٥��ʸ�����ϥ롼����
 */
extern void cpu_putc(char c);

#endif /* _MACRO_ONLY_ */

#endif /* _CPU_CONFIG_H_ */
