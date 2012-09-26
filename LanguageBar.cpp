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

	if ((_pPowerButton = new PowerButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pPowerButton) != S_OK)
	{
		_pPowerButton->Release();
		_pPowerButton = NULL;
		goto Exit;
	}

	if ((_pModeSwitchButton = new ModeSwitchButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pModeSwitchButton) != S_OK)
	{
		_pModeSwitchButton->Release();
		_pModeSwitchButton = NULL;
		goto Exit;
	}

	if ((_pToolButton = new ToolButton(this)) == NULL)
        goto Exit;
	
	if (pLangBarItemMgr->AddItem(_pToolButton) != S_OK)
	{	
		_pToolButton->Release();
		_pToolButton = NULL;
		goto Exit;
	}

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

	//销毁工具按钮
	if (_pToolButton != NULL){
		if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) == S_OK)
		{
			pLangBarItemMgr->RemoveItem(_pToolButton);
		}

		_pToolButton->Release();
		_pToolButton = NULL;
	}

	//销毁模式按钮
	if (_pModeSwitchButton != NULL){
		if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) == S_OK)
		{
			pLangBarItemMgr->RemoveItem(_pModeSwitchButton);
		}

		_pModeSwitchButton->Release();
		_pModeSwitchButton = NULL;
	}

	// 销毁开关按钮
	if (_pPowerButton != NULL){
		if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) == S_OK)
		{
			pLangBarItemMgr->RemoveItem(_pPowerButton);
		}

		_pPowerButton->Release();
		_pPowerButton = NULL;
	}

	pLangBarItemMgr->Release();
}
