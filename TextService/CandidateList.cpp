
#include "Globals.h"
#include "TextService.h"
#include "EditSession.h"
#include "CandidateWindow.h"
#include "CandidateList.h"
#include "CandidateTree.h"

class CGetTextExtentEditSession : public CEditSessionBase{
public:
    CGetTextExtentEditSession(CTextService *pTextService, ITfContext *pContext, ITfContextView *pContextView, ITfRange *pRangeComposition, CCandidateWindow *pCandidateWindow) : CEditSessionBase(pTextService, pContext)
    {
        _pContextView = pContextView;
        _pRangeComposition = pRangeComposition;
        _pCandidateWindow = pCandidateWindow;
    }

    // ITfEditSession
    STDMETHODIMP DoEditSession(TfEditCookie ec);

private:
    ITfContextView *_pContextView;
    ITfRange *_pRangeComposition;
    CCandidateWindow *_pCandidateWindow;
};

STDAPI CGetTextExtentEditSession::DoEditSession(TfEditCookie ec){
    RECT rc;
    BOOL fClipped;

    if (SUCCEEDED(_pContextView->GetTextExt(ec, _pRangeComposition, &rc, &fClipped)))
        _pCandidateWindow->_Move(rc.left, rc.bottom);

    return S_OK;
}

CCandidateList::CCandidateList(CTextService *pTextService){
    _pTextService = pTextService;

    _hwndParent = NULL;
    _pCandidateWindow = NULL;
    _pRangeComposition = NULL;
    _pContextCandidateWindow = NULL;
    _pContextDocument = NULL;
    _pDocumentMgr = NULL;

    _dwCookieContextKeyEventSink = TF_INVALID_COOKIE;
    _dwCookieTextLayoutSink = TF_INVALID_COOKIE;

    _cRef = 1;

    DllAddRef();
}

CCandidateList::~CCandidateList()
{
    _EndCandidateList();
    DllRelease();
}

