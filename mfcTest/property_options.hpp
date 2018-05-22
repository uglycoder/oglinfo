//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once


#include <initializer_list>
#include <string>
#include <unordered_map>
#include <utility>

#include <oglinfo/interface/ogl_info.hpp>

namespace gridproperties_ns
{
  using WGL = OGL_Info_ns::WGL_ATTRIBS;

  struct pixel_property_t
  {
    WGL  const            attrib;
    wchar_t const * const propName;
    std::wstring    const description;

    std::wstring    const defaultOption;
    std::unordered_map<std::wstring, int> const options;

    wchar_t const * const editMask{};
    wchar_t const * const editTemplate{};
    wchar_t const * const validChars{};
  };

  constexpr wchar_t const * TRUE_STR{ L"True" };
  constexpr wchar_t const * FALSE_STR{ L"False" };
  constexpr wchar_t const * const DEFAULT_OPTION_STR{ L"Not selected" };
  std::wstring const DEFAULT_DESC_STR{ L"One of: " + std::wstring{DEFAULT_OPTION_STR} };
  std::wstring const BOOLEAN_DESC_STR{ DEFAULT_DESC_STR + L", " + TRUE_STR + L", " + FALSE_STR };

#define DECL_BOOL_PROPERTY(name, propname) pixel_property_t const name{ WGL::name##_ARB, propname, BOOLEAN_DESC_STR, DEFAULT_OPTION_STR, {{TRUE_STR, 1}, {FALSE_STR, 0}, { DEFAULT_OPTION_STR , -1}}}
  DECL_BOOL_PROPERTY(DRAW_TO_WINDOW,      L"Draw to Window");
  DECL_BOOL_PROPERTY(DRAW_TO_BITMAP,      L"Draw to Bitmap");
  DECL_BOOL_PROPERTY(NEED_PALETTE,        L"Need Palette");
  DECL_BOOL_PROPERTY(NEED_SYSTEM_PALETTE, L"Need System Palette");
  DECL_BOOL_PROPERTY(SWAP_LAYER_BUFFERS,  L"Swap Layer Buffers");
  DECL_BOOL_PROPERTY(SHARE_DEPTH,         L"Share Depth");
  DECL_BOOL_PROPERTY(SHARE_STENCIL,       L"Share Stencil");
  DECL_BOOL_PROPERTY(SHARE_ACCUM,         L"Share Accum");
  DECL_BOOL_PROPERTY(SUPPORT_GDI,         L"Support GDI");
  DECL_BOOL_PROPERTY(SUPPORT_OPENGL,      L"Support OpenGL");
  DECL_BOOL_PROPERTY(DOUBLE_BUFFER,       L"Double Buffer");
  DECL_BOOL_PROPERTY(STEREO,              L"Stereo");
#undef DECL_BOOL_PROPERTY

  pixel_property_t const ACCELERATION{
    WGL::ACCELERATION_ARB
    ,L"Acceleration"
    ,DEFAULT_DESC_STR + L", None, Generic, Full" 
    ,DEFAULT_OPTION_STR
    ,{ { DEFAULT_OPTION_STR, -1}
    ,{L"None", static_cast<int>(WGL::NO_ACCELERATION_ARB)}
    ,{L"Generic", static_cast<int>(WGL::GENERIC_ACCELERATION_ARB)}
    ,{L"Full", static_cast<int>(WGL::FULL_ACCELERATION_ARB)} }
  };

  pixel_property_t const SWAP_METHOD{
    WGL::SWAP_METHOD_ARB
    , L"Swap Method"
    , DEFAULT_DESC_STR + L", Undefined, Exchange, Copy"
    , DEFAULT_OPTION_STR
    ,{ { DEFAULT_OPTION_STR, -1 }
    ,{ L"Undefined", static_cast<int>(WGL::SWAP_UNDEFINED_ARB) }
    ,{ L"Exchange", static_cast<int>(WGL::SWAP_EXCHANGE_ARB) }
    ,{ L"Copy", static_cast<int>(WGL::SWAP_COPY_ARB) } }
  };

