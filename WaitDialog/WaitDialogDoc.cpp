// WaitDialogDoc.cpp : implementation of the CWaitDialogDoc class
//

#include "stdafx.h"
#include "WaitDialog.h"

#include "WaitDialogDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogDoc

IMPLEMENT_DYNCREATE(CWaitDialogDoc, CDocument)

BEGIN_MESSAGE_MAP(CWaitDialogDoc, CDocument)
	//{{AFX_MSG_MAP(CWaitDialogDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogDoc construction/destruction

CWaitDialogDoc::CWaitDialogDoc()
{
	// TODO: add one-time construction code here

}

CWaitDialogDoc::~CWaitDialogDoc()
{
}

BOOL CWaitDialogDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CWaitDialogDoc serialization

void CWaitDialogDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogDoc diagnostics

#ifdef _DEBUG
void CWaitDialogDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CWaitDialogDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWaitDialogDoc commands
