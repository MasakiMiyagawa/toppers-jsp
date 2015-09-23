/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ��ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ�
 *  �եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ�����
 *  �ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ�������Х��ʥꥳ���ɤη��ޤ��ϵ�����Ȥ߹����������
 *      �Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
 *    (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
 *        ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
 *        ���ȡ�
 *  (3) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
 *  �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
 *  �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
 *  ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
 * 
 *  @(#) $Id: sample1.c,v 1.1 2000/11/14 16:28:41 honda Exp $
 */

/* 
 *  ����ץ�ץ����(1)������
 *
 *  JSP�����ͥ�δ���Ū��ư����ǧ���뤿��Υ���ץ�ץ���ࡥ
 *
 *  �ץ����γ���:
 *
 *  �桼�����󥿥ե�������������ĥᥤ�󥿥����ʥ�����ID: MAIN_TASK��
 *  ͥ����: MAIN_PRIORITY�ˤȡ����Ĥ�����¹Ԥ���륿�����ʥ�����ID:
 *  TASK1��TASK3�����ͥ����: MID_PRIORITY�ˤǹ�������롥�ޤ�����ư��
 *  ����2�äμ����ϥ�ɥ�ʼ����ϥ�ɥ�ID: CYCHDR1�ˤ��Ѥ��롥
 *
 *  ����¹Ԥ���륿�����ϡ�TASK_LOOP ����롼�פ�¹Ԥ����٤ˡ�������
 *  ���¹���Ǥ��뤳�Ȥ򤢤�魯��å�������ɽ�����롥
 *
 *  �����ϥ�ɥ�ϡ����Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��
 *  LOW_PRIORITY�ˤΥ�ǥ����塼���ž�����롥�ץ����ε�ưľ��ϡ�
 *  �����ϥ�ɥ����߾��֤ˤʤäƤ��롥
 *
 *  �ᥤ�󥿥����ϡ����ꥢ��I/O�ݡ��Ȥ����ʸ�����Ϥ�Ԥ���ʸ�����Ϥ�
 *  �ԤäƤ���֤ϡ�����¹Ԥ���륿�������¹Ԥ���Ƥ���ˡ����Ϥ��줿
 *  ʸ�����б�����������¹Ԥ��롥���Ϥ��줿ʸ���Ƚ����δط��ϼ����̤ꡥ
 *  Control-C �ޤ��� 'Q' �����Ϥ����ȡ��ץ�����λ���롥
 *
 *  '1' : �ʹߤΥ��ޥ�ɤ� TASK1 ���Ф��ƹԤ���
 *  '2' : �ʹߤΥ��ޥ�ɤ� TASK2 ���Ф��ƹԤ���
 *  '3' : �ʹߤΥ��ޥ�ɤ� TASK3 ���Ф��ƹԤ���
 *  'a' : �������� act_tsk �ˤ�굯ư���롥
 *  'A' : ���������Ф��뵯ư�׵�� can_act �ˤ�ꥭ��󥻥뤹�롥
 *  'e' : �������� ext_tsk ��ƤӽФ�������λ�����롥
 *  't' : �������� ter_tsk �ˤ�궯����λ���롥
 *  '>' : ��������ͥ���٤� HIGH_PRIORITY �ˤ��롥
 *  '=' : ��������ͥ���٤� MID_PRIORITY �ˤ��롥
 *  '<' : ��������ͥ���٤� LOW_PRIORITY �ˤ��롥
 *  'G' : ��������ͥ���٤� get_pri ���ɤ߽Ф���
 *  's' : �������� slp_tsk ��ƤӽФ����������Ԥ��ˤ����롥
 *  'S' : �������� tslp_tsk(10��) ��ƤӽФ����������Ԥ��ˤ����롥
 *  'w' : �������� wup_tsk �ˤ�굯�����롥
 *  'W' : ���������Ф��뵯���׵�� can_wup �ˤ�ꥭ��󥻥뤹�롥
 *  'l' : �������� rel_wai �ˤ�궯��Ū���Ԥ�����ˤ��롥
 *  'u' : �������� sus_tsk �ˤ�궯���Ԥ����֤ˤ��롥
 *  'm' : �������ζ����Ԥ����֤� rsm_tsk �ˤ�������롥
 *  'M' : �������ζ����Ԥ����֤� frsm_tsk �ˤ�궯��������롥
 *  'd' : �������� dly_tsk(10��) ��ƤӽФ��������ַв��Ԥ��ˤ����롥
 *  'x' : �������˥ѥ����� 0x0001 ���㳰�������׵᤹�롥
 *  'X' : �������˥ѥ����� 0x0002 ���㳰�������׵᤹�롥
 *  'r' : ���Ĥ�ͥ���١�HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY�ˤ�
 *        ��ǥ����塼���ž�����롥
 *  'c' : �����ϥ�ɥ��ư����롥
 *  'C' : �����ϥ�ɥ����ߤ����롥
 *  'v' : ȯ�Ԥ��������ƥॳ�����ɽ�����롥
 *  'q' : ȯ�Ԥ��������ƥॳ�����ɽ�����ʤ��ʥǥե���ȡˡ�
 */

#include <jsp_services.h>
#include "kernel_id.h"
#include "sample1.h"

/*
 *  �¹Լ¹Ԥ���륿�����ؤΥ�å������ΰ�
 */
char message[3];

/*
 *  �¹Լ¹Ԥ���륿����
 */
void task(VP_INT exinf)
{
	INT	i, n = 0;
	INT	tskno = (INT) exinf;
	char	*graph[] = { "|", "  +", "    *" };
	char	c;

	ena_tex();
	while (1) {
                syslog(LOG_NOTICE, "task%d is running (%03d).   %s",
					tskno, ++n, graph[tskno-1]);
		for (i = 0; i < TASK_LOOP; i++);
		c = message[tskno-1];
		message[tskno-1] = 0;
		switch (c) {
		case 'e':
			syslog(LOG_INFO, "#%d#ext_tsk()", tskno);
			ext_tsk();
		case 's':
			syslog(LOG_INFO, "#%d#slp_tsk()", tskno);
			syscall(slp_tsk());
			break;
		case 'S':
			syslog(LOG_INFO, "#%d#tslp_tsk(10000)", tskno);
			syscall(tslp_tsk(10000));
			break;
		case 'd':
			syslog(LOG_INFO, "#%d#dly_tsk(10000)", tskno);
			syscall(dly_tsk(10000));
			break;
		case 'z':
			syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0);
			break;
		case 'Z':
			loc_cpu();
			syslog(LOG_NOTICE, "zerodiv = %d", 10 / 0);
			unl_cpu();
			break;
		default:
			break;
		}
	}
}

/*
 *  �¹Ԥ��Ƽ¹Ԥ���륿�����ѤΥ������㳰�����롼����
 */
void tex_routine(TEXPTN texptn, VP_INT exinf)
{
	INT	i;
	INT	tskno = (INT) exinf;

	syslog(LOG_NOTICE, "task%d receives exception 0x%04x. ",
					tskno, texptn);
	for (i = 0; i < TEX_LOOP; i++);
}

/*
 *  ����������Ф���CPU�㳰�ϥ�ɥ�
 */
void
zerodiv_handler(VP p_excinf)
{
	ID	tskid;
	VW	*frame = p_excinf;

	syslog(LOG_NOTICE, "Zero Divide Stack Frame: %08x %08x %08x",
				*frame, *(frame+1), *(frame+2));
	syslog(LOG_NOTICE,
		"vxsns_loc = %d vxsns_ctx = %d vxsns_dsp = %d vxsns_dpn = %d",
		vxsns_loc(p_excinf), vxsns_ctx(p_excinf),
		vxsns_dsp(p_excinf), vxsns_dpn(p_excinf));

	if (!vxsns_loc(p_excinf) && !vxsns_ctx(p_excinf)) {
		syscall(iget_tid(&tskid));
		syscall(iras_tex(tskid, 0x8000));
	}
}

/*
 *  �����ϥ�ɥ�
 *
 *  HIGH_PRIORITY��MID_PRIORITY��LOW_PRIORITY �γ�ͥ���٤Υ�ǥ����塼
 *  ���ž�����롥
 */
void cyclic_handler(VP_INT exinf)
{
	irot_rdq(HIGH_PRIORITY);
	irot_rdq(MID_PRIORITY);
	irot_rdq(LOW_PRIORITY);
}

/*
 *  �ᥤ�󥿥���
 */
void main_task(VP_INT exinf)
{
	char	buf[1];
	ID	tskid = TASK1;
	INT	tskno = 1;
	ER_UINT	ercd;	
	PRI	tskpri;



	syslog(LOG_NOTICE, "Sample task starts (exinf = %d).", exinf);

	serial_ioctl(0, (IOCTL_CRLF | IOCTL_RAW | IOCTL_IXON | IOCTL_IXOFF));
    
	act_tsk(TASK1);
	act_tsk(TASK2);
	act_tsk(TASK3);

	do {
		serial_read(0, buf, 1);
		switch (buf[0]) {
		case 'e':
		case 's':
		case 'S':
		case 'd':
		case 'z':
		case 'Z':
			message[tskno-1] = buf[0];
			break;
		case '1':
			tskno = 1;
			tskid = TASK1;
			break;
		case '2':
			tskno = 2;
			tskid = TASK2;
			break;
		case '3':
			tskno = 3;
			tskid = TASK3;
			break;
		case 'a':
			syslog(LOG_INFO, "#act_tsk(%d)", tskno);
			syscall(act_tsk(tskid));
			break;
		case 'A':
			syslog(LOG_INFO, "#can_act(%d)", tskno);
			syscall(ercd = can_act(tskid));
			if (MERCD(ercd) >= 0) {
				syslog(LOG_NOTICE, "can_act(%d) returns %d",
						tskid, ercd);
			}
			break;
		case 't':
			syslog(LOG_INFO, "#ter_tsk(%d)", tskno);
			syscall(ter_tsk(tskid));
			break;
		case '>':
			syslog(LOG_INFO, "#chg_pri(%d, HIGH_PRIORITY)", tskno);
							
			chg_pri(tskid, HIGH_PRIORITY);
			break;
		case '-':
			syslog(LOG_INFO, "#chg_pri(%d, MID_PRIORITY)", tskno);
			chg_pri(tskid, MID_PRIORITY);
			break;
		case '<':
			syslog(LOG_INFO, "#chg_pri(%d, LOW_PRIORITY)", tskno);
			chg_pri(tskid, LOW_PRIORITY);
			break;
		case 'G':
			syslog(LOG_INFO, "#get_pri(%d, &tskpri)", tskno);
			syscall(ercd = get_pri(tskid, &tskpri));
			if (MERCD(ercd) >= 0) {
				syslog(LOG_NOTICE, "priority of task %d is %d",
						tskid, tskpri);
			}
			break;
		case 'w':
			syslog(LOG_INFO, "#wup_tsk(%d)", tskno);
			syscall(wup_tsk(tskid));
			break;
		case 'W':
			syslog(LOG_INFO, "#can_wup(%d)", tskno);
			syscall(ercd = can_wup(tskid));
			if (MERCD(ercd) >= 0) {
				syslog(LOG_NOTICE, "can_wup(%d) returns %d",
						tskid, ercd);
			}
			break;
		case 'l':
			syslog(LOG_INFO, "#rel_wai(%d)", tskno);
			syscall(rel_wai(tskid));
			break;
		case 'u':
			syslog(LOG_INFO, "#sus_tsk(%d)", tskno);
			syscall(sus_tsk(tskid));
			break;
		case 'm':
			syslog(LOG_INFO, "#rsm_tsk(%d)", tskno);
			syscall(rsm_tsk(tskid));
			break;
		case 'M':
			syslog(LOG_INFO, "#frsm_tsk(%d)", tskno);
			syscall(frsm_tsk(tskid));
			break;
		case 'x':
			syslog(LOG_INFO, "#ras_tsk(%d, 0x0001)", tskno);
			syscall(ras_tex(tskid, 0x0001));
			break;
		case 'X':
			syslog(LOG_INFO, "#ras_tsk(%d, 0x0002)", tskno);
			syscall(ras_tex(tskid, 0x0002));
			break;
		case 'r':
			syslog(LOG_INFO, "#rot_rdq(three priorities)");
			rot_rdq(HIGH_PRIORITY);
			rot_rdq(MID_PRIORITY);
			rot_rdq(LOW_PRIORITY);
			break;
		case 'c':
			sta_cyc(CYCHDR1);
			break;
		case 'C':
			stp_cyc(CYCHDR1);
			break;
		case 'v':
			setlogmask(LOG_UPTO(LOG_INFO));
			break;
		case 'q':
			setlogmask(LOG_UPTO(LOG_NOTICE));
			break;
		default:
			break;
		}
	} while (buf[0] != '\003' && buf[0] != 'Q');

	syslog(LOG_NOTICE, "Sample task ends.");
	kernel_exit();
}
