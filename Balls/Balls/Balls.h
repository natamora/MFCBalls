
// Balls.h : main header file for the Balls application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBallsApp:
// See Balls.cpp for the implementation of this class
//

class CBallsApp : public CWinApp
{
public:
	CBallsApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBallsApp theApp;
