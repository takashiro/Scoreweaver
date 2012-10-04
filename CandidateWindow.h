
#ifndef CANDIDATEWINDOW_H
#define CANDIDATEWINDOW_H

class CCandidateWindow{
public:
    CCandidateWindow();

    static BOOL _InitWindowClass();
    static void _UninitWindowClass();

    BOOL _Create();
    void _Destroy();

    void _Move(int x, int y);
    void _Show();
    void _Hide();

    HRESULT _OnKeyDown(UINT uVKey);
    HRESULT _OnKeyUp(UINT uVKey);

	void SetCurPage(int page);
	int CurPage() const;
	void NextPage();
	void PrevPage();

	void SetCandidateNum(int num);

	void SetPageLimit(int limit);
	int PageLimit() const;

	void SetCandidates(const wstring &keys, const wstring &values);

private:
    static LRESULT CALLBACK _WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    static void _SetThis(HWND hwnd, LPARAM lParam){
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
    }

    static CCandidateWindow *_GetThis(HWND hwnd){
        return (CCandidateWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    static ATOM _atomWndClass;

    HWND _hwnd;

	int _pageLimit, _curPage, _candidateNum;
	int _windowWidth, _windowHeight;
};

extern CCandidateWindow *CandidateWindow;

#endif // CANDIDATEWINDOW_H
