
// mfc_xunlei_vipDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "UrlFile.h"


typedef struct
{
	CListCtrl *p_list_ctrl;
	UrlFile *url_file;
}PARAMETER;   //传递线程参数结构

// Cmfc_xunlei_vipDlg 对话框
class Cmfc_xunlei_vipDlg : public CDialogEx
{
// 构造
public:
	Cmfc_xunlei_vipDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_XUNLEI_VIP_DIALOG };
#endif

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
	CListCtrl m_list_ctrol;  //列表框控件
	UrlFile m_url_file;  //用来保存url文件的对象
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonExport();
	static char xlvip_ini[3][256];  //程序初始化数据
	afx_msg void OnBnClickedButtonCpyAcc();
	afx_msg void OnBnClickedButtonCpyPwd();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawListAccount(NMHDR *pNMHDR, LRESULT *pResult);
};
