// QuoterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Quoter.h"
#include "QuoterDlg.h"
#include "About.h"
#include "EditQuote.h"
#include "Random.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define QUOTE_TIMER_ID 9999

/////////////////////////////////////////////////////////////////////////////
// CQuoterDlg dialog

CQuoterDlg::CQuoterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuoterDlg::IDD, pParent)
{
  m_pSysMenu = NULL;
  m_timeron = FALSE;
  m_iconClass = _T("");
  m_floatOn = FALSE;
  m_quotes = NULL;
  m_display = 2;
	//{{AFX_DATA_INIT(CQuoterDlg)
	m_quote = _T("");
	m_comboval = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon    = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
 
    m_r = 0;
    m_g = 0;
    m_b = 0;
    m_fromResource = TRUE;
    m_bmpFilename = _T("");
}

CQuoterDlg::~CQuoterDlg ()
{
    UnregisterClass(m_iconClass, AfxGetApp()->m_hInstance);

    if (::IsWindow(m_iconWnd.m_hWnd))
        m_iconWnd.DestroyWindow();

    POSITION pos = m_targetList.GetHeadPosition ();
    targetInfo *info;
    while (pos)
    {
        info = m_targetList.GetNext (pos);
        delete info;
    }

    m_targetList.RemoveAll ();

    m_transer.DestroyWindow ();

    if (m_quotes)
    {
        delete m_quotes;
        m_quotes = NULL;
    }
}

void CQuoterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuoterDlg)
	DDX_Control(pDX, IDC_SELECTCOMBO, m_combobox);
	DDX_Text(pDX, IDC_QUOTE_SPACE, m_quote);
	DDX_CBIndex(pDX, IDC_SELECTCOMBO, m_comboval);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CQuoterDlg, CDialog)
	//{{AFX_MSG_MAP(CQuoterDlg)
  ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETQUOTE, OnQuote)
	ON_BN_CLICKED(IDC_FIRST, OnFirst)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREVIOUS, OnPrevious)
	ON_CBN_SELCHANGE(IDC_SELECTCOMBO, OnChangeCombo)
	ON_COMMAND(ID_OPTIONS_EDIT, OnOptionsEdit)
	ON_COMMAND(ID_OPTION_LOADDEFAULT, OnLoadDefault)
	ON_COMMAND(ID_OPTION_SHOWFLOAT, OnShowFloat)
	ON_UPDATE_COMMAND_UI(ID_OPTION_SHOWFLOAT, OnUpdateShowFloat)
	ON_WM_TIMER()
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_BN_CLICKED(IDC_WRITETARGET, OnWritetarget)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	ON_COMMAND(ID_OPTIONS_FLOATEROPTIONS, OnFloaterOptions)
  ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_COMMAND(ID_FILE_EXIT,        OnFileExit)
	ON_COMMAND(ID_HELP_ABOUT,       OnHelpAbout)
	ON_COMMAND(ID_POPUP_QUOTE,      OnPopupQuote)
	ON_COMMAND(ID_FLOATER_CLOSE, OnShowFloat)
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_RESTORE, OnPopupQuote)
	ON_COMMAND(ID_OPTIONS_RANDOMGEN, OnOptionsRandomgen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
	//ON_WM_QUERYENDSESSION()

/////////////////////////////////////////////////////////////////////////////
// CQuoterDlg message handlers

BOOL CQuoterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

  // Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
  m_taskbarOn = TRUE;

  // initialize taskbar
  if (!m_TrayIcon.Create((CQuoterDlg*) this, m_hIcon))
    return -1;
  m_iconClass = AfxRegisterWndClass (NULL, NULL, NULL, m_hIcon);

  // initialize system menu
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
    pSysMenu->RemoveMenu (4, MF_BYPOSITION);
    pSysMenu->RemoveMenu (2, MF_BYPOSITION);

		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUT);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->InsertMenu(3, MF_BYPOSITION | MF_SEPARATOR);
			pSysMenu->InsertMenu(4, MF_BYPOSITION | MF_STRING, IDM_ABOUT, strAboutMenu);
		  }
  	}

    LoadFloater ();

  // Read quote file
  SetQuotes ();

  if (m_timerval != 5) 
  {
     WriteTargets();
  }
  SetupTimer();

  // Manage icons in taskbar and system tray
	ManageIcons();

	return TRUE;  // return TRUE  unless you set the focus to a control
  }

void CQuoterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
  switch (nID) {
    case IDM_ABOUT :
      OnHelpAbout();
      break;
    case SC_MINIMIZE :
      ShowWindow (SW_HIDE);
      break;
    case SC_RESTORE :
      ShowWindow (SW_SHOW);
      break;
    default:
      CDialog::OnSysCommand(nID, lParam);
      break;
    }
  }

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CQuoterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQuoterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CQuoterDlg::OnQuote() 
{
  if (m_quotes) {
    char* quote = m_quotes->Random();
    if (quote) {
      m_quote = quote;
      m_comboval = m_quotes->Index();
      UpdateData (FALSE);
      ValidateButtons();
      }
    }
  } 

void CQuoterDlg::OnFirst() 
{
  if (m_quotes) {
    char* quote = m_quotes->First();
    if (quote) {
      m_quote = quote;
      m_comboval = m_quotes->Index();
      UpdateData (FALSE);
      ValidateButtons();
      }
    }
  }

void CQuoterDlg::OnLast() 
{
  if (m_quotes) {
    char* quote = m_quotes->Last();
    if (quote) {
      m_quote = quote;
      m_comboval = m_quotes->Index();
      UpdateData (FALSE);
      ValidateButtons();
      }
    }
  }

void CQuoterDlg::OnNext() 
{
  if (m_quotes) {
    char* quote = m_quotes->Next();
    if (quote) {
      m_quote = quote;
      m_comboval = m_quotes->Index();
      UpdateData (FALSE);
      ValidateButtons();
      }
    }
  }

void CQuoterDlg::OnPrevious() 
{
  if (m_quotes) {
    char* quote = m_quotes->Previous();
    if (quote) {
      m_quote = quote;
      m_comboval = m_quotes->Index();
      UpdateData (FALSE);
      ValidateButtons();
      }
    }
  }

void CQuoterDlg::ValidateButtons()
{
  BOOL upEnable = !(m_quotes->IsLast());
  BOOL downEnable = !(m_quotes->IsFirst());
  GetDlgItem (IDC_FIRST)->EnableWindow (downEnable);
  GetDlgItem (IDC_PREVIOUS)->EnableWindow (downEnable);
  GetDlgItem (IDC_LAST)->EnableWindow (upEnable);
  GetDlgItem (IDC_NEXT)->EnableWindow (upEnable);
  }

void CQuoterDlg::OnChangeCombo() 
{
  UpdateData (TRUE);
  if (m_quotes) {
    char* quote = m_quotes->At(m_comboval);
    if (quote) {
      m_quote = quote;
      UpdateData (FALSE);
      ValidateButtons();
      }
    }  
  }


void CQuoterDlg::OnFileExit() 
{
  OnOK();	
  }

void CQuoterDlg::OnHelpAbout() 
{
	CAbout dlg;
  dlg.DoModal();
  }

void CQuoterDlg::OnOptionsEdit() 
{
    CEditQuote dlg;

    dlg.m_quoteDlg = (CQuoterDlg*) this;
    dlg.m_timerval    = m_timerval;
    dlg.m_display     = m_display;
    dlg.m_defaultfile = m_defaultfile;
    dlg.m_currentfile = m_filename;
    
    dlg.m_separator   = m_separator;
    if (dlg.DoModal() == IDOK) {
        if (dlg.m_timerval != m_timerval)
        {
            if ((dlg.m_timerval < 4) && (dlg.m_timerval < m_timerval))
                WriteTargets();
            m_timerval    = dlg.m_timerval;
            SetupTimer();
        }

        POSITION pos = m_targetList.GetHeadPosition ();
        targetInfo *info, *info2;

        while (pos)
        {
            info = m_targetList.GetNext (pos);
            delete info;
        }
        m_targetList.RemoveAll ();

        pos = dlg.m_afterList.GetHeadPosition ();
        while (pos)
        {
            info2 = dlg.m_afterList.GetNext (pos);
            info = new targetInfo;
            strcpy_s (info->displayname, info2->displayname);
            strcpy_s (info->footerfile, info2->footerfile);
            strcpy_s (info->headerfile, info2->headerfile);
            strcpy_s (info->targetfile, info2->targetfile);
            strcpy_s (info->eoltag, info2->eoltag);

            m_targetList.AddTail (info);
        }

        m_display     = dlg.m_display;
        m_defaultfile = dlg.m_defaultfile;
        m_separator   = dlg.m_separator;
        ManageIcons();
        WriteIniData();
    }
}
void CQuoterDlg::stripright(char *data)
{
	char        *d_ptr = data + strlen(data); 

    while ( d_ptr > data && *(--d_ptr) == ' ' )
        {
		*d_ptr = '\0';
 		}
}

