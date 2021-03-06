//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once

#include <oglinfo/interface/ogl_info.hpp>


// CDrvrInfoPage dialog

class CDrvrInfoPage final : public CPropertyPage
{
	DECLARE_DYNAMIC(CDrvrInfoPage)

public:
	explicit CDrvrInfoPage(OGL_Info_ns::driverInfo const & drvrInfo);

  void loadOGLInfo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRVR_INFO_PPAGE};
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

private:
  void loadStaticText() const;
  void loadListBoxes();

  OGL_Info_ns::driverInfo m_drvrInfo;

  CListBox m_oglExtList;
  CListBox m_wglExtList;

	DECLARE_MESSAGE_MAP()
};
