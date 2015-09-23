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
 *  @(#) $Id: c54x.h,v 1.3 2002/04/14 14:19:50 reiji Exp $
 */


#ifndef _C54X_H_
#define _C54X_H_

#ifndef _MACRO_ONLY
typedef unsigned char byte;
typedef unsigned int  word;
typedef volatile word  HIOREG;
#endif

/******************************************
 *  �ãУ� ���ꡦ�ޥåץɡ��쥸����
 ******************************************/
#define IMR  (*(HIOREG *)0x0)
#define IFR  (*(HIOREG *)0x1)
#define ST0  (*(HIOREG *)0x6)
#define ST1  (*(HIOREG *)0x7)
#define AL   (*(HIOREG *)0x8)
#define AH   (*(HIOREG *)0x9)
#define AG   (*(HIOREG *)0xA)
#define BL   (*(HIOREG *)0xB)
#define BH   (*(HIOREG *)0xC)
#define BG   (*(HIOREG *)0xD)
#define T    (*(HIOREG *)0xE)
#define TRN  (*(HIOREG *)0xF)
#define AR0  (*(HIOREG *)0x10)
#define AR1  (*(HIOREG *)0x11)
#define AR2  (*(HIOREG *)0x12)
#define AR3  (*(HIOREG *)0x13)
#define AR4  (*(HIOREG *)0x14)
#define AR5  (*(HIOREG *)0x15)
#define AR6  (*(HIOREG *)0x16)
#define AR7  (*(HIOREG *)0x17)
#define SP   (*(HIOREG *)0x18)
#define BK   (*(HIOREG *)0x19)
#define BRC  (*(HIOREG *)0x1A)
#define RSA  (*(HIOREG *)0x1B)
#define REA  (*(HIOREG *)0x1C)
#define PMST (*(HIOREG *)0x1D)
#define XPC  (*(HIOREG *)0x1E)


/********************************************
 *   �ڥ�ե���� ���ꡦ�ޥåץɡ��쥸����
 *******************************************/
/*
 * �����ޡ��쥸����
 */
#ifndef _MACRO_ONLY
typedef struct{
  HIOREG TIM;
  HIOREG PRD;
  HIOREG TCR;
}tmu;
#endif

#define TMU0 (*(volatile tmu *)0x24)
#define TMU1 (*(volatile tmu *)0x30)

#define TCR_TSS 0x0010
#define TCR_TRB 0x0020



/***********************************************
 *  I/O  ���ꡦ�ޥåץɡ��쥸����            *
***********************************************/
/*
 *  complex Programmable Logic Device (CPLD)   *
 *  I/O ���ꡦ�ޥåץɡ��쥸����                 *
 */

/*  �쥸���������ɥ쥹��*/
#ifndef _MACRO_ONLY
volatile ioport word port0;
volatile ioport word port1;
volatile ioport word port2;
volatile ioport word port3;
volatile ioport word port4;
volatile ioport word port5;
volatile ioport word port6;
#endif

/*  CPLD���쥸���� */
#define CPLD_CTRL1            port0
#define CPLD_STAT             port1
#define CPLD_DMCTRL           port2
#define CPLD_DBIO             port3
#define CPLD_CTRL2            port4
#define CPLD_SEM0             port5
#define CPLD_SEM1             port6

/*
 *  UART I/O ���ꡦ�ޥåץɡ��쥸���� *
 */
/*  �쥸���� ���ɥ쥹 */
#ifndef _MACRO_ONLY
volatile ioport word   port4000;
volatile ioport word   port4001;
volatile ioport word   port4002;
volatile ioport word   port4003;
volatile ioport word   port4004;
volatile ioport word   port4005;
volatile ioport word   port4006;
volatile ioport word   port4007;
#endif

/*  UART �쥸����  */
#define UART_RBR  port4000
#define UART_THR  port4000
#define UART_IER  port4001
#define UART_IIR  port4002
#define UART_FCR  port4002
#define UART_LCR  port4003
#define UART_MCR  port4004
#define UART_LSR  port4005
#define UART_MSR  port4006
#define UART_SCR  port4007
/*  �ʲ��Υ쥸�����˥��������������ˡ�
 *   DLAB=1 (b7 of LCR) �򥻥åȤ���ɬ�פ�����
 */
#define UART_DLL  port4000
#define UART_DLM  port4001

/*
 *  �ӥåȥե�����ɤ����  */
#define FCR_FIFO  0x01
#define FCR_RFRST 0x02
#define FCR_TFRST 0x04
#define FIFO_TRIG      0x00

#define LCR_DLAB  0x80

/* �������������ߤ���� */
#define IER_ERBI      0x01  /* ���������� */
#define IER_RIE   IER_ERBI 
#define IER_ETBEI     0x02  /* ���������� */
#define IER_TIE   IER_ETBEI

#define LSR_DR   0x01
#define LSR_THRE 0x20

/*
 *   �����ߥޥ����쥸����(IMR)�ӥåȥե������
 */
#define INT0           0
#define INT1           1
#define INT2           2
#define TINT0          3

#define RINT0          4
#define XINT0          5

#define TINT1          7

#define INT3           8
#define HPINT          9
#define RINT1         10
#define XINT1         11

#define DMAC0         6
#define DMAC1         7
#define DMAC2         10
#define DMAC3         11
#define DMAC4         12
#define DMAC5         13


/*
 *  �����ߥϥ�ɥ��ֹ� INHNO
 */
#define RESET_VEC             0
#define NMI_VEC	              1
#define SINT17_VEC            2
#define SINT18_VEC            3
#define SINT19_VEC           4
#define SINT20_VEC        5
#define SINT21_VEC        6
#define SINT22_VEC        7
#define SINT23_VEC        8
#define SINT24_VEC        9
#define SINT25_VEC        10
#define SINT26_VEC        11
#define SINT27_VEC        12
#define SINT28_VEC        13
#define SINT29_VEC        14
#define SINT30_VEC        15
#define INT0_VEC        16
#define INT1_VEC        17
#define INT2_VEC        18
#define TINT0_VEC        19
#define RINT0_VEC        20
#define XINT0_VEC        21
#define DMAC0_VEC        22
#define TINT1_VEC        23
#define INT3_VEC        24
#define HPI_VEC            25
#define RINT1_VEC        26
#define XINT1_VEC        27
#define DMAC2_VEC        26
#define DMAC3_VEC        27
#define DMAC4_VEC        28
#define DMAC5_VEC        29

/*
 *  TRAP�ֹ�
 */
#define RS_TRAP           0
#define NMI_TRAP       1
#define INT0_TRAP       16
#define INT1_TRAP       17
#define INT2_TRAP       18
#define TINT_TRAP       19
#define RINT0_TRAP       20
#define XINT0_TRAP       21
#define DMAC0_TRAP       22
#define DMAC1_TRAP       23
#define INT3_TRAP       24
#define HPINT_TRAP       25
#define RINT1_TRAP       26
#define DMAC2_TRAP       26
#define XINT1_TRAP       27
#define DMAC3_TRAP       27
#define DMAC4_TRAP       28
#define DMAC5_TRAP       29

#define SINTR        0
#define SINT16        1
#define SINT17        2
#define SINT18        3
#define SINT19        4
#define SINT20        5
#define SINT21        6
#define SINT22        7
#define SINT23        8
#define SINT24        9
#define SINT25        10
#define SINT26        11
#define SINT27        12
#define SINT28        13
#define SINT29        14
#define SINT30        15
#define SINT0        16
#define SINT1        17
#define SINT2        18
#define SINT3        19
#define SINT4        20
#define SINT5        21
#define SINT6        22
#define SINT7        23
#define SINT8        24
#define SINT9        25
#define SINT10        26
#define SINT11        27
#define SINT12          28
#define SINT13          29



/*  sys_putc��uart_putc�������printf��
 *  �Ѥ�����PRINTF��������롣�ޤ�����
 *  ���ϥ饤�֥��rts.lib�򥤥󥯥롼�ɤ���
 */
//#define PRINTF

#ifndef PRINTF
/* �ݡ���󥰤ǥ��ꥢ������� */
#ifndef _MACRO_ONLY
Inline char
uart_putc(char c)
{
  while((UART_LSR & LSR_THRE) == 0);      /*  �����쥸�����������ɤ���  */
  UART_THR = c;
  return(c);
}
#endif /* _MACRO_ONLY */
#endif /* PRINTF */
#endif
