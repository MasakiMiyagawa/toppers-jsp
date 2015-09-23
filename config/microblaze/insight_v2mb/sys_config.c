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
 *  @(#) $Id: sys_config.c,v 1.2 2002/04/10 09:48:56 honda Exp $
 */

#include "jsp_kernel.h"
#include "insight_v2mb.h"
#include "microblaze.h"

/*
 *  �������åȥ����ƥ��¸ ������롼�����Insight VirtexII�ѡ�
 */
void
sys_initialize()
{
  led_seg_init(); /* 7SEG �ν���� */
  lcd_init();     /* LCD�ν����   */
  lcd_write_string("TOPPERS/JSP Kernel Start!");
}


/*
 *  �������åȥ����ƥ�ν�λ�롼����
 *
 *  �����ƥ��λ������˻Ȥ����̾�ϥ�˥��ƤӽФ��Ǽ¸����롥
 *  
 */
void
sys_exit(void)
{

}

void
sys_putc(char c)
{
    if (c == '\n') {
        uart_putc('\r');
    }
    uart_putc(c);
}


/*
 *  LCD���롼����
 */
void
lcd_init(void)
{
  /* first reset */
  lcd_write_cmd(LCD_CMD_RESET);
  lcd_delay_loop(10000);

  /* second reset */
  lcd_write_cmd(LCD_CMD_RESET);
  lcd_delay_loop(10000);

  /* third reset */
  lcd_write_cmd(LCD_CMD_RESET);
  lcd_delay_loop(10000);

  /* setup interface size , row and font size */
  lcd_write_cmd(LCD_CMD_FUNC | LCD_FUNC_8BIT | LCD_FUNC_2LINE);
  lcd_delay_loop(10000);

  /* turn off */
  lcd_write_cmd(LCD_CMD_DONOFF);
  lcd_delay_loop(10000);

  /* clear display */
  lcd_write_cmd(LCD_CMD_CLRDP);
  lcd_delay_loop(10000);

  /* setup mode */
  lcd_write_cmd(LCD_CMD_MODE | LCD_MODE_IORD);
  lcd_delay_loop(10000);

  /* display on, cursor on , blink on */
  lcd_write_cmd(LCD_CMD_DONOFF | LCD_DONOFF_DON | LCD_DONOFF_CUR | LCD_DONOFF_BLK);
}



BOOL
lcd_set_cur_posi(int row, int col)
{
  unsigned char addr;

  if(row >= LCD_NUM_ROW)
    return FALSE;

  if(col >= LCD_NUM_COL)
    return FALSE;

  addr = (row == 0)? 0x00 : 0x40;
  addr += col;
  
  lcd_delay_bf();
  lcd_write_cmd(LCD_CMD_ADDDDR | addr);

  return TRUE;
}



void
lcd_write_string(char *string)
{
  int row,col;
  
  lcd_clr_disp();
  lcd_cur_at_home();

  for(row = 0; row < LCD_NUM_ROW; row++){
    for(col = 0; col < LCD_NUM_COL; col++){
      lcd_set_cur_posi(row,col);
      if(*string == '\0')
        return;
      else
        lcd_write_char(*(string++));
      
    }
  }
}

