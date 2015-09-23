/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: insight_v2mb.h,v 1.1 2002/04/10 09:48:56 honda Exp $
 */

#ifndef _INSIGHT_VIRTEXII_
#define _INSIGHT_VIRTEXII_

#include "microblaze.h"

/*
 * Insight ��7�������ȥɥ饤��
 * I/O�ݡ��Ȥ����num to seg ��ϩ����³���Ƥ��� 
 */

#define SEG_BASE 0xFFFF8200

#define SEG_DATAREG   ((LIOREG *)(SEG_BASE))
#define SEG_TRIREG    ((LIOREG *)(SEG_BASE + 0x04))

#ifndef _MACRO_ONLY
Inline void
led_seg_init(void)
{
  *SEG_TRIREG = 0x00;
}

Inline void
disp_seg(int num)
{
  *SEG_TRIREG = num;
}
#endif /* _MACRO_ONLY */

/*
 *  LCD control
 */
#define LCD_BASE 0xFFE00000

#define LCD_CTL  ((IOREG *)(LCD_BASE))
#define LCD_DATA ((IOREG *)(LCD_BASE + 0x01))


#define LCD_CMD_CLRDP   0x01
#define LCD_CMD_CAHOME  0x02
#define LCD_CMD_MODE    0x04
#define LCD_CMD_DONOFF  0x08
#define LCD_CMD_SHIFT   0x10
#define LCD_CMD_FUNC    0x20
#define LCD_CMD_ADDCGR  0x40
#define LCD_CMD_ADDDDR  0x80
#define LCD_CMD_RESET   0x30

#define LCD_MODE_IORD   0x02
#define LCD_MODE_DSHIFT 0x01

#define LCD_DONOFF_DON  0x04
#define LCD_DONOFF_CUR  0x02
#define LCD_DONOFF_BLK  0x01

#define LCD_SHIFT_DSHIFT 0x08
#define LCD_SHIFT_RIGHT  0x04

#define LCD_FUNC_8BIT    0x10
#define LCD_FUNC_2LINE   0x08
#define LCD_FUNC_BDOT    0x04

#define LCD_BF           0x80

#define LCD_NUM_ROW      2
#define LCD_NUM_COL      16


#ifndef _MACRO_ONLY

Inline void
lcd_delay_loop(int wait){
  for(; wait > 0 ; wait--);
}


Inline void
lcd_delay_bf(void){
    while((*LCD_CTL & LCD_BF) == LCD_BF);
    lcd_delay_loop(10);
}


Inline void
lcd_write_cmd(char cmd){
  *LCD_CTL = cmd;
}


Inline void
lcd_clr_disp(void){
  lcd_delay_bf();
  lcd_write_cmd(LCD_CMD_CLRDP);
}


Inline void
lcd_cur_at_home(void){
  lcd_delay_bf();
  lcd_write_cmd(LCD_CMD_CAHOME);
}


Inline void
lcd_write_char(char c){
  lcd_delay_bf();
  *LCD_DATA = c;
}

#endif /* _MACRO_ONLY */
#endif /* _INSIGHT_VIRTEXII_ */
