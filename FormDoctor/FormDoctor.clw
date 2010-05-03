; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFormDataDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FormDoctor.h"
ODLFile=FormDoctor.odl
LastPage=0

ClassCount=8
Class1=CFormDoctorApp
Class2=CFormDoctorDoc
Class3=CFormDoctorView
Class4=CMainFrame

ResourceCount=5
Resource1=IDR_FORMDOTYPE
Resource2=IDD_ABOUTBOX
Resource3=IDD_RESPONSE
Class5=CChildFrame
Class6=CAboutDlg
Class7=CFormDataDlg
Resource4=IDD_FORMDATA
Class8=CResponseDlg
Resource5=IDR_MAINFRAME

[CLS:CFormDoctorApp]
Type=0
HeaderFile=FormDoctor.h
ImplementationFile=FormDoctor.cpp
Filter=N

[CLS:CFormDoctorDoc]
Type=0
HeaderFile=FormDoctorDoc.h
ImplementationFile=FormDoctorDoc.cpp
Filter=N

[CLS:CFormDoctorView]
Type=0
HeaderFile=FormDoctorView.h
ImplementationFile=FormDoctorView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=ID_FORM_VIEWLASTRESPONSE


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=FormDoctor.cpp
ImplementationFile=FormDoctor.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_HELP_FINDER
Command9=ID_APP_ABOUT
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_CONTEXT_HELP
CommandCount=9

[MNU:IDR_FORMDOTYPE]
Type=1
Class=CFormDoctorView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_SEND_MAIL
Command10=ID_FILE_MRU_FILE1
Command11=ID_APP_EXIT
Command12=ID_EDIT_UNDO
Command13=ID_EDIT_CUT
Command14=ID_EDIT_COPY
Command15=ID_EDIT_PASTE
Command16=ID_VIEW_TOOLBAR
Command17=ID_VIEW_STATUS_BAR
Command18=ID_FORM_ENTERDATA
Command19=ID_FORM_SUBMIT
Command20=ID_FORM_VIEWLASTRESPONSE
Command21=ID_WINDOW_NEW
Command22=ID_WINDOW_CASCADE
Command23=ID_WINDOW_TILE_HORZ
Command24=ID_WINDOW_ARRANGE
Command25=ID_HELP_FINDER
Command26=ID_APP_ABOUT
CommandCount=26

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
Command15=ID_CONTEXT_HELP
Command16=ID_HELP
CommandCount=16

[DLG:IDR_MAINFRAME]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[DLG:IDD_FORMDATA]
Type=1
Class=CFormDataDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_FORMDATAEDIT,edit,1350631620
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_URL,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_SERVER,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_USER_AGENT,edit,1350631552
Control11=IDC_STATIC,static,1342308352

[CLS:CFormDataDlg]
Type=0
HeaderFile=FormDataDlg.h
ImplementationFile=FormDataDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_USER_AGENT

[DLG:IDD_RESPONSE]
Type=1
Class=CResponseDlg
ControlCount=2
Control1=IDCANCEL,button,1342242816
Control2=IDC_RESPONSE,edit,1353779396

[CLS:CResponseDlg]
Type=0
HeaderFile=ResponseDlg.h
ImplementationFile=ResponseDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