STDAPI CCandidateList::QueryInterface(REFIID riid, void **ppvObj)
{
    if (ppvObj == NULL)
        return E_INVALIDARG;

    *ppvObj = NULL;

    if(IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_ITfContextKeyEventSink)){
        *ppvObj = (ITfContextKeyEventSink *)this;
    }else if(IsEqualIID(riid, IID_ITfTextLayoutSink)){
        *ppvObj = (ITfTextLayoutSink *)this;
    }

    if(*ppvObj){
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

STDAPI_(ULONG) CCandidateList::AddRef(){
    return ++_cRef;
}

STDAPI_(ULONG) CCandidateList::Release(){
    LONG cr = --_cRef;

    assert(_cRef >= 0);

    if (_cRef == 0){
        delete this;
    }

    return cr;
}

STDAPI CCandidateList::OnKeyDown(WPARAM wParam, LPARAM lParam, BOOL *pfEaten){
    if (pfEaten == NULL)
        return E_INVALIDARG;

    //*pfEaten = TRUE;
    _pCandidateWindow->_OnKeyDown((UINT)wParam);

    return S_OK;
}

STDAPI CCandidateList::OnKeyUp(WPARAM wParam, LPARAM lParam, BOOL *pfEaten){
    if (pfEaten == NULL)
        return E_INVALIDARG;

    //*pfEaten = TRUE;

    // consume VK_RETURN here to finish candidate list.
	switch(wParam){
	case VK_SPACE:
	case VK_RETURN:
        _EndCandidateList();
		break;

	default:
        _pCandidateWindow->_OnKeyUp((UINT)wParam);
	}

    return S_OK;
}

STDAPI CCandidateList::OnTestKeyDown(WPARAM wParam, LPARAM lParam, BOOL *pfEaten){
    if (pfEaten == NULL)
        return E_INVALIDARG;

    *pfEaten = TRUE;

    return S_OK;
}

STDAPI CCandidateList::OnTestKeyUp(WPARAM wParam, LPARAM lParam, BOOL *pfEaten){
    if (pfEaten == NULL)
        return E_INVALIDARG;

    *pfEaten = TRUE;

    return S_OK;
}

STDAPI CCandidateList::OnLayoutChange(ITfContext *pContext, TfLayoutCode lcode, ITfContextView *pContextView){
    if (pContext != _pContextDocument)
        return S_OK;

    switch (lcode){
    case TF_LC_CHANGE:
        if (_pCandidateWindow != NULL)
        {
            CGetTextExtentEditSession *pEditSession;

            if ((pEditSession = new CGetTextExtentEditSession(_pTextService, pContext, pContextView, _pRangeComposition, _pCandidateWindow)) != NULL)
            {
                HRESULT hr;
                // a lock is required
                // nb: this method is one of the few places where it is legal to use
                // the TF_ES_SYNC flag
                pContext->RequestEditSession(_pTextService->_GetClientId(), pEditSession, TF_ES_SYNC | TF_ES_READ, &hr);

                pEditSession->Release();
             }
        }
        break;

    case TF_LC_DESTROY:
        _EndCandidateList();
        break;
    }

    return S_OK;
}

HRESULT CCandidateList::_StartCandidateList(TfClientId tfClientId, ITfDocumentMgr *pDocumentMgr, ITfContext *pContextDocument, TfEditCookie ec, ITfRange *pRangeComposition){
    TfEditCookie ecTmp;
    HRESULT hr = E_FAIL;
    BOOL fClipped;

    // clear the previous candidate list.
    // only one candidate window is supported.
    _EndCandidateList();

    // create a new context on the document manager object for
    // the candidate ui.
    if (FAILED(pDocumentMgr->CreateContext(tfClientId, 0, NULL, &_pContextCandidateWindow, &ecTmp)))
        return E_FAIL;

    // push the new context. 
    if (FAILED(pDocumentMgr->Push(_pContextCandidateWindow)))
        goto Exit;

    _pDocumentMgr = pDocumentMgr;
    _pDocumentMgr->AddRef();

    _pContextDocument = pContextDocument;
    _pContextDocument->AddRef();

    _pRangeComposition = pRangeComposition;
    _pRangeComposition->AddRef();

    // advise ITfContextKeyEventSink to the new context.
    if (FAILED(_AdviseContextKeyEventSink()))
        goto Exit;

    // advise ITfTextLayoutSink to the document context.
    if (FAILED(_AdviseTextLayoutSink()))
        goto Exit;

	//���뻺����
	int cchMax = 10;
	wchar_t *pchText = new wchar_t[cchMax];

	//��������ַ�
	ULONG pcch = 0;
	if(_pRangeComposition->GetText(ec, NULL, pchText, cchMax, &pcch) == S_OK){
		pchText[pcch] = 0;
	}

	//��ѯ��ѡ��
	if(!CandidateTree->ForwardTo(pchText[pcch - 1])){
		_pRangeComposition->Collapse(ec, TF_ANCHOR_END);
		_pTextService->_TerminateComposition(ec, _pContextDocument);
	
	}else{

		CCandidateTree::Node *node = CandidateTree->GetCurrent();
		if(node != NULL){
			//��ʾ/�����ѡ��
			if(node->IsEnd()){
				_InputDefaultCandidate(ec);
			
			// create an instance of CCandidateWindow class.
			}else if(_pCandidateWindow = new CCandidateWindow()){
				RECT rc;
				ITfContextView *pContextView;

				// get an active view of the document context.
				if (FAILED(pContextDocument->GetActiveView(&pContextView)))
					goto Exit;

				// get text extent for the range of the composition.
				if (FAILED(pContextView->GetTextExt(ec, pRangeComposition, &rc, &fClipped)))
					goto Exit;

				pContextView->Release();

		        
				// create the dummy candidate window
				if (!_pCandidateWindow->_Create())
					goto Exit;

				_pCandidateWindow->_Move(rc.left, rc.bottom);
				_pCandidateWindow->_Show();

				hr = S_OK;
			}
		}
	}

	//�ͷŻ�����
	delete[] pchText;


Exit:
    if (FAILED(hr))
    {
        _EndCandidateList();
    }
    return hr;
}

void CCandidateList::_EndCandidateList(){
    if (_pCandidateWindow){
        _pCandidateWindow->_Destroy();
        delete _pCandidateWindow;
        _pCandidateWindow = NULL;
    }

    if (_pRangeComposition){
       _pRangeComposition->Release();
       _pRangeComposition = NULL;
    }

    if (_pContextCandidateWindow){
       _UnadviseContextKeyEventSink();
       _pContextCandidateWindow->Release();
       _pContextCandidateWindow = NULL;
    }

    if (_pContextDocument){
       _UnadviseTextLayoutSink();
       _pContextDocument->Release();
       _pContextDocument = NULL;
    }

    if (_pDocumentMgr){
       _pDocumentMgr->Pop(0);
       _pDocumentMgr->Release();
       _pDocumentMgr = NULL;
    }
}

void CCandidateList::_InputDefaultCandidate(TfEditCookie ec){
	CCandidateTree::Node *current = CandidateTree->GetCurrent();
	if(current != NULL && _pRangeComposition != NULL){
		wchar_t pchText = CandidateTree->GetCurrent()->GetValue();
		_pRangeComposition->SetText(ec, NULL, &pchText, 1);

		_pTextService->_HandleArrowKey(ec, _pContextDocument, VK_RIGHT);

		_pRangeComposition->Collapse(ec, TF_ANCHOR_END);
		_pTextService->_TerminateComposition(ec, _pContextDocument);
	}
}

BOOL CCandidateList::_IsContextCandidateWindow(ITfContext *pContext){
    return (_pContextCandidateWindow == pContext) ? TRUE : FALSE;
}

HRESULT CCandidateList::_AdviseContextKeyEventSink(){
    HRESULT hr;
    ITfSource *pSource = NULL;

    hr = E_FAIL;

    if (FAILED(_pContextCandidateWindow->QueryInterface(IID_ITfSource, (void **)&pSource)))
        goto Exit;

    if (FAILED(pSource->AdviseSink(IID_ITfContextKeyEventSink, (ITfContextKeyEventSink *)this, &_dwCookieContextKeyEventSink)))
        goto Exit;

    hr = S_OK;

Exit:
    if (pSource != NULL)
        pSource->Release();
    return hr;
}

HRESULT CCandidateList::_UnadviseContextKeyEventSink()
{
    HRESULT hr;
    ITfSource *pSource = NULL;

    hr = E_FAIL;

    if (_pContextCandidateWindow == NULL)
        goto Exit;

    if (FAILED(_pContextCandidateWindow->QueryInterface(IID_ITfSource, (void **)&pSource)))
        goto Exit;

    if (FAILED(pSource->UnadviseSink(_dwCookieContextKeyEventSink)))
        goto Exit;

    hr = S_OK;

Exit:
    if (pSource != NULL)
        pSource->Release();
    return hr;
}

HRESULT CCandidateList::_AdviseTextLayoutSink()
{
    HRESULT hr;
    ITfSource *pSource = NULL;

    hr = E_FAIL;

    if (FAILED(_pContextDocument->QueryInterface(IID_ITfSource, (void **)&pSource)))
        goto Exit;

    if (FAILED(pSource->AdviseSink(IID_ITfTextLayoutSink, (ITfTextLayoutSink *)this, &_dwCookieTextLayoutSink)))
        goto Exit;

    hr = S_OK;

Exit:
    if (pSource != NULL)
        pSource->Release();
    return hr;
}

HRESULT CCandidateList::_UnadviseTextLayoutSink()
{
    HRESULT hr;
    ITfSource *pSource = NULL;

    hr = E_FAIL;

    if (_pContextDocument == NULL)
        goto Exit;

    if (FAILED(_pContextDocument->QueryInterface(IID_ITfSource, (void **)&pSource)))
        goto Exit;

    if (FAILED(pSource->UnadviseSink(_dwCookieTextLayoutSink)))
        goto Exit;

    hr = S_OK;

Exit:
    if (pSource != NULL)
        pSource->Release();
    return hr;
}
