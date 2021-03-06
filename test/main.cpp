// main.cpp : Defines the entry point for the console application.
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#include "stdafx.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>


#include "../oglinfo/interface/ogl_info.hpp"

int main()
{
  using namespace OGL_Info_ns;

  auto const [success, errStr, vendor, renderer, version, mjr_ver, mnr_ver, wglExts, oglExts, numPixFmts] { GetDriverInfo()};

  if(success)
  {
    std::cout << "No errors detected\n";
    std::cout
      << "Vendor: " << vendor << '\n'
      << "Renderer: " << renderer << '\n'
      << "Version: " << version << '\n'
      << "Major version supported: " << mjr_ver << '\n'
      << "Minor version supported: " << mnr_ver << '\n';

    std::cout << "Number of OGL extensions: " << oglExts.size() << '\n';
    std::copy(std::cbegin(oglExts), std::cend(oglExts), std::ostream_iterator<std::string>{std::cout, "\n"});

    std::cout << '\n';

    std::cout << "Number of WGL extensions: " << wglExts.size() << '\n';
    std::copy(std::cbegin(wglExts), std::cend(wglExts), std::ostream_iterator<std::string>{std::cout, "\n"});
    std::cout << "Number of pixel formats supported = " << numPixFmts << '\n';  
  }

  auto const & pixelFormats{ ChoosePixelFormats(
    { OGL_MAJOR_VERSION_4, OGL_MINOR_VERSION_6, OGL_CORE_PROFILE_CONTEXT }
    , {
      DRAW_TO_WINDOW(true)
      , SUPPORT_OPENGL(true)
      , DOUBLE_BUFFER(true)
      , TYPE_RGBA
      , COLOR_BITS(32)
      , DEPTH_BITS(24)
      , STENCIL_BITS(8)
      , SAMPLES(4)
      , FULL_ACCELERATION
    }
  , 100) };

  if(!pixelFormats.formats.empty())
  {
    auto const & pixelFormatDetails{ QueryPixelFormat(
      pixelFormats.formats[0]
      , { OGL_MAJOR_VERSION_4, OGL_MINOR_VERSION_6, OGL_CORE_PROFILE_CONTEXT }
      , { WGL_ATTRIBS::STENCIL_BITS_ARB, WGL_ATTRIBS::SUPPORT_GDI_ARB, WGL_ATTRIBS::ACCELERATION_ARB
          , WGL_ATTRIBS::TRANSPARENT_ARB, WGL_ATTRIBS::PIXEL_TYPE_ARB, WGL_ATTRIBS::COLOR_BITS_ARB
          , WGL_ATTRIBS::SUPPORT_OPENGL_ARB, WGL_ATTRIBS::SAMPLES_ARB }
    ) };

    for(auto const & wglAtttrib : pixelFormatDetails.results)
    {
      auto const & [attStr, valStr] {GetWGL_AttributeStrings(wglAtttrib)};
      std::cout << attStr << " = " << valStr << '\n';
    }

    std::cout << "\nChecking pixel format " << pixelFormats.formats[0] << '\n';
    auto const result{ CheckPixelFormat(
      pixelFormats.formats[0]
    ) };
    std::cout << (result.first ? "OK" : result.second) << '\n';
  }

  return 0;
}

