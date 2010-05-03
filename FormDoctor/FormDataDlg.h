#if !defined(AFX_FORMDATADLG_H__2969B3D6_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
#define AFX_FORMDATADLG_H__2969B3D6_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FormDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFormDataDlg dialog

class CFormDataDlg : public CDialog
{
// Construction
public:
	CFormDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFormDataDlg)
	enum { IDD = IDD_FORMDATA };
	CString	m_formdata;
	CString	m_url;
	CString	m_server;
	CString	m_userAgent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFormDataDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDATADLG_H__2969B3D6_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
