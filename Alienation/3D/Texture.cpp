// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "3D/Texture.h"
#include <SDL_image.h>
#include <GL/gl.h>

#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture() :
   m_uiTexture(0)
{
}

bool CTexture::load(const char* strFilename)
{
   bool bGood = false;
   char strFile[200];
   
   // We will load into an SDL surface
   SDL_Surface * poTextureImage = NULL;
   
   if (strlen(strFilename) == 0)
      return false;
   
   strcpy(strFile, "Data/Texture/");
   strcat(strFile, strFilename);
   
   // Load the file
   poTextureImage = IMG_Load(strFile);
   
   // If texture was loaded OK
   if (poTextureImage)
   {
      bGood=true;
      
      glGenTextures(1, &m_uiTexture);
      
      // Convert surface to right pixel format
      if (poTextureImage->format->BitsPerPixel != 32) 
      {
         // Create pixel format
         SDL_PixelFormat fmt;
         fmt.palette = NULL;
         fmt.BitsPerPixel = 32;

         // Check byte ordering
#if SDL_BYTEORDER == 1234
         fmt.Rmask=0x000000ff;
         fmt.Gmask=0x0000ff00;
         fmt.Bmask=0x00ff0000;
         fmt.Amask=0xff000000;
#else
         fmt.Rmask=0xff000000;
         fmt.Gmask=0x00ff0000;
         fmt.Bmask=0x0000ff00;
         fmt.Amask=0x000000ff;
#endif

         // Convert
         SDL_Surface * tmp = poTextureImage;
         poTextureImage = SDL_ConvertSurface(tmp, &fmt, SDL_HWSURFACE);
         SDL_FreeSurface(tmp);
      }
      
      // Create Linear Filtered Texture
      glBindTexture(GL_TEXTURE_2D, m_uiTexture);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, poTextureImage->w, poTextureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, poTextureImage->pixels);

   }

   // Free the SDL surface
   SDL_FreeSurface(poTextureImage);
   // Done
   return bGood;
}
