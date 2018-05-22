//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#include "stdafx.h"
#include "mfc_utils.hpp"

void SetHorizontalExtentForLongestString(CListBox & listBox)
{
  auto const lbItemCount{ listBox.GetCount() };
  if(lbItemCount > 0)
  {
    CString    str;
    CSize      sz{};
    int        dx{};
    TEXTMETRIC tm{};
    CDC*       pDC = listBox.GetDC();
    CFont*     pFont = listBox.GetFont();

    // Select the listbox font, save the old font
    CFont* pOldFont = pDC->SelectObject(pFont);
    // Get the text metrics for avg char width
    pDC->GetTextMetrics(&tm);

    for(int i{}; i < listBox.GetCount(); ++i)
    {
      listBox.GetText(i, str);
      sz = pDC->GetTextExtent(str);

      // Add the avg width to prevent clipping
      sz.cx += tm.tmAveCharWidth;

      if(sz.cx > dx)
      {
        dx = sz.cx;
      }
    }
    // Select the old font back into the DC
    pDC->SelectObject(pOldFont);
    listBox.ReleaseDC(pDC);

    // Set the horizontal extent so every character of all strings 
    // can be scrolled to.
    listBox.SetHorizontalExtent(dx);
  }
}

void SetColumnWidth(CListBox & listBox)
{
  // Find the pixel width of the largest item.
  auto const lbItemCount{ listBox.GetCount() };
  if(lbItemCount > 0)
  {
    CString str;
    CSize   sz{};
    int     dx{};
    CDC*    pDC = listBox.GetDC();
    for(int i{}; i < lbItemCount; ++i)
    {
      listBox.GetText(i, str);
      sz = pDC->GetTextExtent(str);

      if(sz.cx > dx)
        dx = sz.cx;
    }
    listBox.ReleaseDC(pDC);

    // Set the column width of the first column to be one and 1/3 units
    // of the largest string. 
    listBox.SetColumnWidth(dx * 4 / 3);
  }
}