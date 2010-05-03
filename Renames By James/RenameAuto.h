#if !defined(AFX_RENAMEAUTO_H__84478E41_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
#define AFX_RENAMEAUTO_H__84478E41_79C3_11D4_B476_00B0D02A8795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RenameAuto.h : header file
//
#include "RenameConfirm.h"
#include "RenameComplete.h"

/////////////////////////////////////////////////////////////////////////////
// CRenameAuto

class CRenameAuto : public CPropertySheet
{
	DECLARE_DYNAMIC(CRenameAuto)

// Construction
public:
	CRenameAuto(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CRenameAuto(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRenameAuto)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRenameAuto();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRenameAuto)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RENAMEAUTO_H__84478E41_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
