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
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�Xstprmy16�ѡ�
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include <s_services.h>

/*
 *  SIO�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SIO   INHNO_UART

/*
 *  ���ꥢ��I/O�ݡ��ȴ����֥�å������
 */
typedef struct sio_port_control_block {
    const UH uhMagic ;
    const UH uhBase ;
    const UH uhExcpMask ;
    VP_INT vpiExinf ;
    B bNotExist ;
    B bOpened ;
    B bTxIe ;
    B bRxIe ;
    B bLastIsCr ;
} SIOPCB;

/*
 *  ������Хå��롼����μ����ֹ�
 */
#define SIO_ERDY_SND    1u      /* ������ǽ������Хå� */
#define SIO_ERDY_RCV    2u      /* �������Υ�����Хå� */

/*
 *  SIO�ɥ饤�Фν�����롼����
 */
extern void sio_initialize(void) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
extern SIOPCB *sio_opn_por(ID siopid, VP_INT exinf) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
extern void sio_cls_por(SIOPCB *siopcb) throw() ;

/*
 *  SIO�γ���ߥϥ�ɥ�
 */
extern void sio_handler(void) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
extern BOOL sio_snd_chr(SIOPCB *siopcb, char c) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
extern INT sio_rcv_chr(SIOPCB *siopcb) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
extern void sio_ena_cbr(SIOPCB *siopcb, UINT cbrtn) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
extern void sio_dis_cbr(SIOPCB *siopcb, UINT cbrtn) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
extern void sio_ierdy_snd(VP_INT exinf) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
extern void sio_ierdy_rcv(VP_INT exinf) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ���Ʊ��ʸ������
 */
extern void sio_asnd_chr( INT c ) throw() ;

/*
 *  ���ꥢ��I/O�ݡ��Ȥ������Ʊ��ʸ������
 */
extern INT sio_arcv_chr( void ) throw() ;

#endif /* _HW_SERIAL_H_ */
