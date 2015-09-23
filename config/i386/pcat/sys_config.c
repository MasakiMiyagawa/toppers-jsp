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
 *  @(#) $Id: sys_config.c,v 1.2 2002/04/10 12:08:17 honda Exp $
 */

/*
 *	�������åȥ����ƥ��¸�⥸�塼���PC/AT�ѡ�
 */

#include "jsp_kernel.h"
#include "cpu_insn.h"

#include "irc.h"
#include "irc_inline.h"

/*
 *  �������åȥ����ƥ��¸�ν����
 */
void
sys_initialize()
{
	irc_initialize();
}

/*
 *  �������åȥ����ƥ�ν�λ
 */
void
sys_exit(void)
{
	while(1);
}

ER irc_eoi_irq(UB irq)
{
	UW mask;
	BOOL cpu_locked;

	cpu_locked = sense_lock();

	if(!cpu_locked)
	{
		i386_lock_cpu();
	}

	mask = 1 << (irq & 7);
	if (irq < 8)
	{
		outb(0x21, inb(0x21) | mask);/* block the irq */
		outb(0x20, 0x20);/* acknowledge the irq */

		outb(0x20, 0x0B);
		if (inb(0x20) & mask)
			syslog_0(LOG_EMERG, "irq still active");
	}
	else 
	{
		unsigned foo;

		outb(0xA1, inb(0xA1) | mask);/* block */
		outb(0xA0, 0x20);/* acknowledge */

		outb(0xA0, 0x0B);
		if ((foo = inb(0xA0)) == 0)
			outb(0x20, 0x20);
		if (foo & mask)
		syslog_0(LOG_EMERG, "irqslave still active");
	}

	if(!cpu_locked)
	{
		i386_unlock_cpu();
	}

	return E_OK;
}

ER irc_dis_irq(UB irq)
{
	BOOL cpu_locked;

	cpu_locked = sense_lock();

	if(!cpu_locked)
	{
		i386_lock_cpu();
	}

	if(irq < 8)
	{
		outb(0x21, inb(0x21) | (1 << irq));
	}
	else
	{
		outb(0xA1, inb(0xA1) | (1 << (irq - 8)));
	}

	if(!cpu_locked)
	{
		i386_unlock_cpu();
	}

	return E_OK;
}

ER irc_ena_irq(UB irq)
{
	BOOL cpu_locked;

	cpu_locked = sense_lock();

	if(!cpu_locked)
	{
		i386_lock_cpu();
	}

	if(irq < 8)
	{
		outb(0x21, inb(0x21) & ~(1 << irq));
	}
	else
	{
		outb(0xA1, inb(0xA1) & ~(1 << (irq - 8)));
	}

	if(!cpu_locked)
	{
		i386_unlock_cpu();
	}

	return E_OK;
}


#ifdef WITH_STUB
#error "WITH_STUB option isn't supported in this release."
#define SYS_PUT_CHAR(c) stub_putc(c)
#else
#include "serial.h"	/*  serial_write( )  */
#define SYS_PUT_CHAR(c) {		\
	char cc=c;			\
	serial_write(1, &cc, 1);	\
}
#endif /* WITH_STUB */

void
sys_putc(char c)
{
    if (c == '\n') {
        SYS_PUT_CHAR('\r');
    }
    SYS_PUT_CHAR(c);
}
