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
 *  @(#) $Id: check.h,v 1.2 2001/09/06 12:39:51 hiro Exp $
 */

/*
 *	���顼�����å��ѥޥ���
 */

#ifndef _CHECK_H_
#define _CHECK_H_

/*
 *  ͥ���٤��ϰϤ�Ƚ��
 */
#define VALID_TPRI(tpri) \
	(TMIN_TPRI <= (tpri) && (tpri) <= TMAX_TPRI)

/*
 *  ������ͥ���٤Υ����å���E_PAR��
 */
#define CHECK_TPRI(tpri) {					\
	if (!VALID_TPRI(tpri)) {				\
		return(E_PAR);					\
	}							\
}

#define CHECK_TPRI_INI(tpri) {					\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_INI)) {	\
		return(E_PAR);					\
	}							\
}

#define CHECK_TPRI_SELF(tpri) {					\
	if (!(VALID_TPRI(tpri) || (tpri) == TPRI_SELF)) {	\
		return(E_PAR);					\
	}							\
}

/*
 *  �����ॢ���Ȼ����ͤΥ����å���E_PAR��
 */
#define CHECK_TMOUT(tmout) {					\
	if (!(TMO_FEVR <= (tmout))) {				\
		return(E_PAR);					\
	}							\
}

/*
 *  ����¾�Υѥ�᡼�����顼�Υ����å���E_PAR��
 */
#define CHECK_PAR(exp) {					\
	if (!(exp)) {						\
		return(E_PAR);					\
	}							\
}

/*
 *  ���֥�������ID���ϰϤ�Ƚ��
 */
#define VALID_TSKID(tskid) \
	(TMIN_TSKID <= (tskid) && (tskid) <= tmax_tskid)

#define VALID_SEMID(semid) \
	(TMIN_SEMID <= (semid) && (semid) <= tmax_semid)

#define VALID_FLGID(flgid) \
	(TMIN_FLGID <= (flgid) && (flgid) <= tmax_flgid)

#define VALID_DTQID(dtqid) \
	(TMIN_DTQID <= (dtqid) && (dtqid) <= tmax_dtqid)

#define VALID_MBXID(mbxid) \
	(TMIN_MBXID <= (mbxid) && (mbxid) <= tmax_mbxid)

#define VALID_MPFID(mpfid) \
	(TMIN_MPFID <= (mpfid) && (mpfid) <= tmax_mpfid)

#define VALID_CYCID(cycid) \
	(TMIN_CYCID <= (cycid) && (cycid) <= tmax_cycid)

/*
 *  ���֥�������ID�Υ����å���E_ID��
 */
#define CHECK_TSKID(tskid) {					\
	if (!VALID_TSKID(tskid)) {				\
		return(E_ID);					\
	}							\
}

#define CHECK_TSKID_SELF(tskid) {				\
	if (!(VALID_TSKID(tskid) || (tskid) == TSK_SELF)) {	\
		return(E_ID);					\
	}							\
}

#define CHECK_SEMID(semid) {					\
	if (!VALID_SEMID(semid)) {				\
		return(E_ID);					\
	}							\
}

#define CHECK_FLGID(flgid) {					\
	if (!VALID_FLGID(flgid)) {				\
		return(E_ID);					\
	}							\
}

#define CHECK_DTQID(dtqid) {					\
	if (!VALID_DTQID(dtqid)) {				\
		return(E_ID);					\
	}							\
}

#define CHECK_MBXID(mbxid) {					\
	if (!VALID_MBXID(mbxid)) {				\
		return(E_ID);					\
	}							\
}

#define CHECK_MPFID(mpfid) {					\
	if (!VALID_MPFID(mpfid)) {				\
		return(E_ID);					\
	}							\
}

#define CHECK_CYCID(cycid) {					\
	if (!VALID_CYCID(cycid)) {				\
		return(E_ID);					\
	}							\
}

/*
 *  �ƽФ�����ƥ����ȤΥ����å���E_CTX��
 */
#define CHECK_TSKCTX() {					\
	if (sense_context()) {					\
		return(E_CTX);					\
	}							\
}

#define CHECK_INTCTX() {					\
	if (!sense_context()) {					\
		return(E_CTX);					\
	}							\
}

/*
 *  �ƽФ�����ƥ����Ȥ�CPU��å����֤Υ����å���E_CTX��
 */
#define CHECK_TSKCTX_UNL() {					\
	if (sense_context() || t_sense_lock()) {		\
		return(E_CTX);					\
	}							\
}

#define CHECK_INTCTX_UNL() {					\
	if (!sense_context() || i_sense_lock()) {		\
		return(E_CTX);					\
	}							\
}

/*
 *  �ǥ����ѥå���α���֤Ǥʤ����Υ����å���E_CTX��
 */
#define CHECK_DISPATCH() {					\
	if (sense_context() || t_sense_lock() || !(enadsp)) {	\
		return(E_CTX);					\
	}							\
}

/*
 *  ����¾�Υ���ƥ����ȥ��顼�Υ����å���E_CTX��
 */
#define CHECK_CTX(exp) {					\
	if (!(exp)) {						\
		return(E_CTX);					\
	}							\
}

/*
 *  ������������ꤷ�Ƥ��ʤ����Υ����å���E_ILUSE��
 */
#define CHECK_NONSELF(tcb) {					\
	if ((tcb) == runtsk) {					\
		return(E_ILUSE);				\
	}							\
}

/*
 *  ����¾���������ѥ��顼�Υ����å���E_ILUSE��
 */
#define CHECK_ILUSE(exp) {					\
	if (!(exp)) {						\
		return(E_ILUSE);				\
	}							\
}

#endif /* _CHECK_H_ */
