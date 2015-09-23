/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2001-2003 by Industrial Technology Institute,
 *                              Miyagi Prefectural Government, JAPAN
 *  Copyright (C) 2001-2003 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *  Copyright (C) 2003 by Katsuhiro Amano
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
 *  @(#) $Id: cpu_config.c,v 1.9 2003/12/11 07:00:10 honda Exp $
 */

#include "jsp_kernel.h"
#include "check.h"
#include "task.h"

#include <hw_serial.h>

/*
 *  �ץ��å���¸�⥸�塼���H8�ѡ�
 */

/*
 *  �󥿥�������ƥ����ȤǤγ���ߥޥ���
 */

UB	int_intmask = 0;

/*
 *  ����ߥͥ��ȥ�����
 */

UW	intnest = 0;

/*
 *  �٥����ơ��֥�ν������for RedBoot��
 */
#ifdef REDBOOT
#define VECTOR_TABLE_ADDR 	0x00fffd20
#define JMP_OPECODE		0x5a000000
extern void	vectors(void);

static void
vector_table_copy(void)
{
	unsigned int n = 0x100/sizeof(unsigned int);		/* �٥����ơ��֥륵���� */
	unsigned int *o = (unsigned int *)VECTOR_TABLE_ADDR;	/* �٥����ơ��֥륳�ԡ��� */
	unsigned int *i = (unsigned int *)vectors;		/* �٥����ơ��֥륳�ԡ��� */

    while (n -- > 0)
        *o ++ = JMP_OPECODE | (*i ++);		/* jmp̿����ղ� */

}
#endif	/* of #ifdef REDBOOT */

/*
 *  �ץ��å���¸�ν����
 */

void
cpu_initialize()
{
	SCI_initialize(SYSTEM_PORTID);

#ifdef REDBOOT
	vector_table_copy();
#endif	/* of #ifdef REDBOOT */
	}

/*
 *  �ץ��å���¸�ν�λ����
 */

void
cpu_terminate()
{
}

/*
 * ��Ͽ����Ƥ��ʤ������ߤ�ȯ������ȸƤӽФ����
 */

void cpu_experr(EXCSTACK *sp)
{
    syslog(LOG_EMERG, "Unexpected interrupt.");
    syslog(LOG_EMERG, "PC  = %08x SP  = %08x", sp->pc, sp - 32);
    syslog(LOG_EMERG, "ER0 = %08x ER1 = %08x ER2 = %08x ER3 = %08x",
                       sp->er0, sp->er1, sp->er2, sp->er3);
    syslog(LOG_EMERG, "ER4 = %08x ER5 = %08x ER6 = %08x",
                       sp->er4, sp->er5, sp->er6);
    while(1)
    	;
}

/*
 *   �����ƥ�ʸ��������λ���
 */

void
cpu_putc(char c)
{
    if (c == '\n') {
        SCI_wait_putchar(SYSTEM_SCI, '\r');
    }
    SCI_wait_putchar(SYSTEM_SCI, c);
}

/*
 *  local_memcpy
 *
 *    ɸ�� C �饤�֥��� memcpy ��Ʊ�������ॳ�ԡ��ؿ�
 *    ��󥯻��˥��顼��ȯ�����뤿�ᡢ̾�����Ѥ��Ƥ��롣
 *    �ޤ�����󥯥�����ץȤκǸ�ιԤ�
 *
 *       PROVIDE(_memcpy = _local_memcpy);
 *
 *    ���ɲä�����
 */

void *
local_memcpy (void *out, const void *in, unsigned int n)
{
    char *o = out;
    const char *i = in;

    while (n -- > 0)
        *o ++ = *i ++;
    return out;
}
