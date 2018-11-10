// ogl_info.cpp
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter


#include "stdafx.h"

#include "../interface/ogl_info.hpp"

#include <Windows.h>
#include <strsafe.h>
#include <gl/GL.h>

#include <cassert>

#include <algorithm>
#include <future>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "resource.h"

#include "windows_utils.hpp"
#include "wgl_functions.hpp"

#include "../interface/wgl_defs.hpp"


namespace
{
  // These 4 functions will be run in their own individual thread: one function, one thread; one thread one function

  OGL_Info_ns::driverInfo DrvrInfo() noexcept;

  OGL_Info_ns::pixelFormats ChoosePixFormats(
    OGL_Info_ns::contextAttribs_t const & contextAttribs
    , OGL_Info_ns::pixelAttribs_t const & requiredPixAttribs
    , unsigned int nMaxFormats) noexcept;

  OGL_Info_ns::pixelFormatDetails QueryPixFormat(
    int pixelFormat
    , int iLayerPlane
    , OGL_Info_ns::contextAttribs_t const & contextAttribs
    , OGL_Info_ns::attribList_t const & attribsRequested
  ) noexcept;

  std::pair<bool, std::string> CheckPixFormat(
    int pixelFormat
  ) noexcept;

  // 
  OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES GetWGLAttributeValueType(OGL_Info_ns::WGL_ATTRIBS attrib);
}

// ############################## Interface ###################################

OGL_Info_ns::driverInfo OGL_Info_ns::GetDriverInfo() noexcept
{
  try
  {
    // Get driver info in separate thread to isolate temporary OpenGL context
    return std::async(std::launch::async, DrvrInfo).get();
  }
  catch(std::exception const & e)
  {
    return{false, e.what()};
  }
}

/////

OGL_Info_ns::pixelFormats OGL_Info_ns::ChoosePixelFormats(
  contextAttribs_t const & contextAttribs
  , pixelAttribs_t const & requiredPixAttribs
  , unsigned int nMaxFormats) noexcept
{
  try
  {
    // Choose pixel formats in seperate thread to isolate temporary OGL contexts etc 
    return std::async(std::launch::async, ChoosePixFormats, contextAttribs, requiredPixAttribs, nMaxFormats).get();
  }
  catch(std::exception const & e)
  {
    return{ false, e.what() };
  }
}

/////

OGL_Info_ns::pixelFormatDetails OGL_Info_ns::QueryPixelFormat(
  int pixelFormat
  , contextAttribs_t const & contextAttribs
  , attribList_t const & attribsRequested
  , int iLayerPlane
) noexcept
{
  try
  {
    // Query pixel formats in seperate thread to isolate temporary OGL contexts etc 
    return std::async(std::launch::async, QueryPixFormat, pixelFormat, iLayerPlane, contextAttribs, attribsRequested).get();
  }
  catch(std::exception const & e)
  {
    return{ false, e.what() };
  }
}

/////

OGLINFO_API std::pair<bool, std::string> OGL_Info_ns::CheckPixelFormat(
  int pixelFormat
) noexcept
{
  try
  {
    // Choose pixel formats in seperate thread to isolate temporary OGL contexts etc 
    return std::async(std::launch::async, CheckPixFormat, pixelFormat).get();
  }
  catch(std::exception const & e)
  {
    return{ false, e.what() };
  }
}

/////

