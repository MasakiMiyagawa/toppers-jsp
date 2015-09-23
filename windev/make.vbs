'
'   TOPPERS/JSP Kernel
'       Toyohashi Open Platform for Embedded Real-Time Systems/
'       Just Standard Profile Kernel
'  
'   Copyright (C) 2000-2002 by Embedded and Real-Time Systems Laboratory
'                               Toyohashi Univ. of Technology, JAPAN
'  
'   �嵭����Ԥϡ�Free Software Foundation �ˤ�äƸ�ɽ����Ƥ��� 
'   GNU General Public License �� Version 2 �˵��Ҥ���Ƥ����狼����
'   ����(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ��������ܥ��եȥ���
'   ������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ�������ѡ������ۡʰʲ���
'   ���ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
'   (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
'       ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
'       ����������˴ޤޤ�Ƥ��뤳�ȡ�
'   (2) �ܥ��եȥ�����������Ѳ�ǽ�ʥХ��ʥꥳ���ɡʥ�������֥륪��
'       �������ȥե������饤�֥��ʤɡˤη������Ѥ�����ˤϡ�����
'       ��ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ����
'       �������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
'   (3) �ܥ��եȥ�������������Բ�ǽ�ʥХ��ʥꥳ���ɤη��ޤ��ϵ������
'       �߹�����������Ѥ�����ˤϡ����Τ����줫�ξ������������ȡ�
'     (a) ���Ѥ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭������
'         ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
'     (b) ���Ѥη��֤��̤�������ˡ�ˤ�äơ��嵭����Ԥ���𤹤�
'         ���ȡ�
'   (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
'       ������⡤�嵭����Ԥ����դ��뤳�ȡ�
'
'   �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥϡ�
'   �ܥ��եȥ������˴ؤ��ơ�����Ŭ�Ѳ�ǽ����ޤ�ơ������ʤ��ݾڤ�Ԥ�
'   �ʤ����ޤ����ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū����������
'   ���ʤ�»���˴ؤ��Ƥ⡤������Ǥ�����ʤ���
'
'   @(#) $Id: make.vbs,v 1.3 2002/04/05 09:09:20 takayuki Exp $
'

dim model
dim msdev
dim rootdir

rootdir = left(Wscript.ScriptFullName, len(Wscript.scriptfullname) - len(wscript.scriptname))

if msgbox("TOPPERS/JSP Windows �ǥХ����ޥ͡����� ����� ATL�ǥХ�������ȥ�����������ޤ��������򳫻Ϥ��Ƥ������Ǥ���?", vbYesno) = vbyes then

	if msgbox("��꡼���ӥ�ɤ��ޤ���? (�֤������פ����֤ȥǥХå���ǽ�ʼ¹ԥե�������������ޤ�)",vbyesno) = vbyes then
		model = " - Win32 Unicode Release MinDependency"
	else
		model = " - Win32 Debug"
	end if

		'Visual C++ �ε�ư
	set msdev = CreateObject("MSDEV.APPLICATION")
	msdev.visible = true

		'�ǥХ����ޥ͡����������
	msdev.documents.open rootdir + "devicemanager\devicemanager.dsw"
	set msdev.activeproject = msdev.projects("devicemanager")
	set msdev.activeconfiguration = msdev.activeproject.configurations("devicemanager" + model)
	msdev.build

		'�ǥХ�������ȥ��������
	msdev.documents.open rootdir + "devicecontrol\device.dsw"
	set msdev.activeproject = msdev.projects("device")
	set msdev.activeconfiguration = msdev.activeproject.configurations("device" + model)
	msdev.build


msdev.quit
set msdev = nothing

msgbox "���Ƥν�������λ���ޤ���"
end if
