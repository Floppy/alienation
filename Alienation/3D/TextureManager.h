// Texture.h: interface for the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "config.h"
#include <map>
#include "3D/Texture.h"

/**
 * Texture manager class.
 * Deals with all texture objects, including file loading, rendering and ownership of the data.
 * It does this by having one single global instance of the class, g_oTextureManager, and keeping 
 * reference counts for each texture it owns. If only a single class is using a texture, then the
 * reference count can be left at 1, it's default on load. If the texture ID is used in more than 
 * object, each object after the first should call addReference() on creation, and removeReference()
 * on destruction.
 */
class CTextureManager
{
 public:
   
   /**
    * Constructor.
    * @param strTextureRoot The location from which to load texture files.
    */
   CTextureManager(const char* strTextureRoot);

   /**
    * Destructor.
    * Destroys all loaded textures.
    */
   ~CTextureManager();
   
   /**
    * Load a texture from file.
    * The loaded texture will have a reference count of 1. 
    * You don't need to add a reference until you use the texture ID for more than one object.
    * @param strFilename The texture filename to load.
    * @return The texture ID that can be used to access the loaded texture.
    */
   unsigned int load(const char* strFilename);

   /**
    * Create a new texture in memory
    * The loaded texture will have a reference count of 1. 
    * You don't need to add a reference until you use the texture ID for more than one object.
    * @param iX The number of pixels wide the texture should be
    * @param iY The number of pixels high the texture should be
    * @return The texture ID that can be used to access the loaded texture.
    */
   unsigned int create(unsigned int iX, unsigned int iY);

   /**
    * Add a reference to the specified texture.
    * @param uiTexture The texture ID to add the reference to.
    */
   void addReference(unsigned int uiTexture);

   /**
    * Remove a reference from the specified texture.
    * A texture will be deleted when all references are removed.
    * @param uiTexture The texture ID to remove the reference from.
    */
   void removeReference(unsigned int uiTexture);
   
   /**
    * Bind a texture for rendering.
    * @param uiTexture The texture ID to render.
    */
   void render(unsigned int uiTexture);
   
   /**
    * Access the texture itself
    * @param uiTexture The texture ID to access.
    * @return a pointer to the CTexture requested
    */
   CTexture* texture(unsigned int uiTexture);

   /**
    * Access the texture directory location
    * @return The directory from which textures will be loaded.
    */
   const char* textureRoot() const 
   { return m_strTextureRoot; }
   

 protected:
   
   /**
    * Texture pointers.
    */
   std::map<unsigned int, CTexture*> m_hTextures;
   
   /**
    * Reference counts.
    */
   std::map<unsigned int, unsigned int> m_hReferences;

   /**
    * Root location of textures
    */
   char m_strTextureRoot[255];

};

/**
 * A global instance of the CTextureManager class. 
 * All texture access should be done through this object.
 */
extern CTextureManager g_oTextureManager;

#endif // TEXTURE_MANAGER_H
