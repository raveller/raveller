#if !defined(AFX_TASKTHREAD_H__40FAC465_D140_4F76_A9AB_E260C27331F6__INCLUDED_)
#define AFX_TASKTHREAD_H__40FAC465_D140_4F76_A9AB_E260C27331F6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TaskThread.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CTaskThread thread

class CTaskThread : public CWinThread
{
	DECLARE_DYNCREATE(CTaskThread)
protected:
	CTaskThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTaskThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CTaskThread();

	// Generated message map functions
	//{{AFX_MSG(CTaskThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TASKTHREAD_H__40FAC465_D140_4F76_A9AB_E260C27331F6__INCLUDED_)
