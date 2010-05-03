// FormDoctorView.h : interface of the CFormDoctorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMDOCTORVIEW_H__2969B3B2_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
#define AFX_FORMDOCTORVIEW_H__2969B3B2_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFormDoctorView : public CView
{
protected: // create from serialization only
	CFormDoctorView();
	DECLARE_DYNCREATE(CFormDoctorView)

// Attributes
public:
	CFormDoctorDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDoctorView)
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
	virtual ~CFormDoctorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormDoctorView)
	afx_msg void OnFormEnterdata();
	afx_msg void OnFormSubmit();
	afx_msg void OnFormViewlastresponse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FormDoctorView.cpp
inline CFormDoctorDoc* CFormDoctorView::GetDocument()
   { return (CFormDoctorDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDOCTORVIEW_H__2969B3B2_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
