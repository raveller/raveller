#if !defined(AFX_cWAITDIALOG_H__25FAD201_F98F_11D2_8127_F91DB0F31875__INCLUDED_)
#define AFX_cWAITDIALOG_H__25FAD201_F98F_11D2_8127_F91DB0F31875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cWaitDialog.h : header file
//
//////////////////////////////////////////////////// cWaitDialog //
// Author: Todd Andrews
// Email:  tmandrews@mindspring.com
// Copyright 1999, Todd Andrews
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
//
// This class implements a wrapper for a worker thread and dialog

#include "WaitDlgThread.h"

/////////////////////////////////////////////////////////////////////////////
// cWaitDialog command target

class cWaitDialog : public CCmdTarget
{
	DECLARE_DYNCREATE(cWaitDialog)

	cWaitDialog();           // protected constructor used by dynamic creation

// Attributes
public:
	cWaitDlgThread	   *m_Thread;
	bool			      m_bShowCancelButton;
   HANDLE            m_Event;
   CString           m_Text;
   CString           m_EventName;

// Operations
public:
	void Close();
	void Show();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cWaitDialog)
	//}}AFX_VIRTUAL

// Implementation
public:
   virtual ~cWaitDialog();
protected:

	// Generated message map functions
	//{{AFX_MSG(cWaitDialog)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_cWAITDIALOG_H__25FAD201_F98F_11D2_8127_F91DB0F31875__INCLUDED_)
