
/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: sh4.h,v 1.1 2001/11/05 13:31:13 honda Exp $
 */

#ifndef _SH4_H_
#define _SH4_H_

/*
 *  SH4(SH7750)�������쥸�������
 */
typedef unsigned char   byte;
typedef volatile byte   IOREG;          
typedef unsigned short  word;
typedef volatile word   HIOREG;
typedef volatile int    LIOREG;


/*
 *  �㳰���٥�ȥ쥸����
 */
#define TRA	        0xff000020
#define EXPEVT	    0xff000024
#define INTEVT	    0xff000028


/*
 *   �Х����ơ��ȥ���ȥ����Ϣ
 */
#define	RFCR	((HIOREG *)(0xff800028))	

#define    RFCR_CLEAR         0xa400

/*
 * �����ߤˤ�ä� INTEVT �쥸���������ꤵ�����
 */
#define    TMU0_INTEVT        0x400
#define    SCI_RXI_INTEVT     0x500
#define    SCI_TXI_INTEVT     0x520
#define    SCI_ERI_INTEVT     0x4e0
#define    SCIF_RXI_INTEVT    0x720
#define    SCIF_TXI_INTEVT    0x760
#define    SCIF_BRI_INTEVT    0x740


        
/*
 * ����ߥ���ȥ���쥸����
 */
#define	ICR     ((HIOREG *)(0xffd00000))	
#define	IPRA	((HIOREG *)(0xffd00004))		
#define	IPRB	((HIOREG *)(0xffd00008))		
#define	IPRC	((HIOREG *)(0xffd0000c))	
#define	IPRD	((HIOREG *)(0xffd00010))	


/*
 * �����ޡ��쥸����
 */
typedef struct{
    IOREG  TOCR;
    HIOREG dummy1;
    IOREG  TSTR;
    IOREG  dummy2;
    LIOREG TCOR0;
    LIOREG TCNT0;
    HIOREG TCR0;
    LIOREG TCOR1;
    LIOREG TCNT1;
    HIOREG TCR1;
    LIOREG TCOR2;
    LIOREG TCNT2;
    HIOREG TCR2;
} tmu;

#define TMU  (*(volatile tmu *)0xffd80000)
                              
#define	TMU_STR0	0x01
#define	TMU_STR1	0x02
#define	TMU_STR2	0x04
#define TCR_UNF     0x0100    



/*
 *
 *  ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI)
 *
 */
#define SCI_SCSMR1  ((IOREG *)(0xffe00000))
#define SCI_SCBRR1  ((IOREG *)(0xffe00004))
#define SCI_SCSCR1  ((IOREG *)(0xffe00008))
#define SCI_SCTDR1  ((IOREG *)(0xffe0000c))
#define SCI_SCSSR1  ((IOREG *)(0xffe00010))
#define SCI_SCRDR1  ((IOREG *)(0xffe00014))
#define SCI_SCSPTR1 ((IOREG *)(0xffe0001c))


#define	SCSMR_CHR	  0x0040
#define	SCSMR_PE	  0x0020
#define	SCSMR_OE	  0x0010
#define	SCSMR_STOP	  0x0008
#define	SCSMR_CKS1	  0x0002
#define	SCSMR_CKS0	  0x0001

#define SCSCR_TIE	  0x0080
#define SCSCR_RIE	  0x0040
#define SCSCR_TE	  0x0020
#define SCSCR_RE	  0x0010
#define SCSCR_CKE1	  0x0002
#define SCSCR_CKE0	  0x0001

#define SCSSR_TDRE	  0x80
#define SCSSR_RDRF	  0x40
#define SCSSR_ORER	  0x20
#define SCSSR_FER	  0x10
#define SCSSR_PER	  0x08
#define SCSSR_TEND	  0x04
#define SCSSR_MPB	  0x02
#define SCSSR_MPBT	  0x01



/*
 *
 *  FIFO�դ����ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCIF)�쥸����
 *
 */
#define SCIF_SCSMR2  ((HIOREG *)(0xffe80000))
#define SCIF_SCBRR2  ((IOREG  *)(0xffe80004))
#define SCIF_SCSCR2  ((HIOREG *)(0xffe80008))
#define SCIF_SCFTDR2 ((IOREG  *)(0xffe8000c))
#define SCIF_SCFSR2  ((HIOREG *)(0xffe80010))
#define SCIF_SCFRDR2 ((IOREG  *)(0xffe80014))
#define SCIF_SCFCR2  ((HIOREG *)(0xffe80018))
#define SCIF_SCFDR2  ((HIOREG *)(0xffe8001c))
#define	SCIF_SCSPTR2 ((HIOREG *)(0xffe80020))
#define	SCIF_SCLSR2	 ((HIOREG *)(0xffe80024))	


#define	SCSMR2_CHR	  0x0040
#define	SCSMR2_PE	  0x0020
#define	SCSMR2_OE	  0x0010
#define	SCSMR2_STOP	  0x0008
#define	SCSMR2_CKS1	  0x0002
#define	SCSMR2_CKS0	  0x0001

#define SCSCR2_TIE	  0x0080
#define SCSCR2_RIE	  0x0040
#define SCSCR2_TE	  0x0020
#define SCSCR2_RE	  0x0010
#define SCSCR2_CKE1	  0x0002
#define SCSCR2_CKE0	  0x0001

#define SCFSR2_ER	  0x0080
#define SCFSR2_TEND	  0x0040
#define SCFSR2_TDFE	  0x0020
#define SCFSR2_BRK	  0x0010
#define SCFSR2_FER	  0x0008
#define SCFSR2_PER	  0x0004
#define SCFSR2_RDF	  0x0002
#define SCFSR2_DR	  0x0001


#define SCFCR2_RTRG1  0x0080
#define SCFCR2_RTRG0  0x0040
#define SCFCR2_TTRG1  0x0020
#define SCFCR2_TTRG0  0x0010
#define SCFCR2_MCE	  0x0008
#define SCFCR2_TFRST  0x0004
#define SCFCR2_RFRST  0x0002
#define SCFCR2_LOOP	  0x0001


#define SCSPTR2_RTSIO  0x0080
#define SCSPTR2_RTSDT  0x0040
#define SCSPTR2_CTSIO  0x0020
#define SCSPTR2_CTSDT  0x0010
#define SCSPTR2_SPB2IO 0x0002
#define SCSPTR2_SPB2DT 0x0001



/*
 * ����å�������쥸����
 */
#define	CCR	((LIOREG *)0xff00001c)	



#endif /* _SH4_H_ */






