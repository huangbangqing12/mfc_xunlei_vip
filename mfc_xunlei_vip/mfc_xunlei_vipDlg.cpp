
// mfc_xunlei_vipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc_xunlei_vip.h"
#include "mfc_xunlei_vipDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <cstring>
#include <sstream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma warning (disable:4996)
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_xunlei_vipDlg 对话框


char Cmfc_xunlei_vipDlg::xlvip_ini[3][256] = {"\0", "\0", "\0"};
Cmfc_xunlei_vipDlg::Cmfc_xunlei_vipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_XUNLEI_VIP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//************* 读取ini配置文件***************
	//  初始化主页URL "NULL"表示读取不到就不做处理
	GetPrivateProfileString("MAIN_PAGE_URL", "INDEX_URL",
		"NULL", xlvip_ini[0], 256, "../ini/profile.ini");
	//  初始化VIP页面URL  "NULL"表示读取不到就不做处理
	GetPrivateProfileString("XL_VIP_URL", "VIP_URL",
		"NULL", xlvip_ini[1], 256, "../ini/profile.ini");
	//  初始化正则表达式 "NULL"表示读取不到就不做处理
	GetPrivateProfileString("REGEX", "REG",
		"NULL", xlvip_ini[2], 256, "../ini/profile.ini");
}

void Cmfc_xunlei_vipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ACCOUNT, m_list_ctrol);
}

BEGIN_MESSAGE_MAP(Cmfc_xunlei_vipDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GET, &Cmfc_xunlei_vipDlg::OnBnClickedButtonGet)
	ON_BN_CLICKED(IDC_BUTTON_EXPORT, &Cmfc_xunlei_vipDlg::OnBnClickedButtonExport)
//	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &Cmfc_xunlei_vipDlg::OnBnClickedButtonClear)
//	ON_BN_CLICKED(IDC_BUTTON_QUITE, &Cmfc_xunlei_vipDlg::OnBnClickedButtonQuite)
ON_BN_CLICKED(IDC_BUTTON_CPY_ACC, &Cmfc_xunlei_vipDlg::OnBnClickedButtonCpyAcc)
ON_BN_CLICKED(IDC_BUTTON_CPY_PWD, &Cmfc_xunlei_vipDlg::OnBnClickedButtonCpyPwd)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Cmfc_xunlei_vipDlg 消息处理程序

