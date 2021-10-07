//****************************************************************************
//
// Copyright (c) ALTAP, spol. s r.o. All rights reserved.
//
// This is a part of the Altap Salamander SDK library.
//
// The SDK is provided "AS IS" and without warranty of any kind and 
// ALTAP EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS AND IMPLIED, INCLUDING,
// BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE and NON-INFRINGEMENT.
//
//****************************************************************************

#include "precomp.h"
//#include <windows.h>
//#include <commctrl.h>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif // _MSC_VER

// potlaceni warningu C4996: This function or variable may be unsafe. Consider using strcat_s instead.
// duvod: lstrcat a dalsi Windows rutiny prost nejsou safe, takze to nema smysl resit tady
#pragma warning(push)
#pragma warning(disable:4996)

#ifdef  __cplusplus
extern "C"
#endif
LPSTR _sal_lstrcpyA(LPSTR lpString1, LPCSTR lpString2)
{
  return strcpy(lpString1, lpString2);
}

#ifdef  __cplusplus
extern "C"
#endif
LPWSTR _sal_lstrcpyW(LPWSTR lpString1, LPCWSTR lpString2)
{
  return wcscpy(lpString1, lpString2);
}

#ifdef  __cplusplus
extern "C"
#endif
LPSTR _sal_lstrcpynA(LPSTR lpString1, LPCSTR lpString2, int iMaxLength)
{
  if (iMaxLength <= 0) return lpString1;
  LPSTR ret = lpString1;
  LPSTR end = lpString1 + iMaxLength - 1;
  while (lpString1 < end && *lpString2 != 0)
    *lpString1++ = *lpString2++;
  *lpString1 = 0;
  return ret;
}

#ifdef  __cplusplus
extern "C"
#endif
LPWSTR _sal_lstrcpynW(LPWSTR lpString1, LPCWSTR lpString2, int iMaxLength)
{
  if (iMaxLength <= 0) return lpString1;
  LPWSTR ret = lpString1;
  LPWSTR end = lpString1 + iMaxLength - 1;
  while (lpString1 < end && *lpString2 != 0)
    *lpString1++ = *lpString2++;
  *lpString1 = 0;
  return ret;
}

#ifdef  __cplusplus
extern "C"
#endif
int _sal_lstrlenA(LPCSTR lpString)
{
  if (lpString == NULL) return 0;
  return (int)strlen(lpString);
}

#ifdef  __cplusplus
extern "C"
#endif
int _sal_lstrlenW(LPCWSTR lpString)
{
  if (lpString == NULL) return 0;
  return (int)wcslen(lpString);
}

#ifdef  __cplusplus
extern "C"
#endif
LPSTR _sal_lstrcatA(LPSTR lpString1, LPCSTR lpString2)
{
  return strcat(lpString1, lpString2);
}

#ifdef  __cplusplus
extern "C"
#endif
LPWSTR _sal_lstrcatW(LPWSTR lpString1, LPCWSTR lpString2)
{
  return wcscat(lpString1, lpString2);
}

#pragma warning(pop)

#if defined(TRACE_ENABLE) && !defined(INSIDE_SALAMANDER)

#include <ostream>
#include <streambuf>

#if defined(_DEBUG) && defined(_MSC_VER)  // without passing file+line to 'new' operator, list of memory leaks shows only 'crtdbg.h(552)'
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include "spl_base.h"
#include "dbg.h"

#pragma warning (disable: 4074)
#pragma init_seg(compiler)

C__Trace __Trace;

// basic unicode support
std::ostream
&operator <<(std::ostream &out, const wchar_t *str)
{
  char buff[5000];
  // Convert the UNICODE string to ANSI
  WideCharToMultiByte(CP_ACP, 0, str, -1, buff, 5000, NULL, NULL);
  buff[5000 - 1] = 0;
  out << buff;
  return out;
}

//*****************************************************************************
//
// C__Trace
//

C__Trace::C__Trace() : TraceStrStream(&TraceStringBuf)
{
  InitializeCriticalSection(&CriticalSection);
}

C__Trace::~C__Trace()
{
  DeleteCriticalSection(&CriticalSection);
}

C__Trace &
C__Trace::SetInfo(const char *file, int line)
{
  File = file;
  Line = line;
  return *this;
}

struct C__TraceMsgBoxThreadData
{
  char *Msg;          // alokovany text hlasky
  const char *File;   // jen odkaz na staticky string
  int Line;
};

#ifdef __BORLANDC__
#define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))
#endif // __BORLANDC__

