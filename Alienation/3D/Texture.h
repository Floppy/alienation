#ifndef SDS_TEXTURE_H
#define SDS_TEXTURE_H

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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

   void preRenderToTexture();
   // Prepare for offscreen rendering

   void postRenderToTexture();
   // Finish offscreen rendering

   unsigned int ID() 
   { return m_uiTexture; }
   // Get texture ID

 protected:
   
   unsigned int m_uiTexture;

   unsigned int m_iX;

   unsigned int m_iY;

   int m_aiViewport[4];

};

#endif //SDS_TEXTURE_H
