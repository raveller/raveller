#if !defined(AFX_cANIMWND_H__7F9C97E1_F7F4_11D2_837C_00500406DAEB__INCLUDED_)
#define AFX_cANIMWND_H__7F9C97E1_F7F4_11D2_837C_00500406DAEB__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// cAnimWnd.h : header file
//
//////////////////////////////////////////////////// cAnimWnd //
// Author: Todd Andrews
// Email:  tmandrews@mindspring.com
// Copyright 1999, Todd Andrews
//
// You may freely use or modify this code provided this
// Copyright is included in all derived versions.
//
//
// This class implements an animated bitmap

#include "memdc.h"

/////////////////////////////////////////////////////////////////////////////
// cAnimWnd window

#define TIMER_ID 13
class cAnimWnd : public CWnd
{
// Construction
public:
	cAnimWnd();

// Attributes
public:

protected:
   int            m_ImageIndex;
   COLORREF       m_TransparentColor;
   short          m_Width;
   short          m_Height;
   CBitmap        m_Bitmap;
   cMemDC         *m_MemDC;

// Operations
public:
   void SetImageList(UINT BitmapID, short Size, short Sizey, COLORREF TransparentColor = -1);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cAnimWnd)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	int GetImageCount();
	BOOL StopAnim();
	UINT StartAnim(short Delay = 50);
	virtual ~cAnimWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(cAnimWnd)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_cANIMWND_H__7F9C97E1_F7F4_11D2_837C_00500406DAEB__INCLUDED_)
