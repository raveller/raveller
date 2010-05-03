// TransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Quoter.h"
#include "QuoteUtils.h"
#include "TransDlg.h"
#include "QuoterDlg.h"
//#include "afxpriv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// LoadBMP		- Loads a BMP file and creates a logical palette for it.
// Returns		- TRUE for success
// sBMPFile		- Full path of the BMP file
// phDIB		- Pointer to a HGLOBAL variable to hold the loaded bitmap
//			  Memory is allocated by this function but should be 
//			  released by the caller.
// pPal			- Will hold the logical palette
BOOL LoadBMP( LPCTSTR sBMPFile, HGLOBAL *phDIB, CPalette *pPal )
{
    CFile file;
    if( !file.Open( sBMPFile, CFile::modeRead) )
        return FALSE;

    BITMAPFILEHEADER bmfHeader;
    ULONGLONG nFileLen;

    nFileLen = file.GetLength();

    // Read file header
    if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
        return FALSE;

    // File type should be 'BM'
    if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
        return FALSE;

    HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, (SIZE_T) nFileLen);
    if (hDIB == 0)
        return FALSE;

    // Read the remainder of the bitmap file.
    if (file.Read((LPSTR)hDIB, (UINT) nFileLen - sizeof(BITMAPFILEHEADER)) !=
        nFileLen - sizeof(BITMAPFILEHEADER) )
    {
        ::GlobalFree(hDIB);
        return FALSE;
    }

    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;

    int nColors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 
                        1 << bmInfo.bmiHeader.biBitCount;

    // Create the palette
    if( nColors <= 256 )
    {
        UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
        LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

        pLP->palVersion = 0x300;
        pLP->palNumEntries = nColors;

        for( int i=0; i < nColors; i++)
        {
            pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
            pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
            pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
            pLP->palPalEntry[i].peFlags = 0;
        }

        pPal->CreatePalette( pLP );

        delete[] pLP;
    }
    else
        return FALSE;

    *phDIB = hDIB;
    return TRUE;
}


void DrawDIB( CDC* pDC, HGLOBAL hDIB, CPalette *pPal )
{
    LPVOID	lpDIBBits;		// Pointer to DIB bits
    BOOL	bSuccess=FALSE; 	// Success/fail flag

    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;
    int nColors = bmInfo.bmiHeader.biClrUsed ? bmInfo.bmiHeader.biClrUsed : 
    1 << bmInfo.bmiHeader.biBitCount;

    if( bmInfo.bmiHeader.biBitCount > 8 )
        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors +
                    bmInfo.bmiHeader.biClrUsed) +
                    ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

    if( pPal && (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE) )
    {
        pDC->SelectPalette(pPal, FALSE);
        pDC->RealizePalette();
    }

    ::SetDIBitsToDevice(pDC->m_hDC, 				// hDC
                        0,					// DestX
                        0,					// DestY
                        bmInfo.bmiHeader.biWidth,		// nDestWidth
                        bmInfo.bmiHeader.biHeight,		// nDestHeight
                        0,					// SrcX
                        0,					// SrcY
                        0,					// nStartScan
                        bmInfo.bmiHeader.biHeight,		// nNumScans
                        lpDIBBits,				// lpBits
                        (LPBITMAPINFO)hDIB,			// lpBitsInfo
                        DIB_RGB_COLORS); 			// wUsage
}


