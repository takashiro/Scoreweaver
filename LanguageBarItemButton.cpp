
#include "LanguageBarItemButton.h"

// The ids of the menu item of the language bar button.
#define MENUITEM_INDEX_CONFIG 0
#define MENUITEM_INDEX_OPENCLOSE 1
#define MENUITEM_INDEX_ABOUTUS 2

#define BUTTON_TEXT_POWER L"开启/关闭"
#define BUTTON_TEXT_MODESWITCH L"模式切换"
#define BUTTON_TEXT_TOOL L"工具"

// The descriptions of the menu item of the language bar button.
static WCHAR *c_szMenuItemDescription[3] = {L"配置(&C)", L"开启/关闭(&O)", L"关于我们(&A)"};


CLangBarItemButton::CLangBarItemButton(CTextService *pTextService, const char *icon_id, const OLECHAR *text){
	if(icon_id != NULL){
		this->SetIcon(icon_id);
	}

	if(text != NULL){
		this->SetText(text);
	}

    DllAddRef();

	_cRef = 1;

    // initialize TF_LANGBARITEMINFO structure.
    _tfLangBarItemInfo.clsidService = c_clsidTextService;    // This LangBarItem belongs to this TextService.
    _tfLangBarItemInfo.ulSort = 0;                           // The position of this LangBar Item is not specified.
	this->setToolTip(text);

    // Initialize the sink pointer to NULL.
    _pLangBarItemSink = NULL;

    _pTextService = pTextService;
    _pTextService->AddRef();
}

CLangBarItemButton::~CLangBarItemButton(){
    DllRelease();
    _pTextService->Release();
}

