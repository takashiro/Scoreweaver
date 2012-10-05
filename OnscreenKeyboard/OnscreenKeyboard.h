// OnscreenKeyboard.h : main header file for the OnscreenKeyboard application
// Download by http://www.codefans.net

#if !defined(AFX_OnscreenKeyboard_H__EFE558F9_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_)
#define AFX_OnscreenKeyboard_H__EFE558F9_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// COnscreenKeyboardApp:
// See OnscreenKeyboard.cpp for the implementation of this class
//

class COnscreenKeyboardApp : public CWinApp
{
public:
	COnscreenKeyboardApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COnscreenKeyboardApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COnscreenKeyboardApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OnscreenKeyboard_H__EFE558F9_FB84_11D3_8D1D_00C0F0405B24__INCLUDED_)
