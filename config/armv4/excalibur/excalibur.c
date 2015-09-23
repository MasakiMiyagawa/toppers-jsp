/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: excalibur.c,v 1.5 2003/12/24 08:00:42 honda Exp $
 */

/*
 *    Excalibur-ARM ������ǽ�ѥɥ饤��
 */
#include <s_services.h>
#include <excalibur.h>

/*
 * ����UART�� �ʰ�SIO�ɥ饤��
 */

/*
 *  ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
typedef struct sio_port_initialization_block {

} SIOPINIB;

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å�
 */
struct sio_port_control_block {
    const SIOPINIB  *siopinib; /* ���ꥢ��I/O�ݡ��Ƚ�����֥�å� */
    VP_INT          exinf;     /* ��ĥ���� */
    BOOL    openflag;          /* �����ץ�Ѥߥե饰 */
    BOOL    sendflag;          /* ��������ߥ��͡��֥�ե饰 */
    BOOL    getready;          /* ʸ��������������� */
    BOOL    putready;          /* ʸ���������Ǥ������ */
};

/*
 * ���ꥢ��I/O�ݡ��Ƚ�����֥�å�
 */
const SIOPINIB siopinib_table[TNUM_SIOP] = {{}};

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å��Υ��ꥢ
 */
SIOPCB  siopcb_table[TNUM_SIOP];

/*
 *  ���ꥢ��I/O�ݡ���ID��������֥�å�����Ф�����Υޥ���
 */
#define INDEX_SIOP(siopid)  ((UINT)((siopid) - 1))
#define get_siopcb(siopid)  (&(siopcb_table[INDEX_SIOP(siopid)]))


/*
 * ʸ�������������?
 */ 
Inline BOOL
uart_getready(SIOPCB *siopcb)
{
    return((sil_rew_mem((VP)UART_RSR) & UART_RSR_RX_LEVEL) > 0x00);
}

/*
 * ʸ���������Ǥ��뤫?
 */
Inline BOOL
uart_putready(SIOPCB *siopcb)
{
  return((sil_rew_mem((VP)UART_TSR) & UART_TSR_TX_LEVEL) < UART_TX_FIFO_MAX);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline UB
uart_getchar(SIOPCB *siopcb)
{
    return((UB)sil_rew_mem((VP)UART_RD));  
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
uart_putchar(SIOPCB *siopcb, UB c)
{
    sil_wrw_mem((VP)UART_TD, (VW)c);
}

/*
 *  ��������ߵ���
 */
Inline void
uart_enable_send(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)UART_IES,(VW)UART_INT_T);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_send(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)UART_IEC,(VW)UART_INT_T);
}

/*
 *  ��������ߵ���
 */
Inline void
uart_enable_rcv(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)UART_IES,(VW)UART_INT_R);
}

/*
 *  ��������߶ػ�
 */
Inline void
uart_disable_rcv(SIOPCB *siopcb)
{
    sil_wrw_mem((VP)UART_IEC,(VW)UART_INT_R);
}



/*
 * �����ͥ뵯ư���Υ������Ѥν����
 */
void
uart_init(void){
    /* Data 8bit, 1 stop bit, No parity */
    sil_wrw_mem((VP)UART_MC,(VW)UART_DATA_FOMAT);
    
    /* Set bound rate */
    sil_wrw_mem((VP)UART_DIV_LO,(VW)(CAL_BPS(UART_BPS,AHB1_CLK/2) & 0xff));
    sil_wrw_mem((VP)UART_DIV_HI,
                (VW)(CAL_BPS(UART_BPS,AHB1_CLK/2) & 0xff00) >> 8);

    /* clear FIFO  TxThr = 0 RxThr = 1*/
    sil_wrw_mem((VP)UART_FCR,(VW)(UART_FCR_TC | UART_FCR_RC));
  
    /* Clear interrupt */
    sil_wrw_mem((VP)UART_IEC,
                (VW)(UART_INT_R | UART_INT_T | UART_INT_TI | UART_INT_M));
}


/*
 *  ������åפ�UART����Υݡ���󥰽���
 */