void CQuoterDlg::ReadIniData()
{
    CWinApp* pApp = AfxGetApp ();

    CString keyName = _T("");
    CString keyMask = _T("");
    CString lineread = _T("");

    // Separator Key
    CString separator = _T("");
    separator.LoadString (IDS_SEPARATOR);
    keyName.LoadString (IDS_SEPARATORKEY);
    lineread = pApp->GetProfileString (_T(""), keyName, (LPCTSTR) separator);
    lineread.TrimLeft (); lineread.TrimRight();

    if (lineread.IsEmpty())
        m_separator = separator;
    else
        m_separator = lineread;

    // Default File
    char currentDir[_MAX_PATH];
    GetCurrentDirectory (_MAX_PATH, currentDir);
    CString deffilename = _T("");
    deffilename.LoadString (IDS_DEFAULT_QUOTE_FILE);
    CString defaultpath = _T("");
    defaultpath.Format ("%s\\%s",currentDir,deffilename);

    keyName.LoadString (IDS_DEFAULTKEY);
    lineread = pApp->GetProfileString (_T(""), keyName, (LPCTSTR) defaultpath);
    lineread.TrimLeft (); lineread.TrimRight();

    if (lineread.IsEmpty())
        m_defaultfile = defaultpath;
    else 
        m_defaultfile = lineread;

    targetInfo tempInfo;
    CString tgtGrpMask = _T("");
    CString tgtGrp = _T("");
    tgtGrpMask.LoadString (IDS_TARGETGROUPMASK);

    for (int i = 0; i < MAX_TARGETS + 1; i++)
    {
        // Attempt to read old registry settings
        // if no targets found.
        if ((i == MAX_TARGETS) && (m_targetList.GetCount () == 0))
        {
            tgtGrp = _T("");
        }
        else if (i == MAX_TARGETS)
            break;
        else
           tgtGrp.Format (IDS_TARGETGROUPMASK, i);

        strcpy_s (tempInfo.displayname, "");
        strcpy_s (tempInfo.headerfile, "");
        strcpy_s (tempInfo.footerfile, "");
        strcpy_s (tempInfo.targetfile, "");
        strcpy_s (tempInfo.eoltag, "");

        // Display Name
        keyName.LoadString (IDS_DISPLAYKEY);
        lineread = pApp->GetProfileString (tgtGrp, keyName, "");
        lineread.TrimLeft (); lineread.TrimRight();

        if (!lineread.IsEmpty())
            strcpy_s (tempInfo.displayname, (LPCTSTR) lineread);
        else if (i == MAX_TARGETS)
            strcpy_s (tempInfo.displayname, "Default");

        // Header File
        keyName.LoadString (IDS_HEADERKEY);
        lineread = pApp->GetProfileString (tgtGrp, keyName, "");
        lineread.TrimLeft (); lineread.TrimRight();

        if (!lineread.IsEmpty())
            strcpy_s (tempInfo.headerfile, (LPCTSTR) lineread);

        // Footer File
        keyName.LoadString (IDS_FOOTERKEY);
        lineread = pApp->GetProfileString (tgtGrp, keyName, "");
        lineread.TrimLeft (); lineread.TrimRight();

        if (!lineread.IsEmpty())
            strcpy_s (tempInfo.footerfile, (LPCTSTR) lineread);

        // Target File
        keyName.LoadString (IDS_TARGETKEY);
        lineread = pApp->GetProfileString (tgtGrp, keyName, "");
        lineread.TrimLeft (); lineread.TrimRight();

        if (!lineread.IsEmpty())
            strcpy_s (tempInfo.targetfile, (LPCTSTR) lineread);

        // Target File
        keyName.LoadString (IDS_EOLTAGKEY);
        lineread = pApp->GetProfileString (tgtGrp, keyName, "");
        lineread.TrimLeft (); lineread.TrimRight();

        if (!lineread.IsEmpty())
            strcpy_s (tempInfo.eoltag, (LPCTSTR) lineread);

        // Load list of targets if target exists
        if (strlen (tempInfo.displayname) && strlen (tempInfo.targetfile))
        {
            targetInfo *info = new targetInfo;
            
            strcpy_s (info->displayname, tempInfo.displayname);
            strcpy_s (info->headerfile, tempInfo.headerfile);
            strcpy_s (info->footerfile, tempInfo.footerfile);
            strcpy_s (info->targetfile, tempInfo.targetfile);
            strcpy_s (info->eoltag, tempInfo.eoltag);
            
            m_targetList.AddTail (info);
        }
    }

    // UPDATE INTERVAL
    keyName.LoadString (IDS_INTERVALKEY);
    m_timerval = pApp->GetProfileInt (_T(""), keyName, 5);
    if ((m_timerval > 5) || (m_timerval < 0))
        m_timerval = 5;

    // ICON DISPLAY
    keyName.LoadString (IDS_ICONKEY);
    m_display = pApp->GetProfileInt (_T(""), keyName, 2);
    if ((m_display > 2) || (m_display < 0))
        m_display = 2;

    // VERSION
    CString version = _T("");
    version.LoadString (IDS_VERSION);
    keyName.LoadString (IDS_VERSIONKEY);
    lineread = pApp->GetProfileString (_T(""), keyName, version);
    lineread.TrimLeft (); lineread.TrimRight();
    if (lineread.IsEmpty ())
        m_version = version;
    else
        m_version = lineread;

    // Internal Floater
    keyName.LoadString (IDS_INTERNALBMPKEY);
    m_fromResource = pApp->GetProfileInt (_T(""), keyName, 1);

    // BMP Filename
    keyName.LoadString (IDS_BMPFILENAMEKEY);
    lineread = pApp->GetProfileString (_T(""), keyName, NULL);
    lineread.TrimLeft (); lineread.TrimRight();
    m_bmpFilename = lineread;

    // Trans Red
    keyName.LoadString (IDS_REDTRANSKEY);
    m_r = pApp->GetProfileInt (_T(""), keyName, 0);

    // Trans Green
    keyName.LoadString (IDS_GREENTRANSKEY);
    m_g = pApp->GetProfileInt (_T(""), keyName, 0);

    // Trans Blue
    keyName.LoadString (IDS_BLUETRANSKEY);
    m_b = pApp->GetProfileInt (_T(""), keyName, 0);
}

