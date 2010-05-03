// OutputFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Quoter.h"
#include "OutputFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputFileDlg dialog


COutputFileDlg::COutputFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COutputFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COutputFileDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COutputFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COutputFileDlg)
	DDX_Text(pDX, IDC_HEADER, m_headerfile);
	DDX_Text(pDX, IDC_FOOTER, m_footerfile);
	DDX_Text(pDX, IDC_TARGET, m_targetfile);
    DDX_Text(pDX, IDC_EOLTAG, m_eoltag);
	DDV_MaxChars(pDX, m_eoltag, 9);
	DDX_Text(pDX, IDC_DISPLAYNAME, m_displayname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COutputFileDlg, CDialog)
	//{{AFX_MSG_MAP(COutputFileDlg)
	ON_BN_CLICKED(IDC_BROWSEFOOTER, OnBrowseFooter)
	ON_BN_CLICKED(IDC_BROWSEHEADER, OnBrowseHeader)
	ON_BN_CLICKED(IDC_BROWSETARGET, OnBrowseTarget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COutputFileDlg::OnBrowseFooter() 
{
    UpdateData ();

    CString szFilter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
    CFileDialog* dlg = new CFileDialog (TRUE, "txt", (LPCTSTR) m_footerfile,
                                        OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                                        szFilter, (CWnd*) this);

    //dlg->m_ofn.lpstrInitialDir = pinitialDir;

    if (dlg->DoModal() == IDOK)
    {
        m_footerfile = dlg->GetPathName();
        UpdateData (FALSE);
    }
}

void COutputFileDlg::OnBrowseHeader() 
{
    UpdateData ();

    CString szFilter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
    CFileDialog* dlg = new CFileDialog (TRUE, "txt", (LPCTSTR) m_headerfile,
                                        OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                                        szFilter, (CWnd*) this);

    if (dlg->DoModal() == IDOK)
    {
        m_headerfile = dlg->GetPathName();
        UpdateData (FALSE);
    }
}

void COutputFileDlg::OnBrowseTarget() 
{
    UpdateData ();

    CString szFilter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
    CFileDialog* dlg = new CFileDialog (TRUE, "txt", (LPCTSTR) m_targetfile,
                                        OFN_HIDEREADONLY,
                                        szFilter, (CWnd*) this);

    //dlg->m_ofn.lpstrInitialDir = pinitialDir;

    if (dlg->DoModal() == IDOK)
    {
        m_targetfile = dlg->GetPathName();
        UpdateData (FALSE);
    }
}


/////////////////////////////////////////////////////////////////////////////
// COutputFileDlg message handlers