  pixel_property_t const PIXEL_TYPE{
    WGL::PIXEL_TYPE_ARB
    , L"Pixel Type"
    , DEFAULT_DESC_STR + L", RGBA, Color Index"
    , DEFAULT_OPTION_STR
    ,{ { DEFAULT_OPTION_STR, -1 }
    ,{ L"RGBA", static_cast<int>(WGL::TYPE_RGBA_ARB) }
    ,{ L"Color Index", static_cast<int>(WGL::TYPE_COLORINDEX_ARB) } }
  };

#define DECL_INTEGER_PROPERTY(name, propname) pixel_property_t const name{ WGL::name##_ARB, propname, L"Enter integer in range [0, 999]: a zero number, a space or an empty editbox indicates 'Not selected'", L"0", {}, L"ddd", L"___",  L"0123456789"}
  DECL_INTEGER_PROPERTY(NUMBER_OVERLAYS,  L"Number of Overlays");
  DECL_INTEGER_PROPERTY(NUMBER_UNDERLAYS, L"Number of Underlays");
  DECL_INTEGER_PROPERTY(COLOR_BITS,       L"Color Bits");
  DECL_INTEGER_PROPERTY(RED_BITS,         L"Red Bits");
  DECL_INTEGER_PROPERTY(GREEN_BITS,       L"Green Bits");
  DECL_INTEGER_PROPERTY(BLUE_BITS,        L"Blue Bits");
  DECL_INTEGER_PROPERTY(ALPHA_BITS,       L"Alpha Bits");
  DECL_INTEGER_PROPERTY(ACCUM_BITS,       L"Accum Bits");
  DECL_INTEGER_PROPERTY(ACCUM_RED_BITS,   L"Accum Red Bits");
  DECL_INTEGER_PROPERTY(ACCUM_GREEN_BITS, L"Accum Green Bits");
  DECL_INTEGER_PROPERTY(ACCUM_BLUE_BITS,  L"Accum Blue Bits");
  DECL_INTEGER_PROPERTY(ACCUM_ALPHA_BITS, L"Accum Alpha Bits");
  DECL_INTEGER_PROPERTY(DEPTH_BITS,       L"Depth Bits");
  DECL_INTEGER_PROPERTY(STENCIL_BITS,     L"Stencil Bits");
  DECL_INTEGER_PROPERTY(AUX_BUFFERS,      L"Aux Buffers");
  DECL_INTEGER_PROPERTY(SAMPLE_BUFFERS,   L"Sample Buffers");
  DECL_INTEGER_PROPERTY(SAMPLES,          L"Samples");
#undef DECL_INTEGER_PROPERTY

  std::initializer_list<pixel_property_t const *> const optionProps =
  {
     &DRAW_TO_WINDOW       ,&DRAW_TO_BITMAP     ,&NEED_PALETTE
    ,&NEED_SYSTEM_PALETTE  ,&SWAP_LAYER_BUFFERS ,&SHARE_DEPTH
    ,&SHARE_STENCIL        ,&SHARE_ACCUM        ,&SUPPORT_GDI
    ,&SUPPORT_OPENGL       ,&DOUBLE_BUFFER      ,&STEREO
    ,&ACCELERATION         ,&SWAP_METHOD        ,&PIXEL_TYPE
    ,&NUMBER_OVERLAYS      ,&NUMBER_UNDERLAYS   ,&COLOR_BITS
    ,&RED_BITS             ,&GREEN_BITS         ,&BLUE_BITS
    ,&ALPHA_BITS           ,&ACCUM_BITS         ,&ACCUM_RED_BITS
    ,&ACCUM_GREEN_BITS     ,&ACCUM_BLUE_BITS    ,&ACCUM_ALPHA_BITS
    ,&DEPTH_BITS           ,&STENCIL_BITS       ,&AUX_BUFFERS
    ,&SAMPLE_BUFFERS       ,&SAMPLES
  };


  CMFCPropertyGridProperty * buildContextProperties();
  CMFCPropertyGridProperty * buildPixelProperties();

  OGL_Info_ns::contextAttribs_t GetContextData(CMFCPropertyGridProperty & prop);
  OGL_Info_ns::pixelAttribs_t   GetPixelData(CMFCPropertyGridProperty & prop);
}