void CQuoterDlg::WriteIniData()
{
    CWinApp* pApp = AfxGetApp ();

    CString keyName = _T("");
    CString keyMask = _T("");

    // SEPARATOR
    keyName.LoadString (IDS_SEPARATORKEY);
    pApp->WriteProfileString (_T(""), keyName, (LPCTSTR) m_separator);

    // DEFAULT FILE
    keyName.LoadString (IDS_DEFAULTKEY);
    pApp->WriteProfileString (_T(""), keyName, (LPCTSTR) m_defaultfile);

    POSITION pos = m_targetList.GetHeadPosition ();
    targetInfo *info;
    targetInfo tempInfo;

    CString tgtGrpMask = _T("");
    CString tgtGrp = _T("");
    tgtGrpMask.LoadString (IDS_TARGETGROUPMASK);

    for (int i = 0; i < MAX_TARGETS; i++)
    {
        tgtGrp.Format (IDS_TARGETGROUPMASK, i);

        if (pos)
        {
            info = m_targetList.GetNext (pos);

            strcpy_s (tempInfo.displayname,   info->displayname);
            strcpy_s (tempInfo.footerfile, info->footerfile);
            strcpy_s (tempInfo.headerfile, info->headerfile);
            strcpy_s (tempInfo.targetfile, info->targetfile);
            strcpy_s (tempInfo.eoltag, info->eoltag);
        }
        else
        {
            strcpy_s (tempInfo.displayname, "");
            strcpy_s (tempInfo.footerfile, "");
            strcpy_s (tempInfo.headerfile, "");
            strcpy_s (tempInfo.targetfile, "");
            strcpy_s (tempInfo.eoltag, "");
        }

        // Display Name
        keyName.LoadString (IDS_DISPLAYKEY);
        pApp->WriteProfileString (tgtGrp, keyName, tempInfo.displayname);

        // Footer File
        keyName.LoadString (IDS_FOOTERKEY);
        pApp->WriteProfileString (tgtGrp, keyName, tempInfo.footerfile);

        // Header File
        keyName.LoadString (IDS_HEADERKEY);
        pApp->WriteProfileString (tgtGrp, keyName, tempInfo.headerfile);

        // Target File
        keyName.LoadString (IDS_TARGETKEY);
        pApp->WriteProfileString (tgtGrp, keyName, tempInfo.targetfile);

        // EOL Tag
        keyName.LoadString (IDS_EOLTAGKEY);
        pApp->WriteProfileString (tgtGrp, keyName, tempInfo.eoltag);
    }

    // Update Interval
    keyName.LoadString (IDS_INTERVALKEY);
    pApp->WriteProfileInt (_T(""), keyName, m_timerval);

    // Icon Display
    keyName.LoadString (IDS_ICONKEY);
    pApp->WriteProfileInt (_T(""), keyName, m_display);

    // Target File
    keyName.LoadString (IDS_VERSIONKEY);
    pApp->WriteProfileString (_T(""), keyName, m_version);

    // Internal Floater
    keyName.LoadString (IDS_INTERNALBMPKEY);
    pApp->WriteProfileInt (_T(""), keyName, m_fromResource);

    // BMP Filename
    keyName.LoadString (IDS_BMPFILENAMEKEY);
    pApp->WriteProfileString (_T(""), keyName, m_bmpFilename);

    // Trans Red
    keyName.LoadString (IDS_REDTRANSKEY);
    pApp->WriteProfileInt (_T(""), keyName, m_r);

    // Trans Green
    keyName.LoadString (IDS_GREENTRANSKEY);
    pApp->WriteProfileInt (_T(""), keyName, m_g);

    // Trans Blue
    keyName.LoadString (IDS_BLUETRANSKEY);
    pApp->WriteProfileInt (_T(""), keyName, m_b);
}

