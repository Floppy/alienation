// Texture.h: interface for the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEXTURE_H__8395B95E_91B1_4EDB_BBB6_4FB7757FCBA3__INCLUDED_)
#define AFX_TEXTURE_H__8395B95E_91B1_4EDB_BBB6_4FB7757FCBA3__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include <string.h>

class CTexture  
{
 public:

   CTexture();
   // Constructor

   ~CTexture();
   // Destructor

   bool load(const char *strFilename);
   // Load from file

   bool create(unsigned int iX, unsigned int iY);
   // Create an empty RGBA texture of the specified size.

   void prerender();
   // Offscreen rendering setup

   void postrender();
   // Tidy up offscreen rendering

   unsigned int ID() 
   { return m_uiTexture; }
   // Get texture ID

 protected:
   
   unsigned int m_uiTexture;

   unsigned int m_iX;

   unsigned int m_iY;

   int m_aiViewport[4];

};

#endif // !defined(AFX_TEXTURE_H__8395B95E_91B1_4EDB_BBB6_4FB7757FCBA3__INCLUDED_)
