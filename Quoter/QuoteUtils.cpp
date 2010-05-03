#include "stdafx.h"
#include "QuoteUtils.h"

//
// This function creates a palette for a given CWnd
// Item.  The user is responsible for freeing the
// Palette memory.
CPalette* QuikPalette (WORD resource) {

  CPalette* newPal = new CPalette;

  CClientDC dc (AfxGetMainWnd ());
  if ((dc.GetDeviceCaps (RASTERCAPS) & RC_PALETTE) == 0) {
    if (newPal)
      delete newPal;
    return NULL;
    }

	// Get the paletter source bitmap
  HBITMAP hBitmap = QuikBitmap (resource);

  CBitmap mainBmp;
  mainBmp.Attach(hBitmap);
  DIBSECTION ds;
  mainBmp.GetObject(sizeof (DIBSECTION), &ds);
  
  int nColors;
  if (ds.dsBmih.biClrUsed != 0)
    nColors = ds.dsBmih.biClrUsed;
  else
    nColors = 1 << ds.dsBmih.biBitCount;
  if (nColors > 256)
    newPal->CreateHalftonePalette(&dc);
  else {
    RGBQUAD* pRGB = new RGBQUAD[nColors];

    CDC memDC;
    memDC.CreateCompatibleDC (&dc);
    CBitmap* pOldBitmap = memDC.SelectObject (&mainBmp);

    ::GetDIBColorTable((HDC) memDC, 0, nColors, pRGB);
    memDC.SelectObject (pOldBitmap);

    UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * (nColors - 1));
    LOGPALETTE* pLP = (LOGPALETTE*) new BYTE[nSize];

    pLP->palVersion = 0x300;
    pLP->palNumEntries = nColors;
	  for (short n = 0; n < nColors; n++) {
		  pLP->palPalEntry[n].peRed   = pRGB[n].rgbRed;
		  pLP->palPalEntry[n].peGreen = pRGB[n].rgbGreen;
		  pLP->palPalEntry[n].peBlue  = pRGB[n].rgbBlue;
		  pLP->palPalEntry[n].peFlags = (BYTE) 0;
	    }
    newPal->CreatePalette(pLP);

    delete [] pLP;
    delete [] pRGB;
    }
	mainBmp.DeleteObject();
	::DeleteObject(hBitmap);

  return newPal;
  }

HBITMAP QuikBitmap(WORD resource)
{
	return (HBITMAP) ::LoadImage (AfxGetInstanceHandle(),
																MAKEINTRESOURCE (resource),
																IMAGE_BITMAP,
																0,
																0,
																LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
}
