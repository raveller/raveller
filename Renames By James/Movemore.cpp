// MoveMore.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MoveMore.h"
#include "MoveMoreDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMoveMoreApp

BEGIN_MESSAGE_MAP(CMoveMoreApp, CWinApp)
	//{{AFX_MSG_MAP(CMoveMoreApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveMoreApp construction

CMoveMoreApp::CMoveMoreApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMoveMoreApp object

CMoveMoreApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMoveMoreApp initialization

BOOL CMoveMoreApp::InitInstance()
{
	AfxEnableControlContainer();

    //First free the string allocated by MFC at CWinApp startup.
    //The string is allocated before InitInstance is called.
    free((void*)m_pszRegistryKey);
    free((void*)m_pszProfileName);

    //Change the name of the registry key.
    //The CWinApp destructor will free the memory.
    m_pszRegistryKey=_tcsdup(_T("Raveller"));
    m_pszProfileName=_tcsdup(_T("Renames by James"));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CMoveMoreDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
