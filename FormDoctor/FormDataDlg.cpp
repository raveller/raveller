// FormDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FormDoctor.h"
#include "FormDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDataDlg dialog


CFormDataDlg::CFormDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFormDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormDataDlg)
	m_formdata = _T("");
	m_url = _T("");
	m_server = _T("");
	m_userAgent = _T("");
	//}}AFX_DATA_INIT
}


void CFormDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormDataDlg)
	DDX_Text(pDX, IDC_FORMDATAEDIT, m_formdata);
	DDX_Text(pDX, IDC_URL, m_url);
	DDX_Text(pDX, IDC_SERVER, m_server);
	DDX_Text(pDX, IDC_USER_AGENT, m_userAgent);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormDataDlg, CDialog)
	//{{AFX_MSG_MAP(CFormDataDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormDataDlg message handlers
