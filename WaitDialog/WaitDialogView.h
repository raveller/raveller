// WaitDialogView.h : interface of the CWaitDialogView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITDIALOGVIEW_H__25FAD211_F98F_11D2_8127_F91DB0F31875__INCLUDED_)
#define AFX_WAITDIALOGVIEW_H__25FAD211_F98F_11D2_8127_F91DB0F31875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWaitDialogView : public CView
{
protected: // create from serialization only
	CWaitDialogView();
	DECLARE_DYNCREATE(CWaitDialogView)

// Attributes
public:
	CWaitDialogDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitDialogView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaitDialogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWaitDialogView)
	afx_msg void OnViewWaitDlg();
	afx_msg void OnViewAbortDlg();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in WaitDialogView.cpp
inline CWaitDialogDoc* CWaitDialogView::GetDocument()
   { return (CWaitDialogDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDIALOGVIEW_H__25FAD211_F98F_11D2_8127_F91DB0F31875__INCLUDED_)
