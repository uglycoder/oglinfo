// ogl_info.hpp

//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

#include "wgl_defs.hpp"

#ifdef OGLINFO_EXPORTS
#define OGLINFO_API __declspec(dllexport)
#else
#define OGLINFO_API __declspec(dllimport)
#endif

namespace OGL_Info_ns
{
  using wglExtensions_t = std::vector<std::string>;
  using oglExtensions_t = std::vector<std::string>;

  struct driverInfo
  {
    bool            succeeded{};
    std::string     errorStr;
    std::string     vendor;
    std::string     renderer;
    std::string     version;
    int             major_ver{};
    int             minor_ver{};
    wglExtensions_t wglExtensions;
    oglExtensions_t oglExtensions;
    int             numSupportedPixelFormats{};
  };

  /// <summary>
  /// Retrieves general information from the active OpenGL driver
  /// </summary>
  /// <returns>
  /// Returns, on success, any retrieved OpenGL information in a <see cref="driverInfo"/> object.
  /// On success the latter's 'succeeded' member will be set to true otherwise set to false with
  /// the errorStr member containing an error message.
  /// </returns>
  OGLINFO_API [[nodiscard]] driverInfo GetDriverInfo() noexcept;

  /// <summary>
  /// Contains a vector of pixel formats that match the specified attributes
  /// with the "best" pixel formats at the start of the vector.
  /// (order is device dependent)
  /// </summary>
  struct pixelFormats
  {
    bool              succeeded{};
    std::string       errorStr;
    std::vector<int>  formats;
  };

  using contextAttribs_t = std::vector<std::pair<WGL_CONTEXT_NAMES, int>>;
  using pixelAttribs_t   = std::set<std::pair<WGL_ATTRIBS, int>>;

  /// <summary>
  /// For a given set of OpenGL context attributes and required pixel attributes
  /// this function returns a set of pixel formats fulfilling those required pixel attributes
  /// </summary>
  /// <param name="contextAttribs">
  /// [in] The OpenGL context attributes to be used in creating an OpenGL context
  /// </param>
  /// <param name="requiredPixAttribs">
  /// [in] The required OpenGL pixel attributes that a returned pixel format must support
  /// </param>
  /// <param name="nMaxFormats">
  /// [in] The maximum number of pixel formats to be returned
  /// </param>
  /// <returns>
  /// Returns, on success, a set of pixel formats fulfilling those required pixel attributes in a <see cref="pixelFormats"/>
  /// object's formats member. 
  /// On success the latter's 'succeeded' member will be set to true otherwise set to false with
  /// the errorStr member containing an error message.
  /// </returns>
  /// <example> Example use
  /// <code>
  /// auto const & pixelFormats = ChoosePixelFormats(
  ///  { // OpenGL context attributes to used in creating an OpenGL context
  ///    OGL_MAJOR_VERSION_4, OGL_MINOR_VERSION_6, OGL_CORE_PROFILE_CONTEXT
  ///  }
  ///  ,
  ///  { // required pixel attributes
  ///    std::make_pair(WGL_ATTRIBS::DRAW_TO_WINDOW_ARB, true)
  ///    , std::make_pair(WGL_ATTRIBS::SUPPORT_OPENGL_ARB, true)
  ///    , std::make_pair(WGL_ATTRIBS::DOUBLE_BUFFER_ARB, true)
  ///    , std::make_pair(WGL_ATTRIBS::PIXEL_TYPE_ARB, (int)WGL_ATTRIBS::TYPE_RGBA_ARB)
  ///    , std::make_pair(WGL_ATTRIBS::COLOR_BITS_ARB, 32)
  ///    , std::make_pair(WGL_ATTRIBS::DEPTH_BITS_ARB, 24)
  ///    , std::make_pair(WGL_ATTRIBS::STENCIL_BITS_ARB, 8)
  ///    , std::make_pair(WGL_ATTRIBS::ACCELERATION_ARB, (int)WGL_ATTRIBS::FULL_ACCELERATION_ARB)
  ///  }
  ///  , 100); // Maximum number of pixel formats to be returned
  /// </code>
  /// </example>
  OGLINFO_API [[nodiscard]] pixelFormats ChoosePixelFormats(
    contextAttribs_t const & contextAttribs
    , pixelAttribs_t const & requiredPixAttribs
    , unsigned int nMaxFormats) noexcept;

  struct pixelFormatDetails
  {
    bool              succeeded{};
    std::string       errorStr;
    pixelAttribs_t    results;
  };

