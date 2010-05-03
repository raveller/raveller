// WaitDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WaitDialog.h"
#include "WaitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cWaitDlg dialog


cWaitDlg::cWaitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(cWaitDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(cWaitDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
   m_Text = "";
   m_bShowCancelButton = false;
}


void cWaitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cWaitDlg)
	DDX_Control(pDX, IDC_WAITPROGRESSBAR, m_waitProgressCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cWaitDlg, CDialog)
	//{{AFX_MSG_MAP(cWaitDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cWaitDlg message handlers
void cWaitDlg::OnCancel() 
{
   //Override this so the user cannot cancel by hiting ESC
   return;
}

void cWaitDlg::OnOK() 
{
   //Ignore this unless the button is visible
   if (m_bShowCancelButton)
      {
	   m_Thread->m_Event->SetEvent();
	   CDialog::OnOK();
      }
}

BOOL cWaitDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
   if (m_Text.GetLength() > 0)
      GetDlgItem(IDC_BUSY_TEXT)->SetWindowText(m_Text);

   GetDlgItem(IDOK)->ShowWindow(m_bShowCancelButton ? SW_SHOW : SW_HIDE);

   SetTimer(1,75,NULL);
	
   m_waitProgressCtrl.SetRange (0, 30);
   m_Prog = 0;
   m_waitProgressCtrl.SetPos (m_Prog);

   return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void cWaitDlg::OnTimer(UINT nIDEvent) 
{
   m_Prog++;
      
   CSingleLock lock(m_Thread->m_Event, FALSE);

   m_waitProgressCtrl.SetPos (m_Prog);
   
   if (m_Prog == 30) m_Prog = -1;

   if (lock.Lock(0))
      {
      CDialog::OnOK();
      }

	//CDialog::OnTimer(nIDEvent);
}

BOOL cWaitDlg::PreTranslateMessage(MSG* pMsg)
{
// TODO: Add your specialized code here and/or call the base class

// insert this code here
if(pMsg->message == WM_KEYDOWN)
{
if(pMsg->wParam == VK_RETURN) // keyboard return key
{
return TRUE; // ignore return key, do not pass msg along
}

}
// end insert

return CDialog::PreTranslateMessage(pMsg);
} 
