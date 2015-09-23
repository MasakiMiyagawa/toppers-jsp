/*
 *  @(#) $Id: sample1.h,v 1.1 2000/11/14 16:29:22 takayuki Exp $
 */

/* 
 *  ����ץ�ץ����(1)�Υإå��ե�����
 */

#define TASK_LOOP	(0x2ffffff)		/* ��������ǤΥ롼�ײ�� */
#define TEX_LOOP	500000		/* �㳰�����롼������ǤΥ롼�ײ�� */

#define MAIN_PRIORITY	5		/* �ᥤ�󥿥�����ͥ���� */
					/* HIGH_PRIORITY ���⤯���뤳�� */

#define HIGH_PRIORITY	9		/* ����˼¹Ԥ���륿������ͥ���� */
#define MID_PRIORITY	10
#define LOW_PRIORITY	11

#define	STACK_SIZE	8192		/* �������Υ����å������� */

extern void	task(VP_INT tskno);
extern void	tex_routine(TEXPTN texptn, VP_INT tskno);
extern void	main_task(VP_INT exinf);

extern void	cyclic_handler(VP_INT exinf);
