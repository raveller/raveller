// WaitDialogView.cpp : implementation of the CWaitDialogView class
//

#include "stdafx.h"
#include "WaitDialog.h"

#include "WaitDialogDoc.h"
#include "WaitDialogView.h"

#include "CmdWaitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogView

IMPLEMENT_DYNCREATE(CWaitDialogView, CView)

BEGIN_MESSAGE_MAP(CWaitDialogView, CView)
	//{{AFX_MSG_MAP(CWaitDialogView)
	ON_COMMAND(ID_VIEW_WAIT_DLG, OnViewWaitDlg)
	ON_COMMAND(ID_VIEW_ABORT_DLG, OnViewAbortDlg)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogView construction/destruction

CWaitDialogView::CWaitDialogView()
{
	// TODO: add construction code here

}

CWaitDialogView::~CWaitDialogView()
{
}

BOOL CWaitDialogView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogView drawing

void CWaitDialogView::OnDraw(CDC* pDC)
{
	CWaitDialogDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogView printing

BOOL CWaitDialogView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWaitDialogView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWaitDialogView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogView diagnostics

#ifdef _DEBUG
void CWaitDialogView::AssertValid() const
{
	CView::AssertValid();
}

void CWaitDialogView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWaitDialogDoc* CWaitDialogView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaitDialogDoc)));
	return (CWaitDialogDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogView message handlers

void CWaitDialogView::OnViewWaitDlg() 
{
	// TODO: Add your command handler code here
   long i,x;
   cWaitDialog dlg;
   
   dlg.m_Text = "Calculating...please wait";

   dlg.Show();

   i = 0;
   for (int q = 1; q < 7; q++)
   {
       for (x = 0; x <1000000000;x++)
          i = x * x;
   }
       
   dlg.Close();

}

void CWaitDialogView::OnViewAbortDlg() 
{
	// TODO: Add your command handler code here
   HANDLE event;
   event = CreateEvent(NULL, TRUE, FALSE, "CONEVENTTEST");

   cWaitDlgThread *thread = (cWaitDlgThread *)AfxBeginThread(RUNTIME_CLASS(cWaitDlgThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);


   thread->m_Eventname = "CONEVENTTEST";
   thread->m_bShowCancelButton = true;
   thread->m_Text = "Calculating...please wait";

   thread->ResumeThread();

      long i,x;

      x = 0;
   while ((WaitForSingleObject(event, 0)==WAIT_TIMEOUT) && (x < 10000000))
      {
      i = x * x;
      x++;
      }


	if(x>=10000000)  //here!!!!!!!!

		thread->m_Event->SetEvent();

   CloseHandle(event);
	
}

void CWaitDialogView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
