// EditQuote.cpp : implementation file
//

#include "stdafx.h"
#include "Quoter.h"
#include "EditQuote.h"
#include "OutputFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditQuote dialog


CEditQuote::CEditQuote(CWnd* pParent /*=NULL*/)
	: CDialog(CEditQuote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditQuote)
	m_display = 0;
	m_timerval = 5;
	m_separator = _T("");
	m_defaultfile = _T("");
	//}}AFX_DATA_INIT

}

void CEditQuote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditQuote)
	DDX_Radio(pDX, IDC_TRAY, m_display);
	DDX_CBIndex(pDX, IDC_TIMERCOMBO, m_timerval);
	DDX_Text(pDX, IDC_SEPARATOR, m_separator);
	DDX_Text(pDX, IDC_QUOTEFILE, m_defaultfile);
	DDX_Control(pDX, IDC_TARGET_LIST, m_targetList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditQuote, CDialog)
	//{{AFX_MSG_MAP(CEditQuote)
	ON_BN_CLICKED(IDC_BROWSEQUOTE, OnBrowseQuote)
	ON_BN_CLICKED(IDC_ADDOUTPUT, OnAddOutput)
	ON_BN_CLICKED(IDC_SETCURRENT, OnSetCurrent)
	ON_EN_CHANGE(IDC_SEPARATOR, OnChangeSeparator)
	ON_BN_CLICKED(IDC_REMOVEOUTPUT, OnRemoveOutput)
	ON_BN_CLICKED(IDC_EDITOUTPUT, OnEditOutput)
	ON_LBN_SELCHANGE(IDC_TARGET_LIST, OnTargetListChange)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CEditQuote::~CEditQuote()
{
    POSITION pos = m_afterList.GetHeadPosition ();

    while (pos)
    {
        targetInfo* info = m_afterList.GetNext (pos);
        delete info;
    }

    m_afterList.RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////
// CEditQuote message handlers
void CEditQuote::OnBrowseQuote() 
{
  CString szFilter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
  CFileDialog* dlg = new CFileDialog (TRUE, "txt", (LPCTSTR) m_defaultfile,
                                      OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                                      szFilter, (CWnd*) this);

  //dlg->m_ofn.lpstrInitialDir = pinitialDir;

  if (dlg->DoModal() == IDOK) {
    m_defaultfile = dlg->GetPathName();
    UpdateData (FALSE);
    }
  }

void CEditQuote::OnSetCurrent() 
{
  m_defaultfile = m_currentfile;
  UpdateData (FALSE);
  }

void CEditQuote::OnChangeSeparator() 
{
  UpdateData (TRUE);
  CString temp = m_separator;
  temp.TrimLeft(); temp.TrimRight();
  GetDlgItem (IDOK)->EnableWindow (!temp.IsEmpty());
  }

void CEditQuote::OnAddOutput() 
{
    COutputFileDlg dlg;

    if (dlg.DoModal () == IDOK)
    {
        int pos = m_targetList.FindStringExact (0, dlg.m_displayname);

        if (pos >= 0)
        {
            AfxMessageBox ("Specified Display Name already exists in list.");
        }
        else
        {
            targetInfo* info = new targetInfo;

            strcpy_s (info->displayname, dlg.m_displayname);
            strcpy_s (info->footerfile,  dlg.m_footerfile);
            strcpy_s (info->headerfile,  dlg.m_headerfile);
            strcpy_s (info->targetfile,  dlg.m_targetfile);
            strcpy_s (info->eoltag,      dlg.m_eoltag);

            pos = m_targetList.AddString (dlg.m_displayname);
            m_targetList.SetItemDataPtr (pos, (void*) info);
        }
    }

    EnableButtons ();
}

void CEditQuote::OnRemoveOutput() 
{
	int pos = m_targetList.GetCurSel ();

    if (pos != LB_ERR)
    {
        targetInfo* info = (targetInfo*) m_targetList.GetItemDataPtr (pos);

        delete info;

        m_targetList.DeleteString (pos);
    }

    EnableButtons ();
}

void CEditQuote::OnEditOutput() 
{
	int pos = m_targetList.GetCurSel ();

    if (pos != LB_ERR)
    {
        targetInfo* info = (targetInfo*) m_targetList.GetItemDataPtr (pos);

        COutputFileDlg dlg;

        dlg.m_displayname = info->displayname;
        dlg.m_footerfile  = info->footerfile;
        dlg.m_headerfile  = info->headerfile;
        dlg.m_targetfile  = info->targetfile;
        dlg.m_eoltag = info->eoltag;

        if (dlg.DoModal () == IDOK)
        {
            int pos2 = m_targetList.FindStringExact (0, dlg.m_displayname);

            if ((pos2 != pos) && (pos2 != LB_ERR))
            {
                AfxMessageBox ("Duplicate Display Names on Edit are not allowed.");
            }
            else
            {
                m_targetList.DeleteString (pos);

                strcpy_s (info->displayname, dlg.m_displayname);
                strcpy_s (info->footerfile,  dlg.m_footerfile);
                strcpy_s (info->headerfile,  dlg.m_headerfile);
                strcpy_s (info->targetfile,  dlg.m_targetfile);
                strcpy_s (info->eoltag,  dlg.m_eoltag);

                int pos = m_targetList.AddString (dlg.m_displayname);
                m_targetList.SetItemDataPtr (pos, (void*) info);
            }
        }
    }
    EnableButtons ();
}

void CEditQuote::OnTargetListChange() 
{
    EnableButtons ();
}

void CEditQuote::EnableButtons ()
{
	int pos = m_targetList.GetCurSel ();

    if (pos == LB_ERR)
    {
        ((CWnd*) GetDlgItem (IDC_REMOVEOUTPUT))->EnableWindow (FALSE);
        ((CWnd*) GetDlgItem (IDC_EDITOUTPUT))->EnableWindow (FALSE);
    }
    else
    {
        ((CWnd*) GetDlgItem (IDC_REMOVEOUTPUT))->EnableWindow (TRUE);
        ((CWnd*) GetDlgItem (IDC_EDITOUTPUT))->EnableWindow (TRUE);
    }
}

BOOL CEditQuote::OnInitDialog() 
{
	CDialog::OnInitDialog();

    if (m_quoteDlg->m_targetList.GetCount ())
    {
        POSITION pos = m_quoteDlg->m_targetList.GetHeadPosition();
        targetInfo* dlgInfo = NULL;

        while (pos)
        {
            dlgInfo = m_quoteDlg->m_targetList.GetNext (pos);

            targetInfo* info = new targetInfo;

            strcpy_s (info->displayname, dlgInfo->displayname);
            strcpy_s (info->footerfile,  dlgInfo->footerfile);
            strcpy_s (info->headerfile,  dlgInfo->headerfile);
            strcpy_s (info->targetfile,  dlgInfo->targetfile);
            strcpy_s (info->eoltag,  dlgInfo->eoltag);

            int item = m_targetList.AddString (dlgInfo->displayname);
            m_targetList.SetItemDataPtr (item, (void*) info);
        }
    }

	EnableButtons ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditQuote::OnDestroy() 
{
    for (int i = 0; i < m_targetList.GetCount (); i++)
    {
        targetInfo* info = (targetInfo*) m_targetList.GetItemDataPtr (i);
    
        m_afterList.AddTail (info);
    }

	CDialog::OnDestroy();
}

/////////////////////////////////////////////////////////////////////////////
// CFloaterOptions dialog


CFloaterOptions::CFloaterOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CFloaterOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFloaterOptions)
	m_greenval = 0;
	m_blueval = 0;
	m_redval = 0;
	m_internalBMP = TRUE;
	m_filename = _T("");
	//}}AFX_DATA_INIT
}


void CFloaterOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFloaterOptions)
	DDX_Control(pDX, IDC_RED_SLIDER, m_redSlider);
	DDX_Control(pDX, IDC_BLUE_SLIDER, m_blueSlider);
	DDX_Control(pDX, IDC_GREEN_SLIDER, m_greenSlider);
	DDX_Text(pDX, IDC_GREENBOX, m_greenval);
	DDV_MinMaxInt(pDX, m_greenval, 0, 255);
	DDX_Text(pDX, IDC_BLUEBOX, m_blueval);
	DDV_MinMaxInt(pDX, m_blueval, 0, 255);
	DDX_Text(pDX, IDC_REDBOX, m_redval);
	DDV_MinMaxInt(pDX, m_redval, 0, 255);
	DDX_Check(pDX, IDC_INTERNALBMP, m_internalBMP);
	DDX_Text(pDX, IDC_FLOATFILE, m_filename);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFloaterOptions, CDialog)
	//{{AFX_MSG_MAP(CFloaterOptions)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_RED_SLIDER, OnReleaseRed)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_GREEN_SLIDER, OnReleaseGreen)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_BLUE_SLIDER, OnReleaseBlue)
	ON_EN_CHANGE(IDC_REDBOX, OnEditRed)
	ON_EN_CHANGE(IDC_GREENBOX, OnEditGreen)
	ON_EN_CHANGE(IDC_BLUEBOX, OnEditBlue)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_INTERNALBMP, OnInternal)
	ON_BN_CLICKED(IDC_BROWSEFLOAT, OnBrowseBitmap)
	ON_EN_CHANGE(IDC_FLOATFILE, OnChangeFilename)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CFloaterOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    m_redSlider.SetRange (0, 255);
    m_greenSlider.SetRange (0, 255);
    m_blueSlider.SetRange (0, 255);

    m_redSlider.SetPos (m_redval);
    m_greenSlider.SetPos (m_greenval);
    m_blueSlider.SetPos (m_blueval);

    if (!m_internalBMP)
    {
        if (!LoadBMPImage (m_filename, m_bmp, NULL))
            m_internalBMP = TRUE;
    }

    EnableWidgets();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFloaterOptions::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (nIDCtl == IDC_DRAWBITMAP)
    {
    	CDC *pDC;
        pDC = CDC::FromHandle (lpDrawItemStruct->hDC);
    	CRect	rect;
        CWnd* pCtl = CWnd::FromHandle(lpDrawItemStruct->hwndItem);

        pCtl->GetWindowRect (&rect);

        CDC memDC;
        BITMAP   bmpData;
	    CBitmap*		pOldMemBmp = NULL;
	    memDC.CreateCompatibleDC(pDC);
    
        if (m_internalBMP)
        {
	        CBitmap			cBitmap;
    	    cBitmap.LoadBitmap(IDB_FLOATER3);

            pOldMemBmp = memDC.SelectObject(&cBitmap);
		    cBitmap.GetObject(sizeof(BITMAP), (LPVOID) &bmpData);
        }
        else
        {
            pOldMemBmp = memDC.SelectObject(&m_bmp);
		    m_bmp.GetObject(sizeof(BITMAP), (LPVOID) &bmpData);
        }
        int bHeight = bmpData.bmHeight;
        int bWidth  = bmpData.bmWidth;

        float hRat = ((float) rect.Height()) / ((float) bHeight);
        float wRat = ((float) rect.Width())  / ((float) bWidth);
        int x = 0, y = 0;
        int height = 0, width = 0;
        if (hRat > wRat)
        {
            width = rect.Width ();
            height = (int)(wRat * (float) rect.Height());
            y = (rect.Height() - height)/2;
        }
        else
        {
            height = rect.Height ();
            width = (int)(hRat * (float) rect.Width());
            x = (rect.Width() - width)/2;
        }

	    pDC->StretchBlt (x, y, width, height, &memDC, 0, 0, bWidth, bHeight, SRCCOPY);
        pDC->Draw3dRect (x, y, width, height, 0x00FF0000, 0x00FFFFF00); 

        if (pOldMemBmp) memDC.SelectObject( pOldMemBmp );
    }
    else
        CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CFloaterOptions::OnReleaseRed(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_redval = m_redSlider.GetPos ();

    UpdateData (FALSE);
	
	*pResult = 0;
}

