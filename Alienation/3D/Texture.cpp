// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "3D/Texture.h"
#include <SDL_image.h>
#include <SDL_opengl.h>

#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture() :
   m_uiTexture(0),
   m_iX(0),
   m_iY(0)
{
}

CTexture::~CTexture() 
{
   // Dump GL texture ID
   if (m_uiTexture) glDeleteTextures(1, &m_uiTexture);
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

bool CTexture::create(unsigned int iX, unsigned int iY)
{
   // Allocate texture
   int iSize(iX * iY * 4);
   unsigned char* pcTextureData(NULL);
   try {
      pcTextureData = new unsigned char[iSize];
   } catch (...) {
      return false;
   }
   // Clear memory
   memset(pcTextureData,0,iSize);

   // Allocate GL texture ID
   glGenTextures(1, &m_uiTexture);

   glBindTexture(GL_TEXTURE_2D, m_uiTexture);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_iX, m_iY, 0, GL_RGBA, GL_UNSIGNED_BYTE, pcTextureData);
   
   // Dump data
   delete [] pcTextureData;
   
   return true;
}



void CTexture::prerender() {
   glGetIntegerv(GL_VIEWPORT,m_aiViewport);
   // Resize viewport
   glViewport(0,0,m_iX,m_iY);
}

void CTexture::postrender() {
   // Bind texture
   glBindTexture(GL_TEXTURE_2D,m_uiTexture);
   // Copy image from back buffer
   glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, m_iX, m_iY, 0);
   // Restore viewport
   glViewport(m_aiViewport[0],m_aiViewport[1],m_aiViewport[2],m_aiViewport[3]);
   // Clear screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

