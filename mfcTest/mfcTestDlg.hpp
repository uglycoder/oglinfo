
// mfcTestDlg.hpp : header file
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter


#pragma once


#include <oglinfo/interface/ogl_info.hpp>


#include "CDrvrInfoPage.hpp"
#include "CChoosePixelFormatPage.hpp"
#include "CQueryPixelFormatPage.hpp"

// CmfcTestDlg dialog
class CmfcTestDlg final : public CPropertySheet
{
// Construction
public:
	explicit CmfcTestDlg(
    OGL_Info_ns::driverInfo const & drvrInfo
    ,CWnd* pParent = nullptr, unsigned int iSelectPage = 0);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override;	// DDX/DDV support
  BOOL PreTranslateMessage(MSG* pMsg) override;


// Implementation
	HICON m_hIcon;

	// Generated message map functions
	BOOL OnInitDialog() override;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
  CDrvrInfoPage           m_drvrPage;
  CChoosePixelFormatPage  m_choosePixelFmtPage;
  CQueryPixelFormatPage   m_queryPixelFmtPage;
};
