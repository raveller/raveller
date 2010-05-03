// FormDoctorDoc.cpp : implementation of the CFormDoctorDoc class
//

#include "stdafx.h"
#include "FormDoctor.h"

#include "FormDoctorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorDoc

IMPLEMENT_DYNCREATE(CFormDoctorDoc, CDocument)

BEGIN_MESSAGE_MAP(CFormDoctorDoc, CDocument)
	//{{AFX_MSG_MAP(CFormDoctorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFormDoctorDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CFormDoctorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IFormDoctor to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {2969B3A4-40AD-11D4-9ACB-0020182EE5EF}
static const IID IID_IFormDoctor =
{ 0x2969b3a4, 0x40ad, 0x11d4, { 0x9a, 0xcb, 0x0, 0x20, 0x18, 0x2e, 0xe5, 0xef } };

BEGIN_INTERFACE_MAP(CFormDoctorDoc, CDocument)
	INTERFACE_PART(CFormDoctorDoc, IID_IFormDoctor, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorDoc construction/destruction

CFormDoctorDoc::CFormDoctorDoc()
{
	m_formdata = _T("");
	m_url = _T("");
	m_response = _T("");
	m_userAgent = _T("Mozilla/4.0 (compatible; FormDr 0.1)");

	EnableAutomation();

	AfxOleLockApp();
}

CFormDoctorDoc::~CFormDoctorDoc()
{
	AfxOleUnlockApp();
}

BOOL CFormDoctorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFormDoctorDoc serialization

void CFormDoctorDoc::Serialize(CArchive& ar)
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
// CFormDoctorDoc diagnostics

#ifdef _DEBUG
void CFormDoctorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFormDoctorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorDoc commands

