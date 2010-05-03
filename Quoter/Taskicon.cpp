// TaskIcon.cpp : implementation file
//

#include "stdafx.h"
#include "QuoterDlg.h"
#include "TaskIcon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuoterIcon

CQuoterIcon::CQuoterIcon()
{
}

CQuoterIcon::~CQuoterIcon()
{
}


BEGIN_MESSAGE_MAP(CQuoterIcon, CWnd)
	//{{AFX_MSG_MAP(CQuoterIcon)
	ON_WM_SYSCOMMAND()
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()
IMPLEMENT_DYNAMIC(CQuoterTray, CSystemTray)

/////////////////////////////////////////////////////////////////////////////
// CQuoterIcon message handlers

void CQuoterIcon::OnSysCommand(UINT nID, LPARAM lParam) 
{
	m_quoterDlg->OnSysCommand(nID, lParam);
  }

BOOL CQuoterIcon::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, CQuoterDlg* pQuoterDlg) 
{
  m_quoterDlg = pQuoterDlg;
  BOOL retVal = CreateEx (WS_EX_APPWINDOW,
                          lpszClassName,
                          lpszWindowName,
                          WS_VISIBLE | WS_POPUPWINDOW | WS_OVERLAPPED |
                          WS_MINIMIZEBOX | WS_MINIMIZE | WS_CAPTION,
                          0,
                          0,
                          0,
                          0,
                          m_quoterDlg->m_hWnd,
                          NULL);
  // initialize system menu
	CMenu* pSysMenu = GetSystemMenu(FALSE);

	if (pSysMenu != NULL)
	{
    pSysMenu->RemoveMenu (4, MF_BYPOSITION);
    pSysMenu->RemoveMenu (3, MF_BYPOSITION);
    pSysMenu->RemoveMenu (2, MF_BYPOSITION);
    pSysMenu->RemoveMenu (1, MF_BYPOSITION);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUT);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR);
			pSysMenu->InsertMenu(2, MF_BYPOSITION | MF_STRING, IDM_ABOUT, strAboutMenu);
		  }
  	}

	return retVal;
}

BEGIN_MESSAGE_MAP(CQuoterTray, CSystemTray)
	//{{AFX_MSG_MAP(CSystemTray)
	//}}AFX_MSG
END_MESSAGE_MAP()

BOOL CQuoterTray::Create (CQuoterDlg* pQuoter, HICON icon) {
  m_quoterDlg = pQuoter;

  return CSystemTray::Create((CWnd*) pQuoter, WM_ICON_NOTIFY, "Quoter", icon, IDR_POPUP_MENU);
  }

LRESULT CQuoterTray::OnTrayNotification(UINT wParam, LONG lParam) 
{
    //Return quickly if its not for this tray icon
    if (wParam != m_tnd.uID)
        return 0L;

    CMenu menu, *pSubMenu;
    CWnd* pTarget = (CWnd*) m_quoterDlg;

    // Clicking with right button brings up a context menu
    if (LOWORD(lParam) == WM_RBUTTONUP)
    {    
        if (!menu.LoadMenu(m_tnd.uID)) return 0;
        if (!(pSubMenu = menu.GetSubMenu(0))) return 0;

        // Make chosen menu item the default (bold font)
        ::SetMenuDefaultItem(pSubMenu->m_hMenu, m_DefaultMenuItemID, m_DefaultMenuItemByPos);

        // Display and track the popup menu
        CPoint pos;
        GetCursorPos(&pos);

        pTarget->SetForegroundWindow();  
        ::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y, 0, 
                         pTarget->GetSafeHwnd(), NULL);

        // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
        pTarget->PostMessage(WM_NULL, 0, 0);

        menu.DestroyMenu();
    } 
    else if (LOWORD(lParam) == WM_LBUTTONDBLCLK) 
    {
      // double click received, the default action is to execute default menu item
      pTarget->SetForegroundWindow();  

      UINT uItem;
      if (m_DefaultMenuItemByPos)
      {
          if (!menu.LoadMenu(m_tnd.uID)) return 0;
          if (!(pSubMenu = menu.GetSubMenu(0))) return 0;
          uItem = pSubMenu->GetMenuItemID(m_DefaultMenuItemID);
      }
        else
            uItem = m_DefaultMenuItemID;
        
        pTarget->SendMessage(WM_COMMAND, uItem, 0);

        menu.DestroyMenu();
        }

    return 1;
  }
