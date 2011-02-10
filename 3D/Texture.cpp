#include "3D/Texture.h"
#include "3D/TextureManager.h"

#include <SDL_image.h>
#include <SDL_opengl.h>
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture() :
   m_pTexture(NULL),
   m_uiTextureID(0),
   m_bMipmap(true)
{
}

CTexture::~CTexture() 
{
   // Dump SDL surface
   if (m_pTexture) SDL_FreeSurface(m_pTexture);
   // Dump GL texture ID
   if (m_uiTextureID) glDeleteTextures(1, &m_uiTextureID);
}

bool CTexture::load(const char* strFilename, bool bMipmap)
{
   m_bMipmap = bMipmap;

   // Free any existing SDL surface
   if (m_pTexture) 
   {
      SDL_FreeSurface(m_pTexture);
      m_pTexture = NULL;
   }

   bool bGood = false;
   char strFile[200];
   
   // We will load into an SDL surface
   SDL_Surface * pNewTex = NULL;
   
   if (strlen(strFilename) == 0)
      return false;
   
   strcpy(strFile, g_oTextureManager.textureRoot());
   strcat(strFile, strFilename);
   
   // Load the file
   pNewTex = IMG_Load(strFile);
   

   // If texture was loaded OK
   if (pNewTex)
   {
      bGood=true;
      
      // Convert surface to right pixel format
      if (pNewTex->format->BitsPerPixel != 32) 
      {
         // Create pixel format
         SDL_PixelFormat fmt;
         fmt.palette = NULL;
         fmt.BitsPerPixel = 32;

         // Create masks
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
         fmt.Rmask=0xff000000;
         fmt.Gmask=0x00ff0000;
         fmt.Bmask=0x0000ff00;
         fmt.Amask=0x000000ff;
#else
         fmt.Rmask=0x000000ff;
         fmt.Gmask=0x0000ff00;
         fmt.Bmask=0x00ff0000;
         fmt.Amask=0xff000000;
#endif

         // Convert         
         m_pTexture = SDL_ConvertSurface(pNewTex, &fmt, SDL_HWSURFACE);
         SDL_FreeSurface(pNewTex);
	 
      }
      else 
         m_pTexture = pNewTex;

   }

   // Done
   return bGood;
}

bool CTexture::create(unsigned int iX, unsigned int iY)
{
   // Free any existing SDL surface
   if (m_pTexture) 
   {
      SDL_FreeSurface(m_pTexture);
      m_pTexture = NULL;
   }
         
   // Create masks
   unsigned int rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
   rmask = 0xff000000;
   gmask = 0x00ff0000;
   bmask = 0x0000ff00;
   amask = 0x000000ff;
#else
   rmask = 0x000000ff;
   gmask = 0x0000ff00;
   bmask = 0x00ff0000;
   amask = 0xff000000;
#endif

   m_pTexture = SDL_CreateRGBSurface(SDL_SWSURFACE, iX, iY, 32, rmask, gmask, bmask, amask);

   // Don't mipmap manually created textures - at least for now
   m_bMipmap = false;

   return (m_pTexture != NULL);
}

unsigned int CTexture::init() 
{
   if (m_pTexture) {

      // Get maximum texture size
      int iTexSize(0);
      glGetIntegerv(GL_MAX_TEXTURE_SIZE,&iTexSize);
       
      // Rescale?
      
      if (m_uiTextureID == 0)
         // Allocate GL texture ID
         glGenTextures(1, &m_uiTextureID);

      // Bind
      glBindTexture(GL_TEXTURE_2D, m_uiTextureID);

      // Set minification params
      if (m_bMipmap)
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, g_oTextureManager.minFilter());
      else 
         // If no mipmapping, use magnification mode for minification too.
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, g_oTextureManager.magFilter());

      // Set magnification params
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, g_oTextureManager.magFilter());

      // Copy data to GL texture
      if (g_oTextureManager.mipmapsEnabled() && m_bMipmap)
         gluBuild2DMipmaps(GL_TEXTURE_2D,4,m_pTexture->w, m_pTexture->h, 
                           GL_RGBA, GL_UNSIGNED_BYTE, m_pTexture->pixels);
      else
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pTexture->w, m_pTexture->h, 0, 
                      GL_RGBA, GL_UNSIGNED_BYTE, m_pTexture->pixels);
   }
   return m_uiTextureID;
}

void CTexture::render() const
{
   // Bind
   glBindTexture(GL_TEXTURE_2D, m_uiTextureID);
}

void CTexture::preRenderToTexture() { 
   // Store viewport size
   glGetIntegerv(GL_VIEWPORT,m_aiViewport);
   // Resize viewport
   glViewport(0,0,m_pTexture->w, m_pTexture->h);

}

void CTexture::postRenderToTexture(GLenum mode) {
   // Bind texture
   glBindTexture(GL_TEXTURE_2D,m_uiTextureID);
   // Copy image from back buffer
   glCopyTexImage2D(GL_TEXTURE_2D, 0, mode, 0, 0, m_pTexture->w, m_pTexture->h, 0);
   // Restore viewport
   glViewport(m_aiViewport[0],m_aiViewport[1],m_aiViewport[2],m_aiViewport[3]);
}

void CTexture::setPixel(unsigned int iX, unsigned int iY, CRGBAColour oColour) 
{
   // Check texture exists
   if (!m_pTexture) return;
   // Lock
   if (SDL_MUSTLOCK(m_pTexture)) SDL_LockSurface(m_pTexture);
   // Calculate pixel value
   unsigned int iPixel = 
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      static_cast<unsigned int>(oColour.R() * 0xFF) << 24| 
      static_cast<unsigned int>(oColour.G() * 0xFF) << 16 | 
      static_cast<unsigned int>(oColour.B() * 0xFF) << 8 | 
      static_cast<unsigned int>(oColour.A() * 0xFF);
#else
      static_cast<unsigned int>(oColour.R() * 0xFF) | 
      static_cast<unsigned int>(oColour.G() * 0xFF) << 8 | 
      static_cast<unsigned int>(oColour.B() * 0xFF) << 16 | 
      static_cast<unsigned int>(oColour.A() * 0xFF) << 24;
#endif
   // Set pixel
   static_cast<unsigned int*>(m_pTexture->pixels)[iY * m_pTexture->w + iX] = iPixel;
   // Unlock
   if (SDL_MUSTLOCK(m_pTexture)) SDL_UnlockSurface(m_pTexture);
   // Done
   return;
}

unsigned int CTexture::width() const {
   if (m_pTexture) return m_pTexture->w;
   return 0;
}

unsigned int CTexture::height() const {
   if (m_pTexture) return m_pTexture->h;
   return 0;
}
