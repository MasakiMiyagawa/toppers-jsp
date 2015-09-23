/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: kernel.h,v 1.6 2001/09/11 03:52:27 hiro Exp $
 */

/*
 *	��ITRON4.0����ɸ�।�󥯥롼�ɥե�����
 *
 *  ���Υե�����Ǥϡ�����������ɥץ�ե������ɬ�פʤ�Τ����������
 *  �Ƥ��롥�ǡ�����������ϡ�����������ɥץ�ե���������������礦��
 *  ��Ĺ���ˤϤ��Ƥ��ʤ���
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 */

#ifndef _KERNEL_H_
#define _KERNEL_H_

/*
 *  ITRON���Ͷ��̵���Υǡ�������������ޥ���
 */
#include <itron.h>

/*
 *  �����ƥ��ץ��å��˰�¸�������
 */
#include <sys_defs.h>
#include <cpu_defs.h>

/*
 *  ����ޥ���
 */
#define	TROUND_VP(sz)	(((sz) + sizeof(VP) - 1) & ~(sizeof(VP) - 1))
#define	TCOUNT_VP(sz)	(((sz) + sizeof(VP) - 1) / sizeof(VP))

/*
 *  �ǡ����������
 */
#ifndef _MACRO_ONLY

typedef	UINT		TEXPTN;		/* �������㳰�װ��Υӥåȥѥ����� */
typedef	UINT		FLGPTN;		/* ���٥�ȥե饰�Υӥåȥѥ����� */

typedef	struct t_msg {			/* �᡼��ܥå����Υ�å������إå� */
	struct t_msg	*next;
} T_MSG;

typedef	struct t_msg_pri {		/* ͥ�����դ���å������إå� */
	T_MSG		msgque;		/* ��å������إå� */
	PRI		msgpri;		/* ��å�����ͥ���� */
} T_MSG_PRI;

#endif /* _MACRO_ONLY */

/*
 *  �����ӥ�����������
 */
#ifndef _MACRO_ONLY

/*
 *  ������������ǽ
 */
extern ER	act_tsk(ID tskid);
extern ER	iact_tsk(ID tskid);
extern ER_UINT	can_act(ID tskid);
extern void	ext_tsk(void);
extern ER	ter_tsk(ID tskid);
extern ER	chg_pri(ID tskid, PRI tskpri);
extern ER	get_pri(ID tskid, PRI *p_tskpri);

/*
 *  ��������°Ʊ����ǽ
 */
extern ER	slp_tsk(void);
extern ER	tslp_tsk(TMO tmout);
extern ER	wup_tsk(ID tskid);
extern ER	iwup_tsk(ID tskid);
extern ER_UINT	can_wup(ID tskid);
extern ER	rel_wai(ID tskid);
extern ER	irel_wai(ID tskid);
extern ER	sus_tsk(ID tskid);
extern ER	rsm_tsk(ID tskid);
extern ER	frsm_tsk(ID tskid);
extern ER	dly_tsk(RELTIM dlytim);

/*
 *  �������㳰������ǽ
 */
extern ER	ras_tex(ID tskid, TEXPTN rasptn);
extern ER	iras_tex(ID tskid, TEXPTN rasptn);
extern ER	dis_tex(void);
extern ER	ena_tex(void);
extern BOOL	sns_tex(void);

/*
 *  Ʊ�����̿���ǽ
 */
extern ER	sig_sem(ID semid);
extern ER	isig_sem(ID semid);
extern ER	wai_sem(ID semid);
extern ER	pol_sem(ID semid);
extern ER	twai_sem(ID semid, TMO tmout);

extern ER	set_flg(ID flgid, FLGPTN setptn);
extern ER	iset_flg(ID flgid, FLGPTN setptn);
extern ER	clr_flg(ID flgid, FLGPTN clrptn);
extern ER	wai_flg(ID flgid, FLGPTN waiptn,
			MODE wfmode, FLGPTN *p_flgptn);
extern ER	pol_flg(ID flgid, FLGPTN waiptn,
			MODE wfmode, FLGPTN *p_flgptn);
extern ER	twai_flg(ID flgid, FLGPTN waiptn,
			MODE wfmode, FLGPTN *p_flgptn, TMO tmout);

extern ER	snd_dtq(ID dtqid, VP_INT data);
extern ER	psnd_dtq(ID dtqid, VP_INT data);
extern ER	ipsnd_dtq(ID dtqid, VP_INT data);
extern ER	tsnd_dtq(ID dtqid, VP_INT data, TMO tmout);
extern ER	fsnd_dtq(ID dtqid, VP_INT data);
extern ER	ifsnd_dtq(ID dtqid, VP_INT data);
extern ER	rcv_dtq(ID dtqid, VP_INT *p_data);
extern ER	prcv_dtq(ID dtqid, VP_INT *p_data);
extern ER	trcv_dtq(ID dtqid, VP_INT *p_data, TMO tmout);

extern ER	snd_mbx(ID mbxid, T_MSG *pk_msg);
extern ER	rcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER	prcv_mbx(ID mbxid, T_MSG **ppk_msg);
extern ER	trcv_mbx(ID mbxid, T_MSG **ppk_msg, TMO tmout);