void
uart_putc(char c)
{
    UW buf_level;
    
    do{
        buf_level = sil_rew_mem((VP)UART_TSR) & UART_TSR_TX_LEVEL;
    }while(buf_level >= UART_TX_FIFO_MAX);
    
    sil_wrw_mem((VP)UART_TD,(VW)c);
}

/*
 *  SIO�ɥ饤�Фν�����롼����
 *  1�ݡ��Ȥ����ʤ����ᡤ���ޤ��̣�Ϥʤ�
 */
void
uart_initialize()
{
    SIOPCB  *siopcb;
    UINT    i;

    /*
     *  ���ꥢ��I/O�ݡ��ȴ����֥�å��ν����
     */
    for (siopcb = siopcb_table, i = 0; i < TNUM_SIOP; siopcb++, i++) {
        siopcb->siopinib = &(siopinib_table[i]);
        siopcb->openflag = FALSE;
        siopcb->sendflag = FALSE;
    }
}

/*
 * �����ץ󤷤Ƥ���ݡ��Ȥ����뤫
 */
BOOL
uart_openflag(void)
{
    return(siopcb_table[0].openflag);
}


/*
 * ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
uart_opn_por(ID siopid, VP_INT exinf)
{
    SIOPCB      *siopcb;
    const SIOPINIB  *siopinib;

    siopcb = get_siopcb(siopid);
    siopinib = siopcb->siopinib;

    uart_init();
    
    /* Data 8bit, 1 stop bit, No parity */
    sil_wrw_mem((VP)UART_MC,(VW)UART_DATA_FOMAT);
    
    /* Set bound rate */
    sil_wrw_mem((VP)UART_DIV_LO,(VW)(CAL_BPS(UART_BPS,AHB1_CLK/2) & 0xff));
    sil_wrw_mem((VP)UART_DIV_HI,
                (VW)(CAL_BPS(UART_BPS,AHB1_CLK/2) & 0xff00) >> 8);

    /* clear FIFO  TxThr = 0 RxThr = 1*/
    sil_wrw_mem((VP)UART_FCR,(VW)(UART_FCR_TC | UART_FCR_RC));
  
    /* Clear interrupt */
    sil_wrw_mem((VP)UART_IEC,
                (VW)(UART_INT_R | UART_INT_T | UART_INT_TI | UART_INT_M));

    /* ��������ߵ��� */
    sil_wrw_mem((VP)UART_IES,(VW)UART_INT_R);
    
    siopcb->exinf = exinf;
    siopcb->getready = siopcb->putready = FALSE;
    siopcb->openflag = TRUE;

    return(siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
uart_cls_por(SIOPCB *siopcb)
{
    siopcb->openflag = FALSE;
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
BOOL
uart_snd_chr(SIOPCB *siopcb, char c)
{
    if (uart_putready(siopcb)){
        uart_putchar(siopcb, c);
        return(TRUE);
    }
    return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
INT
uart_rcv_chr(SIOPCB *siopcb)
{
    if (uart_getready(siopcb)) {
        return((INT)(UB) uart_getchar(siopcb));
    }
    return(-1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
uart_ena_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            uart_enable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            uart_enable_rcv(siopcb);
            break;
    }
}


/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
uart_dis_cbr(SIOPCB *siopcb, UINT cbrtn)
{
    switch (cbrtn) {
        case SIO_ERDY_SND:
            uart_disable_send(siopcb);
            break;
        case SIO_ERDY_RCV:
            uart_disable_rcv(siopcb);
            break;
    }
}



/*
 *  ���ꥢ��I/O�ݡ��Ȥ��Ф������߽���
 */
static void
uart_isr_siop(SIOPCB *siopcb)
{
    if (uart_getready(siopcb)) {
        /*
         *  �������Υ�����Хå��롼�����ƤӽФ���
         */
        uart_ierdy_rcv(siopcb->exinf);
    }
    if (uart_putready(siopcb)) {
        /*
         *  ������ǽ������Хå��롼�����ƤӽФ���
         */
        uart_ierdy_snd(siopcb->exinf);
    }
}


/*
 *  SIO�γ���ߥ����ӥ��롼����
 */
void
uart_isr()
{
    uart_isr_siop(&(siopcb_table[0]));
}

