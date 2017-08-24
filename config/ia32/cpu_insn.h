/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000,2001 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2002 by Monami software, Limited Partners.
 *  Copyright (C) 2008-     by Monami Software Limited Partnership, JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: cpu_insn.h,v 1.1 2004/07/21 02:49:36 monaka Exp $
 */

#ifndef	_CPU_INSN_H_
#define	_CPU_INSN_H_

#ifndef _MACRO_ONLY

Inline void disint(void) {
	Asm("cli");
}

Inline void enaint(void) {
	Asm("sti");
}

Inline void write_msr(UW msr, UW low, UW high)
{
	asm volatile("wrmsr"
		:
		: "c" (msr), "a" (low), "d" (high)
		: "memory");
}

Inline void read_msr(UW msr, UW *low, UW *high)
{
	UW _low = 0;
	UW _high = 0;
	
	asm volatile("rdmsr"
		: "=a" (_low), "=d" (_high)
		: "c" (msr));

	*low = _low;
	*high = _high;
}

Inline UD rdtsc(void)
{
	UD ret = 0;
	asm volatile("rdtsc" : "=A" (ret));
	return ret;
}

Inline void cpuid(UW *eax, UW *ebx, UW *ecx, UW *edx)
{
	UW _eax, _ebx, _ecx, _edx;

	_eax = *eax;

	asm volatile("cpuid"
		: "=a" (_eax), "=b" (_ebx), "=c" (_ecx), "=d" (_edx)
		: "a" (_eax));

	*eax = _eax;
	*ebx = _ebx;
	*ecx = _ecx;
	*edx = _edx;	
}

#endif /* _MACRO_ONLY */

#endif	/* _CPU_INSN_H_ */