BOOL Cmfc_xunlei_vipDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//初始化list控件
	m_list_ctrol.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list_ctrol.InsertColumn(0, "迅雷VIP账号", LVCFMT_LEFT, 180);
	m_list_ctrol.InsertColumn(1, "密码", LVCFMT_LEFT, 180);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmfc_xunlei_vipDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmfc_xunlei_vipDlg::OnPaint()
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
HCURSOR Cmfc_xunlei_vipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
///                      线程处理函数:
///      由于在给list控件插入的条目太多时,造成程序界面卡死,为了解决这个问题,在此
///      使用线程处理来函数来向list控件中插入获取到的VIP和密码,这样主线程窗口
///      就不会卡死了.
//////////////////////////////////////////////////////////////////////////
void ThreadFunc(LPVOID pParam)
{
    PARAMETER *p_parameter = (PARAMETER *)pParam;  //自定义线程参数结构,传递需要的参数
	// TODO: 在此添加控件通知处理程序代码
	int item_count = p_parameter->p_list_ctrl->GetItemCount();  //获取list控件中条目数
	if (item_count) {
		p_parameter->p_list_ctrl->DeleteAllItems();
		item_count = 0;
	}
	
	//     抓取提供VIP网站的网页，获取当天的用户名和密码列表
	//     请确保自己机器的时间同当前的日期时间相符（以后可能会更新为网络获取时间）

	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);  //获取系统时间--->结果为秒数
	timeinfo = localtime(&rawtime);  //转换成tm结构

	char cur_day[32];
	char yesterday[32];
	strftime(cur_day, 32, "%Y-%m-%d", timeinfo);  //格式化时间字符串

	rawtime = rawtime - 24 * 3600;
	strftime(yesterday, 32, "%Y-%m-%d", localtime(&rawtime));

	//  到521xunlei页面去获取vip帐号

	std::string str_xlvip_html(Cmfc_xunlei_vipDlg::xlvip_ini[0]);
	std::string str_vipid_html;
	//  通过curl库保存抓取到的主页文件
	p_parameter->url_file->url2file(str_xlvip_html.c_str(), "index.html");

	char update_html_reg[256];
	sprintf(update_html_reg, Cmfc_xunlei_vipDlg::xlvip_ini[1], cur_day);
	std::regex e(update_html_reg);
	std::ifstream infile("index.html");
	std::string line;
	std::smatch m;
	//    获取今天的vip帐号页面
	bool cur_day_flag = false;
	while (getline(infile, line)) {
		if (std::regex_search(line, m, e)) {
			str_vipid_html = m.format("$1");
			cur_day_flag = true;
			break;
		}
	}

	//  获取昨天的vip帐号页面
	if (!cur_day_flag) {
		sprintf(update_html_reg, Cmfc_xunlei_vipDlg::xlvip_ini[1], yesterday);
		e = update_html_reg;
		infile.clear();
		infile.seekg(std::ios_base::beg);

		while (getline(infile, line)) {
			if (std::regex_search(line, m, e)) {
				//$1 表示第一个捕获到分组,即在正则中第一个小括号匹配的内容,其他的以此类推.
				str_vipid_html = m.format("$1");
				break;
			}
		}

	}

	str_xlvip_html = str_xlvip_html + "/" + str_vipid_html;
	//  将url指向的文件保存
	p_parameter->url_file->url2file(str_xlvip_html.c_str(), str_vipid_html.c_str());

	// 从VIP帐号页面获取 帐号和密码
	std::ifstream vipid_file(str_vipid_html.c_str(), std::ios::in);
	if (!vipid_file.is_open()) {
		AfxMessageBox("打开文件VIP页面失败");
		return;
	}

	std::regex vipid_reg(Cmfc_xunlei_vipDlg::xlvip_ini[2]);
	while (getline(vipid_file, line)) {
		if (std::regex_search(line, m, vipid_reg)) {
			// $1表示第一个捕获组,也就是正则中第一个小括号匹配到的内容
			p_parameter->p_list_ctrl->InsertItem(item_count, (m.format("$1")).c_str());  //插入账号
			p_parameter->p_list_ctrl->SetItemText(item_count, 1, (m.format("$2")).c_str());  //插入密码
			item_count++;
		}
	}

	infile.close();
	vipid_file.close();
	AfxEndThread(1);  //结束线程
}

void Cmfc_xunlei_vipDlg::OnBnClickedButtonGet()
{

	PARAMETER *p_parameter = new PARAMETER;  //自定义线程参数结构
	p_parameter->p_list_ctrl = &m_list_ctrol;  //列表框控件
	p_parameter->url_file = &m_url_file;  //保存url文件的对象
	//    创建插入list控件线程
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, p_parameter, 0, NULL);
}


void Cmfc_xunlei_vipDlg::OnBnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	size_t item_count = m_list_ctrol.GetItemCount();
	if (item_count == 0) {
		AfxMessageBox("VIP列表为空,请获取后再保存");
		return;
	}
	CFileDialog xlvip_dlg(FALSE, "txt");  //创建保存文件对话框  "txt"参数表示默认文件后缀名
	xlvip_dlg.m_ofn.lpstrFilter = "txt files(*.txt)|*.txt||";
	xlvip_dlg.m_ofn.lpstrTitle = "导出迅雷VIP";

	if (xlvip_dlg.DoModal() == IDOK) {
		std::ofstream xlvip_file(xlvip_dlg.GetPathName(), std::ios::out);
		if (!xlvip_file.is_open()) {
			AfxMessageBox("保存文件失败,未知错误!");
			return ;
		}
		// VIP写入文件
		xlvip_file << "迅雷VIP账号"  << "\t\t" << "密码" << std::endl;
		for (size_t i = 0; i < item_count; i++) {
		   xlvip_file << m_list_ctrol.GetItemText(i, 0) << "\t\t"  //写入VIP账号
			  << m_list_ctrol.GetItemText(i, 1) << std::endl;  //写入密码
		}
		xlvip_file.close();
		AfxMessageBox("保存成功");
	}
}


