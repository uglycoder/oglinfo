
// mfcTestDlg.cpp : implementation file
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#include "stdafx.h"

#include <initializer_list>
#include <utility>

#include "mfcTest.hpp"
#include "mfcTestDlg.hpp"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
  void HidePropertySheetButtons(CPropertySheet & pSheet);
  void ResizePropertySheet(CPropertySheet & pSheet);
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmfcTestDlg dialog



CmfcTestDlg::CmfcTestDlg(
  OGL_Info_ns::driverInfo const & drvrInfo
  ,CWnd* pParent /*=nullptr*/, unsigned int iSelectPage /*= 0*/)
	:
  m_drvrPage{ drvrInfo }
  ,CPropertySheet(IDS_PSHEET_CAPTION, pParent, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_NOCONTEXTHELP;

  m_drvrPage.Construct(IDD_DRVR_INFO_PPAGE);
  m_choosePixelFmtPage.Construct(IDD_CHOOSE_PIXEL_FORMAT_PPAGE);
  m_queryPixelFmtPage.Construct(IDD_QUERY_PIXEL_FORMAT_PPAGE);

  AddPage(&m_drvrPage);
  AddPage(&m_choosePixelFmtPage);
  AddPage(&m_queryPixelFmtPage);
}


void CmfcTestDlg::DoDataExchange(CDataExchange* pDX)
{
  CPropertySheet::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcTestDlg, CPropertySheet)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CmfcTestDlg message handlers

BOOL CmfcTestDlg::OnInitDialog()
{
  CPropertySheet::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
  HidePropertySheetButtons(*this);
  ResizePropertySheet(*this);

  m_drvrPage.loadOGLInfo();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmfcTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
    CPropertySheet::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmfcTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
    CPropertySheet::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmfcTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CmfcTestDlg::PreTranslateMessage(MSG* pMsg)
{
  // TODO: Add your specialized code here and/or call the base class
  if(pMsg->message == WM_KEYDOWN)
  {
    if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
    {
      pMsg->wParam = NULL;
    }
  }
  return CPropertySheet::PreTranslateMessage(pMsg);
}

// ############################################################################

namespace
{
  void HidePropertySheetButtons(CPropertySheet & pSheet)
  {
    for(auto const & id : { IDOK, IDCANCEL, IDHELP })
    {
      pSheet.GetDlgItem(id)->ShowWindow(SW_HIDE);
    }
  }

  void ResizePropertySheet(CPropertySheet & pSheet)
  {
    CRect rcButton{};
    pSheet.GetDlgItem(IDOK)->GetWindowRect(&rcButton);

    CRect rcPSheet{};
    pSheet.GetWindowRect(&rcPSheet);
    pSheet.SetWindowPos(
      nullptr
      , 0, 0
      , rcPSheet.Width()
      , rcPSheet.Height() - rcButton.Height() - 5
      , SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE
    );
  }
}