void CQuoterDlg::OnLoadDefault() 
{
	m_filename = m_defaultfile;
  delete m_quotes;
  m_quotes = new RandomQuote (m_filename, m_separator);
  OnQuote();
  SetQuotes();
  }

LRESULT CQuoterDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
  // Delegate all the work back to the default implementation in CSystemTray.
  return m_TrayIcon.OnTrayNotification(wParam, lParam);
  }

void CQuoterDlg::ManageIcons()
{
  if (m_display > 0)
    //Show tray icon
    m_TrayIcon.ShowIcon ();
  else
    m_TrayIcon.HideIcon ();

  if ((m_display != 1) && (!(::IsWindow(m_iconWnd.m_hWnd)))) {
    m_iconWnd.Create (m_iconClass, "Quoter", this);
    }
  else if ((m_display == 1) && (::IsWindow(m_iconWnd.m_hWnd))) {
    m_iconWnd.DestroyWindow();
    }
  }

void CQuoterDlg::OnPopupQuote() 
{
  ShowWindow (SW_SHOW);
  }

void CQuoterDlg::OnShowFloat() 
{
  if (m_floatOn) {
    m_transer.ShowWindow (SW_HIDE);
    m_floatOn = FALSE;
    }
  else {
    m_transer.ShowWindow (SW_SHOW);
    m_floatOn = TRUE;
    }
  }

void CQuoterDlg::OnUpdateShowFloat(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck(m_floatOn);
  }

