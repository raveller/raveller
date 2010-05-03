// RenameComplete.cpp : implementation file
//

#include "stdafx.h"
#include "MoveMore.h"
#include "RenameComplete.h"

#include <errno.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenameComplete property page

IMPLEMENT_DYNCREATE(CRenameComplete, CPropertyPage)

CRenameComplete::CRenameComplete() : CPropertyPage(CRenameComplete::IDD)
{
	//{{AFX_DATA_INIT(CRenameComplete)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_toList   = NULL;
    m_fromList = NULL;
}

CRenameComplete::~CRenameComplete()
{
}

void CRenameComplete::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenameComplete)
	DDX_Control(pDX, IDC_COMCTRL, m_comTrol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRenameComplete, CPropertyPage)
	//{{AFX_MSG_MAP(CRenameComplete)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenameComplete message handlers

BOOL CRenameComplete::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
    CWnd *parent = GetParent ();

    if (parent->IsKindOf ( RUNTIME_CLASS( CPropertySheet )) )
    {
	  ((CPropertySheet*)parent)->SetWizardButtons (PSWIZB_FINISH);
    }

    if (m_fromList && m_toList)
    {
        m_comTrol.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB);
        m_comTrol.InsertColumn(0, "Renamed?", LVCFMT_LEFT, 80, 1);
        m_comTrol.InsertColumn(1, "From Files", LVCFMT_LEFT, 260, 2);
        m_comTrol.InsertColumn(2, "To Files", LVCFMT_LEFT, 260, 3);

        int i = 0;
        POSITION fromPos = m_fromList->GetHeadPosition ();
        POSITION toPos   = m_toList->GetHeadPosition ();
        while (fromPos && toPos)
        {

            m_comTrol.InsertItem (i, (LPCTSTR) m_fromList->GetAt (fromPos));
            m_comTrol.SetItemText (i, 0, _T(""));
            m_comTrol.SetItemText (i, 1, (LPCTSTR) m_fromList->GetAt (fromPos));

            m_comTrol.SetItemText(i, 2, (LPCTSTR) m_toList->GetAt (toPos));

            m_fromList->GetNext (fromPos);
            m_toList->GetNext (toPos);
            i++;
        }
        
        i = 0;

        CWaitCursor waitc;

        fromPos = m_fromList->GetHeadPosition ();
        toPos   = m_toList->GetHeadPosition ();
        while (fromPos && toPos)
        {
            int rstat = _trename ((LPCTSTR) m_fromList->GetAt (fromPos), (LPCTSTR) m_toList->GetAt (toPos));

            switch (rstat) {
            case 0: 
                m_comTrol.SetItemText (i, 0, _T("X"));
                break;
            case EACCES :
                m_comTrol.SetItemText (i, 0, _T("AD"));
                break;
            case ENOENT :
                m_comTrol.SetItemText (i, 0, _T("NF"));
                break;
            case EINVAL:
                m_comTrol.SetItemText (i, 0, _T("IV"));
                break;
            default:
                m_comTrol.SetItemText (i, 0, _T("?"));
                break;
            }

            m_comTrol.RedrawWindow ();
            
            m_fromList->GetNext (fromPos);
            m_toList->GetNext (toPos);
            i++;
        }
    }

    if (parent->IsKindOf ( RUNTIME_CLASS( CPropertySheet )) )
    {
	  ((CPropertySheet*)parent)->SetFinishText ("All Done.");
    }

    CancelToClose ();

	return CPropertyPage::OnSetActive();
}

LRESULT CRenameComplete::OnWizardBack() 
{
	// TODO: Add your specialized code here and/or call the base class

	return CPropertyPage::OnWizardBack();
}

BOOL CRenameComplete::OnWizardFinish() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnWizardFinish();
}

void CRenameComplete::SetLists(CStringList *fromList, CStringList *toList)
{
    m_fromList = fromList;
    m_toList = toList;

}
