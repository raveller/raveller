#if !defined(AFX_RENAMECONFIRM_H__84478E42_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
#define AFX_RENAMECONFIRM_H__84478E42_79C3_11D4_B476_00B0D02A8795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenameConfirm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenameConfirm dialog

class CRenameConfirm : public CPropertyPage
{
	DECLARE_DYNCREATE(CRenameConfirm)

// Construction
public:
	void SetLists (CStringList* fromList, CStringList* toList);
    
    CRenameConfirm();
	~CRenameConfirm();

// Dialog Data
	//{{AFX_DATA(CRenameConfirm)
	enum { IDD = IDC_CONFIRM };
	CListCtrl	m_conTrol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRenameConfirm)
	public:
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStringList *m_fromList;
	CStringList *m_toList;
	// Generated message map functions
	//{{AFX_MSG(CRenameConfirm)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENAMECONFIRM_H__84478E42_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
