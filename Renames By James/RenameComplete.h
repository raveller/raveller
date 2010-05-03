#if !defined(AFX_RENAMECOMPLETE_H__84478E43_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
#define AFX_RENAMECOMPLETE_H__84478E43_79C3_11D4_B476_00B0D02A8795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenameComplete.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRenameComplete dialog

class CRenameComplete : public CPropertyPage
{
	DECLARE_DYNCREATE(CRenameComplete)

// Construction
public:
	void SetLists (CStringList* fromList, CStringList* toList);

	CRenameComplete();
	~CRenameComplete();

// Dialog Data
	//{{AFX_DATA(CRenameComplete)
	enum { IDD = IDC_COMPLETE };
	CListCtrl	m_comTrol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CRenameComplete)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CStringList *m_fromList;
	CStringList *m_toList;
	// Generated message map functions
	//{{AFX_MSG(CRenameComplete)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENAMECOMPLETE_H__84478E43_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
