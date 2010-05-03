// WaitAction.cpp : implementation file
//

#include "stdafx.h"
#include "waitdialog.h"
#include "WaitAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cWaitAction

IMPLEMENT_DYNCREATE(cWaitAction, CWinThread)

cWaitAction::cWaitAction()
{
}

cWaitAction::~cWaitAction()
{
}

BOOL cWaitAction::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int cWaitAction::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(cWaitAction, CWinThread)
	//{{AFX_MSG_MAP(cWaitAction)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cWaitAction message handlers
