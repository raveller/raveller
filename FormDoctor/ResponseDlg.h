#if !defined(AFX_RESPONSEDLG_H__2969B3FC_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
#define AFX_RESPONSEDLG_H__2969B3FC_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResponseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CResponseDlg dialog

class CResponseDlg : public CDialog
{
// Construction
public:
	CResponseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CResponseDlg)
	enum { IDD = IDD_RESPONSE };
	CString	m_response;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResponseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CResponseDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESPONSEDLG_H__2969B3FC_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
