// QuoterDlg.h : header file
//

#if !defined(AFX_QUOTERDLG_H__EDB6EE28_8F75_11D2_9ACB_002018550C46__INCLUDED_)
#define AFX_QUOTERDLG_H__EDB6EE28_8F75_11D2_9ACB_002018550C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RandomQuote.h"
#include "TaskIcon.h"
#include "TransDlg.h"

#define WM_ICON_NOTIFY  WM_USER+10

#define MAX_TARGETS 5

struct targetInfo {
    char displayname [MAX_PATH];
    char footerfile  [MAX_PATH];
    char headerfile  [MAX_PATH];
    char targetfile  [MAX_PATH];
	char eoltag [10];
};

/////////////////////////////////////////////////////////////////////////////
// CQuoterDlg dialog

class CQuoterDlg : public CDialog
{
// Construction
public:
    CQuoterDlg(CWnd* pParent = NULL);	// standard constructor
    ~CQuoterDlg ();


    CQuoterIcon m_iconWnd;
    CTransDlg m_transer;
    CQuoterTray m_TrayIcon;

    int     m_r;
    int     m_g;
    int     m_b;
    int     m_timerval;
    int     m_display;
    BOOL    m_floatOn;
    BOOL    m_taskbarOn;
    BOOL    m_fromResource;
    HICON   m_hTrayIcon;
    CString m_separator;
    CString m_iconClass;
    CString m_defaultfile;
    CString m_version;
    CString m_filename;
    CString m_bmpFilename;

    CList <targetInfo*, targetInfo*> m_targetList;

// Dialog Data
    //{{AFX_DATA(CQuoterDlg)
	enum { IDD = IDD_QUOTER_DIALOG };
    CComboBox	m_combobox;
    CString	m_quote;
    int		m_comboval;
	CString	m_RandomText;
	//}}AFX_DATA

    RandomQuote* m_quotes;

    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CQuoterDlg)
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    //{{AFX_MSG(CQuoterDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnQuote();
    afx_msg void OnFirst();
    afx_msg void OnLast();
    afx_msg void OnNext();
    afx_msg void OnPrevious();
    afx_msg void OnChangeCombo();
    afx_msg void OnOptionsEdit();
    afx_msg void OnLoadDefault();
    afx_msg void OnShowFloat();
    afx_msg void OnUpdateShowFloat(CCmdUI* pCmdUI);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg void OnFileOpen();
    afx_msg void OnWritetarget();
    afx_msg void OnMinimize();
    afx_msg void OnFloaterOptions();
	afx_msg void OnOptionsRandomgen();
	//}}AFX_MSG
public:
    void    OnSysCommand(UINT nID, LPARAM lParam);
    void    ManageIcons();
    LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
    void    WriteIniData();
    void    ReadIniData();
    void    ValidateButtons();
    void    LoadFloater ();
    void    WriteTargets ();
    CMenu*  m_pSysMenu;
    void    SetQuotes ();
    BOOL    m_timeron;
    void    SetupTimer ();
    void    WriteTarget (targetInfo *info);
    void    stripright(char *data);

    afx_msg void OnPopupQuote();
    afx_msg void OnFileExit();
    afx_msg void OnHelpAbout();
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUOTERDLG_H__EDB6EE28_8F75_11D2_9ACB_002018550C46__INCLUDED_)
