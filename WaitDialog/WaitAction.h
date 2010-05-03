#if !defined(AFX_WAITACTION_H__004F1F69_ED47_4EFE_90E8_2781F3497EF4__INCLUDED_)
#define AFX_WAITACTION_H__004F1F69_ED47_4EFE_90E8_2781F3497EF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitAction.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// cWaitAction thread

class cWaitAction : public CWinThread
{
	DECLARE_DYNCREATE(cWaitAction)
protected:
	cWaitAction();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cWaitAction)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~cWaitAction();

	// Generated message map functions
	//{{AFX_MSG(cWaitAction)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITACTION_H__004F1F69_ED47_4EFE_90E8_2781F3497EF4__INCLUDED_)
