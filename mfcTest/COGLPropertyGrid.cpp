// COGLPropertyGrid.cpp : implementation file
//
//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter


#include "stdafx.h"

#include "COGLPropertyGrid.hpp"

#include <cassert>

#include "property_options.hpp"

namespace
{
  void SetColumnWidth(CMFCPropertyGridCtrl & crtl, unsigned int width);
}

// COGLPropertyGrid

IMPLEMENT_DYNAMIC(COGLPropertyGrid, CMFCPropertyGridCtrl)

void COGLPropertyGrid::loadProperties(bool loadContextProps /*= true*/, bool loadPixelProps /*= true*/)
{
  if(loadContextProps)
  {
    AddProperty(gridproperties_ns::buildContextProperties());
  }

  if(loadPixelProps)
  {
    AddProperty(gridproperties_ns::buildPixelProperties());
  }

  SetColumnWidth(*this, 150); 
}




BEGIN_MESSAGE_MAP(COGLPropertyGrid, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()



// COGLPropertyGrid message handlers


namespace
{
  void SetColumnWidth(CMFCPropertyGridCtrl & crtl, unsigned int width)
  {
    assert(crtl.GetPropertyCount() > 0 && "A CMFCPropertyGridCtrl needs to have at least one property to set column width");
    HDITEM hdItem{};
    hdItem.mask = HDI_WIDTH; // indicating cxy is width
    hdItem.cxy = width; // whatever you want the property name column width to be
    crtl.GetHeaderCtrl().SetItem(0, &hdItem);
  }
}
