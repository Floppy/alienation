#ifndef SDS_TEXTURE_H
#define SDS_TEXTURE_H

#include "config.h"
#include "3D/Material.h"
#include <SDL.h>
#include <SDL_opengl.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTexture  
{
 public:

   /**
    * Constructor.
    */
   CTexture();

   /**
    * Destructor.
    * Will free any GL texture IDs or SDL surfaces that remain.
    */
   ~CTexture();

   /**
    * Load texture from file.
    * @param strFilename The filename to load. This is relative to the texture root directory, set in the texture manager.
    * @param bMipmap Generate mipmaps for the texture.
    * @return true if the file was loaded successfully.
    */
   bool load(const char *strFilename, bool bMipmap = true);

   /**
    * Create a blank texture.
    * @param iX The width of the new texture.
    * @param iY The height of the new texture.
    * @return true if the texture was created successfully.
    */
   bool create(unsigned int iX, unsigned int iY);

   /**
    * Initialise the texture for rendering.
    * This function will perform OpenGL setup for the texture.
    * @return The GL texture ID of this texture.
    */
   unsigned int init();

   /**
    * Bind the texture for rendering.
    */
   void render() const;
   
   /**
    * Prepare for offscreen rendering.
    * This function sets up the GL viewport to be the correct size for this texture.
    */
   void preRenderToTexture();

   /**
    * Finish offscreen rendering.
    * This function restores the GL viewport, and copies the contents of the back buffer into the texture.
    */
   void postRenderToTexture(GLenum mode);

   /**
    * Set the value of a single pixel.
    * This function will only have any effect before init() is called.
    * @param iX The x-coordinate of the pixel to set.
    * @param iY The y-coordinate of the pixel to set.
    * @param oColour The new colour of the pixel.
    */
   void setPixel(unsigned int iX, unsigned int iY, CRGBAColour oColour);

   /**
    * Get the width of the texture.
    * @return The width of the texture
    */
   unsigned int width() const;
   
   /**
    * Get the height of the texture.
    * @return The height of the texture
    */
   unsigned int height() const;


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

   /**
    * Allow mipmapping of this texture?
    */
   bool m_bMipmap;

};

#endif //SDS_TEXTURE_H
