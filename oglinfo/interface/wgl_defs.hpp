//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once

#include <utility>

namespace OGL_Info_ns
{
  // See https://www.khronos.org/registry/OpenGL/extensions/ARB/WGL_ARB_pixel_format.txt
  // and https://www.khronos.org/registry/OpenGL/extensions/ARB/ARB_multisample.txt
  enum class WGL_ATTRIBS
  {
    //Attribute                                 Type        Match Criteria

    NUMBER_PIXEL_FORMATS_ARB      = 0x2000  //              ignored                 
    , DRAW_TO_WINDOW_ARB          = 0x2001  //  boolean     exact                    
    , DRAW_TO_BITMAP_ARB          = 0x2002  //  boolean     exact
    , ACCELERATION_ARB            = 0x2003  //  enum        exact
    , NEED_PALETTE_ARB            = 0x2004  //  boolean     exact
    , NEED_SYSTEM_PALETTE_ARB     = 0x2005  //  boolean     exact
    , SWAP_LAYER_BUFFERS_ARB      = 0x2006  //  boolean     exact
    , SWAP_METHOD_ARB             = 0x2007  //  enum        exact
    , NUMBER_OVERLAYS_ARB         = 0x2008  //  integer     minimum
    , NUMBER_UNDERLAYS_ARB        = 0x2009  //  integer     minimum
    , TRANSPARENT_ARB             = 0x200A  //              ignored
    , TRANSPARENT_RED_VALUE_ARB   = 0x2037  //              ignored
    , TRANSPARENT_GREEN_VALUE_ARB = 0x2038  //              ignored
    , TRANSPARENT_BLUE_VALUE_ARB  = 0x2039  //              ignored
    , TRANSPARENT_ALPHA_VALUE_ARB = 0x203A  //              ignored
    , TRANSPARENT_INDEX_VALUE_ARB = 0x203B  //              ignored
    , SHARE_DEPTH_ARB             = 0x200C  //  boolean     exact
    , SHARE_STENCIL_ARB           = 0x200D  //  boolean     exact
    , SHARE_ACCUM_ARB             = 0x200E  //  boolean     exact
    , SUPPORT_GDI_ARB             = 0x200F  //  boolean     exact
    , SUPPORT_OPENGL_ARB          = 0x2010  //  boolean     exact
    , DOUBLE_BUFFER_ARB           = 0x2011  //  boolean     exact
    , STEREO_ARB                  = 0x2012  //  boolean     exact
    , PIXEL_TYPE_ARB              = 0x2013  //  enum        exact
    , COLOR_BITS_ARB              = 0x2014  //  integer     minimum
    , RED_BITS_ARB                = 0x2015  //  integer     minimum
    , RED_SHIFT_ARB               = 0x2016  //              ignored
    , GREEN_BITS_ARB              = 0x2017  //  integer     minimum
    , GREEN_SHIFT_ARB             = 0x2018  //              ignored
    , BLUE_BITS_ARB               = 0x2019  //  integer     minimum
    , BLUE_SHIFT_ARB              = 0x201A  //              ignored
    , ALPHA_BITS_ARB              = 0x201B  //  integer     minimum
    , ALPHA_SHIFT_ARB             = 0x201C  //              ignored
    , ACCUM_BITS_ARB              = 0x201D  //  integer     minimum
    , ACCUM_RED_BITS_ARB          = 0x201E  //  integer     minimum
    , ACCUM_GREEN_BITS_ARB        = 0x201F  //  integer     minimum
    , ACCUM_BLUE_BITS_ARB         = 0x2020  //  integer     minimum
    , ACCUM_ALPHA_BITS_ARB        = 0x2021  //  integer     minimum
    , DEPTH_BITS_ARB              = 0x2022  //  integer     minimum
    , STENCIL_BITS_ARB            = 0x2023  //  integer     minimum
    , AUX_BUFFERS_ARB             = 0x2024  //  integer     minimum
    , SAMPLE_BUFFERS_ARB          = 0x2041  //  integer     minimum
    , SAMPLES_ARB                 = 0x2042  //  integer     minimum

    // ACCELERATION_ARB enum
    , NO_ACCELERATION_ARB         = 0x2025
    , GENERIC_ACCELERATION_ARB    = 0x2026
    , FULL_ACCELERATION_ARB       = 0x2027

    // SWAP_METHOD_ARB enum
    , SWAP_EXCHANGE_ARB           = 0x2028
    , SWAP_COPY_ARB               = 0x2029
    , SWAP_UNDEFINED_ARB          = 0x202A

    // PIXEL_TYPE_ARB enum
    , TYPE_RGBA_ARB               = 0x202B
    , TYPE_COLORINDEX_ARB         = 0x202C
  };

  enum class WGL_ATTRIBS_VALUE_TYPES
  {
    BOOLEAN, ENUM, INTEGER, IGNORED, UNKNOWN
  };

