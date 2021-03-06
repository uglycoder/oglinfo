//  MIT License
//  See LICENSE.txt file in root of project
//  Copyright(c) 2018 Simon Parmenter

#pragma once


// COGLPropertyGrid

class COGLPropertyGrid final : public CMFCPropertyGridCtrl
{
	DECLARE_DYNAMIC(COGLPropertyGrid)

public:
  void loadProperties(bool loadContextProps = true, bool loadPixelProps = true);

  DECLARE_MESSAGE_MAP()
};


