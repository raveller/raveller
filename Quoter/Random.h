#if !defined(AFX_RANDOM_H__93C782F7_7845_446C_8FAB_5474EEBFAD25__INCLUDED_)
#define AFX_RANDOM_H__93C782F7_7845_446C_8FAB_5474EEBFAD25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Random.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Random dialog

class CRandom : public CDialog
{
// Construction
public:
	CRandom(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRandom)
	enum { IDD = IDD_RANDOMIZER };
	int		m_nochars;
	CString	m_random;
	CString	m_other;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRandom)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRandom)
	afx_msg void OnDeltaposNocharspin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGenerate();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCopyclip();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANDOM_H__93C782F7_7845_446C_8FAB_5474EEBFAD25__INCLUDED_)