  // Convenient pixel attribute pairs
  
  constexpr auto DRAW_TO_WINDOW(bool b)       { return std::pair{WGL_ATTRIBS::DRAW_TO_WINDOW_ARB, b}; }
  constexpr auto DRAW_TO_BITMAP(bool b)       { return std::pair{WGL_ATTRIBS::DRAW_TO_BITMAP_ARB, b}; }
  constexpr auto NEED_PALETTE(bool b)         { return std::pair{WGL_ATTRIBS::NEED_PALETTE_ARB, b}; }
  constexpr auto NEED_SYSTEM_PALETTE(bool b)  { return std::pair{WGL_ATTRIBS::NEED_SYSTEM_PALETTE_ARB, b}; }
  constexpr auto SWAP_LAYER_BUFFERS(bool b)   { return std::pair{WGL_ATTRIBS::SWAP_LAYER_BUFFERS_ARB, b}; }
  constexpr auto SHARE_DEPTH(bool b)          { return std::pair{WGL_ATTRIBS::SHARE_DEPTH_ARB, b}; }
  constexpr auto SHARE_STENCIL(bool b)        { return std::pair{WGL_ATTRIBS::SHARE_STENCIL_ARB, b}; }
  constexpr auto SHARE_ACCUM(bool b)          { return std::pair{WGL_ATTRIBS::SHARE_ACCUM_ARB, b}; }
  constexpr auto SUPPORT_GDI(bool b)          { return std::pair{WGL_ATTRIBS::SUPPORT_GDI_ARB, b}; }
  constexpr auto SUPPORT_OPENGL(bool b)       { return std::pair{WGL_ATTRIBS::SUPPORT_OPENGL_ARB, b}; }
  constexpr auto DOUBLE_BUFFER(bool b)        { return std::pair{WGL_ATTRIBS::DOUBLE_BUFFER_ARB, b}; }
  constexpr auto STEREO(bool b)               { return std::pair{WGL_ATTRIBS::STEREO_ARB, b}; }

  constexpr auto NUMBER_OVERLAYS(int i)   { return std::pair{WGL_ATTRIBS::NUMBER_OVERLAYS_ARB, i}; }
  constexpr auto NUMBER_UNDERLAYS(int i)  { return std::pair{WGL_ATTRIBS::NUMBER_UNDERLAYS_ARB, i}; }
  constexpr auto COLOR_BITS(int i)        { return std::pair{WGL_ATTRIBS::COLOR_BITS_ARB, i}; }
  constexpr auto RED_BITS(int i)          { return std::pair{WGL_ATTRIBS::RED_BITS_ARB, i}; }
  constexpr auto GREEN_BITS(int i)        { return std::pair{WGL_ATTRIBS::GREEN_BITS_ARB, i}; }
  constexpr auto BLUE_BITS(int i)         { return std::pair{WGL_ATTRIBS::BLUE_BITS_ARB, i}; }
  constexpr auto ALPHA_BITS(int i)        { return std::pair{WGL_ATTRIBS::ALPHA_BITS_ARB, i}; }
  constexpr auto ACCUM_BITS(int i)        { return std::pair{WGL_ATTRIBS::ACCUM_BITS_ARB, i}; }
  constexpr auto ACCUM_RED_BITS(int i)    { return std::pair{WGL_ATTRIBS::ACCUM_RED_BITS_ARB, i}; }
  constexpr auto ACCUM_GREEN_BITS(int i)  { return std::pair{WGL_ATTRIBS::ACCUM_GREEN_BITS_ARB, i}; }
  constexpr auto ACCUM_BLUE_BITS(int i)   { return std::pair{WGL_ATTRIBS::ACCUM_BLUE_BITS_ARB, i}; }
  constexpr auto ACCUM_ALPHA_BITS(int i)  { return std::pair{WGL_ATTRIBS::ACCUM_ALPHA_BITS_ARB, i}; }
  constexpr auto DEPTH_BITS(int i)        { return std::pair{WGL_ATTRIBS::DEPTH_BITS_ARB, i}; }
  constexpr auto STENCIL_BITS(int i)      { return std::pair{WGL_ATTRIBS::STENCIL_BITS_ARB, i}; }
  constexpr auto AUX_BUFFERS(int i)       { return std::pair{WGL_ATTRIBS::AUX_BUFFERS_ARB, i}; }
  constexpr auto SAMPLE_BUFFERS(int i)    { return std::pair{WGL_ATTRIBS::SAMPLE_BUFFERS_ARB, i}; }
  constexpr auto SAMPLES(int i)           { return std::pair{WGL_ATTRIBS::SAMPLES_ARB, i}; }

