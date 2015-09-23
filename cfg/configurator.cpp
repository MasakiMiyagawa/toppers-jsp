/*
 *  Toppers/JSP Kernel
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
 *  @(#) $Id: configurator.cpp,v 1.7 2001/05/07 07:23:44 takayuki Exp $
 */

// Configurator.cpp : ���󥽡��� ���ץꥱ��������ѤΥ���ȥ� �ݥ���Ȥ����
//

#define APPNAME "Configurator"

#include "manager.h"
#include "simpleparser.h"
#include "exception.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	Manager mainapp(new SimpleParser);
	char * sourcefilename = NULL;
	int i;
	
	for(i=1;i<argc;i++)
	{
		if( *(argv[i]) == '-')
		{
			switch(*(argv[i]+1))
			{
			case 'O':
				mainapp.SetOption(Manager::CREATEORTIFILE);
				break;

			case '-':
				if( strcmp(argv[i]+2, "odl") == 0)
				{
					mainapp.SetOption(Manager::CREATEORTIFILE);
					break;
				}
				
			default:
				fprintf(stderr, MSG_UNKNOWNOPTION "\n", argv[i]);	
				return EXIT_FAILURE;
			}
		}else
		{
			if(sourcefilename == NULL)
				sourcefilename = argv[i];
			else{
				fputs(MSG_ALREADYGIVENSRCFILE "\n",stderr);
				return EXIT_FAILURE;
			}
		}
	}

	try
	{
		mainapp.Body(sourcefilename);
	}
	catch(Exception e)
	{
		fputs("Program was aborted with fatal errors\n",stderr);
		fputs(e,stderr);
		fputc('\n',stderr);
	}
	return EXIT_SUCCESS;
}
