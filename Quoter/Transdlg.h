#if !defined(AFX_TransDlg_H__B5C03EE0_DC82_11D2_9ACB_002018550C46__INCLUDED_)
#define AFX_TransDlg_H__B5C03EE0_DC82_11D2_9ACB_002018550C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Quoter.h"

/////////////////////////////////////////////////////////////////////////////
// CTransDlg dialog
BOOL LoadBMP( LPCTSTR sBMPFile, HGLOBAL *phDIB, CPalette *pPal );

void DrawDIB( CDC* pDC, HGLOBAL hDIB, CPalette *pPal );

BOOL LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal );

class CTransDlg : public CDialog
{
// Construction
public:
    CWnd* m_quoter;
    void OnFloatClose();
    UINT m_maskID;
    void SetBitmap (UINT bmpID, UINT maskID);
    void SetRGB (int r, int g, int b);
    void InitSize();
    UINT m_bmpID;
    CMenu m_popup;
    int m_width;
    int m_height;
    CTransDlg(CWnd* pParent = NULL);   // standard constructor
    void SetupRegion();
    int m_r;
    int m_g;
    int m_b;
    BOOL m_fromResource;
    CBitmap m_bmp;

// Dialog Data
	//{{AFX_DATA(CTransDlg)
	enum { IDD = IDD_TRANS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTransDlg)
	public:
    virtual BOOL DestroyWindow();
	protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTransDlg)
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    virtual BOOL OnInitDialog();
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TransDlg_H__B5C03EE0_DC82_11D2_9ACB_002018550C46__INCLUDED_)
