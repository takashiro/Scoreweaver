// FocusTestDlg.h : header file
// Download by http://www.codefans.net

#if !defined(AFX_FOCUSTESTDLG_H__EFE558FB_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_)
#define AFX_FOCUSTESTDLG_H__EFE558FB_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// COnscreenKeyboardDlg dialog

#include "AfxTempl.h"
#include "SystemTray.h"

struct KEYDEF
{
	char cNormal;
	char cShifted;
	int cWidth;
};

class COnscreenKeyboardDlg : public CDialog
{
// Construction
public:
	int pKeyWidth;
	int pKeyHeight;
	CTypedPtrList<CPtrList, KEYDEF*> cKeys;
	void AddKey(
		char pNormal,
		char pShifted,
		int pWidth);
	void CalcWidthHeight();
	void DrawKey(CDC * dc, CRect & rc, KEYDEF * key, BOOL cHilight=FALSE);
	void SendKey(KEYDEF * key);
	void ReleaseFocus();
	int DescribeKeyState();
	void DrawKeyboard();
	int cCurrentKeyState;
	HWND gFocus;
	COnscreenKeyboardDlg(CWnd* pParent = NULL);	// standard constructor

	CSystemTray cSystray;


// Dialog Data
	//{{AFX_DATA(COnscreenKeyboardDlg)
	enum { IDD = IDD_ONSCREENKEYBOARD_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnscreenKeyboardDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(COnscreenKeyboardDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnShowKeyboard();
	afx_msg void OnUpdateShowKeyboard(CCmdUI* pCmdUI);
	afx_msg void OnHideKeyboard();
	afx_msg void OnUpdateHideKeyboard(CCmdUI* pCmdUI);
	afx_msg void OnExit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FOCUSTESTDLG_H__EFE558FB_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_)