DWORD WINAPI __TraceMsgBoxThread(void *param)
{
  C__TraceMsgBoxThreadData *data = (C__TraceMsgBoxThreadData *)param;
  char msg[1000];
  wsprintf(msg, "TRACE_C message received!\n\n"
                "File: %s\n"
                "Line: %d\n\n"
                "Message: ", data->File, data->Line);
  const char *appendix = "\n\nTRACE_C message means that fatal error has occured. "
                         "Application will be crashed by \"access violation\" exception after "
                         "clicking OK. Please send us bug report to help us fix this problem. "
                         "If you want to copy this message to clipboard, use Ctrl+C key.";
  lstrcpyn(msg + (int)strlen(msg), data->Msg, _countof(msg) - (int)strlen(msg) - (int)strlen(appendix));
  lstrcpyn(msg + (int)strlen(msg), appendix, _countof(msg) - (int)strlen(msg));
  MessageBox(NULL, msg, "ALTAP Debug Message",
             MB_OK | MB_ICONERROR | MB_SETFOREGROUND);
  return 0;
}

void
C__Trace::SendMessageToServer(BOOL information, BOOL crash)
{
  TraceStrStream.flush();             // flushnuti do bufferu
  if (SalamanderDebug != NULL)
  {
    if (information) SalamanderDebug->TraceI(File, Line, TraceStringBuf.c_str());
    else SalamanderDebug->TraceE(File, Line, TraceStringBuf.c_str());
  }
  // jen je-li crash==TRUE:
  // vyrobime kopii dat, start threadu pro msgbox totiz muze vyvolat dalsi TRACE
  // hlasky (napr. v DllMain reakce na DLL_THREAD_ATTACH), pokud bysme neopustili
  // CriticalSection, nastal by deadlock;
  // v DllMain se nesmi pouzivat TRACE_C, jinak dojde k deadlocku:
  //   - pokud se da do DLL_THREAD_ATTACH: chce si otevrit novy thread pro msgbox
  //     a to je z DllMainu blokovane
  //   - pokud se da do DLL_THREAD_DETACH: pri cekani na zavreni threadu s msgboxem
  //     predesleho TRACE_C zachytime TRACE_C z DLL_THREAD_DETACH a nechame ho
  //     cekat v nekonecnem cyklu, viz nize
  // navic zavadime obranu proti mnozeni msgboxu pri vice TRACE_C zaroven, pusobilo
  // by to jen zmatky, ted se otevre msgbox jen pro prvni a ten po uzavreni vyvola
  // padacku, ostatni TRACE_C zustanou chyceny v nekonecne cekaji smycce, viz nize
  static BOOL msgBoxOpened = FALSE;
  C__TraceMsgBoxThreadData threadData;
  memset(&threadData, 0, sizeof(threadData));
  if (crash)  // break/padacka po vypisu TRACE error hlasky (TRACE_C a TRACE_MC)
  {
    if (!msgBoxOpened)
    {
      threadData.Msg = (char *)GlobalAlloc(GMEM_FIXED, TraceStringBuf.length() + 1);
      if (threadData.Msg != NULL)
      {
        lstrcpyn(threadData.Msg, TraceStringBuf.c_str(), (int)TraceStringBuf.length() + 1);
        threadData.File = File;
        threadData.Line = Line;
        msgBoxOpened = TRUE;
      }
    }
    else
    {
      threadData.Msg = NULL;
    }
  }
  TraceStringBuf.erase();  // priprava pro dalsi trace
  LeaveCriticalSection(&CriticalSection);
  if (crash)
  {
    if (threadData.Msg != NULL)  // break/padacka po vypisu TRACE error hlasky (TRACE_C a TRACE_MC)
    {
      // vypiseme hlasku v jinem threadu, aby nepumpovala zpravy aktualniho threadu
      DWORD id;
      HANDLE msgBoxThread = CreateThread(NULL, 0, __TraceMsgBoxThread, &threadData, 0, &id);
      if (msgBoxThread != NULL)
      {
        WaitForSingleObject(msgBoxThread, INFINITE);  // pokud se da TRACE_C do DllMain do DLL_THREAD_ATTACH, dojde k deadlocku - silne nepravdepodobne, neresime
        CloseHandle(msgBoxThread);
      }
      msgBoxOpened = FALSE;
      GlobalFree((HGLOBAL)threadData.Msg);
      // pad softu vyvolame primo v kodu, kde je umisteny TRACE_C/TRACE_MC, aby
      // bylo v bug reportu videt presne kde makra lezi; padacka tedy nasleduje
      // po dokonceni teto metody
    }
    else  // ostatni thready s TRACE_C zablokujeme, az se zavre msgbox otevreny pro
    {     // prvni TRACE_C, tak to tam i spadne, at v tom neni bordel
      if (msgBoxOpened)
      {
        while (1) Sleep(1000);  // blokace vede na deadlock napr. kdyz je (a nema byt) TRACE_C v DLL_THREAD_DETACH
      }
    }
  }
}

//*****************************************************************************

#ifdef _DEBUG
#undef memcpy
void *_sal_safe_memcpy(void *dest, const void *src, size_t count)
{
  if ((char *)dest + count > src && (char *)src + count > dest)
  {
    TRACE_C("_sal_safe_memcpy: source and destination of memcpy overlap!");
  }
  return memcpy(dest, src, count);
}
#endif // _DEBUG

#endif // defined(TRACE_ENABLE) && !defined(INSIDE_SALAMANDER)
