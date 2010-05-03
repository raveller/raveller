// WaitDlgThread.cpp : implementation file
//

#include "stdafx.h"
#include "WaitDialog.h"
#include "WaitDlgThread.h"
#include "WaitDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cWaitDlgThread

IMPLEMENT_DYNCREATE(cWaitDlgThread, CWinThread)

cWaitDlgThread::cWaitDlgThread()
{
   m_bShowCancelButton = false;
   m_Text = "";
}

cWaitDlgThread::~cWaitDlgThread()
{
}

BOOL cWaitDlgThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
   cWaitDlg dlg;

   m_pMainWnd = &dlg;
   m_Event = new CEvent(FALSE, TRUE, m_Eventname);
   dlg.m_bShowCancelButton = m_bShowCancelButton;
   dlg.m_Text = m_Text;
   dlg.m_Thread = this;
   dlg.DoModal();
   delete m_Event;

   return FALSE;
}

int cWaitDlgThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
  return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(cWaitDlgThread, CWinThread)
	//{{AFX_MSG_MAP(cWaitDlgThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cWaitDlgThread message handlers
