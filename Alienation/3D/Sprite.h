#ifndef ALIENATION_SPRITE_H
#define ALIENATION_SPRITE_H

#include "config.h"
#include "3D/3DObject.h"
#include "3D/Material.h"

/**
 * A billboarded sprite.
 */
class CSprite : public C3DObject {
   
 public:
   
   /**
    * Constructor.
    */
   CSprite();

   /**
    * Constructor with material.
    */
   CSprite(const CMaterial& oMaterial);
   
   /**
    * Destructor.
    */
   ~CSprite();
   
   /**
    * Perform one-time initialisation.
    * Should be called once the sprite is completely loaded/created.
    * Builds a display list for the sprite.
    */
   void init();

   /** 
    * Render to screen.
    * Renders the display list built in init()
    */
   void render() const;
    
   /** 
    * Get current size.
    */
   float getSize() const 
   { return m_fSize; }

   /** 
    * Set size.
    * @param fSize New size.
    */
   void setSize(float fSize)
   { m_fSize = fSize; }

   /** 
    * Access the mesh material properties.
    * @return A reference to the material.
    */
   const CMaterial& getMaterial() const
   { return m_oMaterial; }
   
   /** 
    * Set the material properties for the mesh.    
    * @param oMaterial The new material to use.
    */
   void setMaterial(CMaterial& oMaterial)
   { m_oMaterial = oMaterial; }

 protected:
   
   /** 
    * Size
    */
   float m_fSize;

   /** 
    * Material
    */
   CMaterial m_oMaterial;

   /** 
    * OpenGL display list ID
    */
   unsigned int m_uiList;

};

#endif // ALIENATION_SPRITE_H
