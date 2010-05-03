#if !defined(AFX_EDITQUOTE_H__AF05E721_DC5B_11D2_9ACB_002018550C46__INCLUDED_)
#define AFX_EDITQUOTE_H__AF05E721_DC5B_11D2_9ACB_002018550C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditQuote.h : header file
//

#include "QuoterDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CEditQuote dialog

class CEditQuote : public CDialog
{
// Construction
public:
	CQuoterDlg* m_quoteDlg;
	CEditQuote(CWnd* pParent = NULL);   // standard constructor

    ~CEditQuote();

// Dialog Data
	//{{AFX_DATA(CEditQuote)
	enum { IDD = IDD_EDITOPTIONS };
	CListBox	m_targetList;
	int		m_display;
	int		m_timerval;
	CString	m_separator;
	CString	m_defaultfile;
	CString	m_currentfile;
	CString	m_displayname;
	//}}AFX_DATA

    CList <targetInfo*, targetInfo*> m_afterList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditQuote)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableButtons ();

	// Generated message map functions
	//{{AFX_MSG(CEditQuote)
	afx_msg void OnBrowseQuote();
	afx_msg void OnAddOutput();
	afx_msg void OnSetCurrent();
	afx_msg void OnChangeSeparator();
	afx_msg void OnRemoveOutput();
	afx_msg void OnEditOutput();
	afx_msg void OnTargetListChange();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CFloaterOptions dialog

class CFloaterOptions : public CDialog
{
// Construction
public:
	~CFloaterOptions();
	void ChangeBitmap ();
	void EnableWidgets ();
	CFloaterOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFloaterOptions)
	enum { IDD = IDD_FLOATEROPTIONS };
    CSliderCtrl	m_redSlider;
	CSliderCtrl	m_blueSlider;
	CSliderCtrl	m_greenSlider;
	int		m_greenval;
	int		m_blueval;
	int		m_redval;
	BOOL	m_internalBMP;
	CString	m_filename;
	//}}AFX_DATA

    CBitmap  m_bmp;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFloaterOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFloaterOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleaseRed(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleaseGreen(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleaseBlue(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditRed();
	afx_msg void OnEditGreen();
	afx_msg void OnEditBlue();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnClickBitmap();
	afx_msg void OnInternal();
	afx_msg void OnBrowseBitmap();
	afx_msg void OnChangeFilename();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITQUOTE_H__AF05E721_DC5B_11D2_9ACB_002018550C46__INCLUDED_)
