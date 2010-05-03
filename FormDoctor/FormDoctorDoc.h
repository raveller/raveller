// FormDoctorDoc.h : interface of the CFormDoctorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FORMDOCTORDOC_H__2969B3B0_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
#define AFX_FORMDOCTORDOC_H__2969B3B0_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFormDoctorDoc : public CDocument
{
protected: // create from serialization only
	CFormDoctorDoc();
	DECLARE_DYNCREATE(CFormDoctorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFormDoctorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_userAgent;
	CString m_server;
	CString m_path;
	CString m_response;
	CString m_url;
	CString m_formdata;
	virtual ~CFormDoctorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFormDoctorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CFormDoctorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FORMDOCTORDOC_H__2969B3B0_40AD_11D4_9ACB_0020182EE5EF__INCLUDED_)
