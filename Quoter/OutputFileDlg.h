#if !defined(AFX_OUTPUTFILEDLG_H__A19888B3_CA03_11D4_B48D_00B0D02A8795__INCLUDED_)
#define AFX_OUTPUTFILEDLG_H__A19888B3_CA03_11D4_B48D_00B0D02A8795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OutputFileDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COutputFileDlg dialog

class COutputFileDlg : public CDialog
{
// Construction
public:
	COutputFileDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COutputFileDlg)
	enum { IDD = IDD_ADDOUTPUTFILE };
	CString	m_defaultfile;
	CString	m_headerfile;
	CString	m_footerfile;
	CString	m_targetfile;
	CString	m_eoltag;
	CString	m_displayname;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COutputFileDlg)
	afx_msg void OnBrowseFooter();
	afx_msg void OnBrowseHeader();
	afx_msg void OnBrowseTarget();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTFILEDLG_H__A19888B3_CA03_11D4_B48D_00B0D02A8795__INCLUDED_)
