// MoveMoreDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MoveMore.h"
#include "MoveMoreDlg.h"
#include "RenameAuto.h"
#include "FolderDialog.h"


#include <stdio.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveMoreDlg dialog

CMoveMoreDlg::CMoveMoreDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMoveMoreDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMoveMoreDlg)
	m_fromext = _T("");
	m_fromfile = _T("");
	m_toext = _T("");
	m_tofile = _T("");
	m_dir = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMoveMoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMoveMoreDlg)
	DDX_Text(pDX, IDC_FROMEXT, m_fromext);
	DDX_Text(pDX, IDC_FROMFILE, m_fromfile);
	DDX_Text(pDX, IDC_TOEXT, m_toext);
	DDX_Text(pDX, IDC_TOFILE, m_tofile);
	DDX_Text(pDX, IDC_DIRNAME, m_dir);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMoveMoreDlg, CDialog)
	//{{AFX_MSG_MAP(CMoveMoreDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSEFILE, OnBrowsefile)
	ON_BN_CLICKED(IDC_DIRBROWSE, OnDirbrowse)
	ON_BN_CLICKED(IDC_DITTO2, OnDitto)
	ON_BN_CLICKED(IDC_RENAME, OnRename)
	ON_BN_CLICKED(IDC_SWAP, OnSwap)
	ON_BN_CLICKED(IDC_NUHHUH, OnNuhhuh)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMoveMoreDlg message handlers

