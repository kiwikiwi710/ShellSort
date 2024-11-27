
// ShellSort.h : main header file for the ShellSort application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CShellSortApp:
// See ShellSort.cpp for the implementation of this class
//

class CShellSortApp : public CWinApp
{
public:
	CShellSortApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CShellSortApp theApp;
