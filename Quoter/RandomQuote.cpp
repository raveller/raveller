// RandomQuote.cpp: implementation of the RandomQuote class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RandomQuote.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

RandomQuote::RandomQuote(LPCTSTR filename, LPCTSTR separator)
{
  CTime now = CTime::GetCurrentTime();
  long bigNum = ((long)now.GetSecond ()) + 60*(((long) now.GetMinute()) +
               60*(((long)now.GetHour()) + 24*(((long) now.GetDay()) - 1)));
  bigNum /= (((long) now.GetYear()) - 1900);
  srand (((unsigned int) bigNum));
  ReadFile (filename, separator);
}

RandomQuote::~RandomQuote()
{
  ClearQuotes();
  }

void RandomQuote::ReadFile(LPCTSTR filename, LPCTSTR separator)
{
	// Quote file pointer
	CFile* quoteFile  = NULL;
  char*  sep = NULL;
  int    sepLen = 0;

  // Allocate separator string
  {
    if (sepLen = strlen (separator)) {
      sep = new char [sepLen + 1];
      strcpy_s (sep, sepLen + 1, separator);
      sep [sepLen] = '\0';
      }
    }

  // Only attempt quote parsing with defined separator
  // (no defaults)
  if (sep) {
    // Open the given filename for reading
	  TRY   { quoteFile = new CFile (filename, CFile::modeRead); }
	  CATCH ( CFileException, e ) { quoteFile = NULL;}
	  END_CATCH
    }

	// Check for open testfile prior to read operations
	if (quoteFile) {
		// Determine the file length
    char* fileBuffer = NULL;
    ULONGLONG fileLength = 0;
  	TRY   {fileLength = quoteFile->GetLength();}
	  CATCH ( CFileException, e ) {fileLength = 0;}
	  END_CATCH
    
    // Read the entrie file
    if (fileLength > 0) {
      fileBuffer = new char [(int)fileLength];
      TRY {
        quoteFile->Read (fileBuffer, (UINT) fileLength);}
      CATCH (CFileException, e) {
        fileLength = 0;
        delete [] fileBuffer;
        fileBuffer = NULL;
        }
      END_CATCH
      }

    if (fileBuffer) {
      ClearQuotes();

      // Do the parsing voodoo that you do so well
      char* right = NULL;
      char* remainder = fileBuffer;
      char* splice = NULL;
      int iteration = 0;
      while (remainder) {
        iteration++;
        right = strstr (remainder, sep);

        if (right != NULL ) {
          int offset = right - remainder;

          if (offset > 0) {
            splice = new char [offset + 1];
            strncpy_s (splice, offset + 1, remainder, offset);
            splice[offset] = '\0';
            }
          remainder = right + sepLen;
          }
        else {
          int offset = fileBuffer + fileLength - remainder;
          if (offset) {
            splice = new char [offset + 1];
            strncpy_s (splice, offset + 1, remainder, offset);
            splice[offset] = '\0';
            }
          remainder = NULL;
          }
        if (splice) {
          int temp = iteration;
          m_quotes.AddTail (splice);
          splice = NULL;
          }
        }
      // Clear up the allocated memory
      delete [] fileBuffer;
      fileBuffer = NULL;
      }

    // Delete allocated separator string
    delete [] sep;
    sep = NULL;

    // Clear up the allocated file pointer.
    quoteFile->Close();
    delete quoteFile;
    quoteFile = NULL;
    }
  }

char* RandomQuote::Random()
{
  if (m_quotes.IsEmpty()) return NULL;

  int count =  Count();
  m_index = rand() % count;
  POSITION pos = m_quotes.FindIndex (m_index);
  return m_quotes.GetAt (pos);
  }

char* RandomQuote::Next()
{
  if (m_quotes.IsEmpty()) return NULL;

  m_index++;
  if (m_index >= 0 && m_index < Count()) {
    POSITION pos = m_quotes.FindIndex (m_index);
    return m_quotes.GetAt (pos);
    }
  else {
    m_index--;
    return NULL;
    }
  }

char* RandomQuote::Previous()
{
  if (m_quotes.IsEmpty()) return NULL;

  m_index--;
  if (m_index >= 0 && m_index < Count()) {
    POSITION pos = m_quotes.FindIndex (m_index);
    return m_quotes.GetAt (pos);
    }
  else {
    m_index++;
    return NULL;
    }
  }

char* RandomQuote::At(int index)
{
  if (m_quotes.IsEmpty()) return NULL;

  if (index >= 0 && index < Count()) {
    m_index = index;
    POSITION pos = m_quotes.FindIndex (m_index);
    return m_quotes.GetAt (pos);
    }
  else {
    return NULL;
    }
  }

int RandomQuote::Count()
{
  if (m_quotes.IsEmpty()) return 0;
  return m_quotes.GetCount();
  }

char* RandomQuote::First()
{
  if (m_quotes.IsEmpty()) return NULL;

  m_index = 0;
  return m_quotes.GetHead();
  }

char* RandomQuote::Last()
{
  if (m_quotes.IsEmpty()) return NULL;

  m_index = Count() - 1;
  return m_quotes.GetTail();
  }

void RandomQuote::ClearQuotes()
{
  if (!m_quotes.IsEmpty()) {
    int numQuotes = m_quotes.GetCount ();
    for (int i = numQuotes - 1; i >= 0; i--) {
      POSITION pos = m_quotes.FindIndex (i);
      char* freeMe = m_quotes.GetAt (pos);
      if (freeMe) {
        delete [] freeMe;
        freeMe = NULL;
        }
      }
    m_quotes.RemoveAll ();
    m_index = -1;
    }
  }

BOOL RandomQuote::IsFirst()
{
  return (m_index <= 0);
}

BOOL RandomQuote::IsLast()
{
  return (m_index >= (Count() - 1));
}

int RandomQuote::Index()
{
  return m_index;
  }