void CQuoterDlg::SetupTimer() {
  if (m_timeron) 
    KillTimer (QUOTE_TIMER_ID);
  if (m_timerval != 4) {
    int timelen = 5;
    switch (m_timerval) {
      case 1: timelen = 10; break;
      case 2: timelen = 30; break;
      case 3: timelen = 60; break;
      default: break;
      }
    SetTimer (QUOTE_TIMER_ID, timelen*60*1000, NULL);
    m_timeron = TRUE;
    }
  }

void CQuoterDlg::OnTimer(UINT nIDEvent) 
{
    if (nIDEvent == QUOTE_TIMER_ID)
    {
        //   CString temp = "";
        //   temp.Format ("%d", nIDEvent);
        //   AfxMessageBox (temp);
        OnQuote();

        WriteTargets ();
    }
    CDialog::OnTimer(nIDEvent);
}

void CQuoterDlg::WriteTarget(targetInfo* info)
{
    if (!info)
        return;

  if (strlen (info->targetfile)) {
    CString header = "";
    CString footer = "";
    CString out = "";
    if (strlen (info->headerfile)) {
      CFile* headFile = NULL;
      
      // Open the given filename for reading
	    TRY   { headFile = new CFile (info->headerfile, CFile::modeRead); }
	    CATCH ( CFileException, e ) { headFile = NULL;}
	    END_CATCH
      if (headFile) {
    		// Determine the file length
        char* fileBuffer = NULL;
        ULONGLONG fileLength = 0;
  	    TRY   {fileLength = headFile->GetLength();}
	      CATCH ( CFileException, e ) {fileLength = 0;}
     	  END_CATCH
 
        // Read the entrie file
        if (fileLength > 0) {
          fileBuffer = new char [(int)fileLength+1];
          TRY {
            headFile->Read (fileBuffer, (UINT) fileLength);}
          CATCH (CFileException, e) {
            fileLength = 0;
            delete [] fileBuffer;
            fileBuffer = NULL;
            }
          END_CATCH

          if (fileBuffer) {
            fileBuffer [fileLength] = '\0';
            header = fileBuffer;
            fileLength = 0;
            delete [] fileBuffer;
            fileBuffer = NULL;
            }
          }
        headFile->Close();
        delete headFile;
        headFile = NULL;
        }
      }
    if (strlen (info->footerfile)) {
      CFile* footFile = NULL;
      
      // Open the given filename for reading
	    TRY   { footFile = new CFile (info->footerfile, CFile::modeRead); }
	    CATCH ( CFileException, e ) { footFile = NULL;}
	    END_CATCH
      if (footFile) {
    		// Determine the file length
        char* fileBuffer = NULL;
        ULONGLONG fileLength = 0;
  	    TRY   {fileLength = footFile->GetLength();}
	      CATCH ( CFileException, e ) {fileLength = 0;}
     	  END_CATCH
 
        // Read the entrie file
        if (fileLength > 0) {
          fileBuffer = new char [(int)fileLength + 1];
          TRY {
            footFile->Read (fileBuffer, (UINT) fileLength);}
          CATCH (CFileException, e) {
            fileLength = 0;
            delete [] fileBuffer;
            fileBuffer = NULL;
            }
          END_CATCH

          if (fileBuffer) {
            fileBuffer [fileLength] = '\0';
            footer = fileBuffer;
            fileLength = 0;
            delete [] fileBuffer;
            fileBuffer = NULL;
            }
          }
        footFile->Close();
        delete footFile;
        footFile = NULL;
        }
      }
    CFile* outFile = NULL;
      
    // Open the given filename for reading
    TRY   { outFile = new CFile (info->targetfile, CFile::modeCreate | CFile::modeWrite); }
    CATCH ( CFileException, e ) { outFile = NULL;}
    END_CATCH
    
    if (outFile) {
        CString modquote = m_quote;
      if (strlen (info->eoltag))
      {
          char repTag [12];
          sprintf_s (repTag, "%s\r\n", info->eoltag);
          modquote.Replace ("\r\n", repTag);
      }

      if (header.IsEmpty() && footer.IsEmpty())
        out = modquote;
      else if (header.IsEmpty())
        out = modquote + "\r\n" + footer;
      else if (footer.IsEmpty())
        out = header + "\r\n" + modquote;
      else
        out = header + "\r\n" + modquote + "\r\n" + footer;

      outFile->Write (out.GetBuffer (_MAX_PATH), out.GetLength());
      out.ReleaseBuffer();
      outFile->Close();
      delete outFile;
      outFile = NULL;
      }
    }
  }

