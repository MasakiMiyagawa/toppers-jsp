echo off
rem �V�X�e���E�R���t�B�M�����[�V�����ƃx�N�^�e�[�u���̎�������

rem HEW�ł́A���΃p�X�w��ŊO���c�[�����Ăяo���Ȃ����߁A
rem �o�b�`�t�@�C�����o�R���āA�R���t�B�M�����[�^���Ăяo���Ă���
rem
rem �V�X�e���E�R���t�B�M�����[�V�����E�t�@�C�����v���v���Z�X���ꂽ
rem ���ʂ̃t�@�C�������A����%1�Ƃ���HEW���炱�̃o�b�`�t�@�C���ɓn�����B

rem �ȉ��̕����͈ڐA�̍ۂɕύX����K�v������
rem �V�X�e���ˑ����̃f�B���N�g����
rem cfg.exe -s %1 -c -obj -cpu h8 -system xxxxxxxx

rem �x�N�^�e�[�u���̃T�C�Y
rem genvector.pl -s xxx

echo on

..\..\..\..\cfg\cfg.exe -s %1 -c -obj -cpu h8 -system hsb8f3048bf25
perl ..\..\..\..\utils\h8\filter1.pl %1 > tmpfile2
perl ..\..\..\..\utils\h8-renesas\filter2.pl tmpfile2 > tmp_script.pl
type ..\..\..\..\config\h8-renesas\vector_header.src > vector.src
perl ..\..\..\..\utils\h8-renesas\genvector.pl -s 61 >> vector.src
del tmpfile2 tmp_script.pl
