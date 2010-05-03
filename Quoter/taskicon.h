#if !defined(AFX_TASKICON_H__A928F424_DE02_11D2_9ACB_002018550C46__INCLUDED_)
#define AFX_TASKICON_H__A928F424_DE02_11D2_9ACB_002018550C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskIcon.h : header file
//
#include "SystemTray.h"
class CQuoterDlg;

/////////////////////////////////////////////////////////////////////////////
// CQuoterIcon window

class CQuoterIcon : public CWnd
{
// Construction
public:
	CQuoterIcon();
// Attributes
public:

// Operations
public:
	BOOL Create(LPCTSTR     lpszClassName,
              LPCTSTR     lpszWindowName,
              CQuoterDlg* pQuoterDlg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuoterIcon)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CQuoterDlg* m_quoterDlg;
	virtual ~CQuoterIcon();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQuoterIcon)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CQuoterTray : public CSystemTray {
public:
	LRESULT OnTrayNotification(UINT wParam, LONG lParam);
  CQuoterTray() {};
  ~CQuoterTray() {};
  BOOL Create (CQuoterDlg* pQuoter, HICON icon);
  DECLARE_DYNAMIC (CQuoterTray);

protected:
  CQuoterDlg* m_quoterDlg;
  DECLARE_MESSAGE_MAP()
  };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKICON_H__A928F424_DE02_11D2_9ACB_002018550C46__INCLUDED_)