void CQuoterDlg::SetQuotes () {
  if (m_quotes) 
    delete m_quotes;
  m_quotes = new RandomQuote (m_filename, m_separator);

  OnQuote();
  if (m_combobox.GetCount () > 0) 
    m_combobox.ResetContent ();
  CString comboStr = "";
  for (int q = 1; q <= m_quotes->Count(); q++) {
    comboStr.Format ("%d", q);
    m_combobox.AddString (comboStr);
    }
  m_comboval = m_quotes->Index();
  UpdateData (FALSE);
  }

void CQuoterDlg::OnFileOpen() 
{
  CString szFilter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
  CFileDialog* dlg = new CFileDialog (TRUE, "txt", (LPCTSTR) m_filename,
                                      OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                                      szFilter, (CWnd*) this);

  //dlg->m_ofn.lpstrInitialDir = pinitialDir;

  if (dlg->DoModal() == IDOK) {
    m_filename = dlg->GetPathName();
    SetQuotes();
    }
	}

void CQuoterDlg::OnWritetarget() 
{
        WriteTargets ();
}

void CQuoterDlg::OnMinimize() 
{
  ShowWindow (SW_HIDE);
  }

void CQuoterDlg::WriteTargets()
{
    POSITION pos = m_targetList.GetHeadPosition ();
    targetInfo* info;
    while (pos)
    {
        info = m_targetList.GetNext (pos);
        WriteTarget (info);
    }
}

void CQuoterDlg::OnFloaterOptions() 
{
    CFloaterOptions dlg;

    dlg.m_blueval = m_b;
    dlg.m_redval = m_r;
    dlg.m_greenval = m_g;
    dlg.m_internalBMP = m_fromResource;
    dlg.m_filename = m_bmpFilename;
    
    if (dlg.DoModal () == IDOK)
    {
        BOOL bmpModified = FALSE;

        if (m_fromResource != dlg.m_internalBMP)
            bmpModified = TRUE;
        m_fromResource = dlg.m_internalBMP;
        
        if (!dlg.m_internalBMP)
        {
            if (m_b != dlg.m_blueval)
                bmpModified = TRUE;
            m_b = dlg.m_blueval;

            if (m_r != dlg.m_redval)
                bmpModified = TRUE;
            m_r = dlg.m_redval;

            if (m_g != dlg.m_greenval)
                bmpModified = TRUE;
            m_g = dlg.m_greenval;
        }

        if (dlg.m_filename != m_bmpFilename)
        {
            bmpModified = TRUE;
            m_bmpFilename = dlg.m_filename;
        }

        if (bmpModified)
        {
            if (m_floatOn)
            { 
                m_transer.ShowWindow (FALSE);
            }
            m_transer.DestroyWindow ();

            LoadFloater ();

            if (m_floatOn)
            { 
                m_transer.ShowWindow (TRUE);
            }    
        }
        WriteIniData();
    }
}

void CQuoterDlg::LoadFloater()
{
    
    m_transer.m_fromResource = m_fromResource;

    if (!m_fromResource)
    {
        if (LoadBMPImage (m_bmpFilename, m_transer.m_bmp, NULL))
        {
            m_transer.SetRGB (m_r, m_g, m_b);
            m_transer.m_fromResource = FALSE;
        }
        else
            m_fromResource = TRUE;
    }

    if (m_fromResource)
    {
        m_transer.m_fromResource = TRUE;
        m_transer.SetBitmap (IDB_FLOATER3, IDB_FLOATER3);
        m_transer.SetRGB (255, 0, 255);
    }
    m_transer.Create (IDD_TRANS);
    m_transer.m_quoter = (CWnd*) this;
}

void CQuoterDlg::OnOptionsRandomgen() 
{
    
    CRandom dlg;

    dlg.DoModal();
}