CTransDlg::CTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTransDlg::IDD, pParent)
{
    m_r = 0;
    m_g = 0;
    m_b = 0;
    m_width  = 200;
    m_height = 200;
    m_bmpID  = 0;
    m_maskID = 0;
    m_fromResource = TRUE;

	//{{AFX_DATA_INIT(CTransDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTransDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTransDlg, CDialog)
	//{{AFX_MSG_MAP(CTransDlg)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_FLOATER_CLOSE, OnFloatClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CTransDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CDialog::OnLButtonDown(nFlags, point);
    PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

void CTransDlg::SetupRegion()
{
    CDC*        pDC        = GetWindowDC();
    CDC					memDC;
    CBitmap			cBitmap;
    CBitmap*		pOldMemBmp = NULL;
    COLORREF		col;
    CRect				cRect;
    int					x, y;
    CRgn				wndRgn, rgnTemp;
    int         top, bottom;
    int         height, width;
    BOOL        tempOn = FALSE;
    COLORREF maskcolor = m_r + 256*(m_g + 256*m_b);
    COLORREF    lastcol;

    GetWindowRect(&cRect);

    memDC.CreateCompatibleDC(pDC);

    if (m_fromResource)
    {
        cBitmap.LoadBitmap(m_maskID);
        pOldMemBmp = memDC.SelectObject(&cBitmap);
    }
    else
    {
        pOldMemBmp = memDC.SelectObject(&m_bmp);
    }

    height = cRect.Height(); width = cRect.Width();
    wndRgn.CreateRectRgn(0, 0, width, height);


    if (maskcolor)
        lastcol = 0;
    else
        lastcol = 1;

    for(x=0; x<=width; x++)
    {
        for(y=0; y<=height; y++)
        {
            col = memDC.GetPixel(x, y);

            if ((lastcol != maskcolor) && (col == maskcolor))
                top = y;

            if (col != maskcolor)
                BOOL bob = TRUE;

            if (((lastcol == maskcolor) && (col != maskcolor)) ||
                ((y  == height) && (col == maskcolor)))
            {
                if (col == maskcolor)
                    bottom = y + 1;
                else
                    bottom = y;

                if (!tempOn)
                {
                    rgnTemp.CreateRectRgn(x, top, x+1, bottom);
                    tempOn = TRUE;
                }
                else
                    rgnTemp.SetRectRgn (x, top, x+1, bottom);
                wndRgn.CombineRgn(&wndRgn, &rgnTemp, RGN_XOR);
            }
            lastcol = col;
        }
        lastcol = 1;
    }
    if (tempOn)
        rgnTemp.DeleteObject();

	if (pOldMemBmp)
        memDC.SelectObject(pOldMemBmp);
	SetWindowRgn((HRGN)wndRgn, TRUE);
}

void CTransDlg::OnPaint() 
{
    CDialog::OnPaint();
}

BOOL CTransDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();

    InitSize();

    // Size the Dialog and move it to the center of its parent
    MoveWindow(0, 0, m_width, m_height, FALSE);

    SetupRegion();

    CenterWindow (GetParent());

    m_popup.LoadMenu (IDR_FLOATER_POPUP);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}


void CTransDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
    CPoint lpt = point;
    ClientToScreen(&lpt);
    CMenu* popup = m_popup.GetSubMenu(0);

    // display the popup menu
    popup->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON, lpt.x, lpt.y,
                          (CWnd*) this, NULL);

    // BUGFIX: See "PRB: Menus for Notification Icons Don't Work Correctly"
    GetParent()->PostMessage(WM_NULL, 0, 0);

    CDialog::OnRButtonDown(nFlags, point);
}

void CTransDlg::InitSize()
{
    BITMAP   bmpData;

    if (m_fromResource)
    {
        HBITMAP hbitmap;
        hbitmap = QuikBitmap (m_bmpID);
        CBitmap* pBmpCurrent;

        pBmpCurrent = CBitmap::FromHandle (hbitmap);

        if (pBmpCurrent)
        {
            pBmpCurrent->GetObject(sizeof(BITMAP), (LPVOID) &bmpData);
            m_height = bmpData.bmHeight;
            m_width  = bmpData.bmWidth;

            pBmpCurrent->DeleteObject();
            // Delete the allocated bitmap
            if (hbitmap)
            ::DeleteObject (hbitmap);
        }
    }
    else
    {
        m_bmp.GetObject(sizeof(BITMAP), (LPVOID) &bmpData);
        m_height = bmpData.bmHeight;
        m_width  = bmpData.bmWidth;
    }
}

