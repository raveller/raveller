; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRandom
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "quoter.h"
LastPage=0

ClassCount=10
Class1=CAbout
Class2=CEditQuote
Class3=CFloaterOptions
Class4=COutputFileDlg
Class5=CQuoterApp
Class6=CQuoterDlg
Class7=CRandom
Class8=CSystemTray
Class9=CQuoterIcon
Class10=CTransDlg

ResourceCount=12
Resource1=IDR_POPUP_MENU
Resource2=IDR_FLOATER_POPUP
Resource3=IDD_FLOATER
Resource4=IDD_TRANS
Resource5=IDD_ADDOUTPUTFILE
Resource6=IDD_FLOATEROPTIONS
Resource7=IDD_RANDOMIZER
Resource8=IDR_QUOTER_MENU
Resource9=IDR_TASKBAR_POPUP
Resource10=IDD_ABOUT
Resource11=IDD_EDITOPTIONS
Resource12=IDD_QUOTER_DIALOG

[CLS:CAbout]
Type=0
BaseClass=CDialog
HeaderFile=About.h
ImplementationFile=About.cpp

[CLS:CEditQuote]
Type=0
BaseClass=CDialog
HeaderFile=EditQuote.h
ImplementationFile=EditQuote.cpp

[CLS:CFloaterOptions]
Type=0
BaseClass=CDialog
HeaderFile=EditQuote.h
ImplementationFile=EditQuote.cpp

[CLS:COutputFileDlg]
Type=0
BaseClass=CDialog
HeaderFile=OutputFileDlg.h
ImplementationFile=OutputFileDlg.cpp

[CLS:CQuoterApp]
Type=0
BaseClass=CWinApp
HeaderFile=Quoter.h
ImplementationFile=Quoter.cpp

[CLS:CQuoterDlg]
Type=0
BaseClass=CDialog
HeaderFile=QuoterDlg.h
ImplementationFile=QuoterDlg.cpp

[CLS:CRandom]
Type=0
BaseClass=CDialog
HeaderFile=Random.h
ImplementationFile=Random.cpp
Filter=D
LastObject=CRandom
VirtualFilter=dWC

[CLS:CSystemTray]
Type=0
BaseClass=CWnd
HeaderFile=SystemTray.h
ImplementationFile=SystemTray.cpp

[CLS:CQuoterIcon]
Type=0
BaseClass=CWnd
HeaderFile=taskicon.h
ImplementationFile=Taskicon.cpp

[CLS:CTransDlg]
Type=0
BaseClass=CDialog
HeaderFile=Transdlg.h
ImplementationFile=Transdlg.cpp

[DLG:IDD_ABOUT]
Type=1
Class=CAbout
ControlCount=1
Control1=IDOK,button,1342275595

[DLG:IDD_EDITOPTIONS]
Type=1
Class=CEditQuote
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_TIMERCOMBO,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_SEPARATOR,edit,1350631552
Control6=IDC_STATIC,static,1342308352
Control7=IDC_QUOTEFILE,edit,1350631552
Control8=IDC_BROWSEQUOTE,button,1342242816
Control9=IDC_SETCURRENT,button,1342242816
Control10=IDC_TRAY,button,1342308361
Control11=IDC_TASKBAR,button,1342177289
Control12=IDC_BOTH,button,1342177289
Control13=IDC_STATIC,button,1342177287
Control14=IDC_TARGET_LIST,listbox,1352728835
Control15=IDC_ADDOUTPUT,button,1342242816
Control16=IDC_REMOVEOUTPUT,button,1342242816
Control17=IDC_EDITOUTPUT,button,1342242816
Control18=IDC_EDITQUOTE,button,1342242816
Control19=IDOK,button,1342242817
Control20=IDCANCEL,button,1342242816

[DLG:IDD_FLOATEROPTIONS]
Type=1
Class=CFloaterOptions
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_FLOATFILE,edit,1350631552
Control5=IDC_BROWSEFLOAT,button,1342242816
Control6=IDC_BLUE_SLIDER,msctls_trackbar32,1342242840
Control7=IDC_RED_SLIDER,msctls_trackbar32,1342242840
Control8=IDC_STATIC,static,1342308352
Control9=IDC_GREEN_SLIDER,msctls_trackbar32,1342242840
Control10=IDC_STATIC,static,1342308352
Control11=IDC_GREENBOX,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_REDBOX,edit,1350631552
Control14=IDC_BLUEBOX,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_INTERNALBMP,button,1342242819
Control17=IDC_DRAWBITMAP,button,1342275595

[DLG:IDD_ADDOUTPUTFILE]
Type=1
Class=COutputFileDlg
ControlCount=18
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_TARGET,edit,1350631552
Control7=IDC_HEADER,edit,1350631552
Control8=IDC_FOOTER,edit,1350631552
Control9=IDC_BROWSETARGET,button,1342242816
Control10=IDC_BROWSEHEADER,button,1342242816
Control11=IDC_BROWSEFOOTER,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_DISPLAYNAME,edit,1350631552
Control14=IDC_BUTTON1,button,1342242816
Control15=IDC_HEADEREDIT,button,1342242816
Control16=IDC_FOOTEREDIT,button,1342242816
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EOLTAG,edit,1350631552

[DLG:IDD_QUOTER_DIALOG]
Type=1
Class=CQuoterDlg
ControlCount=10
Control1=IDC_MINIMIZE,button,1342242817
Control2=IDOK,button,1342242816
Control3=IDC_QUOTE_SPACE,edit,1350631620
Control4=IDC_GETQUOTE,button,1342242816
Control5=IDC_PREVIOUS,button,1342242816
Control6=IDC_FIRST,button,1342242816
Control7=IDC_NEXT,button,1342242816
Control8=IDC_LAST,button,1342242816
Control9=IDC_SELECTCOMBO,combobox,1344339971
Control10=IDC_WRITETARGET,button,1342242816

[DLG:IDD_RANDOMIZER]
Type=1
Class=CRandom
ControlCount=10
Control1=IDC_RANDOM_STRING,edit,1350633600
Control2=IDC_NOCHARS,edit,1350639744
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NUM,button,1342177289
Control5=IDC_HEX,button,1342177289
Control6=IDC_ALPHA,button,1342177289
Control7=IDC_ALPHANUM,button,1342177289
Control8=IDC_OTHERRAD,button,1342177289
Control9=IDC_OTHERTEXT,edit,1350631552
Control10=IDC_GENERATE,button,1342242816

[DLG:IDD_TRANS]
Type=1
Class=CTransDlg
ControlCount=0

[MNU:IDR_QUOTER_MENU]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_OPTION_LOADDEFAULT
Command3=ID_FILE_EXIT
Command4=ID_OPTIONS_EDIT
Command5=ID_OPTIONS_FLOATEROPTIONS
Command6=ID_OPTIONS_RANDOMGEN
Command7=ID_OPTION_SHOWFLOAT
Command8=ID_HELP_ABOUT
CommandCount=8

[DLG:IDD_FLOATER]
Type=1
Class=?
ControlCount=0

[MNU:IDR_POPUP_MENU]
Type=1
Class=?
Command1=ID_POPUP_QUOTE
Command2=ID_OPTIONS_EDIT
Command3=ID_HELP_ABOUT
Command4=ID_FILE_EXIT
CommandCount=4

[MNU:IDR_FLOATER_POPUP]
Type=1
Class=?
Command1=ID_FLOATER_CLOSE
CommandCount=1

[MNU:IDR_TASKBAR_POPUP]
Type=1
Class=?
Command1=ID_RESTORE
Command2=ID_FILE_EXIT
CommandCount=2

