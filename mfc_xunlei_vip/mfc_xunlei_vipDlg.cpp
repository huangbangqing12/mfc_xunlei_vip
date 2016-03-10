
// mfc_xunlei_vipDlg.cpp : ʵ���ļ�
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cmfc_xunlei_vipDlg �Ի���


char Cmfc_xunlei_vipDlg::xlvip_ini[3][256] = {"\0", "\0", "\0"};
Cmfc_xunlei_vipDlg::Cmfc_xunlei_vipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_XUNLEI_VIP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//************* ��ȡini�����ļ�***************
	//  ��ʼ����ҳURL "NULL"��ʾ��ȡ�����Ͳ�������
	GetPrivateProfileString("MAIN_PAGE_URL", "INDEX_URL",
		"NULL", xlvip_ini[0], 256, "../ini/profile.ini");
	//  ��ʼ��VIPҳ��URL  "NULL"��ʾ��ȡ�����Ͳ�������
	GetPrivateProfileString("XL_VIP_URL", "VIP_URL",
		"NULL", xlvip_ini[1], 256, "../ini/profile.ini");
	//  ��ʼ��������ʽ "NULL"��ʾ��ȡ�����Ͳ�������
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


// Cmfc_xunlei_vipDlg ��Ϣ�������

BOOL Cmfc_xunlei_vipDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//��ʼ��list�ؼ�
	m_list_ctrol.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_list_ctrol.InsertColumn(0, "Ѹ��VIP�˺�", LVCFMT_LEFT, 180);
	m_list_ctrol.InsertColumn(1, "����", LVCFMT_LEFT, 180);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cmfc_xunlei_vipDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cmfc_xunlei_vipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//////////////////////////////////////////////////////////////////////////
///                      �̴߳�����:
///      �����ڸ�list�ؼ��������Ŀ̫��ʱ,��ɳ�����濨��,Ϊ�˽���������,�ڴ�
///      ʹ���̴߳�������������list�ؼ��в����ȡ����VIP������,�������̴߳���
///      �Ͳ��Ῠ����.
//////////////////////////////////////////////////////////////////////////
void ThreadFunc(LPVOID pParam)
{
    PARAMETER *p_parameter = (PARAMETER *)pParam;  //�Զ����̲߳����ṹ,������Ҫ�Ĳ���
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int item_count = p_parameter->p_list_ctrl->GetItemCount();  //��ȡlist�ؼ�����Ŀ��
	if (item_count) {
		p_parameter->p_list_ctrl->DeleteAllItems();
		item_count = 0;
	}
	
	//     ץȡ�ṩVIP��վ����ҳ����ȡ������û����������б�
	//     ��ȷ���Լ�������ʱ��ͬ��ǰ������ʱ��������Ժ���ܻ����Ϊ�����ȡʱ�䣩

	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);  //��ȡϵͳʱ��--->���Ϊ����
	timeinfo = localtime(&rawtime);  //ת����tm�ṹ

	char cur_day[32];
	char yesterday[32];
	strftime(cur_day, 32, "%Y-%m-%d", timeinfo);  //��ʽ��ʱ���ַ���

	rawtime = rawtime - 24 * 3600;
	strftime(yesterday, 32, "%Y-%m-%d", localtime(&rawtime));

	//  ��521xunleiҳ��ȥ��ȡvip�ʺ�

	std::string str_xlvip_html(Cmfc_xunlei_vipDlg::xlvip_ini[0]);
	std::string str_vipid_html;
	//  ͨ��curl�Ᵽ��ץȡ������ҳ�ļ�
	p_parameter->url_file->url2file(str_xlvip_html.c_str(), "index.html");

	char update_html_reg[256];
	sprintf(update_html_reg, Cmfc_xunlei_vipDlg::xlvip_ini[1], cur_day);
	std::regex e(update_html_reg);
	std::ifstream infile("index.html");
	std::string line;
	std::smatch m;
	//    ��ȡ�����vip�ʺ�ҳ��
	bool cur_day_flag = false;
	while (getline(infile, line)) {
		if (std::regex_search(line, m, e)) {
			str_vipid_html = m.format("$1");
			cur_day_flag = true;
			break;
		}
	}

	//  ��ȡ�����vip�ʺ�ҳ��
	if (!cur_day_flag) {
		sprintf(update_html_reg, Cmfc_xunlei_vipDlg::xlvip_ini[1], yesterday);
		e = update_html_reg;
		infile.clear();
		infile.seekg(std::ios_base::beg);

		while (getline(infile, line)) {
			if (std::regex_search(line, m, e)) {
				//$1 ��ʾ��һ�����񵽷���,���������е�һ��С����ƥ�������,�������Դ�����.
				str_vipid_html = m.format("$1");
				break;
			}
		}

	}

	str_xlvip_html = str_xlvip_html + "/" + str_vipid_html;
	//  ��urlָ����ļ�����
	p_parameter->url_file->url2file(str_xlvip_html.c_str(), str_vipid_html.c_str());

	// ��VIP�ʺ�ҳ���ȡ �ʺź�����
	std::ifstream vipid_file(str_vipid_html.c_str(), std::ios::in);
	if (!vipid_file.is_open()) {
		AfxMessageBox("���ļ�VIPҳ��ʧ��");
		return;
	}

	std::regex vipid_reg(Cmfc_xunlei_vipDlg::xlvip_ini[2]);
	while (getline(vipid_file, line)) {
		if (std::regex_search(line, m, vipid_reg)) {
			// $1��ʾ��һ��������,Ҳ���������е�һ��С����ƥ�䵽������
			p_parameter->p_list_ctrl->InsertItem(item_count, (m.format("$1")).c_str());  //�����˺�
			p_parameter->p_list_ctrl->SetItemText(item_count, 1, (m.format("$2")).c_str());  //��������
			item_count++;
		}
	}

	infile.close();
	vipid_file.close();
	AfxEndThread(1);  //�����߳�
}

