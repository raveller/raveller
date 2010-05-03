// Quoter.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Quoter.h"
#include "QuoterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuoterApp

BEGIN_MESSAGE_MAP(CQuoterApp, CWinApp)
	//{{AFX_MSG_MAP(CQuoterApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuoterApp construction

CQuoterApp::CQuoterApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CQuoterApp object

CQuoterApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CQuoterApp initialization

BOOL CQuoterApp::InitInstance()
{
	AfxEnableControlContainer();

    //First free the string allocated by MFC at CWinApp startup.
    //The string is allocated before InitInstance is called.
    free((void*)m_pszRegistryKey);
    free((void*)m_pszProfileName);

    //Change the name of the registry key.
    //The CWinApp destructor will free the memory.
    m_pszRegistryKey=_tcsdup(_T("Raveller"));
    m_pszProfileName=_tcsdup(_T("Quoter by James"));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

  m_sClassName = AfxRegisterWndClass(NULL, NULL);
  m_wndParent.CreateEx(NULL, m_sClassName, "", NULL, 
                       0, 0, 10, 10,  NULL, NULL);
	CQuoterDlg dlg;
	m_pMainWnd = &m_wndParent;
  dlg.ReadIniData ();

  CFile* tempFile = NULL;
  if (m_lpCmdLine[0] == '\0')
    dlg.m_filename = dlg.m_defaultfile;
  else {
		// Transfer the command line into a CString
		dlg.m_filename = m_lpCmdLine;
    dlg.m_filename.TrimLeft();
    dlg.m_filename.TrimRight();
    }

  if (!dlg.m_filename.IsEmpty()) {
	  TRY   { tempFile = new CFile (dlg.m_filename, CFile::modeRead); }
	  CATCH ( CFileException, e ) { tempFile = NULL;}
	  END_CATCH
    }

  if (tempFile) {
    if (dlg.m_defaultfile.IsEmpty())
      dlg.m_defaultfile = dlg.m_filename;

    dlg.WriteIniData ();

    tempFile->Close();
    delete tempFile;
    tempFile = NULL;
	  int nResponse = dlg.DoModal();
	  if (nResponse == IDOK) {
  		// TODO: Place code here to handle when the dialog is
		  //  dismissed with OK
	    }
	  else if (nResponse == IDCANCEL) {
  		// TODO: Place code here to handle when the dialog is
		  //  dismissed with Cancel
	    }
    }
  else
    AfxMessageBox ("File could not be read.");


//  UnregisterClass(m_sClassName, AfxGetApp()->m_hInstance);
//  if (::IsWindow(m_wndParent.m_hWnd)) {
//    m_wndParent.DestroyWindow();
//    }

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CQuoterApp::ExitInstance() 
{
  UnregisterClass(m_sClassName, AfxGetApp()->m_hInstance);
  if (::IsWindow(m_wndParent.m_hWnd)) {
    m_wndParent.DestroyWindow();
    }

	return CWinApp::ExitInstance();
  }
