
// HackerTools.h: Main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "Include 'stdafx.h' before including this file for PCH generation"
#endif

#include "resource.h"		// Main symbols


// CHackerToolsApp:
// See HackerTools.cpp for the implementation of this class
//

class CHackerToolsApp : public CWinApp
{
public:
	CHackerToolsApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CHackerToolsApp theApp;
