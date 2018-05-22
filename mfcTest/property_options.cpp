//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#include "stdafx.h"

#include <cassert>

#include "property_options.hpp"

#include <string>


CMFCPropertyGridProperty * gridproperties_ns::buildContextProperties()
{
  auto const pGroupContext = new CMFCPropertyGridProperty(_T("Context"));

  using WGLCT = OGL_Info_ns::WGL_CONTEXT_NAMES;

  auto prop = new CMFCPropertyGridProperty(
    L"Major Version"
    , L"1"
    , L"Enter integer in range [1-5]"
    , static_cast<DWORD_PTR>(WGLCT::MAJOR_VERSION_ARB)
    , L"d"
    , L"_"
    , L"12345");
  pGroupContext->AddSubItem(prop);
  prop = new CMFCPropertyGridProperty(
    L"Minor Version"
    , L"0"
    , L"Enter integer in range [0-7]"
    , static_cast<DWORD_PTR>(WGLCT::MINOR_VERSION_ARB)
    , L"d"
    , L"_"
    , L"01234567");
  pGroupContext->AddSubItem(prop);

  prop = new CMFCPropertyGridProperty(
    L"Layer Plane"
    , L"0"
    , L"Enter integer in range [0-9]"
    , static_cast<DWORD_PTR>(WGLCT::LAYER_PLANE_ARB)
    , L"d"
    , L"_"
    , L"0123456789");
  pGroupContext->AddSubItem(prop);

  prop = new CMFCPropertyGridProperty(
    L"Debug"
    , COleVariant(VARIANT_FALSE, VT_BOOL)
    , L"Select True to request an OpenGL debugging context"
    , static_cast<DWORD_PTR>(WGLCT::FLAGS_ARB));
  pGroupContext->AddSubItem(prop);

  prop = new CMFCPropertyGridProperty(
    L"Forward Compatibility"
    , COleVariant(VARIANT_FALSE, VT_BOOL)
    , L"Select True to request an OpenGL forward compatibility context"
    , static_cast<DWORD_PTR>(WGLCT::FLAGS_ARB));
  pGroupContext->AddSubItem(prop);

  prop = new CMFCPropertyGridProperty(
    L"Core Profile"
    , COleVariant(VARIANT_TRUE, VT_BOOL)
    , L"Select True to request an OpenGL core profile context"
    , static_cast<DWORD_PTR>(WGLCT::PROFILE_MASK_ARB));
  pGroupContext->AddSubItem(prop);

  prop = new CMFCPropertyGridProperty(
    L"Compatibility Profile"
    , COleVariant(VARIANT_FALSE, VT_BOOL)
    , L"Select True to request an OpenGL compatibility profile context."
    , static_cast<DWORD_PTR>(WGLCT::PROFILE_MASK_ARB));
  pGroupContext->AddSubItem(prop);

  return pGroupContext;
}

CMFCPropertyGridProperty * gridproperties_ns::buildPixelProperties()
{
  auto const pGroupPixel = new CMFCPropertyGridProperty(_T("Pixel"));

  auto const CreateProperty = [](gridproperties_ns::pixel_property_t const & prop)
  {
    auto const mfcProp = new CMFCPropertyGridProperty(
      prop.propName
      , prop.defaultOption.c_str()
      , prop.description.c_str()
      , reinterpret_cast<DWORD_PTR>(&prop)
      , prop.editMask
      , prop.editTemplate
      , prop.validChars
    );

    for(auto const & opt : prop.options)
    {
      mfcProp->AddOption(opt.first.c_str());
    }

    mfcProp->AllowEdit(prop.editMask ? TRUE : FALSE);
    return mfcProp;
  };

  for(auto const & prop : gridproperties_ns::optionProps)
  {
    auto const & mfcProp{ CreateProperty(*prop) };
    pGroupPixel->AddSubItem(mfcProp);
  }

  return pGroupPixel;
}

