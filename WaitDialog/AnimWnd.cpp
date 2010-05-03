// cAnimWnd.cpp : implementation file
//

#include "stdafx.h"
#include "WaitDialog.h"
#include "AnimWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cAnimWnd

cAnimWnd::cAnimWnd()
{
   m_ImageIndex = -1;
   m_MemDC = NULL;
}

cAnimWnd::~cAnimWnd()
{
   if (m_MemDC)
      delete m_MemDC;

   m_Bitmap.Detach();
   m_Bitmap.DeleteObject();
}


BEGIN_MESSAGE_MAP(cAnimWnd, CWnd)
	//{{AFX_MSG_MAP(cAnimWnd)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// cAnimWnd message handlers

void cAnimWnd::SetImageList(UINT BitmapID, short Sizex, short Sizey, COLORREF TransparentColor)
{
   m_TransparentColor = TransparentColor;

   m_Bitmap.LoadBitmap(BitmapID);
   m_Width = Sizex;
   m_Height = Sizey;

   CPoint ptSize;
   BITMAP bm_info;
   m_Bitmap.GetBitmap(&bm_info);
   ptSize.x = bm_info.bmWidth;
	ptSize.y = bm_info.bmHeight;

   m_MemDC = new cMemDC(this->GetDC(), CRect(0,0,ptSize.x, ptSize.y));
   m_MemDC->SelectObject(&m_Bitmap);
}

void cAnimWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
   if (m_MemDC)
      {
      // paint current image
      dc.BitBlt(0,0,m_Width, m_Height, m_MemDC, ((m_ImageIndex) * m_Width),0,SRCCOPY);
      }
   else
      {
	   CWnd::DefWindowProc(WM_PAINT, (WPARAM)dc.m_hDC, 0);
      return;
      }

	// Do not call CWnd::OnPaint() for painting messages
}

void cAnimWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
      {
      case TIMER_ID:
         {
         if (m_MemDC)
            {
            if (m_ImageIndex++ >= GetImageCount() - 1)
               m_ImageIndex = 0;
            Invalidate(TRUE);
            }
         }
      }

	CWnd::OnTimer(nIDEvent);
}

UINT cAnimWnd::StartAnim(short Delay)
{
   UINT ret = SetTimer(TIMER_ID, Delay, NULL);

   return ret;
}

BOOL cAnimWnd::StopAnim()
{
   if (!KillTimer(TIMER_ID))
      return FALSE;

   return TRUE;
}

BOOL cAnimWnd::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
   CString wndclass = ::AfxRegisterWndClass(CS_DBLCLKS,
     ::LoadCursor(NULL, IDC_ARROW),
     ::GetSysColorBrush(COLOR_BTNFACE), 0);
	
	BOOL ret = CWnd::CreateEx(0L, wndclass, NULL, dwStyle, rect, pParentWnd, nID, pContext);

   return ret;
}


int cAnimWnd::GetImageCount()
{
   BITMAP bm_info;
   m_Bitmap.GetBitmap(&bm_info);
   int x = bm_info.bmWidth;

   return (int)(x / m_Width);
}

