
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

	void SetPageLimit(int limit);
	int PageLimit() const;

	void SetCandidateList(const string &list);
	int CandidateNum() const;
	string CandidateList() const;

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

	int _pageLimit, _curPage;

	string _candidateList;

	int _windowWidth, _windowHeight;
};

extern CCandidateWindow *CandidateWindow;

#endif // CANDIDATEWINDOW_H
