// About.cpp : implementation file
//

#include "stdafx.h"
#include "Quoter.h"
#include "About.h"
#include "QuoteUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbout dialog


CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAbout)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbout)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
	//{{AFX_MSG_MAP(CAbout)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbout message handlers

void CAbout::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
//	COLORREF buttonColor ;
//	BOOL     button = FALSE;
  CRect    rect   = lpDrawItemStruct->rcItem;
  CDC*     pDC    = CDC::FromHandle(lpDrawItemStruct->hDC);

	switch (nIDCtl) {
		case IDOK: {
			// Get and Set palette
		  CPalette* pOldPalette = NULL;
      CPalette* m_palette = QuikPalette (IDB_ABOUT);
      if ((HPALETTE) m_palette != NULL) {
				pOldPalette = pDC->SelectPalette(m_palette, FALSE);
				pDC->RealizePalette();
				}
	
			HBITMAP hbitmap;
			hbitmap = QuikBitmap (IDB_ABOUT);
			// Draw the Wizard bitmap
			CDC      memDC;
			BITMAP   bmpData;
			CBitmap* pBmpCurrent;
			CBitmap* pOldBitmap;

			pBmpCurrent = CBitmap::FromHandle (hbitmap);

			if (pBmpCurrent) {
				memDC.CreateCompatibleDC(pDC);
				pOldBitmap = memDC.SelectObject(pBmpCurrent);
				pBmpCurrent->GetObject(sizeof(BITMAP), (LPVOID) &bmpData);

				pDC->StretchBlt (rect.left, rect.top,
												 rect.Width(),
												 rect.Height(),
												 &memDC,
												 0, 0,
												 bmpData.bmWidth, bmpData.bmHeight,
												 SRCCOPY);
				//pBmpCurrent->DeleteObject();
				memDC.SelectObject (pOldBitmap);
        pBmpCurrent->DeleteObject();
		    memDC.DeleteDC ();

				// Delete the allocated bitmap
				if (hbitmap)
					::DeleteObject (hbitmap);

				// Select the old palette
				if ((HPALETTE) m_palette != NULL) {
					pDC->SelectPalette(pOldPalette, FALSE);
          delete m_palette;
          m_palette = NULL;
					}
			  }	
      }
			break;
		default:
    	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
      break;
	  }	
  }

BOOL CAbout::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Size the Dialog and move it to the center of its parent
	MoveWindow(0, 0, 309, 173, FALSE);
	CenterWindow (GetParent());
	GetDlgItem(IDOK)->MoveWindow (0, 0, 309, 173, FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
