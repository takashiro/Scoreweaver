//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 2003  Microsoft Corporation.  All rights reserved.
//
//  Globals.cpp
//
//          Global variables
//
//////////////////////////////////////////////////////////////////////

#include "globals.h"

HINSTANCE g_hInst;

LONG g_cRefDll = -1; // -1 /w no refs, for win95 InterlockedIncrement/Decrement compat

CRITICAL_SECTION g_cs;

/* e7ea138e-69f8-11d7-a6ea-00065b84435c */
const CLSID c_clsidTextService = {
    0xe7ea138e,
    0x69f8,
    0x11d7,
    {0xa6, 0xea, 0x00, 0x06, 0x5b, 0x84, 0x43, 0x5c}
  };
/* e7ea138f-69f8-11d7-a6ea-00065b84435c */
const GUID c_guidProfile = { 0xe7ea138f, 0x69f8, 0x11d7, {0xa6, 0xea, 0x00, 0x06, 0x5b, 0x84, 0x43, 0x5c} };

// {1A76EA74-1300-43e5-8301-19601008CE43}
const GUID c_guidLangBar_Power = { 0x1a76ea74, 0x1300, 0x43e5, { 0x83, 0x1, 0x19, 0x60, 0x10, 0x8, 0xce, 0x43 } };


/* 41f46e67-86d5-49fb-a1d9-3dc0941a66a3 */
const GUID c_guidLangBar_ModeSwitch = { 0x41f46e67, 0x86d5, 0x49fb, {0xa1, 0xd9, 0x3d, 0xc0, 0x94, 0x1a, 0x66, 0xa3} };

// {2AA218C4-0444-465a-B456-043C0214D8FB}
const GUID c_guidLangBar_Tool = { 0x2aa218c4, 0x444, 0x465a, {0xb4, 0x56, 0x4, 0x3c, 0x2, 0x14, 0xd8, 0xfb} };


//
//  define two guids for display attribute info. This textservice has
//  two display attribute. One is for input text and the other is for the
//  converted text.
//
//      c_guidDisplayAttributeInput 
//      c_guidDisplayAttributeConverted
//
/* 4e1aa3fe-6c7f-11d7-a6ec-00065b84435c */
const GUID c_guidDisplayAttributeInput = { 
    0x4e1aa3fe,
    0x6c7f,
    0x11d7,
    {0xa6, 0xec, 0x00, 0x06, 0x5b, 0x84, 0x43, 0x5c}
  };
/* 4e1aa3ff-6c7f-11d7-a6ec-00065b84435c */
const GUID c_guidDisplayAttributeConverted = { 
    0x4e1aa3ff,
    0x6c7f,
    0x11d7,
    {0xa6, 0xec, 0x00, 0x06, 0x5b, 0x84, 0x43, 0x5c}
  };

