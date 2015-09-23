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
 *  @(#) $Id: itron.h,v 1.2 2000/11/24 06:05:04 hiro Exp $
 */

/*
 *	ITRON���Ͷ��̵���Υǡ�������������ޥ���
 *
 *  ���Υե�����ˤϡ�����������ɥץ�ե�����ˤ�ɬ�פʤ������ޤ��
 *  ���롥�ǡ�����������ϡ�����������ɥץ�ե���������������礦�ɤ�
 *  Ĺ���ˤϤ��Ƥ��ʤ���
 *  ������֥����Υ������ե�����䥷���ƥॳ��ե�����졼�����ե�
 *  ���뤫�餳�Υե�����򥤥󥯥롼�ɤ�����ϡ�_MACRO_ONLY ���������
 *  �������Ȥǡ��ޥ�������ʳ��ε��Ҥ�������Ȥ��Ǥ��롥
 *
 *  ���Υե�������Υǡ�����������ϡ�����ѥ���˱������ѹ�����ɬ�פ�
 *  ���롥�ޤ����������åȤ˱������ѹ����������⤷��ʤ������塤������
 *  �������åȰ�¸���˰�ư����ʤɤ��ѹ���Ԥ���ǽ�������롥
 */

#ifndef _ITRON_H_
#define _ITRON_H_

/*
 *  ITRON���Ͷ��̥ǡ�����
 */
#ifndef _MACRO_ONLY

#define	__bool	int			/* �֡��뷿 */
#ifndef _MSC_VER
#define	__int8	char			/* 8�ӥåȤ������� */
#define	__int16	short			/* 16�ӥåȤ������� */
#define	__int32	int			/* 32�ӥåȤ������� */
#define __int64	long long		/* 64�ӥåȤ������� */
#endif /* _MSC_VER */

typedef	signed __int8	B;		/* ����դ�8�ӥå����� */
typedef	signed __int16	H;		/* ����դ�16�ӥå����� */
typedef	signed __int32	W;		/* ����դ�32�ӥå����� */
typedef	signed __int64	D;		/* ����դ�64�ӥå����� */

typedef	unsigned __int8		UB;	/* ���̵��8�ӥå����� */
typedef	unsigned __int16 	UH;	/* ���̵��16�ӥå����� */
typedef	unsigned __int32	UW;	/* ���̵��32�ӥå����� */
typedef	unsigned __int64	UD;	/* ���̵��64�ӥå����� */

typedef	__int8		VB;		/* ������ޤ�ʤ�8�ӥåȤ��� */
typedef	__int16		VH;		/* ������ޤ�ʤ�16�ӥåȤ��� */
typedef	__int32		VW;		/* ������ޤ�ʤ�32�ӥåȤ��� */
typedef	__int64		VD;		/* ������ޤ�ʤ�64�ӥåȤ��� */

typedef	void		*VP;		/* ������ޤ�ʤ���ΤؤΥݥ��� */
typedef	void		(*FP)();	/* �ץ����ε�ư���ϡʥݥ��󥿡� */

typedef signed int	INT;		/* �����ʥ�����������դ����� */
typedef unsigned int	UINT;		/* �����ʥ����������̵������ */

typedef __bool		BOOL;		/* ������ */

typedef INT		FN;		/* ��ǽ������ */
typedef	INT		ER;		/* ���顼������ */
typedef	INT		ID;		/* ���֥������Ȥ�ID�ֹ� */
typedef	UINT		ATR;		/* ���֥������Ȥ�°�� */
typedef	UINT		STAT;		/* ���֥������Ȥξ��� */
typedef	UINT		MODE;		/* �����ӥ��������ư��⡼�� */
typedef	INT		PRI;		/* ͥ���� */
typedef	UINT		SIZE;		/* �����ΰ�Υ����� */

typedef	INT		TMO;		/* �����ॢ���Ȼ��� */
typedef	UINT		RELTIM;		/* ���л��� */
typedef	UINT		SYSTIM;		/* �����ƥ���� */

typedef	VP		VP_INT;		/* VP �ޤ��� INT */

typedef	INT		ER_BOOL;	/* ER �ޤ��� BOOL */
typedef	INT		ER_ID;		/* ER �ޤ��� ID */
typedef	INT		ER_UINT;	/* ER �ޤ��� UINT */

#endif /* _MACRO_ONLY */

/*
 *  ITRON���Ͷ������
 */

/*
 *  ����
 */
#define	NULL		0		/* ̵���ݥ��� */
#define	TRUE		1		/* �� */
#define	FALSE		0		/* �� */
#define	E_OK		0		/* ���ｪλ */

/*
 *  ���顼������
 */
#define	E_SYS		(-5)		/* �����ƥ२�顼 */
#define	E_NOSPT		(-9)		/* ̤���ݡ��ȵ�ǽ */
#define	E_RSFN		(-10)		/* ͽ��ǽ������ */
#define	E_RSATR		(-11)		/* ͽ��°�� */
#define	E_PAR		(-17)		/* �ѥ�᡼�����顼 */
#define	E_ID		(-18)		/* ����ID�ֹ� */
#define	E_CTX		(-25)		/* ����ƥ����ȥ��顼 */
#define	E_MACV		(-26)		/* ���ꥢ��������ȿ */
#define	E_OACV		(-27)		/* ���֥������ȥ���������ȿ */
#define	E_ILUSE		(-28)		/* �����ӥ��������������� */
#define	E_NOMEM		(-33)		/* ������­ */
#define	E_NOID		(-34)		/* ID�ֹ���­ */
#define	E_OBJ		(-41)		/* ���֥������Ⱦ��֥��顼 */
#define	E_NOEXS		(-42)		/* ���֥�������̤���� */
#define	E_QOVR		(-43)		/* ���塼���󥰥����С��ե� */
#define	E_RLWAI		(-49)		/* �Ԥ����֤ζ������ */
#define	E_TMOUT		(-50)		/* �ݡ���󥰼��Ԥޤ��ϥ����ॢ���� */
#define	E_DLT		(-51)		/* �Ԥ����֥������Ȥκ�� */
#define	E_CLS		(-52)		/* �Ԥ����֥������Ȥξ����Ѳ� */
#define	E_WBLK		(-57)		/* �Υ�֥�å��󥰼��դ� */
#define	E_BOVR		(-58)		/* �Хåե������С��ե� */

/*
 *  ���֥�������°��
 */
#define	TA_NULL		0		/* ���֥�������°������ꤷ�ʤ� */

/*
 *  �����ॢ���Ȼ���
 */
#define TMO_POL		0		/* �ݡ���� */
#define TMO_FEVR	(-1)		/* �ʵ��Ԥ� */
#define TMO_NBLK	(-2)		/* �Υ�֥�å��� */

/*
 *  ITRON���Ͷ��̥ޥ���
 */

/*
 *  ���顼�����ɼ�Ф��ޥ���
 */
#define	MERCD(ercd)	((ER)((B)(ercd)))
#define	SERCD(ercd)	((ercd) >> 8)

#endif /* _ITRON_H_ */