void CTransDlg::SetBitmap(UINT bmpID, UINT mask)
{
    m_bmpID = bmpID;
    m_maskID = mask;
}

void CTransDlg::SetRGB (int r, int g, int b)
{
    m_r = r;
    m_g = g;
    m_b = b;
}

BOOL CTransDlg::DestroyWindow() 
{
    m_popup.DestroyMenu ();

    return CDialog::DestroyWindow();
}

BOOL CTransDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect	rect;
	GetWindowRect(&rect);

	CDC memDC;
	CBitmap			cBitmap;
	CBitmap*		pOldMemBmp = NULL;
    CBitmap*        pNullBmp = NULL;

    memDC.CreateCompatibleDC(pDC);
    if (m_fromResource)
    {
	    cBitmap.LoadBitmap(m_bmpID);
	    pOldMemBmp = memDC.SelectObject(&cBitmap);
    }
    else
    {
	    pOldMemBmp = memDC.SelectObject(&m_bmp);
    }
    pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	if (pOldMemBmp) memDC.SelectObject( pOldMemBmp );

	return TRUE;
}

BOOL LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal )
{
    CFile file;
    if( !file.Open( sBMPFile, CFile::modeRead) )
        return FALSE;

    BITMAPFILEHEADER bmfHeader;

    // Read file header
    if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
        return FALSE;

    // File type should be 'BM'
    if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
        return FALSE;

    // Get length of the remainder of the file and allocate memory
    ULONGLONG nPackedDIBLen = file.GetLength() - sizeof(BITMAPFILEHEADER);
    HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, (SIZE_T) nPackedDIBLen);
    if (hDIB == 0)
        return FALSE;

    // Read the remainder of the bitmap file.
    if (file.Read((LPSTR)hDIB, (UINT) nPackedDIBLen) != nPackedDIBLen )
    {
        ::GlobalFree(hDIB);
        return FALSE;
    }


    BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB ;
    BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;

    // If bmiHeader.biClrUsed is zero we have to infer the number
    // of colors from the number of bits used to specify it.
    int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 
    			    1 << bmiHeader.biBitCount;

    LPVOID lpDIBBits;
    if( bmInfo.bmiHeader.biBitCount > 8 )
        lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
                    ((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
    else
        lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

    // Create the logical palette
    if( pPal != NULL )
    {
        // Create the palette
        if( nColors <= 256 )
        {
            UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
            LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

            pLP->palVersion = 0x300;
            pLP->palNumEntries = nColors;

            for( int i=0; i < nColors; i++)
            {
	            pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
	            pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
	            pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
	            pLP->palPalEntry[i].peFlags = 0;
            }

            pPal->CreatePalette( pLP );

            delete[] pLP;
        }
    }

    CClientDC dc(NULL);
    CPalette* pOldPalette = NULL;
    if( pPal )
    {
        pOldPalette = dc.SelectPalette( pPal, FALSE );
        dc.RealizePalette();
    }

    HBITMAP hBmp = CreateDIBitmap(dc.m_hDC,		// handle to device context 
                                  &bmiHeader,	// pointer to bitmap size and format data 
                                  CBM_INIT,	// initialization flag 
                                  lpDIBBits,	// pointer to initialization data 
                                  &bmInfo,	// pointer to bitmap color-format data 
                                  DIB_RGB_COLORS);		// color-data usage 

    if (bitmap.m_hObject)
    {
        HBITMAP delBMP = (HBITMAP) bitmap.Detach ();
        ::DeleteObject (delBMP);
    }

    bitmap.Attach( hBmp );

    if( pOldPalette )
        dc.SelectPalette( pOldPalette, FALSE );

    ::GlobalFree(hDIB);
    return TRUE;
}


void CTransDlg::OnFloatClose()
{
    ((CQuoterDlg*) m_quoter)->m_floatOn = FALSE;
    this->ShowWindow (FALSE);
}
