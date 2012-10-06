
#include "Globals.h"
#include "TextService.h"
#include "Resource.h"
#include "LanguageBarItemButton.h"

BOOL CTextService::_InitLanguageBar()
{
    ITfLangBarItemMgr *pLangBarItemMgr;
    BOOL fRet;

    if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) != S_OK)
        return FALSE;

    fRet = FALSE;

	CLangBarItemButton *buttons[] = {new PowerButton(this), new ModeButton(this), new PunctButton(this), new VKeyboardButton(this), new ToolButton(this)};
	for(int i = 0; i < 5; i++){
		if (buttons[i] != NULL){
			if (buttons[i] == NULL){
				goto Exit;
			}
			
			if (pLangBarItemMgr->AddItem(buttons[i]) != S_OK){
				buttons[i]->Release();
				goto Exit;
			}
		}
	}

	_pPowerButton = buttons[0];
	_pModeButton = buttons[1];
	_pPunctButton = buttons[2];
	_pVKeyboardButton = buttons[3];
	_pToolButton = buttons[4];

    fRet = TRUE;

Exit:
    pLangBarItemMgr->Release();
    return fRet;
}

void CTextService::_UninitLanguageBar()
{
    ITfLangBarItemMgr *pLangBarItemMgr;

	if (_pThreadMgr->QueryInterface(IID_ITfLangBarItemMgr, (void **)&pLangBarItemMgr) != S_OK){
		return;
	}

	//Ïú»Ù°´Å¥
	CLangBarItemButton *buttons[] = {_pToolButton, _pPunctButton, _pModeButton, _pVKeyboardButton, _pPowerButton};
	for(int i = 0; i < 5; i++){
		if (buttons[i] != NULL){
			pLangBarItemMgr->RemoveItem(buttons[i]);

			buttons[i]->Release();
			buttons[i] = NULL;
		}
	}
	_pToolButton = _pPunctButton = _pModeButton = _pVKeyboardButton = _pPowerButton = NULL;

	pLangBarItemMgr->Release();
}
