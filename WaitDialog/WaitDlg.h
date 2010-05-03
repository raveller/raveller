#if !defined(AFX_WAITDLG_H__55050813_F8E6_11D2_837D_00500406DAEB__INCLUDED_)
#define AFX_WAITDLG_H__55050813_F8E6_11D2_837D_00500406DAEB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WaitDlg.h : header file
//
#include <afxmt.h>

#include "WaitDlgThread.h"
#include "AnimWnd.h"

/////////////////////////////////////////////////////////////////////////////
// cWaitDlg dialog

class cWaitDlg : public CDialog
{
// Construction
public:
	cWaitDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(cWaitDlg)
	enum { IDD = IDD_BUSY_DLG };
	CProgressCtrl	m_waitProgressCtrl;
	//}}AFX_DATA
    cWaitDlgThread	*m_Thread;
    CString          m_Text;
    bool             m_bShowCancelButton;
    long             m_Prog;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cWaitDlg)
    public:
    virtual BOOL PreTranslateMessage(MSG* pMsg); // <---
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	virtual void OnCancel();
	// Generated message map functions
	//{{AFX_MSG(cWaitDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDLG_H__55050813_F8E6_11D2_837D_00500406DAEB__INCLUDED_)
