// COnscreenKeyboardDlg.cpp : implementation file
// Download by http://www.codefans.net

#include "stdafx.h"
#include "OnscreenKeyboard.h"
#include "OnscreenKeyboardDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	WM_ICON_NOTIFY WM_USER + 10
#define TIMER_ID 101

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// COnscreenKeyboardDlg dialog

COnscreenKeyboardDlg::COnscreenKeyboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COnscreenKeyboardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COnscreenKeyboardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COnscreenKeyboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COnscreenKeyboardDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COnscreenKeyboardDlg, CDialog)
	//{{AFX_MSG_MAP(COnscreenKeyboardDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_SIZE()
	ON_COMMAND(IDM_SHOW_KEYBOARD, OnShowKeyboard)
	ON_UPDATE_COMMAND_UI(IDM_SHOW_KEYBOARD, OnUpdateShowKeyboard)
	ON_COMMAND(IDM_HIDE_KEYBOARD, OnHideKeyboard)
	ON_UPDATE_COMMAND_UI(IDM_HIDE_KEYBOARD, OnUpdateHideKeyboard)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COnscreenKeyboardDlg message handlers

#define TAB 0x02
#define CAPSLOCK 0x03
#define SHIFT 0x04
#define CTRL 0x05
#define BSPACE 0x06
#define ENTER 0x07
#define ALT 0x08
#define WINDOW 0x9
#define LEFT 0x0A
#define RIGHT 0x0B
#define UP 0x0C
#define DOWN 0x0D
#define ESC 0x0E
#define PUP 0x0F
#define PDN 0x10
#define HOME 0x11
#define END 0x12
#define INS 0x13
#define DEL 0x14
#define WWW 0x15

BOOL COnscreenKeyboardDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	

	//build the keyboard definition

	//control row
	AddKey(0x00,0x00,0); //signal row change
	AddKey(0x00,ESC,10);
	for(int fnkey = 0x70; fnkey < 0x7C; fnkey++)
	{
		AddKey(0x00,fnkey & 0xFF,10);
	}
	AddKey(0x00,INS,14);
	AddKey(0x00,DEL,-10);

	//first row
	AddKey(0x00,0x00,1); //signal row change
	AddKey('`','~',10);
	AddKey('1','!',10);
	AddKey('2','@',10);
	AddKey('3','#',10);
	AddKey('4','$',10);
	AddKey('5','%',10);
	AddKey('6','^',10);
	AddKey('7','&',10);
	AddKey('8','*',10);
	AddKey('9','(',10);
	AddKey('0',')',10);
	AddKey('-','_',10);
	AddKey('=','+',10);
	AddKey(0x00,BSPACE,14); //backspace
	AddKey(0x00,PUP,-12);

	//second row
	AddKey(0x00,0x00,2); //signal row change
	AddKey(0x00,TAB,14); //tab
	AddKey('q','Q',10);
	AddKey('w','W',10);
	AddKey('e','E',10);
	AddKey('r','R',10);
	AddKey('t','T',10);
	AddKey('y','Y',10);
	AddKey('u','U',10);
	AddKey('i','I',10);
	AddKey('o','O',10);
	AddKey('p','P',10);
	AddKey('[','{',10);
	AddKey(']','}',10);
	AddKey('\\','|',10);
	AddKey(0x00,PDN,-12);

	//third row
	AddKey(0x00,0x00,3); //signal row change
	AddKey(0x00,CAPSLOCK,18); //caps lock
	AddKey('a','A',10);
	AddKey('s','S',10);
	AddKey('d','D',10);
	AddKey('f','F',10);
	AddKey('g','G',10);
	AddKey('h','H',10);
	AddKey('j','J',10);
	AddKey('k','K',10);
	AddKey('l','L',10);
	AddKey(';',':',10);
	AddKey('\'','\"',10);
	AddKey(0x00,ENTER,16); //enter
	AddKey(0x00,HOME,-10);

	//fourth row
	AddKey(0x00,0x00,4); //signal row change
	AddKey(0x00,SHIFT,22); //shift
	AddKey('z','Z',10);
	AddKey('x','X',10);
	AddKey('c','C',10);
	AddKey('v','V',10);
	AddKey('b','B',10);
	AddKey('n','N',10);
	AddKey('m','M',10);
	AddKey(',','<',10);
	AddKey('.','>',10);
	AddKey('/','?',10);
	AddKey(0x00,SHIFT,22); //shift
	AddKey(0x00,END,-10);

	//fifth row
	AddKey(0x00,0x00,5); //signal row change
	AddKey(0x00,CTRL,12); //ctrl
	AddKey(0x00,WINDOW,12); //window
	AddKey(0x00,ALT,12); //alt
	AddKey(' ',' ',60);
	AddKey(0x00,LEFT,12); //left
	AddKey(0x00,UP,12); //up
	AddKey(0x00,DOWN,12); //down
	AddKey(0x00,RIGHT,12); //right
	AddKey(0x00,WWW,-10); //http://WWW

	CalcWidthHeight();

	//put an icon for us in the system tray
	//add us the the system tray
	VERIFY(cSystray.Create(NULL,			// Parent window
			WM_ICON_NOTIFY,					// Icon notify message to use
			_T("Onscreen Keyboard"),		// tooltip
			m_hIcon,						// Icon to use
			IDR_TRAY_MENU));				// ID of tray icon

	SetTimer(TIMER_ID,250,NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COnscreenKeyboardDlg::CalcWidthHeight()
{
	pKeyWidth = 0;
	pKeyHeight = 0;
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	long totalWidth = 0;
	long longest = 0;
	long rows = 0;
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if((key->cNormal == 0x00) && (key->cShifted == 0x00))
		{
			rows++;
			if(totalWidth > longest)
			{
				longest = totalWidth;
			}
			totalWidth = 0;
		}
		else
		{
			totalWidth += abs(key->cWidth);
		}
	}
	CRect rect;
	GetClientRect(rect);
	pKeyHeight = rect.Height() / rows;
	pKeyWidth = (int)(((double)rect.Width()) / ((((double)(longest)) / 10)));
}

void COnscreenKeyboardDlg::AddKey(
	char pNormal,
	char pShifted,
	int pWidth)
{
	KEYDEF * key = new KEYDEF;
	key->cNormal = pNormal;
	key->cShifted = pShifted;
	key->cWidth = pWidth;
	cKeys.AddTail(key);
}

void COnscreenKeyboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void COnscreenKeyboardDlg::DrawKey(CDC * dc, CRect & rc, KEYDEF * key, BOOL cHilight)
{
	if(!cHilight)
	{
		rc.DeflateRect(1,1);
		dc->FillSolidRect(rc,GetSysColor(COLOR_3DFACE));
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DDKSHADOW));
		rc.DeflateRect(1,1);
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DLIGHT),GetSysColor(COLOR_3DSHADOW));
	}
	else
	{
		rc.DeflateRect(1,1);
		dc->FillSolidRect(rc,GetSysColor(COLOR_3DLIGHT));
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DLIGHT),GetSysColor(COLOR_3DSHADOW));
		rc.DeflateRect(1,1);
		dc->Draw3dRect(rc,GetSysColor(COLOR_3DSHADOW),GetSysColor(COLOR_3DDKSHADOW));
	}

	rc.DeflateRect(3,1);
	if(key->cNormal == 0x00)
	{
		CString label = " ";
		BOOL special = FALSE;
		if(key->cShifted > 0x6F) //is a function
		{
			int fkeynum = key->cShifted - 0x6F;
			label.Format("F%d",fkeynum);
		}
		else
		{
			switch(key->cShifted)
			{
			case TAB:    // 0x02
				label = "Tab->";
				break;
			case CAPSLOCK:    // 0x03
				label = "Caps";
				break;
			case SHIFT:    // 0x04
				label = "Shift";
				break;
			case CTRL:    // 0x05
				label = "Ctrl";
				break;
			case BSPACE:    // 0x06
				label = "<-Bspc";
				break;
			case ENTER:    // 0x07
				label = "Enter";
				break;
			case ALT:    // 0x08
				label = "Alt";
				break;
			case WINDOW:    // 0x9
				label = "Wnd";
				break;
			case ESC:
				label = "Esc";
				break;
			case LEFT:    // 0x0A
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx+siz, cy);
					dc->LineTo(cx-siz, cy);
					dc->LineTo(cx-siz + (siz*4)/5, cy - siz/2);
					dc->MoveTo(cx-siz, cy);
					dc->LineTo(cx-siz + (siz*4)/5, cy + siz/2);
				}
				break;
			case RIGHT:    // 0x0B
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx-siz, cy);
					dc->LineTo(cx+siz, cy);
					dc->LineTo(cx+siz - (siz*4)/5, cy - siz/2);
					dc->MoveTo(cx+siz, cy);
					dc->LineTo(cx+siz - (siz*4)/5, cy + siz/2);
				}
				break;
			case UP:    // 0x0C
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx, cy+siz);
					dc->LineTo(cx, cy-siz);
					dc->LineTo(cx - siz/2, cy-siz + (siz*4)/5);
					dc->LineTo(cx, cy-siz);
					dc->LineTo(cx + siz/2, cy-siz + (siz*4)/5);
				}
				break;
			case DOWN:    // 0x0D
				special = TRUE;
				{
					int cx = (rc.left + rc.right)/2;
					int cy = (rc.top + rc.bottom)/2;
					int siz = rc.Width()/3;
					dc->MoveTo(cx, cy-siz);
					dc->LineTo(cx, cy+siz);
					dc->LineTo(cx - siz/2, cy+siz - (siz*4)/5);
					dc->LineTo(cx, cy+siz);
					dc->LineTo(cx + siz/2, cy+siz - (siz*4)/5);
				}
				break;
			case PUP: //0x0F
				label = "PgUp";
				break;
			case PDN: //0x10
				label = "PgDn";
				break;
			case HOME: //0x11
				label = "Home";
				break;
			case END: //0x12
				label = "End";
				break;
			case INS: //0x13
				label = "Ins";
				break;
			case DEL: //0x14
				label = "Del";
				break;
			case WWW:
				label = "WWW";
				break;
			default:
				ASSERT(FALSE);
				label = "#ERR#";
				break;
			}
		}
		if(!special)
		{
			CSize tsize;
			tsize = dc->GetTextExtent(label);
			dc->TextOut(
				((rc.left + rc.right)/2) - (tsize.cx/2), 
				((rc.top + rc.bottom)/2) - (tsize.cy/2), 
				label);
		}
	}
	else
	{
		if((key->cShifted >= 'A') && (key->cShifted <= 'Z'))
		{
			CSize tsize;
			tsize = dc->GetTextExtent(key->cShifted);
			dc->TextOut(
				((rc.left + rc.right)/2) - (tsize.cx/2), 
				((rc.top + rc.bottom)/2) - (tsize.cy/2), 
				key->cShifted);
		}
		else
		{
			CSize tsize;
			tsize = dc->GetTextExtent('M');
			dc->TextOut(rc.left, rc.top, key->cShifted);
			dc->TextOut(
				rc.right - tsize.cx, 
				rc.bottom - tsize.cy,
				key->cNormal);
		}
	}
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COnscreenKeyboardDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		DrawKeyboard();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COnscreenKeyboardDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void COnscreenKeyboardDlg::SendKey(KEYDEF * keydef)
{
	if(keydef->cNormal == 0x00)
	{
		int vk;
		BOOL uptoo = TRUE;
		if(keydef->cShifted > 0x6F) //is a function key
		{
			vk = keydef->cShifted;
		}
		else
		{
			switch(keydef->cShifted)
			{
			case TAB:    // 0x02
				vk = VkKeyScan(0x09) & 0xFF;
				break;
			case CAPSLOCK:    // 0x03
				vk = VK_CAPITAL;
				break;
			case SHIFT:    // 0x04
				vk = VK_SHIFT;
				if(GetKeyState(vk) & 0xF000) return;
				uptoo = FALSE;
				break;
			case CTRL:    // 0x05
				vk = VK_CONTROL;
				if(GetKeyState(vk) & 0xF000) return;
				uptoo = FALSE;
				break;
			case BSPACE:    // 0x06
				vk = VK_BACK;
				break;
			case ENTER:    // 0x07
				vk = VkKeyScan(0x0D) & 0xFF;
				break;
			case ALT:    // 0x08
				vk = VK_MENU;
				break;
			case WINDOW:    // 0x9
				vk = VK_LWIN;
				break;
			case LEFT:    // 0x0A
				vk = VK_LEFT;
				break;
			case RIGHT:    // 0x0B
				vk = VK_RIGHT;
				break;
			case UP:    // 0x0C
				vk = VK_UP;
				break;
			case DOWN:    // 0x0D
				vk = VK_DOWN;
				break;
			case PUP: //0x0F
				vk = VK_PRIOR;
				break;
			case PDN: //0x10
				vk = VK_NEXT;
				break;
			case HOME: //0x11
				vk = VK_HOME;
				break;
			case END: //0x12
				vk = VK_END;
				break;
			case INS: //0x13
				vk = VK_INSERT;
				break;
			case DEL: //0x14
				vk = VK_DELETE;
				break;
			case WWW:
				KEYDEF key;
				key.cNormal = key.cShifted = 'H';
				SendKey(&key);
				key.cNormal = key.cShifted = 'T';
				SendKey(&key);
				SendKey(&key);
				key.cNormal = key.cShifted = 'P';
				SendKey(&key);
				key.cNormal = key.cShifted = ':';
				SendKey(&key);
				key.cNormal = key.cShifted = '/';
				SendKey(&key);
				SendKey(&key);
				key.cNormal = key.cShifted = 'W';
				SendKey(&key);
				SendKey(&key);
				SendKey(&key);
				vk = VkKeyScan('.') & 0xFF;
				break;
			default:
				ASSERT(FALSE);
				break;
			}
		}
		keybd_event(vk,0,0,0);
		if(uptoo)
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
	}
	else
	{
		char pChar = keydef->cNormal;
		SHORT ks = VkKeyScan(pChar);
		BYTE key = ks & 0xFF;

		keybd_event(key,0,0,0);
		keybd_event(key,0,KEYEVENTF_KEYUP,0);

		//turn off the control and shift if they were down
		unsigned char vk = VK_SHIFT;
		if(GetKeyState(vk) & 0xF000)
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
		vk = VK_CONTROL;
		if(GetKeyState(vk) & 0xF000) //allow toggle
		{
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
		}
	}
}

void COnscreenKeyboardDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	ReleaseFocus();

	CRect client;
	GetClientRect(client);
	int x = 0;
	int y = -pKeyHeight;
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if((key->cNormal == 0x00) && (key->cShifted == 0x00))
		{
			x = 0;
			y += pKeyHeight;
		}
		else
		{
			int width = ((abs(key->cWidth) * pKeyWidth) / 10);
			CRect rc(x,y,x + width, y + pKeyHeight);
			if(key->cWidth < 0)
			{
				rc.right = client.right;
			}
			x += width;
			if(rc.PtInRect(point))
			{
				SendKey(key);
			}
		}
	}
}

void COnscreenKeyboardDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	OnLButtonDown(nFlags, point);
}

BOOL COnscreenKeyboardDlg::PreTranslateMessage(MSG* pMsg) 
{
	HWND wnd = ::GetForegroundWindow();
	if(IsWindow(wnd))
	{
		if(wnd != this->m_hWnd)
		{
			if(gFocus != wnd)
			{
				if(IsWindow(gFocus))
				{
					AttachThreadInput(
						GetWindowThreadProcessId(m_hWnd,NULL),
						GetWindowThreadProcessId(gFocus,NULL),
						FALSE);
				}

				gFocus = wnd;
				AttachThreadInput(
					GetWindowThreadProcessId(m_hWnd,NULL),
					GetWindowThreadProcessId(gFocus,NULL),
					TRUE);
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void COnscreenKeyboardDlg::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	OnLButtonDown(nFlags, point);
}

void COnscreenKeyboardDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	OnLButtonDown(nFlags, point);
}

void COnscreenKeyboardDlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseFocus();
}

BOOL COnscreenKeyboardDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	ReleaseFocus();
	return TRUE;
}

void COnscreenKeyboardDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseFocus();
}

void COnscreenKeyboardDlg::ReleaseFocus() 
{
	if(IsWindow(gFocus))
	{
		HWND wnd = ::GetForegroundWindow();
		if(IsWindow(wnd))
		{
			if(wnd == gFocus)
			{
				return;
			}
		}
		::SetForegroundWindow(gFocus);
		::SetFocus(gFocus);
	}
}

void COnscreenKeyboardDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(IsWindow(m_hWnd))
	{
		if(cKeys.GetCount())
		{
			CalcWidthHeight();
			Invalidate();
		}
	}
}

void COnscreenKeyboardDlg::OnOK() 
{
	ShowWindow(SW_HIDE);
}

void COnscreenKeyboardDlg::OnCancel() 
{
	ShowWindow(SW_HIDE);
}

void COnscreenKeyboardDlg::OnShowKeyboard() 
{
	ShowWindow(SW_SHOW);
}

void COnscreenKeyboardDlg::OnUpdateShowKeyboard(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!IsWindowVisible());
}

void COnscreenKeyboardDlg::OnHideKeyboard() 
{
	ShowWindow(SW_HIDE);
}

void COnscreenKeyboardDlg::OnUpdateHideKeyboard(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsWindowVisible());
}

void COnscreenKeyboardDlg::OnExit() 
{
	POSITION pos = cKeys.GetHeadPosition();
	while(pos)
	{
		delete cKeys.GetNext(pos);
	}

	int state = DescribeKeyState();
	if(state & 0x01) keybd_event(VK_CAPITAL,0,KEYEVENTF_KEYUP,0);
	if(state & 0x02) keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
	if(state & 0x04) keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);

	CDialog::OnOK();
}

void COnscreenKeyboardDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	if(bShow)
	{
		cSystray.SetMenuDefaultItem(IDM_HIDE_KEYBOARD, FALSE);
	}
	else
	{
		cSystray.SetMenuDefaultItem(IDM_SHOW_KEYBOARD, FALSE);
	}
}

int COnscreenKeyboardDlg::DescribeKeyState() 
{
	int state = 0;
	short ks;
	ks = GetKeyState(VK_CAPITAL);
	if(ks & 0x000F) state += 0x01;
	ks = GetKeyState(VK_SHIFT);
	if(ks & 0xF000) state += 0x02;
	ks = GetKeyState(VK_CONTROL);
	if(ks & 0xF000) state += 0x04;
	return state;
}

void COnscreenKeyboardDlg::DrawKeyboard()
{
	CClientDC dc(this);
	CRect client;
	GetClientRect(client);
	CRgn clipRgn;
	clipRgn.CreateRectRgnIndirect(&client);
	dc.SelectClipRgn(&clipRgn);
	dc.SelectObject(GetStockObject(DEFAULT_GUI_FONT));
	dc.SetBkMode(TRANSPARENT);
	int x = 0;
	int y = -pKeyHeight;
	KEYDEF * key;
	POSITION pos = cKeys.GetHeadPosition();
	cCurrentKeyState = DescribeKeyState();
	int state = cCurrentKeyState;
	while(pos)
	{
		key = cKeys.GetNext(pos);
		if((key->cNormal == 0x00) && (key->cShifted == 0x00))
		{
			x = 0;
			y += pKeyHeight;
		}
		else
		{
			int width = ((abs(key->cWidth) * pKeyWidth) / 10);
			CRect rc(x,y,x + width, y + pKeyHeight);
			x += width;
			if(key->cWidth < 0)
			{
				rc.right = client.right; 
			}
			BOOL hilight = FALSE;
			if(key->cNormal == 0x00)
			{
				switch(key->cShifted)
				{
				case CAPSLOCK:
					if(state & 0x01)
					{
						hilight = TRUE;
					}
					break;
				case SHIFT:
					if(state & 0x02)
					{
						hilight = TRUE;
					}
					break;
				case CTRL:
					if(state & 0x04)
					{
						hilight = TRUE;
					}
					break;
				default:
					break;
				}
			}
			DrawKey(&dc, rc, key, hilight);
		}
	}
}

long x = 0;
void COnscreenKeyboardDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_ID)
	{
		int state = DescribeKeyState();
		if(state != cCurrentKeyState)
		{
			DrawKeyboard();
		}
	}
}
