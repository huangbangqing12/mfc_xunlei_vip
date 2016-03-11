
// mfc_xunlei_vipDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "UrlFile.h"


typedef struct
{
	CListCtrl *p_list_ctrl;
	UrlFile *url_file;
}PARAMETER;   //�����̲߳����ṹ

// Cmfc_xunlei_vipDlg �Ի���
class Cmfc_xunlei_vipDlg : public CDialogEx
{
// ����
public:
	Cmfc_xunlei_vipDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_XUNLEI_VIP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list_ctrol;  //�б��ؼ�
	UrlFile m_url_file;  //��������url�ļ��Ķ���
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonExport();
	static char xlvip_ini[3][256];  //�����ʼ������
	afx_msg void OnBnClickedButtonCpyAcc();
	afx_msg void OnBnClickedButtonCpyPwd();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawListAccount(NMHDR *pNMHDR, LRESULT *pResult);
};
