; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTaskThread
LastTemplate=CWinThread
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "waitdialog.h"
LastPage=0

ClassCount=12
Class1=cAnimWnd
Class2=cWaitDialog
Class3=CMainFrame
Class4=CWaitDialogApp
Class5=CAboutDlg
Class6=CWaitDialogDoc
Class7=CWaitDialogView
Class8=cWaitDlg
Class9=cWaitDlgThread

ResourceCount=2
Resource1=IDR_MAINFRAME
Class10=cWaitAction
Class11=CWaitDialog
Class12=CTaskThread
Resource2=IDD_BUSY_DLG

[CLS:cAnimWnd]
Type=0
BaseClass=CWnd
HeaderFile=AnimWnd.h
ImplementationFile=AnimWnd.cpp

[CLS:cWaitDialog]
Type=0
BaseClass=CCmdTarget
HeaderFile=CmdWaitDlg.h
ImplementationFile=CmdWaitDlg.cpp

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp

[CLS:CWaitDialogApp]
Type=0
BaseClass=CWinApp
HeaderFile=WaitDialog.h
ImplementationFile=WaitDialog.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=WaitDialog.cpp
ImplementationFile=WaitDialog.cpp

[CLS:CWaitDialogDoc]
Type=0
BaseClass=CDocument
HeaderFile=WaitDialogDoc.h
ImplementationFile=WaitDialogDoc.cpp

[CLS:CWaitDialogView]
Type=0
BaseClass=CView
HeaderFile=WaitDialogView.h
ImplementationFile=WaitDialogView.cpp

[CLS:cWaitDlg]
Type=0
BaseClass=CDialog
HeaderFile=WaitDlg.h
ImplementationFile=WaitDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_WAITPROGRESSBAR

[CLS:cWaitDlgThread]
Type=0
BaseClass=CWinThread
HeaderFile=WaitDlgThread.h
ImplementationFile=WaitDlgThread.cpp

[DLG:IDD_BUSY_DLG]
Type=1
Class=cWaitDlg
ControlCount=3
Control1=IDC_BUSY_TEXT,static,1342308865
Control2=IDOK,button,1342242816
Control3=IDC_WAITPROGRESSBAR,msctls_progress32,1350565888

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_APP_EXIT
Command2=ID_VIEW_TOOLBAR
Command3=ID_VIEW_STATUS_BAR
Command4=ID_VIEW_WAIT_DLG
Command5=ID_VIEW_ABORT_DLG
CommandCount=5

[ACL:IDR_MAINFRAME]
Type=1
Class=?
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
CommandCount=14

[CLS:cWaitAction]
Type=0
HeaderFile=WaitAction.h
ImplementationFile=WaitAction.cpp
BaseClass=CWinThread
Filter=N

[CLS:CWaitDialog]
Type=0
HeaderFile=..\ns\include\imgfc\waitdialog.h
ImplementationFile=..\ns\src\imgfc\waitdialog.cpp
BaseClass=CDialog
Filter=D

[CLS:CTaskThread]
Type=0
HeaderFile=TaskThread.h
ImplementationFile=TaskThread.cpp
BaseClass=CWinThread
Filter=N

