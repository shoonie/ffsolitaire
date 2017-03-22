
// FFSolitaire.h : main header file for the FFSolitaire application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFFSolitaireApp:
// See FFSolitaire.cpp for the implementation of this class
//

class CFFSolitaireApp : public CWinApp
{
public:
	CFFSolitaireApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFFSolitaireApp theApp;
