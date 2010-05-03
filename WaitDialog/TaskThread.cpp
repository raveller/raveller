// TaskThread.cpp : implementation file
//

#include "stdafx.h"
#include "waitdialog.h"
#include "TaskThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTaskThread

IMPLEMENT_DYNCREATE(CTaskThread, CWinThread)

CTaskThread::CTaskThread()
{
}

CTaskThread::~CTaskThread()
{
}

BOOL CTaskThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CTaskThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CTaskThread, CWinThread)
	//{{AFX_MSG_MAP(CTaskThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTaskThread message handlers
