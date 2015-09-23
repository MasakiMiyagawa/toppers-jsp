/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: cpu_config.h,v 1.6 2002/04/14 15:05:15 reiji Exp $
 */


#ifndef _CPU_CONFIG_H_
#define _CPU_CONFIG_H_

#include "c54x.h"


#define TBIT_TCB_TSTAT      6
#define TBIT_TCB_PRIORITY   4

#ifndef _MACRO_ONLY

typedef struct task_context_block{
  VP  sp;
  FP  pc;
}CTXB;

extern UH  nest;

Inline BOOL
sense_context(void)
{
  return (nest > 0);
}

Inline BOOL
sense_lock()
{
  volatile UH temp_st1;
  temp_st1 = ST1;
  return ((temp_st1 & 0x0800) > 0);
}

#endif

#define t_sense_lock sense_lock
#define i_sense_lock sense_lock


#ifndef _MACRO_ONLY

Inline void
t_lock_cpu(void)
{
  asm("\tSSBX INTM");
}

Inline void
t_unlock_cpu()
{
  asm("\tRSBX INTM");
}

#endif

#define i_lock_cpu t_lock_cpu
#define i_unlock_cpu t_unlock_cpu


#ifndef _MACRO_ONLY

extern void dispatch(void);
extern void exit_and_dispatch(void);

extern FP  int_table[32];
extern const UH  int_mask_table[32];


Inline void
define_inh(INHNO inhno, FP inthdr)
{
  int_table[inhno] = inthdr;
}

#endif


#define INTHDR_ENTRY(inthdr) extern void inthdr(void)
#define INT_ENTRY(inthdr) inthdr


/*
 *  TMS320VC54x DSP�ˤ�CPU�㳰��¸�ߤ��ʤ��Τ�
 *  �ʲ���Ŭ��������
 */

#ifndef _MACRO_ONLY

/*
 *   CPU�㳰�ϥ�ɥ������
 *   �����٥������ơ��֥����Ͽ
 */   

Inline void
define_exc(EXCNO excno, FP exchdr)
{
}



/*
 *  CPU�㳰��ȯ���������Υ���ƥ�����Ƚ��
 */
Inline BOOL
exc_sense_context(VP p_excinf)
{
   return(TRUE);
}

/*
 *  CPU�㳰��ȯ����������CPU��å����֤λ���
 */
Inline BOOL
exc_sense_lock(VP p_excinf)
{
   return(TRUE);
}

extern void cpu_initialize(void);
extern void cpu_terminate(void);

#endif

#endif
