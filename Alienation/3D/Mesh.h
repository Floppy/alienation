#ifndef ALIENATION_MESH_H
#define ALIENATION_MESH_H

#include "config.h"
#include "3D/3DObject.h"
#include "3D/Material.h"

/**
 * A polygon mesh structure.
 */
class CMesh : public C3DObject {
   
 public:
   
   /**
    * Constructor.
    */
   CMesh();
   // 
   
   /**
    * Destructor.
    */
   virtual ~CMesh();
   
   /**
    * Perform one-time initialisation.
    * Should be called once the mesh is completely loaded/created.
    */
   void init();

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
    * Mesh material
    */
   CMaterial m_oMaterial;

};

#endif // ALIENATION_MESH_H