  using attribList_t = std::set<WGL_ATTRIBS>;
  /// <summary>
  /// For a given set of OpenGL context attributes and pixel attributes
  /// this function returns a set of values, one for each given pixel attribute for the given pixel format
  /// </summary>
  /// <param name="pixelFormat">
  /// [in] The pixel format to be queried for the given pixel attributes.
  /// </param>
  /// <param name="contextAttribs">
  /// [in] The OpenGL context attributes to be used in creating an OpenGL context
  /// </param>
  /// <param name="attribsRequested">
  /// [in] The OpenGL pixel attributes that the given pixel format is to be queried for.
  /// </param>
  /// <param name="iLayerPlane">
  /// [in] The plane to be queried: default value = 0 , the main plane
  /// </param>
  /// <returns>
  /// Returns, on success, a set of pixel attrbute/int value pairs whose pixel attribute values match the
  /// pixel attributes in the given attribsRequested parameter, in the <see cref="pixelFormatDetails"/> object's results member. 
  /// On success the latter's 'succeeded' member will be set to true otherwise set to false with
  /// the errorStr member containing an error message.
  /// </returns>
  /// <example> Example use
  /// <code>
  /// auto const & pixelFormatDetails = QueryPixelFormat(
  ///   pixelFormats.formats[0]
  ///   , { OGL_MAJOR_VERSION_4, OGL_MINOR_VERSION_6, OGL_CORE_PROFILE_CONTEXT }
  ///   , { WGL_ATTRIBS::ACCELERATION_ARB, WGL_ATTRIBS::TRANSPARENT_ARB, WGL_ATTRIBS::PIXEL_TYPE_ARB, WGL_ATTRIBS::COLOR_BITS_ARB }
  /// );
  ///
  /// for(auto const & wglAtttrib : pixelFormatDetails.results)
  /// {
  ///   auto const & [attStr, valStr] {GetWGL_AttributeStrings(wglAtttrib)};
  ///   std::cout << attStr << " = " << valStr << '\n';
  /// }
  /// </code>
  /// Example output for above code:<BR>
  /// ACCELERATION_ARB = FULL_ACCELERATION_ARB <BR>
  /// TRANSPARENT_ARB = ignored <BR>
  /// PIXEL_TYPE_ARB = TYPE_RGBA_ARB <BR>
  /// COLOR_BITS_ARB = 32
  /// </example>
  OGLINFO_API [[nodiscard]] pixelFormatDetails QueryPixelFormat(
    int pixelFormat
    , contextAttribs_t const & contextAttribs
    , attribList_t const & attribsRequested
    , int iLayerPlane = 0
  ) noexcept;

  /// <summary>
  /// The given pixel format value is forwarded to the Windows [SetPixelFormat](https://msdn.microsoft.com/en-us/library/dd369049(v=vs.85).aspx)
  /// using a temporary window. If successful an attempt to create an OpenGL context is made using this window
  /// and the pixel format.
  /// </summary>
  /// <param name="pixelFormat">.
  /// [in] The pixel format to be checked: should be one returned by <see cref="ChoosePixelFormats"/>
  /// </param>
  /// <returns>
  /// Returns true on success, otherwise false.
  /// </returns>
  OGLINFO_API [[nodiscard]] std::pair<bool, std::string> CheckPixelFormat(
    int pixelFormat
  ) noexcept;

  /// <summary>
  /// Retrieves a string representation for the given WGL_ATTRIBS value pair if any.
  /// </summary>
  /// <param name="wglAttrib_Value">.
  /// [in] A WGL_ATTRIBS value pair
  /// </param>
  /// <returns>
  /// Returns the string representations for the input value if they are available.
  /// If a WGL_ATTRIBS value cannot be found then a ("error", "error") pair is returned.
  /// If a value for a WGL_ATTRIBS value cannot be found then a ("stringised WGL_ATTRIBS value", "unknown value") pair is returned. <BR>
  /// NOTE: <BR>
  /// WGL_ATTRIBS values that are 'boolean' return a "true" or "false" value. <BR>
  /// WGL_ATTRIBS values that are 'ignored' return an "ignored" value. <BR>
  /// WGL_ATTRIBS values that are 'enum' return a string representation of it. <BR>
  /// WGL_ATTRIBS values that are 'integer' return a string representation of it. <BR>
  /// See comments in code for [WGL_ATTRIBS](wgl__defs_8hpp_source.html#1007) 
  /// <remarks/>
  OGLINFO_API [[nodiscard]] std::pair<std::string, std::string> GetWGL_AttributeStrings(std::pair<WGL_ATTRIBS, int> const & wglAttrib_Value) noexcept;
}
