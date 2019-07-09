
// SingleStudentSystem.h: SingleStudentSystem 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号
#include"Student.h"


// CSingleStudentSystemApp:
// 有关此类的实现，请参阅 SingleStudentSystem.cpp
//

class CSingleStudentSystemApp : public CWinAppEx
{
public:
	CSingleStudentSystemApp() noexcept;
	Head HD = new Node;
	Management MG;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
// 实现
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSingleStudentSystemApp theApp;
