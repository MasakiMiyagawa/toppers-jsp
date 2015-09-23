/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001,2002 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *
 *  �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ���
 *  GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
 *  ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
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
 *  @(#) $Id: sh1.h,v 1.4 2002/04/11 11:30:20 imai Exp $
 */

#ifndef _SH1_H_
#define _SH1_H_

/*
 *  ���ͥǡ���ʸ�����ѥޥ���
 */
#define TO_STRING(arg)	#arg
#define _TO_STRING(arg)	TO_STRING(arg)



/*
 *  ����ߤΥ٥����ֹ����
 */
#define GII	 4	/*  ��������̿��:General Illegal Instruction  */
#define SII	 6	/*  ����å�����̿��:Slot Illegal Instruction */
#define CAE	 9	/*  CPU���ɥ쥹���顼:CPU Address Error       */
#define DAE	10	/*  DMA���ɥ쥹���顼:DMA Address Error       */

#define NMI	11	/*  NMI  		*/
#define USBK	12	/*  �桼�����֥졼��  	*/
#define IRQ0	64	/*  ����������׵�  	*/
#define IRQ1	65
#define IRQ2	66
#define IRQ3	67
#define IRQ4	68
#define IRQ5	69
#define IRQ6	70
#define IRQ7	71

	/*  DMAC:�����쥯�ȥ��ꥢ����������ȥ���  */
#define DEI0	72	/*  DMAC0  */
#define DEI1	74	/*  DMAC1  */
#define DEI2	76	/*  DMAC2  */
#define DEI3	78	/*  DMAC3  */

	/*  ITU:����ƥ��졼�ƥåɥ����ޥѥ륹��˥å�  */
#define IMIA0	80	/*  ITU0  */
#define IMIB0	81
#define OVI0	82
#define IMIA1	84	/*  ITU1  */
#define IMIB1	85
#define OVI1	86
#define IMIA2	88	/*  ITU2  */
#define IMIB2	89
#define OVI2	90
#define IMIA3	92	/*  ITU3  */
#define IMIB3	93
#define OVI3	94
#define IMIA4	96	/*  ITU4  */
#define IMIB4	97
#define OVI4	98

	/*  SCI:���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����  */
#define ERI0	100	/*  SCI0  */
#define RXI0	101
#define TXI0	102
#define TEI0	103
#define ERI1	104	/*  SCI1  */
#define RXI1	105
#define TXI1	106
#define TEI1	107

#define PEI	108	/*  PRT:�Х�����ȥ���Υѥ�ƥ�����  */
#define ADI	109	/*  A/D����С���  			*/
#define ITI	112	/*  WDT:�����å��ɥå�������  		*/
#define CMI	113	/*  REF:DRAM��ե�å�������  		*/



#ifndef _MACRO_ONLY

/*
 *  SH1�������쥸�������
 */
typedef unsigned char   byte;
typedef volatile byte   IOREG;
typedef unsigned short  word;
typedef volatile word   HIOREG;
typedef volatile int    LIOREG;


/*
 *   �Х����ơ��ȥ���ȥ���
 */
#define	WCR1	((HIOREG *)0x5ffffa2)	/*  �������ȥ���ȥ���쥸����1 */
#define	WCR2	((HIOREG *)0x5ffffa4)	/*  �������ȥ���ȥ���쥸����2 */
#define	WCR3	((HIOREG *)0x5ffffa6)	/*  �������ȥ���ȥ���쥸����3 */

			/*  ���ꥢ7���꡼�ɥ��������WAIT����ˤ��  	*/
			/*  �������ȥ��ơ�����������  			*/
#define    WCR1_RW7		0x8000
			/*  ���ꥢ3���꡼�ɥ��������WAIT����ˤ��  	*/
			/*  �������ȥ��ơ�����������  			*/
#define    WCR1_RW3		0x800
			/*  ���ꥢ0���꡼�ɥ��������WAIT����ˤ��  	*/
			/*  �������ȥ��ơ�����������  			*/
#define    WCR1_RW0		0x100
			/*  ���ꥢ0,2��1���ơ��ȥ�󥰥�������  	*/
#define    WCR3_A02LW_MASK	~0x6000

/*
 * �ԥ�ե��󥯥���󥳥�ȥ���
 */
#define	PAIOR	((HIOREG *)0x5ffffc4)	/*  �ݡ���A I/O�쥸����  	  */
#define	PACR1	((HIOREG *)0x5ffffc8)	/*  �ݡ���A ����ȥ���쥸����1 */
#define	PACR2	((HIOREG *)0x5ffffca)	/*  �ݡ���A ����ȥ���쥸����2 */
#define	PBIOR	((HIOREG *)0x5ffffc6)	/*  �ݡ���B I/O�쥸����  	  */
#define	PBCR1	((HIOREG *)0x5ffffcc)	/*  �ݡ���B ����ȥ���쥸����1 */
#define	PBCR2	((HIOREG *)0x5ffffce)	/*  �ݡ���B ����ȥ���쥸����2 */
#define	PADR	((HIOREG *)0x5ffffc0)	/*  �ݡ���A �ǡ����쥸����  	  */

#define PBCR1_TD0_RD0_MASK 	~0xf	/*  TxD0,RxD0ü�������ѥޥ���	*/
#define PBCR1_TD0 		 0x8	/*  TxD0ü�������ѥޥ���  	*/
#define PBCR1_RD0 		 0x2	/*  RxD0ü�������ѥޥ���  	*/


/*
 * �����ߥ���ȥ���쥸����
 */
#define	IPRA	((HIOREG *)0x5ffff84)	/*  ����ߥ�٥�����쥸����  */
#define	IPRB	((HIOREG *)0x5ffff86)
#define	IPRC	((HIOREG *)0x5ffff88)
#define	IPRD	((HIOREG *)0x5ffff8a)
#define	IPRE	((HIOREG *)0x5ffff8c)
#define	ICR	((HIOREG *)0x5ffff8e)	/*  ����ߥ���ȥ���쥸����  */



/*
 * �����ޡ��쥸����
 *����ITU:����ƥ��졼�ƥåɎ������ގ��ѥ륹����˥å�
 */
typedef struct{
    	/*  ����  */
    IOREG  TSTR;	/*  �����ޥ������ȥ쥸����  			*/
    IOREG  TSNC;	/*  �����ޥ��󥯥�쥸����  			*/
    IOREG  TMDR;	/*  �����ޥ⡼�ɥ쥸����  			*/
    IOREG  TFCR;	/*  �����ޥե��󥯥���󥳥�ȥ���쥸����  	*/
	/*  ���  */
    	/*  �����ޥ����ȥץåȥ���ȥ���쥸����TOCR�Ϥ����ǤϤʤ�  	*/

	/*  ITU0  */
    IOREG  TCR0;	/*  �����ޥ���ȥ���쥸����0			*/
    IOREG  TIOR0;	/*  ������I/O����ȥ���쥸����0		*/
    IOREG  TIER0;	/*  �����ޥ��󥿥�ץȥ��͡��֥�쥸����0	*/
    IOREG  TSR0;	/*  �����ޥ��ơ������쥸����0			*/
    HIOREG TCNT0;	/*  �����ޥ�����0		 	 	*/
    HIOREG GRA0;	/*  �����ͥ��쥸����A0	 	 	*/
    HIOREG GRB0;	/*  �����ͥ��쥸����B0	 	 	*/

	/*  ITU1  */
    IOREG  TCR1;	/*  �����ޥ���ȥ���쥸����1			*/
    IOREG  TIOR1;	/*  ������I/O����ȥ���쥸����1		*/
    IOREG  TIER1;	/*  �����ޥ��󥿥�ץȥ��͡��֥�쥸����1	*/
    IOREG  TSR1;	/*  �����ޥ��ơ������쥸����1			*/
    HIOREG TCNT1;	/*  �����ޥ�����1		 	 	*/
    HIOREG GRA1;	/*  �����ͥ��쥸����A1	 	 	*/
    HIOREG GRB1;	/*  �����ͥ��쥸����B1	 	 	*/

	/*  ITU2  */
    IOREG  TCR2;	/*  �����ޥ���ȥ���쥸����2			*/
    IOREG  TIOR2;	/*  ������I/O����ȥ���쥸����2		*/
    IOREG  TIER2;	/*  �����ޥ��󥿥�ץȥ��͡��֥�쥸����2	*/
    IOREG  TSR2;	/*  �����ޥ��ơ������쥸����2			*/
    HIOREG TCNT2;	/*  �����ޥ�����2		 	 	*/
    HIOREG GRA2;	/*  �����ͥ��쥸����A2	 	 	*/
    HIOREG GRB2;	/*  �����ͥ��쥸����B2	 	 	*/

	/*  ITU3  */
    IOREG  TCR3;	/*  �����ޥ���ȥ���쥸����3			*/
    IOREG  TIOR3;	/*  ������I/O����ȥ���쥸����3		*/
    IOREG  TIER3;	/*  �����ޥ��󥿥�ץȥ��͡��֥�쥸����3	*/
    IOREG  TSR3;	/*  �����ޥ��ơ������쥸����3			*/
    HIOREG TCNT3;	/*  �����ޥ�����3		 	 	*/
    HIOREG GRA3;	/*  �����ͥ��쥸����A3	 	 	*/
    HIOREG GRB3;	/*  �����ͥ��쥸����B3	 	 	*/
    HIOREG BRA3;	/*  �Хåե��쥸����A3	 	 		*/
    HIOREG BRB3;	/*  �Хåե��쥸����B3	 	 		*/

    	/*  ����  */
    char   dummy;	/*  ���饤�����Ĵ��  			*/
    IOREG  TOCR;	/*  �����ޥ����ȥץåȥ���ȥ���쥸����  	*/

	/*  ITU4  */
    IOREG  TCR4;	/*  �����ޥ���ȥ���쥸����4			*/
    IOREG  TIOR4;	/*  ������I/O����ȥ���쥸����4		*/
    IOREG  TIER4;	/*  �����ޥ��󥿥�ץȥ��͡��֥�쥸����4	*/
    IOREG  TSR4;	/*  �����ޥ��ơ������쥸����4			*/
    HIOREG TCNT4;	/*  �����ޥ�����4		 	 	*/
    HIOREG GRA4;	/*  �����ͥ��쥸����A4	 	 	*/
    HIOREG GRB4;	/*  �����ͥ��쥸����B4	 	 	*/
    HIOREG BRA4;	/*  �Хåե��쥸����A4	 	 		*/
    HIOREG BRB4;	/*  �Хåե��쥸����B4	 	 		*/
} tmu;

#define ITU  (*(volatile tmu *)0x5ffff00)

#define TSR_IMFA	0x1	/*  GRA����ڥ��ޥå��ե饰  		*/
#define TSTR_STR0	0x1	/*  �����ޥ������ȥӥå�  		*/
#define TCR_CCLR_GRA	0x20	/*  GRA����ڥ��ޥå��ǥ����󥿤򥯥ꥢ */
#define TIER_RESERVE	0x78	/*  TIER�쥸������ͽ��ӥå�  		*/
#define TIER_IMIEA	0x1	/*  GRA����ڥ��ޥå��ˤ�������׵����� */
#define TIOR_RESERVE	0x8	/*  TIOR�쥸������ͽ��ӥå�  		*/
#define TIOR_IOA	0x0	/*  GRA����ڥ��ޥå��ˤ��ü�ҽ��϶ػ� */



/*
 *  ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI)
 */
typedef struct{
	/*  ����ͥ�0  */
    IOREG  SMR0;	/*  ���ꥢ��⡼�ɥ쥸����  			*/
    IOREG  BRR0;	/*  �ӥåȥ졼�ȥ쥸����  			*/
    IOREG  SCR0;	/*  ���ꥢ�륳��ȥ���쥸����		*/
    IOREG  TDR0;	/*  �ȥ�󥹥ߥåȥǡ����쥸����  		*/
    IOREG  SSR0;	/*  ���ꥢ�륹�ơ������쥸����  		*/
    IOREG  RDR0;	/*  �쥷���֥ǡ����쥸����  			*/
    char   dummy1;	/*  ���饤�����Ĵ��  			*/
    char   dummy2;	/*  ���饤�����Ĵ��  			*/

	/*  ����ͥ�1  */
    IOREG  SMR1;	/*  ���ꥢ��⡼�ɥ쥸����  			*/
    IOREG  BRR1;	/*  �ӥåȥ졼�ȥ쥸����  			*/
    IOREG  SCR1;	/*  ���ꥢ�륳��ȥ���쥸����		*/
    IOREG  TDR1;	/*  �ȥ�󥹥ߥåȥǡ����쥸����  		*/
    IOREG  SSR1;	/*  ���ꥢ�륹�ơ������쥸����  		*/
    IOREG  RDR1;	/*  �쥷���֥ǡ����쥸����  			*/
} sci;

#define SCI (*(volatile sci *)0x5fffec0)

/*  ���ꥢ�륹�ơ������쥸����SSR�γƥӥå�  */
#define SSR_TDRE	0x80	/* �ȥ�󥹥ߥåȥǡ����쥸��������ץƥ� */
#define SSR_RDRF	0x40	/* �쥷���֥ǡ����쥸�����ե� 		*/
#define SSR_ORER	0x20	/* �����С���󥨥顼 			*/
#define SSR_FER		0x10	/* �ե졼�ߥ󥰥��顼 			*/
#define SSR_PER		0x08	/* �ѥ�ƥ����顼 			*/
#define SSR_TEND	0x04	/* �ȥ�󥹥ߥåȥ���� 		*/
#define SSR_MPB		0x02	/* �ޥ���ץ��å��ӥå� 		*/
#define SSR_MPBT	0x01	/* �ޥ���ץ��å��ӥåȥȥ�󥹥ե� 	*/

/*  ���ꥢ�륳��ȥ���쥸����SCR�γƥӥå�  */
#define SCR_TIE		0x80	/* �ȥ�󥹥ߥåȥ��󥿥�ץȥ��͡��֥� */
#define SCR_RIE		0x40	/* �쥷���֥��󥿥�ץȥ��͡��֥� 	*/
#define SCR_TE		0x20	/* �ȥ�󥹥ߥåȥ��͡��֥� 		*/
#define SCR_RE		0x10	/* �쥷���֥��͡��֥� 			*/
#define SCR_MPIE	0x08	/* �ޥ���ץ��å����󥿥�ץȥ��͡��֥� */
				/* �ȥ�󥹥ߥåȥ���ɥ��󥿥�ץ�	*/
#define SCR_TEIE	0x04	/* ���͡��֥� 				*/
#define SCR_CKE_MASK	0x03	/* ����å������������ѥޥ���		*/
#define SCR_CKE		0x00	/* ����å����͡��֥�			*/
				/*   Ĵ��Ʊ�����ΤȤ�  			*/
				/*   	��������å�����  		*/
				/*   	���Ϥʤ�  			*/

/*  ���ꥢ��⡼�ɥ�����SMR�γƥӥå�  */
				/* ���ߥ�˥��������⡼�� 	*/
#define SMR_CA_CLOCK	0x80	/* 	����å�Ʊ���� 		*/
#define SMR_CA_ASYNC	0x00	/* 	Ĵ��Ʊ������ 		*/
	/*  Ĵ��Ʊ�����̿�����Asynchronous Communication method */
				/* ����饯����󥰥� 		*/
#define SMR_CHR8	0x00	/* 	8�ӥå� 		*/
#define SMR_CHR7	0x40	/* 	7�ӥå� 		*/
				/* �ѥ�ƥ����͡��֥� 		*/
#define SMR_PE		0x20	/* 	�ѥ�ƥ����� 		*/
#define SMR_PE_NON	0x00	/* 	�ѥ�ƥ��ʤ� 		*/
#define SMR_OE_ODD	0x10	/* �ѥ�ƥ��⡼�ɡʴ���ѥ�ƥ���*/
#define SMR_STOP2	0x08	/* ���ȥåץӥåȥ�󥰥���2 	*/
#define SMR_STOP1	0x00	/* ���ȥåץӥåȥ�󥰥���1 	*/
#define SMR_MP		0x04	/* �ޥ���ץ��å��⡼�� 	*/
/*  ����å���ʬ����ϥܡ��ɰ�¸��sys_config.h��  */


/*
 *  gdb stub�ˤ�����	��ա������ִ�����˻���
 */

Inline int
stub_putc(int c)
{
  Asm("mov #0x00,r0; mov %0,r4; trapa #0x3f"
               : /* no output */
               : "r"(c)
               : "r0","r4");
  return(c);
}

/*
 *  SCI�ˤ�����	���
 */

Inline int
sci_putc(int c)
{
    return(c);
}


/*
 *  ����֥�å����饤�֥��
 *	(ItIs�����ή��)
 *
 *  �ؿ��λ��ͤϡ�ANSI C �饤�֥��λ��ͤ�Ʊ����ɸ��饤�֥��Τ�Τ�
 *  �Ȥä�������Ψ���ɤ���ǽ�������롥
 *
 */

VP _dummy_memcpy(VP dest, VP src, UINT len);

VP memcpy(VP dest, VP src, UINT len);

#endif /* _MACRO_ONLY */

#endif /* _SH1_H_ */
