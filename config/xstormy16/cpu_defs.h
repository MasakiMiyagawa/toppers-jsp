/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2005 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 */

/*
 *  �ץ��å��˰�¸���������Xstormy16�ѡ�
 */

#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

/*
 *  �ץ��å�ά��
 */
#define XSTORMY16

/*
 *  ����ߡ�CPU�㳰�ϥ�ɥ��ֹ�η�
 */
#ifndef _MACRO_ONLY
typedef UINT INHNO;         /* ����ߥϥ�ɥ��ֹ� */
typedef UINT EXCNO;         /* CPU�㳰�ϥ�ɥ��ֹ� */
#endif /* _MACRO_ONLY */

/*
 *  �ץ��å��Υ���ǥ�����
 */
#define SIL_ENDIAN SIL_ENDIAN_LITTLE

/*
 *  ����ߥϥ�ɥ��ֹ�
 */
#define TNUM_INTERRUPT 17   /* �������װ��� */
#define INHNO_WATCHDOG 0    /* ��å��ɥå������ޡ������ߥϥ�ɥ��ֹ� */
#define INHNO_BASETIMER 1   /* �١��������ޡ������ߥϥ�ɥ��ֹ� */
#define INHNO_TIMER0 2      /* �����ޡ�0�����ߥϥ�ɥ��ֹ� */
#define INHNO_TIMER1 3      /* �����ޡ�1�����ߥϥ�ɥ��ֹ� */
#define INHNO_UART 16       /* UART�����ߥϥ�ɥ��ֹ� */

/*
 *  CPU�㳰�ϥ�ɥ��ֹ�
 */
#define TNUM_EXCEPTION 4    /* �㳰�װ��� */
#define EXCNO_UDINST 0      /* ̤���̿���㳰�ϥ�ɥ��ֹ� */
#define EXCNO_WORDODD 1     /* ������ϤؤΥ�ɥ��������㳰�ϥ�ɥ��ֹ� */
#define EXCNO_OUTRANGE 2    /* �����ϰϳ����������㳰�ϥ�ɥ��ֹ� */
#define EXCNO_UNKNOWN 3     /* ������CPU�㳰�ϥ�ɥ��ֹ� */

#ifndef _MACRO_ONLY

/*
 *  ������ƥ��å������
 */
extern UINT _kernel_tic_nume ;          /* ������ƥ��å��μ�����ʬ�� */
#define TIC_NUME    _kernel_tic_nume    /*     (global�ѿ��Ȥ������) */
#define TIC_DENO    1u                  /* ������ƥ��å��μ�����ʬ�� */

/*
 *  �ǥХå��ѥ֥졼���ݥ����
 */
#define __BREAKPOINT() { __asm__( "nop" ); __asm__( ".hword 0x0007" ); }

/*
 *  stdio�����٥������ϴؿ�
 */
extern int _write ( int fd, char *buf, int nbytes ) ;
extern int _read ( int fd, char *buf, int nbytes ) ;

#endif /* _MACRO_ONLY */
#endif /* _CPU_DEFS_H_ */
