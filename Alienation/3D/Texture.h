#ifndef SDS_TEXTURE_H
#define SDS_TEXTURE_H

#include "config.h"
#include "3D/Material.h"
#include <SDL.h>

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

   unsigned int init();
   // Initialise the texture for rendering

   void render() const;
   // Apply the texture for rendering
   
   void preRenderToTexture();
   // Prepare for offscreen rendering

   void postRenderToTexture();
   // Finish offscreen rendering

   unsigned int ID() 
   { return m_uiTextureID; }
   // Get texture ID
   
   void setPixel(unsigned int iX, unsigned int iY, CRGBAColour colour);
   // Set pixel data

   unsigned int width() const;
   // Texture width
   
   unsigned int height() const;
   // Texture height


 protected:
   
   /**
    * The texture data.
    * This is only valid until init() is called. At that point, it is freed and 
    * the texture cannot be modified except by using the RenderToTexture functions.
    */
   SDL_Surface * m_pTexture;

   /**
    * A GL texture ID.
    */
   unsigned int m_uiTextureID;

   /**
    * Temporary storage for viewport data.
    * Used in the RenderToTexture functions.
    */
   int m_aiViewport[4];

};

#endif //SDS_TEXTURE_H
