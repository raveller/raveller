; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMoveMoreDlg
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MoveMore.h"

ClassCount=6
Class1=CMoveMoreApp
Class2=CMoveMoreDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDC_CONFIRM
Resource2=IDR_MAINFRAME
Class4=CRenameAuto
Resource3=IDD_MOVEMORE_DIALOG
Resource4=IDD_ABOUTBOX
Class5=CRenameConfirm
Class6=CRenameComplete
Resource5=IDC_COMPLETE

[CLS:CMoveMoreApp]
Type=0
HeaderFile=MoveMore.h
ImplementationFile=MoveMore.cpp
Filter=N

[CLS:CMoveMoreDlg]
Type=0
HeaderFile=MoveMoreDlg.h
ImplementationFile=MoveMoreDlg.cpp
Filter=D
LastObject=IDC_CLEAR
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=MoveMoreDlg.h
ImplementationFile=MoveMoreDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MOVEMORE_DIALOG]
Type=1
Class=CMoveMoreDlg
ControlCount=20
Control1=IDCANCEL,button,1342242816
Control2=IDC_FROMFILE,edit,1350631552
Control3=IDC_TOFILE,edit,1350631552
Control4=IDC_FROMEXT,edit,1350631552
Control5=IDC_DIRBROWSE,button,1342242816
Control6=IDC_BROWSEFILE,button,1342242816
Control7=IDC_TOEXT,edit,1350631552
Control8=IDC_SWAP,button,1342242816
Control9=IDC_RENAME,button,1342254849
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_DIRNAME,static,1342308352
Control18=IDC_NUHHUH,button,1342242816
Control19=IDC_DITTO2,button,1342242816
Control20=IDC_CLEAR,button,1342242816

[CLS:CRenameAuto]
Type=0
HeaderFile=RenameAuto.h
ImplementationFile=RenameAuto.cpp
BaseClass=CPropertySheet
Filter=D
LastObject=CRenameAuto
VirtualFilter=hWC

[DLG:IDC_CONFIRM]
Type=1
Class=CRenameConfirm
ControlCount=2
Control1=IDC_STATIC,static,1342308353
Control2=IDC_CONCTRL,SysListView32,1350631425

[DLG:IDC_COMPLETE]
Type=1
Class=CRenameComplete
ControlCount=2
Control1=IDC_COMCTRL,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352

[CLS:CRenameConfirm]
Type=0
HeaderFile=RenameConfirm.h
ImplementationFile=RenameConfirm.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_LIST1

[CLS:CRenameComplete]
Type=0
HeaderFile=RenameComplete.h
ImplementationFile=RenameComplete.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC

