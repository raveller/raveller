#if !defined(AFX_WAITDLGTHREAD_H__55050812_F8E6_11D2_837D_00500406DAEB__INCLUDED_)
#define AFX_WAITDLGTHREAD_H__55050812_F8E6_11D2_837D_00500406DAEB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WaitDlgThread.h : header file
//
//////////////////////////////////////////////////// cWaitDlgThread //
// Author: Todd Andrews
// Email:  tmandrews@mindspring.com
// Copyright 1999, Todd Andrews
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
//
// This class implements a worker thread

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// WaitDlgThread thread

class cWaitDlgThread : public CWinThread
{
	DECLARE_DYNCREATE(cWaitDlgThread)

public:
   cWaitDlgThread();           // protected constructor used by dynamic creation

protected:
// Attributes
   
public:
   CString  m_Eventname;
   CEvent   *m_Event;
   bool     m_bShowCancelButton;
   CString  m_Text;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cWaitDlgThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~cWaitDlgThread();

protected:

	// Generated message map functions
	//{{AFX_MSG(cWaitDlgThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDLGTHREAD_H__55050812_F8E6_11D2_837D_00500406DAEB__INCLUDED_)