void Cmfc_xunlei_vipDlg::OnBnClickedButtonGet()
{

	PARAMETER *p_parameter = new PARAMETER;  //�Զ����̲߳����ṹ
	p_parameter->p_list_ctrl = &m_list_ctrol;  //�б��ؼ�
	p_parameter->url_file = &m_url_file;  //����url�ļ��Ķ���
	//    ��������list�ؼ��߳�
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFunc, p_parameter, 0, NULL);
}


void Cmfc_xunlei_vipDlg::OnBnClickedButtonExport()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	size_t item_count = m_list_ctrol.GetItemCount();
	if (item_count == 0) {
		AfxMessageBox("VIP�б�Ϊ��,���ȡ���ٱ���");
		return;
	}
	CFileDialog xlvip_dlg(FALSE, "txt");  //���������ļ��Ի���  "txt"������ʾĬ���ļ���׺��
	xlvip_dlg.m_ofn.lpstrFilter = "txt files(*.txt)|*.txt||";
	xlvip_dlg.m_ofn.lpstrTitle = "����Ѹ��VIP";

	if (xlvip_dlg.DoModal() == IDOK) {
		std::ofstream xlvip_file(xlvip_dlg.GetPathName(), std::ios::out);
		if (!xlvip_file.is_open()) {
			AfxMessageBox("�����ļ�ʧ��,δ֪����!");
			return ;
		}
		// VIPд���ļ�
		xlvip_file << "Ѹ��VIP�˺�"  << "\t\t" << "����" << std::endl;
		for (size_t i = 0; i < item_count; i++) {
		   xlvip_file << m_list_ctrol.GetItemText(i, 0) << "\t\t"  //д��VIP�˺�
			  << m_list_ctrol.GetItemText(i, 1) << std::endl;  //д������
		}
		xlvip_file.close();
		AfxMessageBox("����ɹ�");
	}
}


