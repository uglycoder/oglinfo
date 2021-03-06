// CQueryPixelFormatPage.cpp : implementation file
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter


#include "stdafx.h"
#include "CQueryPixelFormatPage.hpp"

#include <map>
#include <string>
#include <vector>

#include "mfc_utils.hpp"
#include "property_options.hpp"
#include "resource.h"
#


// CQueryPixelFormatPage dialog

IMPLEMENT_DYNAMIC(CQueryPixelFormatPage, CPropertyPage)

void CQueryPixelFormatPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CQueryPixelFormatPage, CPropertyPage)
  ON_BN_CLICKED(IDC_QPF_QUERY_BTN, &CQueryPixelFormatPage::OnBnClickedQpfQueryBtn)
END_MESSAGE_MAP()


// CQueryPixelFormatPage message handlers


BOOL CQueryPixelFormatPage::OnInitDialog()
{
  CPropertyPage::OnInitDialog();

  // TODO:  Add extra initialization here
  m_oglPropertyGrid.EnableDescriptionArea();

  // Calculate size and position of grid control
  auto const editBox{ GetDlgItem(IDC_QPF_PXL_NUMBER_EDIT) };
  CRect editPos{};
  editBox->GetWindowRect(&editPos);
  ScreenToClient(&editPos);

  CRect gridPos{};
  GetClientRect(&gridPos);
  gridPos.bottom = editPos.top - 10;

  m_oglPropertyGrid.Create(WS_VISIBLE | WS_CHILD, gridPos, this, 1);
  m_oglPropertyGrid.loadProperties(true, false); // context properties only required

  auto const attribList{static_cast<CListBox*>(GetDlgItem(IDC_QPF_PIXEL_ATTRIBUTES_LIST))};

  for(auto prop: gridproperties_ns::optionProps)
  {
    auto const index{ attribList->AddString(prop->propName) };
    attribList->SetItemDataPtr(index, (void*)prop);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
                // EXCEPTION: OCX Property Pages should return FALSE
}

void CQueryPixelFormatPage::OnBnClickedQpfQueryBtn()
{
  // TODO: Add your control notification handler code here
  try
  {
    SetDlgItemTextW(IDC_QPF_ERROR_STATIC, L"");
    auto const & attribValueList{ static_cast<CListBox*>(GetDlgItem(IDC_QPF_PIXEL_ATTRIBUTE_VALUES_LIST)) };
    attribValueList->ResetContent();

    auto const & contextProp{ m_oglPropertyGrid.GetProperty(0) };
    auto const & contextData{ gridproperties_ns::GetContextData(*contextProp) };

    CStringW pxFmtNumStr;
    GetDlgItemTextW(IDC_QPF_PXL_NUMBER_EDIT, pxFmtNumStr);

    auto const & pixFmtNum{ std::stoi(pxFmtNumStr.operator LPCWSTR()) };

    auto const & attribList{ static_cast<CListBox*>(GetDlgItem(IDC_QPF_PIXEL_ATTRIBUTES_LIST)) };
    auto const & selectionCount{ attribList->GetSelCount() };
    std::vector indexList(selectionCount, 0);
    attribList->GetSelItems(selectionCount, indexList.data());
    std::map<OGL_Info_ns::WGL_ATTRIBS, CStringW> attribNameMap;
    OGL_Info_ns::attribList_t attribSet;
    for(auto const & idx : indexList)
    {
      auto const & itemData{ (gridproperties_ns::pixel_property_t const*)attribList->GetItemDataPtr(idx) };
      attribSet.emplace(itemData->attrib);
      attribNameMap[itemData->attrib] = itemData->propName;
    }

    auto const & pixelFormatDetails{ OGL_Info_ns::QueryPixelFormat(pixFmtNum, contextData, attribSet) };
    if(pixelFormatDetails.succeeded)
    {
      for(auto const  [attrib, fmtNum]: pixelFormatDetails.results)
      {
        // try to line up values
        auto const attribNameFieldSize{28};
        auto const & attribName{ attribNameMap[attrib]};
        auto const & attribNameLength{attribName.GetLength()};
        std::wstring const padStr(attribNameFieldSize - attribNameLength, L' ');
        auto const & attribValuePair{ OGL_Info_ns::GetWGL_AttributeStrings({attrib, fmtNum}) };
        CStringW str{ attribName + padStr.c_str() + L"\t" + CStringW(attribValuePair.second.c_str()) };
        attribValueList->AddString(str);
      }
      ::SetHorizontalExtentForLongestString(*attribValueList);
    }
    else
    {
      SetDlgItemTextW(IDC_QPF_ERROR_STATIC, CStringW(pixelFormatDetails.errorStr.c_str()));
    }
  }
  catch(...)
  {
    SetDlgItemTextW(IDC_QPF_ERROR_STATIC, L"Unknown error occurred.");
  }
}
