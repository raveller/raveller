// RenameConfirm.cpp : implementation file
//

#include "stdafx.h"
#include "MoveMore.h"
#include "RenameConfirm.h"
#include <afxcmn.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenameConfirm property page

IMPLEMENT_DYNCREATE(CRenameConfirm, CPropertyPage)

CRenameConfirm::CRenameConfirm() : CPropertyPage(CRenameConfirm::IDD)
{
	//{{AFX_DATA_INIT(CRenameConfirm)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
    m_toList   = NULL;
    m_fromList = NULL;
}

CRenameConfirm::~CRenameConfirm()
{
}

void CRenameConfirm::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRenameConfirm)
	DDX_Control(pDX, IDC_CONCTRL, m_conTrol);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRenameConfirm, CPropertyPage)
	//{{AFX_MSG_MAP(CRenameConfirm)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRenameConfirm message handlers

LRESULT CRenameConfirm::OnWizardBack() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnWizardBack();
}

LRESULT CRenameConfirm::OnWizardNext() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CPropertyPage::OnWizardNext();
}

BOOL CRenameConfirm::OnSetActive() 
{
	// SETUP: Wizard Buttons
    CWnd *parent = GetParent ();

    if (parent->IsKindOf ( RUNTIME_CLASS( CPropertySheet )) )
    {
	  ((CPropertySheet*)parent)->SetWizardButtons (PSWIZB_NEXT);
    }

    if (m_fromList && m_toList)
    {
        m_conTrol.SetExtendedStyle (LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP | LVS_EX_FLATSB);
        
        m_conTrol.InsertColumn(0, "From Files", LVCFMT_LEFT, 300, 1);
        m_conTrol.InsertColumn(1, "To Files", LVCFMT_LEFT, 300, 2);

        int i = 0;
        POSITION fromPos = m_fromList->GetHeadPosition ();
        POSITION toPos   = m_toList->GetHeadPosition ();
        while (fromPos && toPos)
        {

            m_conTrol.InsertItem (i, (LPCTSTR) m_fromList->GetAt (fromPos));
            //m_conTrol.SetItemText (i, 1, (LPCTSTR) m_fromList->GetAt (fromPos));

            m_conTrol.SetItemText(i, 1, (LPCTSTR) m_toList->GetAt (toPos));

            m_fromList->GetNext (fromPos);
            m_toList->GetNext (toPos);
            i++;
        }
    }

	return CPropertyPage::OnSetActive();
}

void CRenameConfirm::SetLists(CStringList *fromList, CStringList *toList)
{
    m_fromList = fromList;
    m_toList = toList;
}
