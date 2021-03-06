// CChoosePixelFormatPage.cpp : implementation file
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#include "stdafx.h"
#include "CChoosePixelFormatPage.hpp"

#include <cassert>

#include <string>

#include <oglinfo/interface/ogl_info.hpp>

#include "resource.h"
#include "mfc_utils.hpp"
#include "property_options.hpp"



// CChoosePixelFormatPage dialog

IMPLEMENT_DYNAMIC(CChoosePixelFormatPage, CPropertyPage)

void CChoosePixelFormatPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BOOL CChoosePixelFormatPage::OnInitDialog()
{
  CPropertyPage::OnInitDialog();

  // TODO:  Add extra initialization here
  m_oglPropertyGrid.EnableDescriptionArea();

  // Calculate size and position of grid control- between top of dlg and top of choose button
  auto const & chooseBtn{GetDlgItem(IDC_CPF_CHOOSE_FMTS_BTN)};
  CRect btnPos{};
  chooseBtn->GetWindowRect(&btnPos);
  ScreenToClient(&btnPos);
  CRect gridPos{};
  GetClientRect(&gridPos);
  gridPos.bottom = btnPos.top - 10;

  m_oglPropertyGrid.Create(WS_VISIBLE | WS_CHILD, gridPos, this, 1);
  m_oglPropertyGrid.loadProperties();

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(CChoosePixelFormatPage, CPropertyPage)
  ON_BN_CLICKED(IDC_CPF_CHOOSE_FMTS_BTN, &CChoosePixelFormatPage::OnClickedCpfChooseFmtsBtn)
  ON_BN_CLICKED(IDC_CPF_CHECK_PIXEL_FORMAT_BUTTON, &CChoosePixelFormatPage::OnClickedCpfCheckPixelFormatButton)
END_MESSAGE_MAP()

// CChoosePixelFormatPage message handlers

void CChoosePixelFormatPage::OnClickedCpfChooseFmtsBtn()
{
  // TODO: Add your control notification handler code here
  assert(m_oglPropertyGrid.GetPropertyCount() > 0 && "CMFCPropertyGridCtrl should have at east 1 top level property");

  auto const & contextProp{ m_oglPropertyGrid.GetProperty(0) };
  auto const & contextData{ gridproperties_ns::GetContextData(*contextProp)};

  auto const & pixelProp{ m_oglPropertyGrid.GetProperty(1) };
  auto const & pixelData{ gridproperties_ns::GetPixelData(*pixelProp) };

  auto const & pixelFormats{ OGL_Info_ns::ChoosePixelFormats(contextData, pixelData, 1000) };

  auto const & numFmtsStatic{ GetDlgItem(IDC_CPF_NUM_PIXFMTS_STATIC) };
  numFmtsStatic->SetWindowTextW(L"");
  auto const & listBox{static_cast<CListBox*>(GetDlgItem(IDC_CPF_CHOSEN_PIXEL_FMTS_LIST))};
  listBox->ResetContent();
  if(pixelFormats.succeeded)
  {
    numFmtsStatic->SetWindowTextW(std::to_wstring(pixelFormats.formats.size()).c_str());
    for(auto const & pixelFormat : pixelFormats.formats)
    {
      listBox->AddString(std::to_wstring(pixelFormat).c_str());
    }
    ::SetColumnWidth(*listBox);
  }
  else
  {
    listBox->AddString(CString(pixelFormats.errorStr.c_str()));
    ::SetColumnWidth(*listBox);
  }
}


void CChoosePixelFormatPage::OnClickedCpfCheckPixelFormatButton()
{
  // TODO: Add your control notification handler code here
  CStringW editTxt;
  GetDlgItemTextW(IDC_CPF_PIXEL_FORMAT_NUMBER_EDIT, editTxt);
  if(editTxt.GetLength() > 0)
  {
    auto const number{ std::stoi(editTxt.operator LPCWSTR()) };
    auto const result{OGL_Info_ns::CheckPixelFormat(number)};

    CStringW const errStr(result.second.c_str());
    SetDlgItemTextW(IDC_CPF_CHECK_RESULT_STATIC, result.first ? L"PASS" : errStr);
  }
  else
  {
    SetDlgItemTextW(IDC_CPF_CHECK_RESULT_STATIC, L"Please enter a non-zero number");
  }
}
