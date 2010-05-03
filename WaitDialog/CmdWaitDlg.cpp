// cWaitDialog.cpp : implementation file
//

#include "stdafx.h"
#include "WaitDialog.h"
#include "CmdWaitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cWaitDialog

IMPLEMENT_DYNCREATE(cWaitDialog, CCmdTarget)

cWaitDialog::cWaitDialog()
{
   m_bShowCancelButton = false;
   m_Text = "";
   m_EventName = "";
}

cWaitDialog::~cWaitDialog()
{
}


BEGIN_MESSAGE_MAP(cWaitDialog, CCmdTarget)
	//{{AFX_MSG_MAP(cWaitDialog)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cWaitDialog message handlers

void cWaitDialog::Show()
{
   m_Event = CreateEvent(NULL, TRUE, FALSE, m_EventName);
   m_Thread = (cWaitDlgThread *)AfxBeginThread(RUNTIME_CLASS(cWaitDlgThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
   m_Thread->m_Eventname = m_EventName;
   m_Thread->m_Text = m_Text;
   m_Thread->m_bShowCancelButton = m_bShowCancelButton;
   m_Thread->ResumeThread();

}

void cWaitDialog::Close()
{
   m_Thread->m_Event->SetEvent();
   CloseHandle(m_Event);
}
