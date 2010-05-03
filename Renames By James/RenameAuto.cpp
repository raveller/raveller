// RenameAuto.cpp : implementation file
//

#include "stdafx.h"
#include "MoveMore.h"
#include "RenameAuto.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRenameAuto

IMPLEMENT_DYNAMIC(CRenameAuto, CPropertySheet)

CRenameAuto::CRenameAuto(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CRenameAuto::CRenameAuto(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{

}

CRenameAuto::~CRenameAuto()
{
}


BEGIN_MESSAGE_MAP(CRenameAuto, CPropertySheet)
	//{{AFX_MSG_MAP(CRenameAuto)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