BOOL CMoveMoreDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    // DECLARE: current path variable
    CString folderKey = "";

    // READ: keys names from the String Table
    folderKey.LoadString (IDS_PROFILE_DIR);
    char currPath [_MAX_PATH];
    DWORD pathlen = 0;

    // DETERMINE: Current Directory
    if (pathlen = GetCurrentDirectory (_MAX_PATH, currPath))
        currPath [pathlen] = '\0';

    // RETRIEVE: Local app name
    CWinApp* app = AfxGetApp();
    
    m_dir = app->GetProfileString (_T(""), (LPCTSTR) folderKey, _T(""));
    if (m_dir.IsEmpty())
        {
        m_dir = currPath;
        if (m_dir.ReverseFind ('\\') != (m_dir.GetLength () - 1))
            m_dir += '\\';
        app->WriteProfileString (_T(""), (LPCTSTR) folderKey, (LPCTSTR) m_dir);
        }

    // READ/READ: Keys name from String Table/Values from registry
    folderKey.LoadString (IDS_PROFILE_TONAME);
    m_tofile = app->GetProfileString (_T(""), (LPCTSTR) folderKey, "" );
    folderKey.LoadString (IDS_PROFILE_FROMNAME);
    m_fromfile = app->GetProfileString (_T(""), (LPCTSTR) folderKey, "" );
    folderKey.LoadString (IDS_PROFILE_TOEXT);
    m_toext = app->GetProfileString (_T(""), (LPCTSTR) folderKey, "");
    folderKey.LoadString (IDS_PROFILE_FROMEXT);
    m_fromext = app->GetProfileString (_T(""), (LPCTSTR) folderKey, _T(""));

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	UpdateData (FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMoveMoreDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMoveMoreDlg::OnPaint() 
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
HCURSOR CMoveMoreDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMoveMoreDlg::OnBrowsefile() 
{
    UpdateData (TRUE);
    CFileDialog fileDlg (TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR | OFN_READONLY | OFN_SHAREAWARE, "All Files (*.*)|*.*");

    // Free previous start up directory
    free((void*)fileDlg.m_ofn.lpstrInitialDir);

    //Change the name of the registry key.
    //The CWinApp destructor will free the memory.
    fileDlg.m_ofn.lpstrInitialDir =_tcsdup((LPCTSTR) m_dir);

    if (fileDlg.DoModal () == IDOK)
    {
        CString tempname = fileDlg.GetFileName ();
        m_fromext = "." + fileDlg.GetFileExt ();
        
        int namelen = tempname.GetLength () - m_fromext.GetLength ();
        m_fromfile = tempname.Left (namelen);
        UpdateData (FALSE);
    }
}

void CMoveMoreDlg::OnDirbrowse() 
{
	// DECLARE: The folder dialog.
	CFolderDialog foldDlg;

    foldDlg.SetPathName ((LPCTSTR) m_dir);

    if (foldDlg.DoModal() == IDOK)
    {
        m_dir = foldDlg.GetPathName ();
        if (m_dir.ReverseFind ('\\') != (m_dir.GetLength () - 1))
            m_dir += '\\';

        // DECLARE: current path variable
        CString folderKey = "";

        // READ: keys names from the String Table
        folderKey.LoadString (IDS_PROFILE_DIR);
        // RETRIEVE: Local app name
        CWinApp* app = AfxGetApp();
    
        app->WriteProfileString (_T(""), (LPCTSTR) folderKey, (LPCTSTR) m_dir);

        UpdateData (FALSE);
    }
}

void CMoveMoreDlg::OnDitto() 
{
    UpdateData (TRUE);

	// Copy Original Values down
	m_tofile = m_fromfile;
    m_toext  = m_fromext;

    // Feed the active dialog
    UpdateData (FALSE);
}

void CMoveMoreDlg::OnRename() 
{
    UpdateData (TRUE);

    WriteProfileForFileExt ();

    // DECLARE: Rename Wildcard variables, etc.
    CStringList *fromList = new CStringList ();;
    CStringList *toList = new CStringList ();
    CString headpath = m_dir + m_fromfile;
    CString wildpath = headpath + "*" + m_fromext;
    int headlen = headpath.GetLength();
    long hFile;
    struct _finddata_t wildfile;
    BOOL nofiles = TRUE;

    CString fromname = "";
    /*  */
    if( (hFile = _tfindfirst ((LPCTSTR) wildpath, &wildfile) ) != -1L )
    {
        if ((wildfile.attrib & _A_SUBDIR) == 0)
        {
            fromname.Format ("%s%s", (LPCTSTR) m_dir, wildfile.name);
            fromList->AddTail (fromname);
            nofiles = FALSE;
        }

        while ( (_tfindnext (hFile, &wildfile) ) == 0 )
        {
            if ((wildfile.attrib & _A_SUBDIR) == 0)
            {
                fromname.Format ("%s%s", (LPCTSTR) m_dir, wildfile.name);
                fromList->AddTail (fromname);
                nofiles = FALSE;
            }
        }
        
        _findclose (hFile);
    }

    if (nofiles) 
    {
        AfxMessageBox (IDS_NOFILES);
    }
    else
    {
        CString currFile = "";
        CString newFile  = "";
        CString tail  = "";
        CString toTailRev = m_toext;
        toTailRev.MakeReverse ();
        CString tailTemp = "";
        int fromExtLen = m_fromext.GetLength ();


        POSITION pos;
        pos = fromList->GetHeadPosition(); 
        while (pos)
        {
            currFile = fromList->GetAt (pos);

            tailTemp = currFile.Mid (headlen);
            tailTemp.MakeReverse ();
            tail = toTailRev + tailTemp.Mid (fromExtLen);
            tail.MakeReverse();

            newFile = m_dir + m_tofile + tail;
            toList->AddTail (newFile);

            fromList->GetNext( pos );
        }

        
        // DECLARE: Rename Property Sheet
        CRenameAuto moveWiz ("Multiple Rename");
	    CRenameConfirm  confirmPage;
	    CRenameComplete completePage;

        // SET: to and from lists
        confirmPage.SetLists (fromList, toList);
        completePage.SetLists (fromList, toList);

        moveWiz.m_psh.dwFlags &= ~PSH_HASHELP;
        confirmPage.m_psp.dwFlags &= ~PSP_HASHELP;
        completePage.m_psp.dwFlags &= ~PSP_HASHELP;

        // INIT: Add Property pages, set Wizard mode.
        moveWiz.AddPage (&confirmPage);
	    moveWiz.AddPage (&completePage);
        moveWiz.SetWizardMode();

        // LAUNCH: Multiple Rename Wizard
        moveWiz.DoModal ();

        delete fromList;
        delete toList;
    }
}

void CMoveMoreDlg::OnSwap() 
{
    UpdateData (TRUE);

    CString swap = "";

	// Copy Original Values down
    swap = m_fromfile;
	m_fromfile = m_tofile;
	m_tofile = swap;

    swap = m_fromext;
    m_fromext  = m_toext;
    m_toext = swap;

    // Feed the active dialog
    UpdateData (FALSE);		
}

void CMoveMoreDlg::OnNuhhuh() 
{
    UpdateData (TRUE);

	// Copy Original Values down
	m_fromfile = m_tofile;
    m_fromext  = m_toext;

    // Feed the active dialog
    UpdateData (FALSE);	
}

void CMoveMoreDlg::OnClear() 
{
    UpdateData (TRUE);

	// Copy Original Values down
	m_fromfile = _T("");
    m_tofile   = _T("");
    m_fromext  = _T("");
    m_toext    = _T("");

    WriteProfileForFileExt ();

    // Feed the active dialog
    UpdateData (FALSE);
}

void CMoveMoreDlg::WriteProfileForFileExt()
{
    // DECLARE: current path variable
    CString proKey = "";

    // RETRIEVE: Local app name
    CWinApp* app = AfxGetApp();


    // READ/WRITE: keys names from the String Table/string to registry
    proKey.LoadString (IDS_PROFILE_TONAME);
    app->WriteProfileString (_T(""), (LPCTSTR) proKey, (LPCTSTR) m_tofile);

    proKey.LoadString (IDS_PROFILE_FROMNAME);
    app->WriteProfileString (_T(""), (LPCTSTR) proKey, (LPCTSTR) m_fromfile);

    proKey.LoadString (IDS_PROFILE_TOEXT);
    app->WriteProfileString (_T(""), (LPCTSTR) proKey, (LPCTSTR) m_toext);

    proKey.LoadString (IDS_PROFILE_FROMEXT);
    app->WriteProfileString (_T(""), (LPCTSTR) proKey, (LPCTSTR) m_fromext);

}
