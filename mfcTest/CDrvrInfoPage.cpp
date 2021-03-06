// CDrvrInfoPage.cpp : implementation file
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter


#include "stdafx.h"

#include "CDrvrInfoPage.hpp"

#include <initializer_list>
#include <string>
#include <utility>


#include "resource.h"
#include "mfc_utils.hpp"


// CDrvrInfoPage dialog

IMPLEMENT_DYNAMIC(CDrvrInfoPage, CPropertyPage)

CDrvrInfoPage::CDrvrInfoPage(OGL_Info_ns::driverInfo const & drvrInfo)
	:
  m_drvrInfo{drvrInfo}
  ,CPropertyPage()
{
}

void CDrvrInfoPage::loadStaticText() const
{
  for(auto const & [text, ids] :
    { std::make_pair(&m_drvrInfo.vendor,IDC_VENDOR_STATIC)
    , std::make_pair(&m_drvrInfo.version,IDC_VERSION_STATIC)
    , std::make_pair(&m_drvrInfo.renderer,IDC_RENDERER_STATIC) })
  {
    GetDlgItem(ids)->SetWindowTextW(CStringW{ text->c_str() });
  }

  for(auto const & [vec, ids] :
    { std::make_pair(&m_drvrInfo.oglExtensions,IDC_NUM_OGLEXTS_STATIC)
    , std::make_pair(&m_drvrInfo.wglExtensions,IDC_NUM_WGLEXTS_STATIC) })
  {
    auto const & wStr{ std::to_wstring(vec->size()) };
    GetDlgItem(ids)->SetWindowTextW(wStr.c_str());
  }

  auto wStr{ std::to_wstring(m_drvrInfo.major_ver) };
  wStr += L'.' + std::to_wstring(m_drvrInfo.minor_ver);
  GetDlgItem(IDC_VERSION_NUMBER_STATIC)->SetWindowTextW(wStr.c_str());

  wStr = std::to_wstring(m_drvrInfo.numSupportedPixelFormats);
  GetDlgItem(IDC_NUM_PIX_FMTS_STATIC)->SetWindowTextW(wStr.c_str());
}

void CDrvrInfoPage::loadListBoxes()
{
  for(auto const & [vec, listbox] :
    { std::make_pair(&m_drvrInfo.oglExtensions, &m_oglExtList)
    , std::make_pair(&m_drvrInfo.wglExtensions, &m_wglExtList) })
  {
    for(auto const & item : *vec)
    {
      listbox->AddString(CStringW{ item.c_str() });
    }
    ::SetHorizontalExtentForLongestString(*listbox);
  }
}

void CDrvrInfoPage::loadOGLInfo()
{
  loadStaticText();

  loadListBoxes();
 }

void CDrvrInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_OGL_EXTS_LIST, m_oglExtList);
  DDX_Control(pDX, IDC_WGL_EXTS_LIST, m_wglExtList);
}


BEGIN_MESSAGE_MAP(CDrvrInfoPage, CPropertyPage)
END_MESSAGE_MAP()


// CDrvrInfoPage message handlers



