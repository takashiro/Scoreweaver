//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 2003  Microsoft Corporation.  All rights reserved.
//
//  Globals.h
//
//          Global variable declarations.
//
//////////////////////////////////////////////////////////////////////

#ifndef GLOBALS_H
#define GLOBALS_H

#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <assert.h>
#include "msctf.h"

void DllAddRef();
void DllRelease();

#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))
#endif

#define TEXTSERVICE_LANGID    MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED)

#define TEXTSERVICE_DESC    L"古琴谱输入法"
#define TEXTSERVICE_DESC_A   "古琴谱输入法"
#define TEXTSERVICE_MODEL   TEXT("Apartment")

#define TEXTSERVICE_ICON_INDEX  0
#define LANGBAR_ITEM_DESC   L"古琴谱输入法"

enum InputMode{	//输入模式
	Zheng,		//正字
	Pang,		//旁字
	Zhu			//旁注
};

//+---------------------------------------------------------------------------
//
// SafeStringCopy
//
// Copies a string from one buffer to another.  wcsncpy does not always
// null-terminate the destination buffer; this function does.
//----------------------------------------------------------------------------

inline void SafeStringCopy(WCHAR *pchDst, ULONG cchMax, const WCHAR *pchSrc, ULONG dstLen = 0)
{
    if (cchMax > 0)
    {
		#if _MSC_VER <= 1200  // VC7.0以下的版本
			wcsncpy(pchDst, pchSrc, cchMax);
		#else
			wcsncpy_s(pchDst, dstLen, pchSrc, cchMax);
		#endif
        pchDst[cchMax-1] = '\0';
    }
}

extern HINSTANCE g_hInst;

extern LONG g_cRefDll;

extern CRITICAL_SECTION g_cs;

extern const CLSID c_clsidTextService;

extern const GUID c_guidProfile;

extern const GUID c_guidLangBar_ModeSwitch;
extern const GUID c_guidLangBar_Tool;

extern const GUID c_guidDisplayAttributeInput;
extern const GUID c_guidDisplayAttributeConverted;

#endif // GLOBALS_H
