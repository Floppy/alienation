// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "3D/TextureManager.h"

using namespace std;

CTextureManager g_oTextureManager("Data/Texture/");

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTextureManager::CTextureManager(const char* strTextureRoot)   
{
   strcpy(m_strTextureRoot,strTextureRoot);
}

CTextureManager::~CTextureManager()
{
   // Dump all textures
   for (map<unsigned int,CTexture*>::iterator it(m_hTextures.begin()); it != m_hTextures.end(); it++) {
      delete it->second;
   }
}

unsigned int CTextureManager::load(const char* strFilename)
{   
   // Test if texture has already been loaded
   string str(strFilename);
   map<string, unsigned int>::iterator it = m_hFiles.find(str);
   if (it!=m_hFiles.end()) return it->second;

   // Create new texture
   CTexture* pTexture = new CTexture;
   // Load
   if (pTexture->load(strFilename)) 
   {
      unsigned int uiTexture = m_hTextures.size();
      // Add to hashes
      m_hTextures[uiTexture] = pTexture;
      m_hReferences[uiTexture] = 1;
      // Store filename
      m_hFiles[str] = uiTexture;
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

unsigned int CTextureManager::create(unsigned int iX, unsigned int iY)
{
   // Create new texture
   CTexture* pTexture = new CTexture;
   // Load
   if (pTexture->create(iX,iY)) 
   {
      unsigned int uiTexture = m_hTextures.size();
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

void CTextureManager::render(unsigned int uiTexture)
{
   CTexture* pTexture = m_hTextures[uiTexture];
   if (pTexture) pTexture->render();
}

CTexture* CTextureManager::texture(unsigned int uiTexture) {
   return m_hTextures[uiTexture];
}