  constexpr auto NO_ACCELERATION      {std::pair{WGL_ATTRIBS::ACCELERATION_ARB, (int)WGL_ATTRIBS::NO_ACCELERATION_ARB}};
  constexpr auto GENERIC_ACCELERATION {std::pair{WGL_ATTRIBS::ACCELERATION_ARB, (int)WGL_ATTRIBS::GENERIC_ACCELERATION_ARB}};
  constexpr auto FULL_ACCELERATION    {std::pair{WGL_ATTRIBS::ACCELERATION_ARB, (int)WGL_ATTRIBS::FULL_ACCELERATION_ARB}};

  constexpr auto SWAP_EXCHANGE  {std::pair{WGL_ATTRIBS::SWAP_METHOD_ARB, (int)WGL_ATTRIBS::SWAP_EXCHANGE_ARB}};
  constexpr auto SWAP_COPY      {std::pair{WGL_ATTRIBS::SWAP_METHOD_ARB, (int)WGL_ATTRIBS::SWAP_COPY_ARB}};
  constexpr auto SWAP_UNDEFINED {std::pair{WGL_ATTRIBS::SWAP_METHOD_ARB, (int)WGL_ATTRIBS::SWAP_UNDEFINED_ARB}};

  constexpr auto TYPE_RGBA        {std::pair{WGL_ATTRIBS::PIXEL_TYPE_ARB, (int)WGL_ATTRIBS::TYPE_RGBA_ARB}};
  constexpr auto TYPE_COLORINDEX  {std::pair{WGL_ATTRIBS::PIXEL_TYPE_ARB, (int)WGL_ATTRIBS::TYPE_COLORINDEX_ARB}};


  // Context

  enum class WGL_CONTEXT_NAMES
  {
    MAJOR_VERSION_ARB             = 0x2091  // default associated value is 1
    ,MINOR_VERSION_ARB            = 0x2092  // default associated value is 0
    ,LAYER_PLANE_ARB              = 0x2093  // default associated value is 0
    ,FLAGS_ARB                    = 0x2094  // default associated value is 0
    ,PROFILE_MASK_ARB             = 0x9126  // default associated value is WGL_CONTEXT_CORE_PROFILE_BIT_ARB = 1
  };

  // MAJOR_VERSION_ARB, MINOR_VERSION_ARB
  constexpr auto OGL_MAJOR_VERSION_5  { std::pair{WGL_CONTEXT_NAMES::MAJOR_VERSION_ARB, 5} };
  constexpr auto OGL_MAJOR_VERSION_4  { std::pair{WGL_CONTEXT_NAMES::MAJOR_VERSION_ARB, 4} };
  constexpr auto OGL_MAJOR_VERSION_3  { std::pair{WGL_CONTEXT_NAMES::MAJOR_VERSION_ARB, 3} };
  constexpr auto OGL_MAJOR_VERSION_2  { std::pair{WGL_CONTEXT_NAMES::MAJOR_VERSION_ARB, 2} };
  constexpr auto OGL_MAJOR_VERSION_1  { std::pair{WGL_CONTEXT_NAMES::MAJOR_VERSION_ARB, 1} };

  constexpr auto OGL_MINOR_VERSION_7  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 7} };
  constexpr auto OGL_MINOR_VERSION_6  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 6} };
  constexpr auto OGL_MINOR_VERSION_5  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 5} };
  constexpr auto OGL_MINOR_VERSION_4  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 4} };
  constexpr auto OGL_MINOR_VERSION_3  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 3} };
  constexpr auto OGL_MINOR_VERSION_2  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 2} };
  constexpr auto OGL_MINOR_VERSION_1  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 1} };
  constexpr auto OGL_MINOR_VERSION_0  { std::pair{WGL_CONTEXT_NAMES::MINOR_VERSION_ARB, 0} };

  

  // FLAGS
  constexpr int WGL_CONTEXT_DEBUG_BIT_ARB               { 0x0001 };
  constexpr int WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  { 0x0002 };

  constexpr auto OGL_DEBUG_CONTEXT              { std::pair{WGL_CONTEXT_NAMES::FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB} };
  constexpr auto OGL_FORWARD_COMPATIBLE_CONTEXT { std::pair{WGL_CONTEXT_NAMES::FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB} };
  constexpr auto OGL_DEBUG_FORWARD_CONTEXT      { std::pair{WGL_CONTEXT_NAMES::FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB | WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB} };
  
  // PROFILE_MASK_ARB
  constexpr int WGL_CONTEXT_CORE_PROFILE_BIT_ARB          { 0x00000001 }; // Specified as default value
  constexpr int WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB { 0x00000002 };

  constexpr auto OGL_CORE_PROFILE_CONTEXT   { std::pair{WGL_CONTEXT_NAMES::PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB} };
  constexpr auto OGL_COMPATIBILITY_CONTEXT  { std::pair{WGL_CONTEXT_NAMES::PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB} };

} // namespace OGL_Info_ns