OGL_Info_ns::contextAttribs_t gridproperties_ns::GetContextData(CMFCPropertyGridProperty & prop)
{
  assert(std::wstring{ prop.GetName() } == L"Context");
  assert(prop.GetSubItemsCount() == 7);

  using WGLCT = OGL_Info_ns::WGL_CONTEXT_NAMES;
  auto const & majorVersionStr{ prop.GetSubItem(0)->GetValue().bstrVal };
  assert(prop.GetSubItem(0)->GetData() == static_cast<int>(WGLCT::MAJOR_VERSION_ARB));

  auto const & minorVersionStr{ prop.GetSubItem(1)->GetValue().bstrVal };
  assert(prop.GetSubItem(1)->GetData() == static_cast<int>(WGLCT::MINOR_VERSION_ARB));

  auto const & layerPlaneStr{ prop.GetSubItem(2)->GetValue().bstrVal };
  assert(prop.GetSubItem(2)->GetData() == static_cast<int>(WGLCT::LAYER_PLANE_ARB));

  auto const & debug{ prop.GetSubItem(3)->GetValue().boolVal == VARIANT_TRUE };
  assert(prop.GetSubItem(3)->GetData() == static_cast<int>(WGLCT::FLAGS_ARB));

  auto const & forwardComp{ prop.GetSubItem(4)->GetValue().boolVal == VARIANT_TRUE };
  assert(prop.GetSubItem(4)->GetData() == static_cast<int>(WGLCT::FLAGS_ARB));

  auto const & coreProfile{ prop.GetSubItem(5)->GetValue().boolVal };
  assert(prop.GetSubItem(5)->GetData() == static_cast<int>(WGLCT::PROFILE_MASK_ARB));

  auto const & compProfile{ prop.GetSubItem(6)->GetValue().boolVal == VARIANT_TRUE };
  assert(prop.GetSubItem(6)->GetData() == static_cast<int>(WGLCT::PROFILE_MASK_ARB));

  auto const & majorVersion{ std::make_pair(WGLCT::MAJOR_VERSION_ARB  ,std::stoi(majorVersionStr)) };
  auto const & minorVersion{ std::make_pair(WGLCT::MINOR_VERSION_ARB  ,std::stoi(minorVersionStr)) };
  auto const & layerPlane{ std::make_pair(WGLCT::LAYER_PLANE_ARB      ,std::stoi(layerPlaneStr)) };

  namespace OGL = OGL_Info_ns;
  auto const & debugFlagValue   { debug       ? OGL::WGL_CONTEXT_DEBUG_BIT_ARB : 0 };
  auto const & fwdCompFlagValue { forwardComp ? OGL::WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB : 0 };
  auto const & flagBits         { debugFlagValue | fwdCompFlagValue };

  auto const & flags{ std::make_pair(WGLCT::FLAGS_ARB, flagBits) };

  auto const & coreProfileFlagValue { coreProfile ? OGL::WGL_CONTEXT_CORE_PROFILE_BIT_ARB : 0 };
  auto const & compProfileFlagValue { compProfile ? OGL::WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : 0 };
  auto const & profileBits          { coreProfileFlagValue | compProfileFlagValue };

  auto const & prof{ std::make_pair(WGLCT::PROFILE_MASK_ARB, profileBits) };

  return { majorVersion ,minorVersion ,layerPlane, flags, prof };
}

OGL_Info_ns::pixelAttribs_t gridproperties_ns::GetPixelData(CMFCPropertyGridProperty & prop)
{
  assert(std::wstring{ prop.GetName() } == L"Pixel");
  auto const subItemCount{ prop.GetSubItemsCount() };
  assert(subItemCount == 32);

  OGL_Info_ns::pixelAttribs_t pixelAttribs;

  for(int n{}; n < subItemCount; ++n)
  {
    auto const & propInfo{*reinterpret_cast<gridproperties_ns::pixel_property_t*>(prop.GetSubItem(n)->GetData())};

    std::wstring const value{ CString{ prop.GetSubItem(n)->GetValue().bstrVal } };

    if(!propInfo.editMask)
    {
      if(propInfo.defaultOption != value)
      {
        pixelAttribs.emplace(propInfo.attrib, propInfo.options.at(value.c_str()));
      }
    }
    else
    {      
      try
      {
        auto const & defaultNumber{ std::stoi(propInfo.defaultOption) };
        auto const & valueNumber{ std::stoi(value) };
        if(defaultNumber != valueNumber)
        {
          pixelAttribs.emplace(propInfo.attrib, valueNumber);
        }
      }
      catch(...)
      {
        // do nothing
      }
    }
  }
  return pixelAttribs;
}