void Cmfc_xunlei_vipDlg::OnBnClickedButtonCpyAcc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cur_sel = m_list_ctrol.GetSelectionMark();
	if (cur_sel == -1)
	{
		AfxMessageBox("��ѡ��һ���ٸ���!");
		return;
	}
	CString account;  //�����˺�
	account = m_list_ctrol.GetItemText(cur_sel, 0);
	HGLOBAL hClip;     //������������ڴ��
	CloseClipboard();  //�رռ��а�,�ͷż��а���Դ��ռ��Ȩ
	if (OpenClipboard())
	{
		EmptyClipboard();
		hClip = GlobalAlloc(GMEM_MOVEABLE, account.GetLength() + 1);
		char *buff;
		buff = (char *)GlobalLock(hClip);  // ���ڴ�����
		strcpy(buff, account);             //�������ݵ��ڴ��
		GlobalUnlock(hClip);               //����д�����,���н���
		SetClipboardData(CF_TEXT, hClip);  //���ڴ�������а���Դ������
		CloseClipboard();  //�رռ��а�,�ͷż��а���Դ��ռ��Ȩ
	}
}


void Cmfc_xunlei_vipDlg::OnBnClickedButtonCpyPwd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int cur_sel = m_list_ctrol.GetSelectionMark();
	if (cur_sel == -1)
	{
		AfxMessageBox("��ѡ��һ���ٸ���!");
		return;
	}
	CString password;  //��������
	password = m_list_ctrol.GetItemText(cur_sel, 1);
	HGLOBAL hClip;     //������������ڴ��
	CloseClipboard();  //�رռ��а�,�ͷż��а���Դ��ռ��Ȩ
	if (OpenClipboard())
	{
		EmptyClipboard();
		hClip = GlobalAlloc(GMEM_MOVEABLE, password.GetLength() + 1);
		char *buff;
		buff = (char *)GlobalLock(hClip);  // ���ڴ�����
		strcpy(buff, password);             //�������ݵ��ڴ��
		GlobalUnlock(hClip);               //����д�����,���н���
		SetClipboardData(CF_TEXT, hClip);  //���ڴ�������а���Դ������
		CloseClipboard();  //�رռ��а�,�ͷż��а���Դ��ռ��Ȩ
	}
}


BOOL Cmfc_xunlei_vipDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	static bool m_ctrl_down = false;  //�˺�����һ�ε��õ�ʱ���ʼ��
	int col = -1;  //ѡ���е��к�
	if (pMsg->message == WM_KEYDOWN)
	{

		switch (pMsg->wParam)
		{
			//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A) �����ִ�Сд
		case 'C':  //Ctrl + C
			if (m_ctrl_down)
			{
				col = 0;  //�˺���
			}
			break;
		case 'F':
			if (m_ctrl_down)
			{
				col = 1;  //������
			}
			break;
		case VK_CONTROL:
			m_ctrl_down = true; return TRUE;
		default:
			return TRUE;
		}

		//   �����˺Ż�������
		int cur_sel = m_list_ctrol.GetSelectionMark();
		if (cur_sel == -1)
		{
			AfxMessageBox("��ѡ��һ���ٸ���!");
			return false;
		}
		CString cpy;
		cpy = m_list_ctrol.GetItemText(cur_sel, col);
		HGLOBAL hClip;     //������������ڴ��
		CloseClipboard();  //�رռ��а�,�ͷż��а���Դ��ռ��Ȩ
		if (OpenClipboard())
		{
			EmptyClipboard();
			hClip = GlobalAlloc(GMEM_MOVEABLE, cpy.GetLength() + 1);
			char *buff;
			buff = (char *)GlobalLock(hClip);  // ���ڴ�����
			strcpy(buff, cpy);             //�������ݵ��ڴ��
			GlobalUnlock(hClip);               //����д�����,���н���
			SetClipboardData(CF_TEXT, hClip);  //���ڴ�������а���Դ������
			CloseClipboard();  //�رռ��а�,�ͷż��а���Դ��ռ��Ȩ
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

	// TODO:  �ڴ˸��� DC ���κ�����
	switch (pWnd->GetDlgCtrlID())
	{
	   case IDC_STATIC_C:
	   case IDC_STATIC_F:
       pDC->SetTextColor(RGB(255, 0, 0));
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
