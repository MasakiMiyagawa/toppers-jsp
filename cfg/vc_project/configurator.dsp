# Microsoft Developer Studio Project File - Name="configurator" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** �Խ����ʤ��Ǥ������� **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=configurator - Win32 Debug
!MESSAGE �����ͭ���ʎҎ����̎����٤ǤϤ���ޤ��� ���Ύ̎ߎێ��ގ����Ĥ�ˎގَĎޤ��뤿��ˤ� NMAKE ����Ѥ��Ƥ���������
!MESSAGE [�Ҏ����̎����٤Ύ������Ύߎ���] ���ώݎĎޤ���Ѥ��Ƽ¹Ԥ��Ƥ�������
!MESSAGE 
!MESSAGE NMAKE /f "configurator.mak".
!MESSAGE 
!MESSAGE NMAKE �μ¹Ի��˹��������Ǥ��ޤ�
!MESSAGE ���ώݎĎ� �׎��ݾ�ǎώ��ۤ������������ޤ�����:
!MESSAGE 
!MESSAGE NMAKE /f "configurator.mak" CFG="configurator - Win32 Debug"
!MESSAGE 
!MESSAGE �����ǽ�ʎˎގَĎ� �ӎ��Ď�:
!MESSAGE 
!MESSAGE "configurator - Win32 Release" ("Win32 (x86) Console Application" ��)
!MESSAGE "configurator - Win32 Debug" ("Win32 (x86) Console Application" ��)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "configurator - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /Gr /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386 /out:"../cfg.exe"

!ELSEIF  "$(CFG)" == "configurator - Win32 Debug"
# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /out:"../cfg.exe" /pdbtype:sept
!ENDIF 
# Begin Target
# Name "configurator - Win32 Release"
# Name "configurator - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\configurator.cpp
# End Source File
# Begin Source File

SOURCE=..\domain.cpp
# End Source File
# Begin Source File

SOURCE=..\exception.cpp
# End Source File
# Begin Source File

SOURCE=..\garbage.cpp
# End Source File
# Begin Source File

SOURCE=..\id.cpp
# End Source File
# Begin Source File

SOURCE=..\manager.cpp
# End Source File
# Begin Source File

SOURCE=..\message.cpp
# End Source File
# Begin Source File

SOURCE=..\multistream.cpp
# End Source File
# Begin Source File

SOURCE=..\parser.cpp
# End Source File
# Begin Source File

SOURCE=..\serializer.cpp
# End Source File
# Begin Source File

SOURCE=..\staticapi.cpp
# End Source File
# Begin Source File

SOURCE=..\value.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\domain.h
# End Source File
# Begin Source File

SOURCE=..\exception.h
# End Source File
# Begin Source File

SOURCE=..\garbage.h
# End Source File
# Begin Source File

SOURCE=..\id.h
# End Source File
# Begin Source File

SOURCE=..\manager.h
# End Source File
# Begin Source File

SOURCE=..\message.h
# End Source File
# Begin Source File

SOURCE=..\multistream.h
# End Source File
# Begin Source File

SOURCE=..\parser.h
# End Source File
# Begin Source File

SOURCE=..\serializer.h
# End Source File
# Begin Source File

SOURCE=..\staticapi.h
# End Source File
# Begin Source File

SOURCE=..\value.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "Target depended"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\jsp\toppers.cpp
# End Source File
# Begin Source File

SOURCE=..\jsp\toppers.h
# End Source File
# End Group
# End Target
# End Project
