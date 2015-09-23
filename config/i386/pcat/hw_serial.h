/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 *
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2002 by Monami software, Limited Partners.
 *  Copyright (C) 2002 by MURANAKA Masaki
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
 *  @(#) $Id: hw_serial.h,v 1.2 2002/04/10 12:08:17 honda Exp $
 */

/*
 *	�������åȰ�¸���ꥢ��I/O�⥸�塼���PC/AT�ѡ�
 */

#ifndef _HW_SERIAL_H_
#define _HW_SERIAL_H_

#include "sys_config.h"
#include "cpu_insn.h"
#include "irc.h"

/*
 *  ���ꥢ��I/O�γ���ߥϥ�ɥ�Υ٥����ֹ�
 */
#define INHNO_SERIAL	 (0x24)

/*
 *  ���ꥢ��ݡ��ȤΥϡ��ɥ�������¸��������
 *  Not yet! m68k�Τ褦�˥���ȥ���쥸������¤�Τˤ��롣
 */
typedef struct pcat_hardware_serial_port_descripter {
  INT	    *initflag;	   /* ������ѥե饰�ؤΥݥ���   */
  BOOL    sendflag;      /* ���������ߥ��͡��֥�ե饰 */
  short base_address;
  short com_irq;
} HWPORT;


/*
 *  ���٥�ݡ��Ⱦ�������֥�å��ν����
 */

#define NUM_PORT	1	/* ���ݡ��Ȥ��륷�ꥢ��ݡ��Ȥο� */

static INT	initflag[2] = { 0, 0 } ;	/* ������ѥե饰 */

#define HWPORT1	{ &initflag[0],  0, PCAT_COM1_BASE, PCAT_COM1_IRQ }
#define HWPORT2 { &initflag[1],  0, PCAT_COM2_BASE, PCAT_COM2_IRQ }

Inline short pcat_com_data_port(HWPORT *p)
{
  return p->base_address;
}

Inline short pcat_com_ier_port(HWPORT *p)
{
  return p->base_address + 1;
}

Inline short pcat_com_lsr_port(HWPORT *p)
{
  return p->base_address + 5;
}

#define PCAT_COM_IER_LS (4)
#define PCAT_COM_IER_TX (2)
#define PCAT_COM_IER_RX (1)

/*
 *  ���ꥢ��I/O�ݡ��Ȥν����
 */

Inline BOOL
hw_port_initialize(HWPORT *p)
{
  outb(pcat_com_ier_port(p), 0); // Disable interrupt.
  outb(p->base_address + 3, 0x83); // DLAB=1, 8bit, stop=1, Non parity.
  outb(p->base_address, 0x0c);  // 9600bps
  outb(p->base_address + 1, 0x00);  // 9600bps
  outb(p->base_address + 3, 0x03); // DLAB=0, 8bit, stop=1, Non parity.
  outb(p->base_address + 2, 0x00);  // Disable FIFO.
  irc_ena_irq(p->com_irq);

  outb(p->base_address + 4, 0x0b); // Enable OUT2 interrupt.

  outb(pcat_com_ier_port(p),
       PCAT_COM_IER_LS |
       PCAT_COM_IER_TX |
       PCAT_COM_IER_RX);  // Enable interrupt (Ls & Tx & Rx)

  inb(pcat_com_lsr_port(p));
  inb(pcat_com_data_port(p));
  inb(p->base_address + 2);
  inb(p->base_address + 4);

  *(p->initflag) = 1;			/* ������ե饰���� */
  return(FALSE);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥν�λ
 */
Inline void
hw_port_terminate(HWPORT *p)
{
    
  *(p->initflag) = -1;			/* ������ե饰���� */
  outb(pcat_com_ier_port(p), 0); // Disable interrupt.
  irc_dis_irq(PCAT_COM1_IRQ);
}


/*
 *  ���ꥢ��ݡ��ȳ���ߥ����ӥ��롼������������ȡ�
 */
extern void	serial_handler_in(int portid);
extern void	serial_handler_out(int portid);


#define PCAT_COM_IIR_RLS (0x06)
#define PCAT_COM_IIR_RXD (0x04)
#define PCAT_COM_IIR_TXD (0x02)

//static volatile UW txcount = 0;

/*
 *  ���ꥢ��I/O�ݡ��Ȥγ���ߥϥ�ɥ�
 */
Inline void
hw_serial_handler()
{
  UB comstat;

  irc_eoi_irq(PCAT_COM1_IRQ);

  comstat = inb(PCAT_COM1_BASE + 2) & 0x0f;

  switch (comstat)
    {
    case PCAT_COM_IIR_RLS:
      inb(PCAT_COM1_BASE + 5);
      break;
    case PCAT_COM_IIR_RXD:
      serial_handler_in(1);
      break;
    case PCAT_COM_IIR_TXD:
      serial_handler_out(1);
      break;
    default:
      break;
    }

  irc_ena_irq(PCAT_COM1_IRQ);

}


/*
 *  ʸ���������������
 */
Inline BOOL
hw_port_getready(HWPORT *p)
{
  UB stat;
  stat = inb(pcat_com_lsr_port(p));

  return ((stat & 0x01) != 0);
}

/*
 *  ʸ���������Ǥ��뤫��
 */
Inline BOOL
hw_port_putready(HWPORT *p)
{
  UB stat;
  stat = inb(pcat_com_lsr_port(p));

  return ((stat & 0x60) != 0);
}

/*
 *  ��������ʸ���μ��Ф�
 */
Inline UB
hw_port_getchar(HWPORT *p)
{
  UB ch;
  
  ch = inb(pcat_com_data_port(p));

  return ch;
}

/*
 *  ��������ʸ���ν񤭹���
 */
Inline void
hw_port_putchar(HWPORT *p, UB c)
{
  outb(pcat_com_data_port(p), c);
}

/*
 *  ��������ؿ�
 */
Inline void
hw_port_sendstart(HWPORT *p)
{
  if (p->sendflag == 0)
    {
      UB stat;
      stat = inb(pcat_com_ier_port(p)) | PCAT_COM_IER_TX;
      outb(pcat_com_ier_port(p), stat);
      p->sendflag = 1;
    }
}

Inline void
hw_port_sendstop(HWPORT *p)
{
  if (p->sendflag)
    {
      UB stat;
      outb(p->base_address + 3, 0x03); // DLAB=0, 8bit, stop=1, Non parity.
      stat = inb(pcat_com_ier_port(p)) & ~PCAT_COM_IER_TX;
      outb(pcat_com_ier_port(p), stat);
      p->sendflag = 0;
    }
}


#endif /* _HW_SERIAL_H_ */