STDAPI CLangBarItemButton::QueryInterface(REFIID riid, void **ppvObj){
    if (ppvObj == NULL)
        return E_INVALIDARG;

    *ppvObj = NULL;

    if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ITfLangBarItem) || IsEqualIID(riid, IID_ITfLangBarItemButton)){
        *ppvObj = (ITfLangBarItemButton *)this;
    
	}else if(IsEqualIID(riid, IID_ITfSource)){
        *ppvObj = (ITfSource *)this;
    }

    if(*ppvObj){
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

STDAPI_(ULONG) CLangBarItemButton::AddRef()
{
    return ++_cRef;
}

STDAPI_(ULONG) CLangBarItemButton::Release()
{
    LONG cr = --_cRef;

    assert(_cRef >= 0);

    if (_cRef == 0)
    {
        delete this;
    }

    return cr;
}

STDAPI CLangBarItemButton::GetInfo(TF_LANGBARITEMINFO *pInfo)
{
    *pInfo = _tfLangBarItemInfo;
    return S_OK;
}

STDAPI CLangBarItemButton::GetStatus(DWORD *pdwStatus)
{
    *pdwStatus = 0;
    return S_OK;
}

STDAPI CLangBarItemButton::Show(BOOL fShow)
{
    return E_NOTIMPL;
}

STDAPI CLangBarItemButton::GetTooltipString(BSTR *pbstrToolTip)
{
	*pbstrToolTip = SysAllocString(text);

    return (*pbstrToolTip == NULL) ? E_OUTOFMEMORY : S_OK;
}

STDAPI CLangBarItemButton::GetIcon(HICON *phIcon){
    *phIcon = (HICON)LoadImage(g_hInst, TEXT(icon_id), IMAGE_ICON, 16, 16, 0);
    return (*phIcon != NULL) ? S_OK : E_FAIL;
}

void CLangBarItemButton::SetIcon(const char *icon){
	this->icon_id = icon;
}

STDAPI CLangBarItemButton::GetText(BSTR *pbstrText)
{
    *pbstrText = SysAllocString(text);

    return (*pbstrText == NULL) ? E_OUTOFMEMORY : S_OK;
}

void CLangBarItemButton::SetText(const OLECHAR *text){
	this->text = text;
}

void CLangBarItemButton::setToolTip(const OLECHAR *description){
	SafeStringCopy(_tfLangBarItemInfo.szDescription, ARRAYSIZE(_tfLangBarItemInfo.szDescription), description, ARRAYSIZE(_tfLangBarItemInfo.szDescription));
}

STDAPI CLangBarItemButton::AdviseSink(REFIID riid, IUnknown *punk, DWORD *pdwCookie)
{
    // We allow only ITfLangBarItemSink interface.
    if(!IsEqualIID(IID_ITfLangBarItemSink, riid))
        return CONNECT_E_CANNOTCONNECT;

    // We support only one sink.
    if(_pLangBarItemSink != NULL)
        return CONNECT_E_ADVISELIMIT;

    // Query the ITfLangBarItemSink interface and store it into _pLangBarItemSink.
    if(punk->QueryInterface(IID_ITfLangBarItemSink, (void **)&_pLangBarItemSink) != S_OK){
        _pLangBarItemSink = NULL;
        return E_NOINTERFACE;
    }

    // return our cookie.
    *pdwCookie = TEXTSERVICE_LANGBARITEMSINK_COOKIE;
    return S_OK;
}

STDAPI CLangBarItemButton::UnadviseSink(DWORD dwCookie){
    // Check the given cookie.
    if (dwCookie != TEXTSERVICE_LANGBARITEMSINK_COOKIE)
        return CONNECT_E_NOCONNECTION;

    // If there is nno connected sink, the method fails.
    if (_pLangBarItemSink == NULL)
        return CONNECT_E_NOCONNECTION;

    _pLangBarItemSink->Release();
    _pLangBarItemSink = NULL;

    return S_OK;
}

STDMETHODIMP CLangBarItemButton::OnClick(TfLBIClick click, POINT pt, const RECT *prcArea){
    return S_OK;
}

STDAPI CLangBarItemButton::InitMenu(ITfMenu *pMenu){
    return S_OK;
}

STDAPI CLangBarItemButton::OnMenuSelect(UINT wID){
    return S_OK;
}

void CLangBarItemButton::updateIcon(){
}

void CLangBarItemButton::repaint(DWORD flags){
	_pLangBarItemSink->OnUpdate(flags);
}

/* Power Button */
PowerButton::PowerButton(CTextService *pTextService): CLangBarItemButton(pTextService, "IDI_OFF", BUTTON_TEXT_POWER){
	_tfLangBarItemInfo.guidItem = c_guidLangBar_Power;
}

STDMETHODIMP PowerButton::OnClick(TfLBIClick click, POINT pt, const RECT *prcArea){
	_pTextService->_SetKeyboardOpen(!_pTextService->_IsKeyboardOpen());

	return S_OK;
}

void PowerButton::updateIcon(){
	if(_pTextService->_IsKeyboardOpen()){
		icon_id = "IDI_ON";
	}else{
		icon_id = "IDI_OFF";
	}

	repaint(TF_LBI_ICON);
}

/* Mode Switch Button */

ModeSwitchButton::ModeSwitchButton(CTextService *pTextService):CLangBarItemButton(pTextService, "IDI_MODE_ZHENG", BUTTON_TEXT_MODESWITCH){
	_tfLangBarItemInfo.guidItem = c_guidLangBar_ModeSwitch;
}

STDAPI ModeSwitchButton::OnClick(TfLBIClick click, POINT pt, const RECT *prcArea){
	_pTextService->SwitchMode();
    return S_OK;
}

void ModeSwitchButton::updateIcon(){
	switch(_pTextService->GetMode()){
	case Pang:
		this->icon_id = "IDI_MODE_PANG";
		break;
	case Zhu:
		this->icon_id = "IDI_MODE_ZHU";
		break;
	case Zheng:default:
		this->icon_id = "IDI_MODE_ZHENG";
		break;
	}

	repaint(TF_LBI_ICON);
}


/* Tool Button */

ToolButton::ToolButton(CTextService *pTextService):CLangBarItemButton(pTextService, "IDI_TOOL", BUTTON_TEXT_TOOL){
	_tfLangBarItemInfo.guidItem = c_guidLangBar_Tool;		//GUID of this LangBarItem.
    _tfLangBarItemInfo.dwStyle = TF_LBI_STYLE_BTN_MENU;		//This LangBar is a button type with a menu.
}

STDMETHODIMP ToolButton::OnClick(TfLBIClick click, POINT pt, const RECT *prcArea){
    return S_OK;
}

STDAPI ToolButton::InitMenu(ITfMenu *pMenu){
    // Add the fisrt menu item.
    pMenu->AddMenuItem(MENUITEM_INDEX_CONFIG, 0, NULL, NULL, c_szMenuItemDescription[MENUITEM_INDEX_CONFIG], (ULONG)wcslen(c_szMenuItemDescription[MENUITEM_INDEX_CONFIG]), NULL);

    // Add the keyboard open close item.
    DWORD dwFlags = 0;
    if (_pTextService->_IsKeyboardDisabled())
        dwFlags |= TF_LBMENUF_GRAYED;
    else if (_pTextService->_IsKeyboardOpen())
        dwFlags |= TF_LBMENUF_CHECKED;

    pMenu->AddMenuItem(MENUITEM_INDEX_OPENCLOSE, dwFlags, NULL, NULL, c_szMenuItemDescription[MENUITEM_INDEX_OPENCLOSE], (ULONG)wcslen(c_szMenuItemDescription[MENUITEM_INDEX_OPENCLOSE]), NULL);

    // Add the second menu item.
    pMenu->AddMenuItem(MENUITEM_INDEX_ABOUTUS, 0, NULL, NULL, c_szMenuItemDescription[MENUITEM_INDEX_ABOUTUS], (ULONG)wcslen(c_szMenuItemDescription[MENUITEM_INDEX_ABOUTUS]), NULL);

    return S_OK;
}

STDAPI ToolButton::OnMenuSelect(UINT wID){
    BOOL fOpen;

    //
    // This is callback when the menu item is selected.
    //
    switch (wID)
    {
        case MENUITEM_INDEX_CONFIG:
            break;

        case MENUITEM_INDEX_ABOUTUS:
            break;

        case MENUITEM_INDEX_OPENCLOSE:
            fOpen = _pTextService->_IsKeyboardOpen();
            _pTextService->_SetKeyboardOpen(fOpen ? FALSE : TRUE);
            break;
    }

    return S_OK;
}