
        �� TOPPERS/JSP�����ͥ� �桼�����ޥ˥奢�� ��
                    ��m16c:TM��ȯ�Ķ���

        ��Release 1.4 �б����ǽ�����: 31-Jan-2004��

------------------------------------------------------------------------
 TOPPERS/JSP Kernel
     Toyohashi Open Platform for Embedded Real-Time Systems/
     Just Standard Profile Kernel

 Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
                             Toyohashi Univ. of Technology, JAPAN
 Copyright (C) 2003-2004 by Platform Development Center
                                         RIOCH COMPANY,LTD. JAPAN

 �嵭����Ԥϡ��ʲ��� (1)��(4) �ξ�狼��Free Software Foundation 
 �ˤ�äƸ�ɽ����Ƥ��� GNU General Public License �� Version 2 �˵�
 �Ҥ���Ƥ���������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ�����
 ����Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
 ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
     ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
     ����������˴ޤޤ�Ƥ��뤳�ȡ�
 (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
     �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
     �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
     ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
     �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
     �ȡ�
   (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
       �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
   (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
       ��𤹤뤳�ȡ�
 (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
     ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�

 �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����
 �ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ
 ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
------------------------------------------------------------------------

���Υɥ�����ȤǤϡ���ͥ����ƥ��Υ��Ҥ���ȯ�����ġ������Ѥ���
m16c-CPU����Ѥ���OAKS16��OAKS16 MINI�ܡ����Ѥ�TOPPERS/JSP��ɬ�פʥ�
������ˤĤ��Ʋ��⤹�롥

1. �ǥ��쥯�ȥ�ι���

jsp
  +--config
  |     +---m16c-renesas
  |            +---oaks16
  |            +---oaks16_mini
  +--tools
  |     +-----M16C-RENESAS
  +--utils
        +-----m16c-renesas


2.�ǥ��쥯�ȥ�ȥե����������

��ͥ����ƥ��Υ��Ҥγ�ȯ�ġ�����Ѥ���m16c�Ѥ�TOPPERS/JSP��ȯ����٤�
��������config/m16c-renesas�ǥ��쥯�ȥ���֤���
���ۤ˺ݤ��ơ�����ߤ䥨�����ץ����Υ٥��ȥ��ư��������ġ���(m16cvec.
exe)�ȡ�TCB�Υ��ե��å��ͤ򥢥���֥�ǽ񤫤줿�����������ꤹ��ġ���(m16co
ffset.exe)�ι��۴Ķ��ȡ�make���Ѥ��Ƴ�ȯ���硢�������ΰ�¸�ط�����������P
ERL������ץȤ�tools/m16c-renesas�ǥ쥯�ȥꥣ���֤���
���糫ȯ�Ķ�TM���Ѥ���TOPPERS/JSP���ۤ���Ķ���tools/M16C-RENESAS�ǥ쥯��
�ꥣ���֤���

2.1 config/m16c-renesas

a. Makefile.config ---- make���ޥ�ɤ��Ѥ���m16c��TOPPERS/JSP���ۤ�����
                        make�ե�����
b. oaks16/Makefile.config ---- make���ޥ�ɤ��Ѥ���m16c-OAKS16��TOPPERS/JSP
                        ���ۤ������make�ե�����
c. oaks16_mini/Makefile.config ---- make���ޥ�ɤ��Ѥ���m16c-OAKS16 MINI��T
                        OPPERS/JSP���ۤ������make�ե�����
d. ����¾ ---- m16c��¸���Υ�����

2.2 utils/m16c-renesas

a. makedep.m16c ---- make���Ѥ��Ƴ�ȯ���硢�������ΰ�¸�ط�����������PERL
                     ������ץ�
b. m16cutils.dsw ---- m16cvec.exe��m16coffset.exe���ޥ��VC++���Ѥ��ƹ��ۤ�
                      �뤿��Υ�����ڡ����ե�����
c. m16cutils.opt ---- VC++�Ѥ�OPT�ե�����
d: m16cutils/m16coffset/m16coffset.dsp
                 ---- m16coffset�����Υץ������ȥե�����
e: m16cutils/m16coffset/m16coffset.cpp
                 ---- m16coffset���ޥ��C++���쵭��
f: m16cutils/m16coffset/StdAfx.h
                 ---- ɸ�ॷ���ƥ।�󥯥롼�ɥե�����
g: m16cutils/m16coffset/StdAfx.cpp
                 ---- ɸ�ॷ���ƥ।�󥯥롼�ɥե������ޤॽ�����ե�����
h: m16cutils/m16coffset/m16cvec.dsp
                 ---- m16cvec�����Υץ������ȥե�����
i: m16cutils/m16coffset/m16cvec.cpp
                 ---- m16cvec���ޥ��C++���쵭��
j: m16cutils/m16coffset/StdAfx.h
                 ---- ɸ�ॷ���ƥ।�󥯥롼�ɥե�����
k: m16cutils/m16coffset/StdAfx.cpp
                 ---- ɸ�ॷ���ƥ।�󥯥롼�ɥե������ޤॽ�����ե�����

2.3 utils/M16C-RENESAS

a.Jsp14sample1.tmi,Jsp14sample.tmk ---- TM���Ѥ���OAKS16�Ѥ�TOPPERS/JSP��
                      �ۤ��뤿��Υץ������ȥե�����
b.Jsp14sample1m.tmi,Jsp14samplem.tmk ---- TM���Ѥ���OAKS16 MINI�Ѥ�TOPPERS/
                      JSP���ۤ��뤿��Υץ������ȥե�����
c.Jsp14sample1.id ---- ��������MOT�ե������OAKS16�ܡ��ɤΥե�å���ROM�ν�
                      ��������˻��Ѥ���ID�ե�����
d.Jsp14sample1m.id ---- ��������MOT�ե������OAKS16 MINI�ܡ��ɤΥե�å���
                      ROM�ν񤭹�����˻��Ѥ���ID�ե�����
e.sample1.cfg ---- OAKS16�Ѥ�TOPPERS/JSP���ۤ��뤿��Υ���ե�����ե�����
f.sample1m.cfg ---- OAKS16 MINI�Ѥ�TOPPERS/JSP���ۤ��뤿��Υ���ե�����
                      �ե�����

2.4  sample

a.Makefile.m16c-oaks16 ---- make���ޥ�ɤ��Ѥ���OAKS16�Ѥ�TOPPERS/JSP����
                      ���뤿���make�ե�����


