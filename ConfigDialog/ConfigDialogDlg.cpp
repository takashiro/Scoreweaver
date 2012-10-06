
// ConfigDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ConfigDialog.h"
#include "ConfigDialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CConfigDialogDlg 对话框




CConfigDialogDlg::CConfigDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigDialogDlg::IDD, pParent)
	, input_prompt(0)
	, dy_adjust_frequency(0)
	, input_style(0)
	, embed_languagebar(0)
	, next_page(0)
	{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//初始化成员变量
	this->dy_adjust_frequency=0;
	this->embed_languagebar=0;
	this->input_prompt=0;
	this->input_style=0;
	this->next_page=0;

	sec_input_prompt= L"input prompt";
	sec_dy_adjust_frequency=L"dynamic adjust frequency";
	sec_input_style=L"input style";
	sec_embed_languagebar=L"embed languagebar";
	sec_next_page=L"next page";

	key_input_prompt=L"input_prompt";
	key_dy_adjust_frequency=L"dy_adjust_frequency";
	key_input_style=L"input_style";
	key_embed_languagebar=L"embed_languagebar";
	key_next_page=L"next_page";
}

void CConfigDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CConfigDialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CConfigDialogDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CConfigDialogDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CConfigDialogDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CConfigDialogDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CConfigDialogDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CConfigDialogDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CConfigDialogDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CConfigDialogDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CConfigDialogDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDOK, &CConfigDialogDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CHECK1, &CConfigDialogDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CConfigDialogDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CConfigDialogDlg 消息处理程序

BOOL CConfigDialogDlg::OnInitDialog()
{
   
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	this->readconfig(); //初始化对话框中的radio button 的状态

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CConfigDialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CConfigDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CConfigDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//输入提示  无字根
void CConfigDialogDlg::OnBnClickedRadio1()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->input_prompt=1;
	}

//输入提示  提示字根
void CConfigDialogDlg::OnBnClickedRadio2()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->input_prompt=2;
	}

//输入提示 联想候选字
void CConfigDialogDlg::OnBnClickedRadio3()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->input_prompt=3;
	}

//调整词频 是
void CConfigDialogDlg::OnBnClickedRadio4()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->dy_adjust_frequency=1;
	}

//调整词频  否
void CConfigDialogDlg::OnBnClickedRadio5()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->dy_adjust_frequency=2;
	}

//输入风格 立即出字
void CConfigDialogDlg::OnBnClickedRadio6()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->input_style=1;
	}

//输入风格 按空格后出字
void CConfigDialogDlg::OnBnClickedRadio7()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->input_style=2;
	}

//嵌入语言栏   是
void CConfigDialogDlg::OnBnClickedRadio8()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->embed_languagebar=1;
	}

//嵌入语言栏  否
void CConfigDialogDlg::OnBnClickedRadio9()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->embed_languagebar=2;
	}


// 读取配置文件初始化对话框
void CConfigDialogDlg::readconfig(void)
	{

	wchar_t strBuff[256];
	//CString strFilePath=L"C:\\Users\\wtp\\Desktop\\config.ini";
	CString strFilePath;
	HWND   hWnd=*AfxGetMainWnd();
	
	GetCurrentDirectory(256,strBuff);  //获取当前路径
	strFilePath.Format(_T("%s//config.ini"),strBuff);
	
	this->dy_adjust_frequency=::GetPrivateProfileIntW(sec_dy_adjust_frequency,key_dy_adjust_frequency,0,strFilePath);
	switch(this->dy_adjust_frequency)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO4,IDC_RADIO5,IDC_RADIO4);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO4,IDC_RADIO5,IDC_RADIO5);
		break;
	default:
		break;
		}
	
	this->embed_languagebar=::GetPrivateProfileIntW(sec_embed_languagebar,key_embed_languagebar,0,strFilePath);
	switch(this->embed_languagebar)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO8,IDC_RADIO9,IDC_RADIO8);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO8,IDC_RADIO9,IDC_RADIO9);
	default:
		break;
		}

	this->input_prompt=::GetPrivateProfileIntW(sec_input_prompt,key_input_prompt,0,strFilePath);
	switch(this->input_prompt)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO1);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO2);
		break;
	case 3:
		::CheckRadioButton(hWnd,IDC_RADIO1,IDC_RADIO3,IDC_RADIO3);
		break;
	default:
		break;
		}

	this->input_style=::GetPrivateProfileIntW( sec_input_style,key_input_style,0,strFilePath);
	switch(this->input_style)
		{
	case 1:
		::CheckRadioButton(hWnd,IDC_RADIO6,IDC_RADIO7,IDC_RADIO6);
		break;
	case 2:
		::CheckRadioButton(hWnd,IDC_RADIO6,IDC_RADIO7,IDC_RADIO7);
		break;
	default:
		break;
		}

	this->next_page=::GetPrivateProfileIntW(sec_next_page,key_next_page,0,strFilePath);
	switch(this->next_page)
		{
	case 1:
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(true);
		break;
	case 2:
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);
		break;
	case 3:
		((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(true);
		((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);
		break;
	default:
		break;
		}
	}


// 分析对话框内容并更新配置文件
void CConfigDialogDlg::writeconfig(void)
	{

	CString val_input_prompt;
	CString val_dy_adjust_frequency;
	CString val_input_style;
	CString val_embed_languagebar;
	CString val_next_page;
	
	wchar_t strBuff[256];
	//CString strFilePath=L"C:\\Users\\wtp\\Desktop\\config.ini";
	CString strFilePath;
	
	GetCurrentDirectory(256,strBuff);  //获取当前路径
	strFilePath.Format(_T("%s//config.ini"),strBuff);

	val_input_prompt.Format(_T("%d"),this->input_prompt);
	::WritePrivateProfileString(sec_input_prompt,key_input_prompt,val_input_prompt,strFilePath);  //写入ini文件中相应字段

	val_dy_adjust_frequency.Format(_T("%d"),this->dy_adjust_frequency);
	::WritePrivateProfileString(sec_dy_adjust_frequency,key_dy_adjust_frequency,val_dy_adjust_frequency,strFilePath);

	val_input_style.Format(_T("%d"),this->input_style);
	::WritePrivateProfileString(sec_input_style,key_input_style,val_input_style,strFilePath); 

	val_embed_languagebar.Format(_T("%d"),this->embed_languagebar);
	::WritePrivateProfileString(sec_embed_languagebar,key_embed_languagebar,val_embed_languagebar,strFilePath); 

	val_next_page.Format(_T("%d"),this->next_page);
	::WritePrivateProfileString(sec_next_page,key_next_page,val_next_page,strFilePath); 

}

void CConfigDialogDlg::OnBnClickedOk()
	{
	// TODO: 在此添加控件通知处理程序代码
	this->writeconfig();
	CDialogEx::OnOK();
	}


void CConfigDialogDlg::OnBnClickedCheck1()
	{
	// TODO: 在此添加控件通知处理程序代码
	if(this->next_page==0||this->next_page==2)
		this->next_page+=1;
	else if(this->next_page==1||this->next_page==3)
		this->next_page-=1;
	}


void CConfigDialogDlg::OnBnClickedCheck2()
	{
	// TODO: 在此添加控件通知处理程序代码
	if(this->next_page==0||this->next_page==1)
		this->next_page+=2;
	else if(this->next_page==2||this->next_page==3)
		this->next_page-=2;
	}