/*
 *  ����ס��������ǽ
 */
extern ER	get_mpf(ID mpfid, VP *p_blk);
extern ER	pget_mpf(ID mpfid, VP *p_blk);
extern ER	tget_mpf(ID mpfid, VP *p_blk, TMO tmout);
extern ER	rel_mpf(ID mpfid, VP blk);

/*
 *  ���ִ�����ǽ
 */
extern ER	set_tim(SYSTIM *p_systim);
extern ER	get_tim(SYSTIM *p_systim);
extern ER	isig_tim(void);

extern ER	sta_cyc(ID cycid);
extern ER	stp_cyc(ID cycid);

/*
 *  �����ƥ���ִ�����ǽ
 */
extern ER	rot_rdq(PRI tskpri);
extern ER	irot_rdq(PRI tskpri);
extern ER	get_tid(ID *p_tskid);
extern ER	iget_tid(ID *p_tskid);
extern ER	loc_cpu(void);
extern ER	iloc_cpu(void);
extern ER	unl_cpu(void);
extern ER	iunl_cpu(void);
extern ER	dis_dsp(void);
extern ER	ena_dsp(void);
extern BOOL	sns_ctx(void);
extern BOOL	sns_loc(void);
extern BOOL	sns_dsp(void);
extern BOOL	sns_dpn(void);

/*
 *  �����ȼ������ӥ�������
 */
extern BOOL	vxsns_ctx(VP p_excinf);
extern BOOL	vxsns_loc(VP p_excinf);
extern BOOL	vxsns_dsp(VP p_excinf);
extern BOOL	vxsns_dpn(VP p_excinf);
extern BOOL	vxsns_tex(VP p_excinf);

#endif /* _MACRO_ONLY */

/*
 *  ���֥�������°�������
 */
#define TA_HLNG		0x00		/* �������ѥ��󥿥ե����� */
#define TA_ASM		0x01		/* ������֥�����ѥ��󥿥ե����� */

#define TA_TFIFO	0x00		/* ���������Ԥ������FIFO��� */
#define TA_TPRI		0x01		/* ���������Ԥ������ͥ���ٽ�� */

#define TA_MFIFO	0x00		/* ��å��������塼��FIFO��� */
#define TA_MPRI		0x02		/* ��å��������塼��ͥ���ٽ�� */

#define TA_ACT		0x02		/* ��������ư���줿���֤����� */

#define TA_WSGL		0x00		/* ���٥�ȥե饰���Ԥ���������1�Ĥ� */
#define TA_CLR		0x04		/* ���٥�ȥե饰�Υ��ꥢ���� */

#define	TA_STA		0x02		/* �����ϥ�ɥ��ư����֤����� */

/*
 *  �����ӥ��������ư��⡼�ɤ����
 */
#define	TWF_ANDW	0x00		/* ���٥�ȥե饰��AND�Ԥ� */
#define	TWF_ORW		0x01		/* ���٥�ȥե饰��OR�Ԥ� */

/*
 *  ����¾����������
 */
#define	TSK_SELF	0		/* ������������ */
#define	TSK_NONE	0		/* �������륿�������ʤ� */
#define	TPRI_SELF	0		/* ���������Υ١���ͥ���٤λ��� */
#define	TPRI_INI	0		/* �������ε�ư��ͥ���٤λ��� */

/*
 *  ��������ȥޥ���
 */

/*
 *  ͥ���٤��ϰ�
 */
#define	TMIN_TPRI	1		/* ������ͥ���٤κǾ��� */
#define	TMAX_TPRI	16		/* ������ͥ���٤κ����� */
#define	TMIN_MPRI	1		/* ��å�����ͥ���٤κǾ��� */
#define	TMAX_MPRI	16		/* ��å�����ͥ���٤κ����� */

/*
 *  �С���������
 */
#define	TKERNEL_MAKER	0x0002		/* �����ͥ�Υ᡼���������� */
#define	TKERNEL_PRID	0x0101		/* �����ͥ�μ����ֹ� */
#define	TKERNEL_SPVER	0x5401		/* ITRON���ͤΥС�������ֹ� */
#define	TKERNEL_PRVER	0x1020		/* �����ͥ�ΥС�������ֹ� */

/*
 *  ���塼���󥰡��ͥ��Ȳ���κ�����
 */
#define	TMAX_ACTCNT	1		/* ��ư�׵ᥭ�塼���󥰿��κ����� */
#define	TMAX_WUPCNT	1		/* �����׵ᥭ�塼���󥰿��κ����� */
#define	TMAX_SUSCNT	1		/* �����Ԥ��׵�ͥ��ȿ��κ����� */

/*
 *  �ӥåȥѥ�����Υӥåȿ�
 */
#define	TBIT_TEXPTN	(sizeof(TEXPTN) * 8)	/* �������㳰�װ��Υӥåȿ� */
#define	TBIT_FLGPTN	(sizeof(FLGPTN) * 8)	/* ���٥�ȥե饰�Υӥåȿ� */

#endif /* _KERNEL_H_ */