OGLINFO_API std::pair<std::string,std::string> OGL_Info_ns::GetWGL_AttributeStrings(std::pair<WGL_ATTRIBS, int> const & wglAttrib_Value) noexcept
{
#define MAKE_WGL_ATTRIB_PAIR(arg) {WGL_ATTRIBS::arg, #arg}
  static std::map<WGL_ATTRIBS, char const * const> const WGL_ATTRIBUTE_TO_STRING
  {
    MAKE_WGL_ATTRIB_PAIR(NUMBER_PIXEL_FORMATS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(DRAW_TO_WINDOW_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(DRAW_TO_BITMAP_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ACCELERATION_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(NEED_PALETTE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(NEED_SYSTEM_PALETTE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SWAP_LAYER_BUFFERS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SWAP_METHOD_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(NUMBER_OVERLAYS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(NUMBER_UNDERLAYS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TRANSPARENT_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TRANSPARENT_RED_VALUE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TRANSPARENT_GREEN_VALUE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TRANSPARENT_BLUE_VALUE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TRANSPARENT_ALPHA_VALUE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TRANSPARENT_INDEX_VALUE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SHARE_DEPTH_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SHARE_STENCIL_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SHARE_ACCUM_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SUPPORT_GDI_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SUPPORT_OPENGL_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(DOUBLE_BUFFER_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(STEREO_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(PIXEL_TYPE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(COLOR_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(RED_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(RED_SHIFT_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(GREEN_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(GREEN_SHIFT_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(BLUE_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(BLUE_SHIFT_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ALPHA_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ALPHA_SHIFT_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ACCUM_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ACCUM_RED_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ACCUM_GREEN_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ACCUM_BLUE_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(ACCUM_ALPHA_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(DEPTH_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(STENCIL_BITS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(AUX_BUFFERS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(NO_ACCELERATION_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(GENERIC_ACCELERATION_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(FULL_ACCELERATION_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SWAP_EXCHANGE_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SWAP_COPY_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SWAP_UNDEFINED_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TYPE_RGBA_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(TYPE_COLORINDEX_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SAMPLE_BUFFERS_ARB)
    ,MAKE_WGL_ATTRIB_PAIR(SAMPLES_ARB)
  };
#undef MAKE_WGL_ATTRIB_PAIR

  try
  {
    std::string value;
    switch(GetWGLAttributeValueType( wglAttrib_Value.first))
    {
    case WGL_ATTRIBS_VALUE_TYPES::BOOLEAN:
      value = wglAttrib_Value.second ? windows_ns::GetString(IDS_TRUE):  windows_ns::GetString(IDS_FALSE);
      break;

    case WGL_ATTRIBS_VALUE_TYPES::INTEGER:
      value = std::to_string(wglAttrib_Value.second);
      break;

    case WGL_ATTRIBS_VALUE_TYPES::ENUM:
      value = WGL_ATTRIBUTE_TO_STRING.at(static_cast<WGL_ATTRIBS>(wglAttrib_Value.second));
      break;

    case WGL_ATTRIBS_VALUE_TYPES::IGNORED:
      value = windows_ns::GetString(IDS_IGNORED);
      break;

    default:
      assert(false && "Unknown value of WGL_ATTRIBS encountered.");
      value = windows_ns::GetString(IDS_UNKNOWN_VALUE);
    }

    return std::make_pair(WGL_ATTRIBUTE_TO_STRING.at(wglAttrib_Value.first), value);
  }
  catch(...)
  {
    auto const & errStr = windows_ns::GetString(IDS_ERROR);
    return{ errStr, errStr };
  }
}
// ############################## End of Interface ############################

namespace
{
  constexpr int OGL_MAJOR_VERSION{ 0x821B };
  constexpr int OGL_MINOR_VERSION{ 0x821C };

  /// <summary>
  /// OpenGL_Window_Context: Simple struct for OpenGL contexts.
  /// </summary>
  /// <remarks>
  /// Client code setups the data members as required.
  /// </remarks>
  struct OpenGL_Window_Context final
  {
    ::HWND        wnd{};
    ::HDC         hdc{};
    ::HGLRC       hglrc{};
    ::HINSTANCE   hinstance{ ::GetModuleHandle(nullptr) };
    std::wstring  className;

    OpenGL_Window_Context() = default;
    ~OpenGL_Window_Context() noexcept
    {
      if(wnd)
      {
        deleteContext();
        ::ReleaseDC(wnd, hdc);
        ::DestroyWindow(wnd);
        ::UnregisterClass(className.c_str(), hinstance);
      }
    }

    OpenGL_Window_Context(OpenGL_Window_Context const &) = delete;
    OpenGL_Window_Context & operator=(OpenGL_Window_Context const &) = delete;

    OpenGL_Window_Context(OpenGL_Window_Context &&) = delete;
    OpenGL_Window_Context & operator=(OpenGL_Window_Context &&) = delete;

    /// <summary>
    /// deleteContext(): Deletes the OpenGL context associated with a set of valid wnd, hdc, hInstance
    /// data members
    /// </summary>
    void deleteContext() & noexcept
    {
      assert(wnd && hdc && hinstance);

      if(hglrc)
      {
        ::wglDeleteContext(hglrc);
        hglrc = nullptr;
      }
    }
  };

  using OGL_ctxt_ptr = std::unique_ptr<OpenGL_Window_Context>;

  struct OGL_Window_result_t
  {
    bool succeeded{};
    std::string errStr;
    OGL_ctxt_ptr ctxt_ptr;
  };

  /////

  OGL_Window_result_t CreateTemporaryOGL_Window(int pixelFormat = 1) noexcept
  {
    static constexpr ::PIXELFORMATDESCRIPTOR DEFAULT_PIXELFORMATDESCRIPTOR{ sizeof ::PIXELFORMATDESCRIPTOR, 1U };

    auto * const glcxt{ new (std::nothrow) OpenGL_Window_Context };
    if(glcxt)
    {
      std::tie(glcxt->wnd, std::ignore, glcxt->hinstance) = windows_ns::CreateTemporaryWindow();

      if(glcxt->wnd)
      {
        glcxt->hdc = ::GetDC(glcxt->wnd);
        if(glcxt->hdc)
        {
          if(::SetPixelFormat(glcxt->hdc, pixelFormat, &DEFAULT_PIXELFORMATDESCRIPTOR))
          {
            // Create OGL context and make it current
            glcxt->hglrc = ::wglCreateContext(glcxt->hdc);
            if(glcxt->hglrc)
            {
              if(::wglMakeCurrent(glcxt->hdc, glcxt->hglrc))
              {
                return { true, "", OGL_ctxt_ptr(glcxt) };
              }
            }
            else
            {
              auto const & msg{ windows_ns::GetString(IDS_OPENGL_CONTEXT_CREATION_FAILED) };
              return { false, msg };
            }
          }
          else
          {
            auto const & errStr{ windows_ns::GetLastError(::GetLastError()) };
            auto const & msg{ windows_ns::GetString(IDS_SETPIXELFORMAT_FAILED) + ": " + errStr };
            return { false, msg };
          }
        }
      }
    }
    return{};
  }

  /////

  OGL_Info_ns::wglExtensions_t Get_WGL_Extensions(::HDC hdc) noexcept
  {
    auto const wglGetExtensionsStringARBProc{ GetWGLProc(OGL_Info_ns::g_wglGetExtensionsStringARB) };

    OGL_Info_ns::wglExtensions_t wglExtensions;
    std::string const strings{ wglGetExtensionsStringARBProc ? wglGetExtensionsStringARBProc(hdc) : "" };
    std::istringstream ss{ strings };
    std::string buf;
    while(ss >> buf)
    {
      wglExtensions.push_back(std::move(buf));
    }
    return wglExtensions;
  }

  /////

  template <class T>
  std::vector<int> ConvertToPairedAttribList(T const & att_list)
  {
    std::vector<int> list;
    list.reserve(att_list.size() + 2);
    for(auto const[name, value] : att_list)
    {
      list.push_back(static_cast<int>(name));
      list.push_back(value);
    }
    list.push_back(0);
    return list;
  }

  /////

  OGL_Window_result_t CreateTemporaryOGL_Window(OGL_Info_ns::contextAttribs_t const & attribs) noexcept
  {
    if(auto tmpOGLcontext{ CreateTemporaryOGL_Window().ctxt_ptr }; tmpOGLcontext)
    {
      if(auto const wglCreateContextAttribsARBProc{ GetWGLProc(OGL_Info_ns::g_wglCreateContextAttribsARB) }; wglCreateContextAttribsARBProc)
      {
        tmpOGLcontext->deleteContext();

        // Convert contextAttribs_t to vector of paired ints for wglCreateContextAttribsARBProc call
        auto const & ARB_attribs{ ConvertToPairedAttribList(attribs) };

        tmpOGLcontext->hglrc = wglCreateContextAttribsARBProc(tmpOGLcontext->hdc, 0, ARB_attribs.data());
        if(tmpOGLcontext->hglrc)
        {
          if(::wglMakeCurrent(tmpOGLcontext->hdc, tmpOGLcontext->hglrc))
          {
            OGL_Info_ns::wglExtensions_t const & wglExts{ Get_WGL_Extensions(tmpOGLcontext->hdc) };
            bool const WGL_ARB_create_context_profile_supported{ std::find(std::cbegin(wglExts), std::cend(wglExts), "WGL_ARB_create_context_profile") != wglExts.cend() };
            if(!WGL_ARB_create_context_profile_supported)
            {
              // Check for WGL_CONTEXT_PROFILE_MASK_ARB in attribs: this should not be present in attribs
              if(std::find_if(std::cbegin(attribs), std::cend(attribs),
                [](auto const & pair) { return pair.first == OGL_Info_ns::WGL_CONTEXT_NAMES::PROFILE_MASK_ARB; }) != attribs.cend())
              {
                auto const & msg1{ windows_ns::GetString(IDS_CREATE_CONTEXT_PROFILE_NOT_SUPPORTED) + ": " };
                auto const & msg2{ msg1 + windows_ns::GetString(IDS_CONTEXT_PROFILE_MASK_ARB_ERROR) };
                return { false, msg2 };
              }
            }
            return { true, "", std::move(tmpOGLcontext) };
          }
        }
        else
        {
          auto const & err{ ::GetLastError() };
          auto const & errStr{ windows_ns::GetWGLErrorString(err) };
          auto const & msg{ windows_ns::GetString(IDS_OPENGL_CONTEXT_CREATION_FAILED) + ": " + errStr };
          return { false, msg };
        }
      }
      else
      {
        return { false, windows_ns::GetString(IDS_NO_CREATE_CONTEXT_FUNCTION_POINTER) };
      }
    }
    return{ false, windows_ns::GetString(IDS_OPENGL_WINDOW_CREATION_ERROR) };
  }

  /////

  void ClearGLErrors() noexcept
  {
    while(::glGetError());
  }
  /////

  OGL_Info_ns::oglExtensions_t Get_OGL_Extensions() noexcept
  {
    auto const * const glExts_ptr{ (char const *)::glGetString(GL_EXTENSIONS) };
    ClearGLErrors();
    std::string const exts{ glExts_ptr ? glExts_ptr : "" };
    OGL_Info_ns::oglExtensions_t oglExts;
    std::string buf;
    std::istringstream is{ exts };
    while(is >> buf)
    {
      oglExts.push_back(std::move(buf));
    }
    return oglExts;
  }

  /////

  std::tuple<bool, std::string, int> GetNumberOfPixelFormats(HDC hdc)
  {
    auto const wglGetPixelFormatAttribivARBProc{ GetWGLProc(OGL_Info_ns::g_wglGetPixelFormatAttribivARB) };
    int numberOfPixelFormats{};
    if(wglGetPixelFormatAttribivARBProc != nullptr)
    {
      constexpr auto attribs{ static_cast<int>(OGL_Info_ns::WGL_ATTRIBS::NUMBER_PIXEL_FORMATS_ARB) };
      if(wglGetPixelFormatAttribivARBProc(hdc, 0, 0, 1, &attribs, &numberOfPixelFormats) == TRUE)
      {
        return std::make_tuple(true, "", numberOfPixelFormats);
      }
      return std::make_tuple(false, windows_ns::GetString(IDS_GETPIXELFORMATATTRIBIV_FAILED), numberOfPixelFormats);
    }
    return std::make_tuple(false, windows_ns::GetString(IDS_GETPIXELFORMATATTRIBIV_NOT_SUPPORTED), numberOfPixelFormats);
  }

  /////

  std::pair<int, int> ParseVersionString(std::string const & versionStr) noexcept
  {
    try
    {
      // The version number is at the start of versionStr and uses one of these forms: major_number.minor_number || major_number.minor_number.release_number
      // then may finish with <space>vendor-specific info. Example: "4.6.0 NVIDIA 388.13"
      auto const firstPt{ versionStr.find_first_of('.') };
      auto const & maj{ versionStr.substr(0, firstPt) };
      auto const secondPt{ versionStr.find_first_of('.', firstPt + 1) };
      auto const & mnr{ versionStr.substr(firstPt + 1, secondPt - firstPt - 1) };
      return{ std::stoi(maj),std::stoi(mnr) };
    }
    catch(...)
    {
      return{ -1,-1 };
    }
  }

  /////

  std::pair<int, int> GetOGLVersionNumbers(std::string const & versionStr) noexcept
  {
    ClearGLErrors();

    int major_version{};
    int minor_version{};
    ::glGetIntegerv(OGL_MAJOR_VERSION, &major_version);
    ::glGetIntegerv(OGL_MINOR_VERSION, &minor_version);
    if(::glGetError() != GL_NO_ERROR)
    {
      std::tie(major_version, minor_version) = ParseVersionString(versionStr);
    }
    return{ major_version, minor_version };
  }

  /////

  OGL_Info_ns::driverInfo DrvrInfo() noexcept
  {
    HINSTANCE const hInstance{ GetModuleHandle(nullptr) };
    if(!hInstance)
    {
      return{ false, windows_ns::GetString(IDS_INVALID_MODULE_HANDLE) };
    }

    if(auto const glcxt{ CreateTemporaryOGL_Window().ctxt_ptr }; glcxt)
    {
      auto const checkForNull{ [](int glDefine) { auto const p{ reinterpret_cast<char const *>(::glGetString(glDefine)) }; return p ? p : ""; } };
      std::string const vendorStr{ checkForNull(GL_VENDOR) };
      std::string const rendererStr{ checkForNull(GL_RENDERER) };
      ClearGLErrors();

      std::string const versionStr{ checkForNull(GL_VERSION) };
      ClearGLErrors();

      auto const [major_version, minor_version] {GetOGLVersionNumbers(versionStr)};

      if(major_version == -1 || minor_version == -1)
      {
        return{ false, windows_ns::GetString(IDS_NO_OPENGL_VERSION_NUMBER_RETRIEVED) };
      }

      auto const & numPixFmts{ std::get<int>(GetNumberOfPixelFormats(glcxt->hdc)) };

      OGL_Info_ns::wglExtensions_t const & wglExts{ Get_WGL_Extensions(glcxt->hdc) };
      OGL_Info_ns::oglExtensions_t const & oglExts{ Get_OGL_Extensions() };

      return { true, "", vendorStr, rendererStr, versionStr, major_version, minor_version, wglExts, oglExts, numPixFmts };
    }
    return { false, windows_ns::GetString(IDS_OPENGL_WINDOW_CREATION_ERROR) };
  }

  /////

  OGL_Info_ns::pixelFormats ChoosePixFormats(
    OGL_Info_ns::contextAttribs_t const & contextAttribs
    , OGL_Info_ns::pixelAttribs_t const & requiredPixAttribs
    , unsigned int nMaxFormats) noexcept
  {
    auto const [succeeded, errString, glcxt] {CreateTemporaryOGL_Window(contextAttribs)};

    if(!glcxt)
    {
      return{ false, errString };
    }

    auto const [success, errStr, numPixfmts] {GetNumberOfPixelFormats(glcxt->hdc)};
    // if no pixformats returned
    if(numPixfmts == 0)
    {
      return{ success, errStr };
    }

    // requiredPixAttribs into vector of paired int attributes
    auto const & attribIList{ ConvertToPairedAttribList(requiredPixAttribs) };

    // (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, unsigned int nMaxFormats, int *piFormats, unsigned int *nNumFormats)
    std::vector<int> formats(nMaxFormats);
    unsigned int numFormatsWritten{ 0 };
    if(auto const wglChoosePixelFormatARB{ GetWGLProc(OGL_Info_ns::g_wglChoosePixelFormatARB) }; wglChoosePixelFormatARB != nullptr)
    {
      if(wglChoosePixelFormatARB(glcxt->hdc, attribIList.data(), nullptr, nMaxFormats, formats.data(), &numFormatsWritten) == TRUE)
      {
        formats.erase(std::cbegin(formats) + numFormatsWritten, std::cend(formats));
        return{ true, "", formats };
      }
      else
      {
        return{ false, windows_ns::GetString(IDS_CHOOSEPIXELFORMAT_FAILED) };
      }
    }
    return{ false, windows_ns::GetString(IDS_NO_CHOOSEPIXELFORMAT_FUNCTION_POINTER) };
  }

  /////

  OGL_Info_ns::pixelFormatDetails QueryPixFormat(
    int pixelFormat
    , int iLayerPlane
    , OGL_Info_ns::contextAttribs_t const & contextAttribs
    , OGL_Info_ns::attribList_t const & attribsRequested
  ) noexcept
  {
    auto const[succeeded, errString, glcxt] {CreateTemporaryOGL_Window(contextAttribs)};

    if(!succeeded)
    {
      return{ false, windows_ns::GetString(IDS_OPENGL_WINDOW_CREATION_ERROR) + " - " + errString };
    }

    std::vector<int> attributes(attribsRequested.size());
    std::transform(std::cbegin(attribsRequested), std::cend(attribsRequested), std::begin(attributes), [](auto const & e) { return static_cast<int>(e); });

    if(auto const wglGetPixelFormatAttribivARB_FN{ GetWGLProc(OGL_Info_ns::g_wglGetPixelFormatAttribivARB) }; wglGetPixelFormatAttribivARB_FN)
    {
      std::vector<int> results_buffer(attributes.size());
      if(wglGetPixelFormatAttribivARB_FN(glcxt->hdc, pixelFormat, iLayerPlane, static_cast<unsigned int>(attributes.size()), attributes.data(), results_buffer.data()) == TRUE)
      {
        OGL_Info_ns::pixelAttribs_t pixelAttribs;
        std::transform(
          std::cbegin(attribsRequested), std::cend(attribsRequested)
          , results_buffer.cbegin(), std::inserter(pixelAttribs, std::begin(pixelAttribs))
          , [](auto const & first, auto const & second) { return std::make_pair(first, second); });

        return { true, "", pixelAttribs };
      }
      return {false, windows_ns::GetString(IDS_GETPIXELFORMATATTRIBIV_FAILED) };
    }

    return{};
  }

  /////

  std::pair<bool, std::string> CheckPixFormat(
    int pixelFormat
  ) noexcept
  {
    auto const [succeeded, errString, ctxt] {CreateTemporaryOGL_Window(pixelFormat)};

    if(succeeded && ctxt)
    {
      return{ true, "" };
    }
    return{ false, windows_ns::GetString(IDS_OPENGL_WINDOW_CREATION_ERROR) + ": " + errString };
  }

  OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES GetWGLAttributeValueType(OGL_Info_ns::WGL_ATTRIBS attrib)
  {
    using WGL_TYPE = OGL_Info_ns::WGL_ATTRIBS;
    switch(attrib)
    {
      // boolean
    case WGL_TYPE::DRAW_TO_WINDOW_ARB:
    case WGL_TYPE::DRAW_TO_BITMAP_ARB:
    case WGL_TYPE::NEED_PALETTE_ARB:
    case WGL_TYPE::NEED_SYSTEM_PALETTE_ARB:
    case WGL_TYPE::SWAP_LAYER_BUFFERS_ARB:
    case WGL_TYPE::SHARE_DEPTH_ARB:
    case WGL_TYPE::SHARE_STENCIL_ARB:
    case WGL_TYPE::SHARE_ACCUM_ARB:
    case WGL_TYPE::SUPPORT_GDI_ARB:
    case WGL_TYPE::SUPPORT_OPENGL_ARB:
    case WGL_TYPE::DOUBLE_BUFFER_ARB:
    case WGL_TYPE::STEREO_ARB:
      return OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES::BOOLEAN;

      // integer
    case WGL_TYPE::NUMBER_OVERLAYS_ARB:
    case WGL_TYPE::NUMBER_UNDERLAYS_ARB:
    case WGL_TYPE::COLOR_BITS_ARB:
    case WGL_TYPE::RED_BITS_ARB:
    case WGL_TYPE::GREEN_BITS_ARB:
    case WGL_TYPE::BLUE_BITS_ARB:
    case WGL_TYPE::ALPHA_BITS_ARB:
    case WGL_TYPE::ACCUM_BITS_ARB:
    case WGL_TYPE::ACCUM_RED_BITS_ARB:
    case WGL_TYPE::ACCUM_GREEN_BITS_ARB:
    case WGL_TYPE::ACCUM_BLUE_BITS_ARB:
    case WGL_TYPE::ACCUM_ALPHA_BITS_ARB:
    case WGL_TYPE::DEPTH_BITS_ARB:
    case WGL_TYPE::STENCIL_BITS_ARB:
    case WGL_TYPE::AUX_BUFFERS_ARB:
    case WGL_TYPE::SAMPLE_BUFFERS_ARB:
    case WGL_TYPE::SAMPLES_ARB:
      return OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES::INTEGER;

      // enums
    case WGL_TYPE::ACCELERATION_ARB:
    case WGL_TYPE::SWAP_METHOD_ARB:
    case WGL_TYPE::PIXEL_TYPE_ARB:
      return OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES::ENUM;

      // ignored
    case WGL_TYPE::NUMBER_PIXEL_FORMATS_ARB:
    case WGL_TYPE::TRANSPARENT_ARB:
    case WGL_TYPE::TRANSPARENT_RED_VALUE_ARB:
    case WGL_TYPE::TRANSPARENT_GREEN_VALUE_ARB:
    case WGL_TYPE::TRANSPARENT_BLUE_VALUE_ARB:
    case WGL_TYPE::TRANSPARENT_ALPHA_VALUE_ARB:
    case WGL_TYPE::TRANSPARENT_INDEX_VALUE_ARB:
    case WGL_TYPE::RED_SHIFT_ARB:
    case WGL_TYPE::GREEN_SHIFT_ARB:
    case WGL_TYPE::BLUE_SHIFT_ARB:
    case WGL_TYPE::ALPHA_SHIFT_ARB:
      return OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES::IGNORED;;

    default:
      return OGL_Info_ns::WGL_ATTRIBS_VALUE_TYPES::UNKNOWN;

    }
  }
}