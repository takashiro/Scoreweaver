//////////////////////////////////////////////////////////////////////
//
//  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
//  PARTICULAR PURPOSE.
//
//  Copyright (C) 2003  Microsoft Corporation.  All rights reserved.
//
//  LanguageBar.cpp
//
//          Language Bar UI code.
//
//////////////////////////////////////////////////////////////////////

#include "Globals.h"
#include "TextService.h"
#include "Resource.h"
#include "LanguageBarItemButton.h"

//+---------------------------------------------------------------------------
//
// _InitLanguageBar
//
//----------------------------------------------------------------------------

BOOL CTextService::_InitLanguageBar()
{
    ITfLangBarItemMgr *pLangBarItemMgr;
    BOOL fRet;

    if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) != S_OK)
        return FALSE;

    fRet = FALSE;

    /*if ((_pLangBarButton[0] = new ModeSwitchButton(this)) == NULL)
        goto Exit;*/

	if ((_pToolButton = new ToolButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pToolButton) != S_OK)
	{
		_pToolButton->Release();
		_pToolButton = NULL;
		goto Exit;
	}

	/*if ((_pModeSwitchButton = new ModeSwitchButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pModeSwitchButton) != S_OK)
	{
		_pModeSwitchButton->Release();
		_pModeSwitchButton = NULL;
		goto Exit;
	}*/

    fRet = TRUE;

Exit:
    pLangBarItemMgr->Release();
    return fRet;
}

//+---------------------------------------------------------------------------
//
// _UninitLanguageBar
//
//----------------------------------------------------------------------------

void CTextService::_UninitLanguageBar()
{
    ITfLangBarItemMgr *pLangBarItemMgr;

	if (_pToolButton == NULL)
		return;

	if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) == S_OK)
	{
		pLangBarItemMgr->RemoveItem(_pToolButton);
	}

	_pToolButton->Release();
	_pToolButton = NULL;

	/*if (_pModeSwitchButton == NULL)
		return;

	if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) == S_OK)
	{
		pLangBarItemMgr->RemoveItem(_pModeSwitchButton);
	}

	_pModeSwitchButton->Release();
	_pModeSwitchButton = NULL;*/

	pLangBarItemMgr->Release();
}
