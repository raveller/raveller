// ResponseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FormDoctor.h"
#include "ResponseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CResponseDlg dialog


CResponseDlg::CResponseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CResponseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CResponseDlg)
	m_response = _T("");
	//}}AFX_DATA_INIT
}


void CResponseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CResponseDlg)
	DDX_Text(pDX, IDC_RESPONSE, m_response);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CResponseDlg, CDialog)
	//{{AFX_MSG_MAP(CResponseDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResponseDlg message handlers
