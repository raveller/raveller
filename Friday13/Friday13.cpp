// Friday13.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdio.h"
#include "Friday13.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		CTime bTime, f13Time, f30Time, f39Time;
		int cnt = 0;
		printf ("year mo d mod 13 30 39\n----------------------\n");
		for (int yr = 1970; yr < 1999; yr++)
		{
			for (int mo = 1; mo < 13; mo++)
			{
				char f13 = ' ', f30 = ' ', f39 = ' ';

				bTime   = CTime( yr, mo, 13, 6, 00, 00);
				f13Time = CTime( yr+13, mo, 13, 6, 00, 00);
				f30Time = CTime( yr+30, mo, 13, 6, 00, 00);
				f39Time = CTime( yr+39, mo, 13, 6, 00, 00);

				if (f13Time.GetDayOfWeek () == 6)
					f13 = 'X';
				if (f30Time.GetDayOfWeek () == 6)
					f30 = 'X';
				if (f39Time.GetDayOfWeek () == 6)
					f39 = 'X';
				if (f13 == 'X')
				{
					cnt++;

					printf ("%04d %02d %d   %d  %c  %c  %c   %08d\n", yr, mo,
					        bTime.GetDayOfWeek (), yr % 4, f13, f30, f39, cnt);
				}

			}
		}
		float perc = (float) cnt / (float) (365.25*29);
		if (cnt > 0)
		printf ("prob ~= %f or 1 in %f\n", perc, 1/perc);
	}

	return nRetCode;
}


