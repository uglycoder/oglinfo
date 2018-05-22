//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once

#include <Windows.h>
#include <gl/GL.h>


namespace OGL_Info_ns
{
  struct wglGetExtensionsStringARB_t
  {
    static constexpr char const * const str{ "wglGetExtensionsStringARB" };

    using fn_t = char const * (WINAPI *)(HDC hdc);

    static constexpr wglGetExtensionsStringARB_t wglGetExtensionsStringARB;
  };

  struct wglCreateContextAttribsARB_t
  {
    static constexpr char const * const str{ "wglCreateContextAttribsARB" };

    using fn_t = HGLRC (WINAPI *) (HDC hDC, HGLRC hShareContext, const int *attribList);

    static constexpr wglCreateContextAttribsARB_t wglCreateContextAttribsARB;
  };

  
struct wglGetPixelFormatAttribivARB_t
{
  static constexpr char const * const str{ "wglGetPixelFormatAttribivARB" };

    using fn_t = BOOL (WINAPI *) (HDC hdc, int iPixelFormat, int iLayerPlane, unsigned int nAttributes, const int *piAttributes, int *piValues);

    static constexpr wglGetPixelFormatAttribivARB_t wglGetPixelFormatAttribivARB;
  };

  
  struct wglChoosePixelFormatARB_t
  {
    static constexpr char const * const str{ "wglChoosePixelFormatARB" };

    using fn_t = BOOL (WINAPI *) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, unsigned int nMaxFormats, int *piFormats, unsigned int *nNumFormats);

    static constexpr wglChoosePixelFormatARB_t wglChoosePixelFormatARB;
  };


  template <typename FN>
  typename FN::fn_t GetWGLProc(FN const & wglType) noexcept
  {
    using FT = typename FN::fn_t;
    auto const wglFunc{ (FT)::wglGetProcAddress(wglType.str) };
    if(wglFunc != nullptr && wglFunc > (FT)3)
    {
      return wglFunc;
    }
    return nullptr;
  }
}