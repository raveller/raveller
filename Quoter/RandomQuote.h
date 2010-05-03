// RandomQuote.h: interface for the RandomQuote class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANDOMQUOTE_H__E93EA900_DBBF_11D2_9ACB_002018550C46__INCLUDED_)
#define AFX_RANDOMQUOTE_H__E93EA900_DBBF_11D2_9ACB_002018550C46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class RandomQuote  
{
public:
	int Index();
	BOOL IsLast();
	BOOL IsFirst();
	void ClearQuotes ();
	char* Last();
	char* First();
	int Count ();
	char* At (int index);
	char* Previous();
	char* Next();
	int m_index;
	char* Random ();
	RandomQuote(LPCTSTR filename, LPCTSTR separator);
	virtual ~RandomQuote();

private:
	void ReadFile (LPCTSTR filename, LPCTSTR separator);

 	CList<char*,char*> m_quotes;
};

#endif // !defined(AFX_RANDOMQUOTE_H__E93EA900_DBBF_11D2_9ACB_002018550C46__INCLUDED_)
