// WaitDialogDoc.h : interface of the CWaitDialogDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITDIALOGDOC_H__25FAD20F_F98F_11D2_8127_F91DB0F31875__INCLUDED_)
#define AFX_WAITDIALOGDOC_H__25FAD20F_F98F_11D2_8127_F91DB0F31875__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CWaitDialogDoc : public CDocument
{
protected: // create from serialization only
	CWaitDialogDoc();
	DECLARE_DYNCREATE(CWaitDialogDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitDialogDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaitDialogDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CWaitDialogDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITDIALOGDOC_H__25FAD20F_F98F_11D2_8127_F91DB0F31875__INCLUDED_)
