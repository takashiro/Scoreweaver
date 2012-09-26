#ifndef LANGUAGEBARITEMBUTTON_H
#define LANGUAGEBARITEMBUTTON_H

#include "Globals.h"
#include "TextService.h"
#include "Resource.h"

// The cookie for the sink to CLangBarItemButton.
#define TEXTSERVICE_LANGBARITEMSINK_COOKIE 0x0fab0fac


class CLangBarItemButton : public ITfLangBarItemButton,
                           public ITfSource
{
public:
    CLangBarItemButton(CTextService *pTextService, const char *icon_id = NULL, const OLECHAR *text = NULL);
    ~CLangBarItemButton();

    // IUnknown
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObj);
    STDMETHODIMP_(ULONG) AddRef(void);
    STDMETHODIMP_(ULONG) Release(void);

    // ITfLangBarItem
    STDMETHODIMP GetInfo(TF_LANGBARITEMINFO *pInfo);
    STDMETHODIMP GetStatus(DWORD *pdwStatus);
    STDMETHODIMP Show(BOOL fShow);
    STDMETHODIMP GetTooltipString(BSTR *pbstrToolTip);

    // ITfLangBarItemButton
    virtual STDMETHODIMP OnClick(TfLBIClick click, POINT pt, const RECT *prcArea) = 0;

	// Submenu
	virtual STDMETHODIMP InitMenu(ITfMenu *pMenu);
    virtual STDMETHODIMP OnMenuSelect(UINT wID);

	// Button Icon
    STDMETHODIMP GetIcon(HICON *phIcon);
    void SetIcon(const char *icon);

	// Button Text
	STDMETHODIMP GetText(BSTR *pbstrText);
	void SetText(const OLECHAR *text);


	// SetToolTip
	void setToolTip(const OLECHAR *tip);

    // ITfSource
    STDMETHODIMP AdviseSink(REFIID riid, IUnknown *punk, DWORD *pdwCookie);
    STDMETHODIMP UnadviseSink(DWORD dwCookie);

	virtual void updateIcon();

	void repaint(DWORD flags = TF_LBI_BTNALL);

protected:
    ITfLangBarItemSink *_pLangBarItemSink;
    TF_LANGBARITEMINFO _tfLangBarItemInfo;

    CTextService *_pTextService;
    LONG _cRef;

	const char *icon_id;
	const OLECHAR *text;
};

class ModeSwitchButton: public CLangBarItemButton{
public:
	ModeSwitchButton(CTextService *pTextService);

	virtual STDMETHODIMP OnClick(TfLBIClick click, POINT pt, const RECT *prcArea);

	virtual STDMETHODIMP InitMenu(ITfMenu *pMenu);
    virtual STDMETHODIMP OnMenuSelect(UINT wID);

	virtual void updateIcon();
};

class ToolButton: public CLangBarItemButton{
public:
	ToolButton(CTextService *pTextService);

	virtual STDMETHODIMP OnClick(TfLBIClick click, POINT pt, const RECT *prcArea);

	virtual STDMETHODIMP InitMenu(ITfMenu *pMenu);
    virtual STDMETHODIMP OnMenuSelect(UINT wID);
};

#endif