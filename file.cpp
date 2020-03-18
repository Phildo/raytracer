#include "file.h"
#ifdef _WIN32
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>

void DisplayError(LPTSTR lpszFunction);

int write_file(const char *filename, char *data, int len)
{
  HANDLE hFile;
  DWORD dwBytesToWrite = (DWORD)len;
  DWORD dwBytesWritten = 0;
  BOOL bErrorFlag = FALSE;

  hFile = CreateFile(filename, // name of the write
    GENERIC_WRITE,             // open for writing
    0,                         // do not share
    NULL,                      // default security
    CREATE_NEW,                // create new file only
    FILE_ATTRIBUTE_NORMAL,     // normal file
    NULL);                     // no attr. template

  if(hFile == INVALID_HANDLE_VALUE)
  {
    DisplayError(TEXT("CreateFile"));
    _tprintf(TEXT("Terminal failure: Unable to open file \"%s\" for write.\n"), filename);
    return 0;
  }

  _tprintf(TEXT("Writing %d bytes to %s.\n"), dwBytesToWrite, filename);

  bErrorFlag = WriteFile(
    hFile,           // open file handle
    data,            // start of data to write
    dwBytesToWrite,  // number of bytes to write
    &dwBytesWritten, // number of bytes that were written
    NULL);           // no overlapped structure

  if(FALSE == bErrorFlag)
  {
    DisplayError(TEXT("WriteFile"));
    printf("Terminal failure: Unable to write to file.\n");
    return 0;
  }
  else
  {
    if(dwBytesWritten != dwBytesToWrite)
    {
      // This is an error because a synchronous write that results in
      // success (WriteFile returns TRUE) should write all data as
      // requested. This would not necessarily be the case for
      // asynchronous writes.
      printf("Error: dwBytesWritten != dwBytesToWrite\n");
      return 0;
    }
    else
    {
      _tprintf(TEXT("Wrote %d bytes to %s successfully.\n"), dwBytesWritten, filename);
    }
  }

  CloseHandle(hFile);
  return 1;
}

void DisplayError(LPTSTR lpszFunction)
// Routine Description:
// Retrieve and output the system error message for the last-error code
{
  LPVOID lpMsgBuf;
  LPVOID lpDisplayBuf;
  DWORD dw = GetLastError();

  FormatMessage(
    FORMAT_MESSAGE_ALLOCATE_BUFFER |
    FORMAT_MESSAGE_FROM_SYSTEM |
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    dw,
    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
    (LPTSTR)&lpMsgBuf,
    0,
    NULL);

  lpDisplayBuf =
    (LPVOID)LocalAlloc(LMEM_ZEROINIT,
      (lstrlen((LPCTSTR)lpMsgBuf)
        + lstrlen((LPCTSTR)lpszFunction)
        + 40) // account for format string
      * sizeof(TCHAR));

  if(FAILED(StringCchPrintf((LPTSTR)lpDisplayBuf,
    LocalSize(lpDisplayBuf) / sizeof(TCHAR),
    TEXT("%s failed with error code %d as follows:\n%s"),
    lpszFunction,
    dw,
    lpMsgBuf)))
  {
    printf("FATAL ERROR: Unable to output error code.\n");
  }

  _tprintf(TEXT("ERROR: %s\n"), (LPCTSTR)lpDisplayBuf);

  LocalFree(lpMsgBuf);
  LocalFree(lpDisplayBuf);
}

#else //!_WIN32

#include <stdio.h>

int write_file(const char *filename, char *data, int len)
{
  FILE *fd;
  fd = fopen(filename,"w");
  size_t written = fwrite(data, sizeof(char), len, fd);
  if(written != len)
  {
    printf("Failed to write file %s\n",filename);
    return 1;
  }
  return 0;
}

#endif

