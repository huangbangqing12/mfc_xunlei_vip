
// mfc_xunlei_vip.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmfc_xunlei_vipApp: 
// �йش����ʵ�֣������ mfc_xunlei_vip.cpp
//

class Cmfc_xunlei_vipApp : public CWinApp
{
public:
	Cmfc_xunlei_vipApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmfc_xunlei_vipApp theApp;