void Cmfc_xunlei_vipDlg::OnBnClickedButtonCpyAcc()
{
	// TODO: 在此添加控件通知处理程序代码
	int cur_sel = m_list_ctrol.GetSelectionMark();
	if (cur_sel == -1)
	{
		AfxMessageBox("请选中一行再复制!");
		return;
	}
	CString account;  //保存账号
	account = m_list_ctrol.GetItemText(cur_sel, 0);
	HGLOBAL hClip;     //句柄变量分配内存块
	CloseClipboard();  //关闭剪切板,释放剪切板资源的占用权
	if (OpenClipboard())
	{
		EmptyClipboard();
		hClip = GlobalAlloc(GMEM_MOVEABLE, account.GetLength() + 1);
		char *buff;
		buff = (char *)GlobalLock(hClip);  // 对内存块加锁
		strcpy(buff, account);             //复制数据到内存块
		GlobalUnlock(hClip);               //数据写入完毕,进行解锁
		SetClipboardData(CF_TEXT, hClip);  //将内存块放入剪切板资源管理中
		CloseClipboard();  //关闭剪切板,释放剪切板资源的占用权
	}
}


void Cmfc_xunlei_vipDlg::OnBnClickedButtonCpyPwd()
{
	// TODO: 在此添加控件通知处理程序代码
	int cur_sel = m_list_ctrol.GetSelectionMark();
	if (cur_sel == -1)
	{
		AfxMessageBox("请选中一行再复制!");
		return;
	}
	CString password;  //保存密码
	password = m_list_ctrol.GetItemText(cur_sel, 1);
	HGLOBAL hClip;     //句柄变量分配内存块
	CloseClipboard();  //关闭剪切板,释放剪切板资源的占用权
	if (OpenClipboard())
	{
		EmptyClipboard();
		hClip = GlobalAlloc(GMEM_MOVEABLE, password.GetLength() + 1);
		char *buff;
		buff = (char *)GlobalLock(hClip);  // 对内存块加锁
		strcpy(buff, password);             //复制数据到内存块
		GlobalUnlock(hClip);               //数据写入完毕,进行解锁
		SetClipboardData(CF_TEXT, hClip);  //将内存块放入剪切板资源管理中
		CloseClipboard();  //关闭剪切板,释放剪切板资源的占用权
	}
}


BOOL Cmfc_xunlei_vipDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	static bool m_ctrl_down = false;  //此函数第一次调用的时候初始化
	int col = -1;  //选中行的列号
	if (pMsg->message == WM_KEYDOWN)
	{

		switch (pMsg->wParam)
		{
			//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A) 不区分大小写
		case 'C':  //Ctrl + C
			if (m_ctrl_down)
			{
				col = 0;  //账号列
			}
			break;
		case 'F':
			if (m_ctrl_down)
			{
				col = 1;  //密码列
			}
			break;
		case VK_CONTROL:
			m_ctrl_down = true; return TRUE;
		default:
			return TRUE;
		}

		//   复制账号或者密码
		int cur_sel = m_list_ctrol.GetSelectionMark();
		if (cur_sel == -1)
		{
			AfxMessageBox("请选中一行再复制!");
			return false;
		}
		CString cpy;
		cpy = m_list_ctrol.GetItemText(cur_sel, col);
		HGLOBAL hClip;     //句柄变量分配内存块
		CloseClipboard();  //关闭剪切板,释放剪切板资源的占用权
		if (OpenClipboard())
		{
			EmptyClipboard();
			hClip = GlobalAlloc(GMEM_MOVEABLE, cpy.GetLength() + 1);
			char *buff;
			buff = (char *)GlobalLock(hClip);  // 对内存块加锁
			strcpy(buff, cpy);             //复制数据到内存块
			GlobalUnlock(hClip);               //数据写入完毕,进行解锁
			SetClipboardData(CF_TEXT, hClip);  //将内存块放入剪切板资源管理中
			CloseClipboard();  //关闭剪切板,释放剪切板资源的占用权
		}
	}

	if (pMsg->message == WM_KEYUP)
	{
		switch (pMsg->wParam)
		{
		case VK_CONTROL:
			m_ctrl_down = false; return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);

}


HBRUSH Cmfc_xunlei_vipDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	switch (pWnd->GetDlgCtrlID())
	{
	   case IDC_STATIC_C:
	   case IDC_STATIC_F:
       pDC->SetTextColor(RGB(255, 0, 0));
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
