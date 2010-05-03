// FormDoctorView.cpp : implementation of the CFormDoctorView class
//

#include "stdafx.h"
#include "FormDoctor.h"

#include "FormDoctorDoc.h"
#include "FormDoctorView.h"
#include "FormDataDlg.h"
#include "ResponseDlg.h"
#include <afxinet.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorView

IMPLEMENT_DYNCREATE(CFormDoctorView, CView)

BEGIN_MESSAGE_MAP(CFormDoctorView, CView)
	//{{AFX_MSG_MAP(CFormDoctorView)
	ON_COMMAND(ID_FORM_ENTERDATA, OnFormEnterdata)
	ON_COMMAND(ID_FORM_SUBMIT, OnFormSubmit)
	ON_COMMAND(ID_FORM_VIEWLASTRESPONSE, OnFormViewlastresponse)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorView construction/destruction

CFormDoctorView::CFormDoctorView()
{
	// TODO: add construction code here

}

CFormDoctorView::~CFormDoctorView()
{
}

BOOL CFormDoctorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorView drawing

void CFormDoctorView::OnDraw(CDC* pDC)
{
	CFormDoctorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  CPoint ptText (5, 5);
  CSize szText = pDC->GetTextExtent (pDoc->m_server);
  CRect rtText (ptText, szText);
  pDC->DrawText (pDoc->m_server, &rtText, DT_CALCRECT);
  pDC->DrawText (pDoc->m_server, &rtText, DT_LEFT);

  rtText.top = rtText.bottom + 5;
  rtText.right = rtText.left + szText.cx;
  rtText.bottom = rtText.top + szText.cy;
  pDC->DrawText (pDoc->m_url, &rtText, DT_CALCRECT);
  pDC->DrawText (pDoc->m_url, &rtText, DT_LEFT);

  szText = pDC->GetTextExtent (pDoc->m_formdata);
  rtText.top = rtText.bottom + 5;
  rtText.right = rtText.left + szText.cx;
  rtText.bottom = rtText.top + szText.cy;
  pDC->DrawText (pDoc->m_formdata, &rtText, DT_CALCRECT);
  pDC->DrawText (pDoc->m_formdata, &rtText, DT_LEFT);

  szText = pDC->GetTextExtent (pDoc->m_response);
  rtText.top = rtText.bottom + 5;
  rtText.right = rtText.left + szText.cx;
  rtText.bottom = rtText.top + szText.cy;
  pDC->DrawText (pDoc->m_response, &rtText, DT_CALCRECT);
  pDC->DrawText (pDoc->m_response, &rtText, DT_LEFT);
  }

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorView printing

BOOL CFormDoctorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFormDoctorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFormDoctorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorView diagnostics

#ifdef _DEBUG
void CFormDoctorView::AssertValid() const
{
	CView::AssertValid();
}

void CFormDoctorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFormDoctorDoc* CFormDoctorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFormDoctorDoc)));
	return (CFormDoctorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorView message handlers

void CFormDoctorView::OnFormEnterdata() 
{
	CFormDoctorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  CFormDataDlg frmdlg;
  frmdlg.m_formdata = pDoc->m_formdata;
  frmdlg.m_server = pDoc->m_server;
  frmdlg.m_url = pDoc->m_url;
  frmdlg.m_userAgent = pDoc->m_userAgent;
  if (frmdlg.DoModal() == IDOK) {
    pDoc->m_server = frmdlg.m_server;
    pDoc->m_formdata = frmdlg.m_formdata;
    pDoc->m_url = frmdlg.m_url;
    pDoc->m_userAgent = frmdlg.m_userAgent;
    }

  Invalidate ();
  }

void CFormDoctorView::OnFormSubmit() 
{
	CFormDoctorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

  CInternetSession* inetsess = new CInternetSession (pDoc->m_userAgent);

  if (inetsess) {
    CHttpConnection* httpconn = inetsess->GetHttpConnection (pDoc->m_server);

    if (httpconn) {
      CHttpFile* httpfile = NULL;
      if (pDoc->m_formdata.GetLength() == 0) 
        httpfile = httpconn->OpenRequest (CHttpConnection::HTTP_VERB_GET, (LPCTSTR) pDoc->m_url);
      else
        httpfile = httpconn->OpenRequest (CHttpConnection::HTTP_VERB_POST, (LPCTSTR) pDoc->m_url);

      if (httpfile) {
        if (pDoc->m_formdata.GetLength() > 0) {
          CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");
          httpfile->SendRequest (strHeaders, (LPVOID)(LPCTSTR) pDoc->m_formdata, (DWORD) pDoc->m_formdata.GetLength ());
          }

        DWORD hflen = 0;
        char rawhfile [50000];
        pDoc->m_response = "";
        CWaitCursor waitabit;
        while (hflen = (DWORD) httpfile->GetLength ()) {
          if (hflen > 49998)
            hflen = 49999;

        
          UINT iRead = httpfile->Read ((void*) rawhfile, (UINT) hflen);
          rawhfile [iRead] = '\0';
          pDoc->m_response += (LPCTSTR) rawhfile;
          }

        httpfile->Close ();
        }
      else
        AfxMessageBox ("Couldn't Open File");
      httpconn->Close ();
      }
    else
      AfxMessageBox ("Couldn't Reach Server");

    inetsess->Close ();
    }
  else
    AfxMessageBox ("Couldn't Open Session");

  Invalidate ();
  }

void CFormDoctorView::OnFormViewlastresponse() 
{
	CResponseDlg response;
  response.m_response = GetDocument()->m_response;

  response.DoModal ();
  }
