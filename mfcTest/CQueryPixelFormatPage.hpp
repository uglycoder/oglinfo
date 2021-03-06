//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once

#include "COGLPropertyGrid.hpp"


// CQueryPixelFormatPage dialog

class CQueryPixelFormatPage final : public CPropertyPage
{
	DECLARE_DYNAMIC(CQueryPixelFormatPage)

public:
  BOOL OnInitDialog() override;
  

  // Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUERY_PIXEL_FORMAT_PPAGE};
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

private:
  afx_msg void OnBnClickedQpfQueryBtn();

  COGLPropertyGrid m_oglPropertyGrid;

	DECLARE_MESSAGE_MAP()
};
