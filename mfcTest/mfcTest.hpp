
// mfcTest.h : main header file for the PROJECT_NAME application
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter


#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CmfcTestApp:
// See mfcTest.cpp for the implementation of this class
//

class CmfcTestApp final : public CWinApp
{
public:
	explicit CmfcTestApp();

// Overrides
public:
	BOOL InitInstance() override;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CmfcTestApp theApp;
