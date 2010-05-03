// FormDoctor.h : main header file for the FORMDOCTOR application
//

#if !defined(AFX_FORMDOCTOR_H__2969B3A7_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
#define AFX_FORMDOCTOR_H__2969B3A7_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CFormDoctorApp:
// See FormDoctor.cpp for the implementation of this class
//

class CFormDoctorApp : public CWinApp
{
public:
	CFormDoctorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDoctorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CFormDoctorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDOCTOR_H__2969B3A7_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
