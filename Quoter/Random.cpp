// Random.cpp : implementation file
//

#include "stdafx.h"
#include "Quoter.h"
#include "Random.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Random dialog


CRandom::CRandom(CWnd* pParent /*=NULL*/)
	: CDialog(CRandom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRandom)
	m_nochars = 20;
	m_random = _T("");
	m_other = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz01234567890!@#$%^&* ()~_+{}|:<>?`-=[];',./'");
	//}}AFX_DATA_INIT
}


void CRandom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRandom)
	DDX_Text(pDX, IDC_NOCHARS, m_nochars);
	DDV_MinMaxInt(pDX, m_nochars, 0, 500);
	DDX_Text(pDX, IDC_RANDOM_STRING, m_random);
	DDX_Text(pDX, IDC_OTHERTEXT, m_other);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRandom, CDialog)
	//{{AFX_MSG_MAP(CRandom)
	ON_BN_CLICKED(IDC_GENERATE, OnGenerate)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_COPYCLIP, &CRandom::OnBnClickedCopyclip)
END_MESSAGE_MAP()

BOOL CRandom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	((CButton*) GetDlgItem (IDC_NUM))->SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CRandom::OnGenerate() 
{
    UpdateData (TRUE);
    CString rndVals = "";

    if (((CButton*) GetDlgItem (IDC_NUM))->GetCheck() == 1)
        rndVals = "0123456789";
    else if (((CButton*) GetDlgItem (IDC_HEX))->GetCheck() == 1)
        rndVals = "0123456789ABCDEF";
    else if (((CButton*) GetDlgItem (IDC_ALPHA))->GetCheck() == 1)
        rndVals = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    else if (((CButton*) GetDlgItem (IDC_ALPHANUM))->GetCheck() == 1)
        rndVals = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    else if (((CButton*) GetDlgItem (IDC_OTHERRAD))->GetCheck() == 1)
        rndVals = m_other;

    int count = rndVals.GetLength();

    CString rndText (' ', m_nochars);

    for (int i = 0; i < m_nochars; i++)
    {
        int index = rand() % count;
        rndText.SetAt(i, rndVals [index]);
    }

    m_random = rndText;
    UpdateData (FALSE);
}

void CRandom::OnBnClickedCopyclip()
{
   if ( !OpenClipboard() )
   {
      return;
   }
   // Remove the current Clipboard contents
   if( !EmptyClipboard() )
   {
      return;
   }
   // Get the currently selected data
   HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, 600);
   strcpy_s((char*)hGlob, m_random.GetLength(), m_random.GetBuffer());
   // For the appropriate data formats...
   if ( ::SetClipboardData( CF_TEXT, hGlob ) == NULL )
   {
      CString msg;
      CloseClipboard();
      GlobalFree(hGlob);
      return;
   }
   CloseClipboard();

}
