// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "3D/TextureManager.h"
#include <GL/gl.h>

#include <iostream>
using namespace std;

CTextureManager g_oTextureManager;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
   // Dump all textures
   for (std::map<unsigned int,CTexture*>::iterator it(m_hTextures.begin()); it != m_hTextures.end(); it++) {
      delete it->second;
   }
}

unsigned int CTextureManager::load(const char* strFilename)
{   
   // Create new texture
   CTexture* pTexture = new CTexture;
   // Load
   if (pTexture->load(strFilename)) 
   {
      unsigned int uiTexture = pTexture->ID();
      // Add to hashes
      m_hTextures[uiTexture] = pTexture;
      m_hReferences[uiTexture] = 1;
      // Done
      return uiTexture;
   }
   else 
   {
      // Drop created texture
      delete pTexture;
      // Done
      return 0;
   }
}

void CTextureManager::addReference(unsigned int uiTexture) 
{
   // Increment reference count
   ++(m_hReferences[uiTexture]);
}

void CTextureManager::removeReference(unsigned int uiTexture) 
{
   if (--(m_hReferences[uiTexture]) == 0) {
      // Delete texture
      delete m_hTextures[uiTexture];
      // Dump map entries
      m_hTextures.erase(uiTexture);
      m_hReferences.erase(uiTexture);
   }   
}

void CTextureManager::activate(unsigned int uiTexture) const
{
   glBindTexture(GL_TEXTURE_2D, uiTexture);
}

bool CTextureManager::valid(unsigned int uiTexture) const 
{
   return glIsTexture(uiTexture);
}
