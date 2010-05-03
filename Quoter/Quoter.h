// Quoter.h : main header file for the QUOTER application
//

#if !defined(AFX_QUOTER_H__EDB6EE26_8F75_11D2_9ACB_002018550C46__INCLUDED_)
#define AFX_QUOTER_H__EDB6EE26_8F75_11D2_9ACB_002018550C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CQuoterApp:
// See Quoter.cpp for the implementation of this class
//

class CQuoterApp : public CWinApp
{
public:
	CQuoterApp();

protected:
  CWnd            m_wndParent;
  CString         m_sClassName;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuoterApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CQuoterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUOTER_H__EDB6EE26_8F75_11D2_9ACB_002018550C46__INCLUDED_)
