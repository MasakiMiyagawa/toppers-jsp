/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2004 by Ryosuke Takeuchi
 *              Platform Development Center RIOCH COMPANY,LTD. JAPAN
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
 *  @(#) $Id: m16coffset.cpp,v 1.1 2004/05/27 12:13:17 honda Exp $
 */
// m16coffset.cpp : ���󥽡��� ���ץꥱ��������ѤΥ���ȥ� �ݥ���Ȥ����
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>

#define	BUF_SIZE		512
#define	STR_SIZE		128

#define	NORMAL_STATE	0
#define	CHECK_STATE		1

struct OFF {
	int		no;
	char	no_value[2][STR_SIZE];
	char	no_label[STR_SIZE];
};

static char const version[] = "01.00";
static char const default_input_file[] = "makeoffset.a30";
static char const default_output_file[] = "offset.inc";
static char const lf[] = "\n";

static char input_file[STR_SIZE];
static char output_file[STR_SIZE];
static int  num_offset = 0;
static int  offset_state = NORMAL_STATE;
static struct OFF off_table[20];

unsigned int atoh(char* s);
void itos(unsigned int i, char* s);
void itoh(unsigned int i, char* s);
static bool test_string(char** s, char const * t);
static bool skip_space(char** s);
static bool skip_char(char** s, char const c);

int main(int argc, char* argv[])
{
	FILE* pfo;
	FILE* pfi;
	struct OFF *v;
	int i, j, k, m;
	char* s;
	char* p;
	char* p2;
	char  buf[BUF_SIZE];
	char  c;

	strcpy(input_file, default_input_file);
	strcpy(output_file, default_output_file);

	for(i = 1 ; i < argc ; i++){
		s = argv[i];
		if(*s++ == '-'){
			c = *s;
			while(*s != 0){
				if(*s == ':')
					break;
				s++;
			}
			if(*s++ == ':'){
				switch(c){
				case 'O':		// �����ȥץåȥե����������
				case 'o':
					strcpy(output_file, s);
					break;
				case 'R':		// ����ץåȥե����������
				case 'r':
					strcpy(input_file, s);
					break;
				default:
					printf("m16coffset -R:input_file -O:output_file\n");
					break;
				}
			}
		}
	}
	printf("version      = %s\n", version);
	printf("input file   = %s\n", input_file);
	printf("output file  = %s\n", output_file);

	if((pfi = fopen(input_file, "r")) == NULL){
		fprintf(stderr, "can't open input file!");
		exit(1);
	}
	if((pfo = fopen(output_file, "w")) == NULL){
		fclose(pfi);
		fprintf(stderr, "can't open output file!");
		exit(1);
	}

	for(;;){
		if((fgets(buf, BUF_SIZE, pfi)) == NULL)
			break;
		s = buf;
		switch(offset_state){
		case CHECK_STATE:
			if(test_string(&s, "! END")){
				num_offset++;
				offset_state = NORMAL_STATE;
				continue;
			}
			if(skip_space(&s))
				continue;
			v = &off_table[num_offset];
			p = &v->no_value[v->no][0];
			if(test_string(&s, "or.w")){
				if(skip_char(&s, '#'))
					continue;
				if(v->no == 0){
					if(skip_char(&s, ','))
						continue;
				}
				while(*s != ',' && *s > ' ')
					*p++ = *s++;
			}
			else if(test_string(&s, "mov.w")){
				if(skip_char(&s, '#'))
					continue;
				while(*s != ',' && *s > ' ')
					*p++ = *s++;
			}
			else if(test_string(&s, "bset")){
				skip_space(&s);
				p2 = &v->no_value[v->no+1][0];
				while(*s != ',' && *s > ' ')
					*p2++ = *s++;
				s++;
				while(*s != ',' && *s > ' ')
					*p++ = *s++;
				v->no++;
			}
			else
				continue;
			v->no++;
			break;
		default:
			if(!test_string(&s, "! BEGIN"))
				continue;
			if(skip_space(&s))
				continue;
			p = off_table[num_offset].no_label;
			while(*s > ' ')
				*p++ = *s++;
			*p++ = 0;
			off_table[num_offset].no = 0;
			offset_state = CHECK_STATE;
			break;
		}
	}
	for(i = 0 ; i < num_offset ; i++){
		v = &off_table[i];
		fputs(v->no_label, pfo);
		fputs("\t.equ\t", pfo);
		itos(atoh(v->no_value[0]), buf);
		fputs(buf, pfo);
		fputs(lf, pfo);
		printf("%s = %s\n", v->no_label, buf);
		if(v->no > 1){
			for(k = m = 0 ; v->no_value[1][k] >= ' ' ; k++){
				if(v->no_value[1][k] == 'H' || v->no_value[1][k] == 'h'){
					m = 1;
					break;
				}
			}
			if(m == 0){
				j = 1 << atoi(v->no_value[1]);
				itoh(j, buf);
				fputs("TCB_enatex_mask\t.equ\t", pfo);
				fputs(buf, pfo);
				fputs("H", pfo);
				fputs(lf, pfo);
				printf("TCB_enatex_mask = %sH\n",buf);
				fputs("TCB_enatex_bit\t.equ\t", pfo);
				fputs(v->no_value[1], pfo);
				fputs(lf, pfo);
				printf("TCB_enatex_bit = %s\n", v->no_value[1]);
				break;
			}
			else{
				fputs("TCB_enatex_mask\t.equ\t", pfo);
				fputs(v->no_value[1], pfo);
				fputs(lf, pfo);
				printf("TCB_enatex_mask = %s\n", v->no_value[1]);
				p = v->no_value[1];
				j = atoh(p);
				for(k = 0 ; k < 16 ; k++){
					if(j & (1<<k))
						break;
				}
				itos(k, buf);
				fputs("TCB_enatex_bit\t.equ\t", pfo);
				fputs(buf, pfo);
				fputs(lf, pfo);
				printf("TCB_enatex_bit = %s\n", buf);
			}
		}
	}
	return 0;
}

/*
 * 16��ʸ�����Х��ʥ���Ѵ�
 */
unsigned int atoh(char* s)
{
	int i = 0;
	for(;;){
		if(*s >= '0' && *s <= '9')
			i = (i * 16) + (*s - '0');
		else if(*s >= 'A' && *s <= 'F')
			i = (i * 16) + (*s - 'A' + 10);
		else if(*s >= 'a' && *s <= 'f')
			i = (i * 16) + (*s - 'a' + 10);
		else
			break;
		s++;
	}
	return i;
}
 
/*
 * �Х��ʥ��10��ʸ������Ѵ�
 */
void itos(unsigned int i, char* s)
{
	if(i >= 10)
		*s++ = (i / 10) + '0';
	*s++ = (i % 10) + '0';
	*s++ = 0;
}

/*
 * �Х��ʥ��16��ʸ������Ѵ�
 */
void itoh(unsigned int i, char* s)
{
	int j, k;

	for(j = 3 ; j >= 0 ; j--){
		k = (i >> (j*4)) & 15;
		if(k >= 10)
			*s++ = (k-10)+'a';
		else
			*s++ = k+'0';
	}
	*s++ = 0;
}

 /*
 * ʸ�������Ӥ���Ʊ��ʤ��TURE
 */
static bool test_string(char** s, char const *t)
{
	char*  p;
	char   c;

	p = *s;
	while(*p <= ' '){
		if(*p == 0)
			return false;
		p++;
	}
	while((c = *p++) != 0){
		if(c != *t++)
			break;
		if(*t == 0){
			*s = p;
			return true;
		}
	}
	return false;
}

/*
 * ����Υ���饯���ޤǥ����å�
 */
static bool skip_char(char** s, char const c)
{
	char* p;

	p = *s;
	while(*p != c){
		if(*p == 0)
			break;
		p++;
	}
	if(*p){
		p++;
		*s = p;
		return false;
	}
	else{
		*s = p;
		return true;
	}
}

/*
 * ���ڡ����ޤ��ϥ��֤򥹥��åפ���
 */
static bool skip_space(char** s)
{
	char* p;

	p = *s;
	while(*p <= ' '){
		if(*p == 0)
			break;
		p++;
	}
	*s = p;
	if(*p)
		return false;
	else
		return true;
}