void CFloaterOptions::OnReleaseGreen(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_greenval = m_greenSlider.GetPos ();

    UpdateData (FALSE);
	
	*pResult = 0;
}

void CFloaterOptions::OnReleaseBlue(NMHDR* pNMHDR, LRESULT* pResult) 
{
    m_blueval = m_blueSlider.GetPos ();

    UpdateData (FALSE);
	
	*pResult = 0;
}

void CFloaterOptions::OnEditRed() 
{
    UpdateData ();

    m_redSlider.SetPos (m_redval);
}

void CFloaterOptions::OnEditGreen() 
{
    UpdateData ();

    m_greenSlider.SetPos (m_greenval);
}

void CFloaterOptions::OnEditBlue() 
{
    UpdateData ();

    m_blueSlider.SetPos (m_blueval);
}

/////////////////////////////////////////////////////////////////////////////
// CFloaterOptions message handlers

void CFloaterOptions::OnInternal() 
{
    UpdateData ();

    EnableWidgets();
}

void CFloaterOptions::EnableWidgets()
{
    ((CWnd*) GetDlgItem (IDC_BLUE_SLIDER))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_RED_SLIDER))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_GREEN_SLIDER))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_BLUEBOX))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_REDBOX))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_GREENBOX))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_BROWSEFLOAT))->EnableWindow (!m_internalBMP);
    ((CWnd*) GetDlgItem (IDC_FLOATFILE))->EnableWindow (!m_internalBMP);
}

void CFloaterOptions::OnBrowseBitmap() 
{
  CString szFilter = "Bitmap Files (*.bmp)|*.bmp|All Files (*.*)|*.*||";
  CFileDialog* dlg = new CFileDialog (TRUE, "bmp", (LPCTSTR) m_filename,
                                      OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
                                      szFilter, (CWnd*) this);

  if (dlg->DoModal() == IDOK) {
    
    m_filename = dlg->GetPathName();

    UpdateData (FALSE);

    ChangeBitmap ();
    }

  delete dlg;
}

void CFloaterOptions::OnChangeFilename() 
{
    UpdateData ();
    ChangeBitmap ();
}

void CFloaterOptions::ChangeBitmap()
{
    CFileStatus fStat;
    if (CFile::GetStatus ((LPCTSTR) m_filename, fStat))
    {
        CString reverse = m_filename;
        reverse.MakeReverse (); reverse.MakeUpper ();
        if (reverse.Find ("PMB.") == 0)
        {
            if (fStat.m_size <= 1000000)
            {
                if (LoadBMPImage (m_filename, m_bmp, NULL))
                {
                    ((CWnd*) GetDlgItem (IDC_DRAWBITMAP))->Invalidate ();
                }
                else
                {
                    AfxMessageBox ("Unable to load Bitmap");
                }
            }
            else
            {
                AfxMessageBox ("File exceeds 1 MB size limit.");
            }
        }
    }
}

CFloaterOptions::~CFloaterOptions()
{

}
