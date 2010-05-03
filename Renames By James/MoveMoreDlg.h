// MoveMoreDlg.h : header file
//

#if !defined(AFX_MOVEMOREDLG_H__84478E37_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
#define AFX_MOVEMOREDLG_H__84478E37_79C3_11D4_B476_00B0D02A8795__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMoveMoreDlg dialog

class CMoveMoreDlg : public CDialog
{
// Construction
public:
	void WriteProfileForFileExt ();
	CMoveMoreDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMoveMoreDlg)
	enum { IDD = IDD_MOVEMORE_DIALOG };
	CString	m_fromext;
	CString	m_fromfile;
	CString	m_toext;
	CString	m_tofile;
	CString	m_dir;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoveMoreDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMoveMoreDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBrowsefile();
	afx_msg void OnDirbrowse();
	afx_msg void OnDitto();
	afx_msg void OnRename();
	afx_msg void OnSwap();
	afx_msg void OnNuhhuh();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOVEMOREDLG_H__84478E37_79C3_11D4_B476_00B0D02A8795__INCLUDED_)
