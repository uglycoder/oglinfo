//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once

#include "COGLPropertyGrid.hpp"

// CChoosePixelFormatPage dialog

class CChoosePixelFormatPage final : public CPropertyPage
{
	DECLARE_DYNAMIC(CChoosePixelFormatPage)

public:
  BOOL OnInitDialog() override;

  afx_msg void OnClickedCpfChooseFmtsBtn();
  afx_msg void OnClickedCpfCheckPixelFormatButton();

  // Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHOOSE_PIXEL_FORMAT_PPAGE};
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

private:
  COGLPropertyGrid m_oglPropertyGrid;

	DECLARE_MESSAGE_MAP()  
};
