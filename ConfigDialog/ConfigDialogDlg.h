
// ConfigDialogDlg.h : 头文件
//

#pragma once


// CConfigDialogDlg 对话框
class CConfigDialogDlg : public CDialogEx
{
// 构造
public:
	CConfigDialogDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CONFIGDIALOG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	// 读取配置文件初始化对话框
	void readconfig(void);
	// 分析对话框内容并更新配置文件
	void writeconfig(void);
private:
	// 输入提示，值为1表示无提示，值为2表示提示字根，值为3表示联想候选字，初始值为0.
	int input_prompt;
	// 动态调整词频，值为1表示是，值为2表示否，初始值为0。
	int dy_adjust_frequency;
	// 输入风格，值为1表示立即出字，值为2表示按空格出字，初始值为0。
	int input_style;
	// 状态栏嵌入语言栏，值为1表示是，值为2表示否，初始值为0；
	int embed_languagebar;

	CString sec_input_prompt;
	CString sec_dy_adjust_frequency;
	CString sec_input_style;
	CString sec_embed_languagebar;
	CString sec_next_page;

	CString key_input_prompt;
	CString key_dy_adjust_frequency;
	CString key_input_style;
	CString key_embed_languagebar;
	CString key_next_page;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
private:
	// 翻页，值为1时表示按加号等号进行翻页，值为2是表示按逗号句号进行翻页，值为3时表示2者都可以。
	int next_page;
	};
