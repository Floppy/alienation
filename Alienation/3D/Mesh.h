#ifndef ALIENATION_MESH_H
#define ALIENATION_MESH_H

#include "config.h"
#include "3D/3DObject.h"
#include "3D/Material.h"
#include "Math/Vector.h"

/**
 * A triangular mesh face.
 * Contains vertex and texture coordinate indices.
 */
class CFace
{

public:

   /**
    * Vertex indices for each corner.
    */
   int m_iVertIndex[3];

   /**
    * Texture coordinate indices for each corner.
    */
   int m_iCoordIndex[3];

};


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
    * Deletes all allocated data.
    */
   ~CMesh();
   
   /**
    * Perform one-time initialisation.
    * Should be called once the mesh is completely loaded/created.
    * Calculates vertex normals, and build an OpenGL display list for the mesh.
    */
   void init();

   /** 
    * Render to screen.
    * Current implementation simply calls the GL display list set up in init().
    */
   void render() const;
    
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
    * Calculate vertex normals.
    * Called during init().
    */
   void computeNormals();
   
 public:
   
   /** 
    * Number of vertices in mesh
    */
   int  m_iNumVertices;

   /** 
    * Number of faces in mesh
    */
   int  m_iNumFaces;

   /** 
    * Number of texture coordinates in mesh
    */
   int  m_iNumTexVertex;

   /** 
    * Vertex array
    */
   CVector3 *m_pVerts;

   /** 
    * Texture coordinate array
    */
   CVector2 *m_pTexVerts;

   /** 
    * Face array
    */
   CFace *m_pFaces;
   
 protected:

   /** 
    * Vertex normal array
    */
   CVector3 *m_pNormals;

   /** 
    * Mesh material
    */
   CMaterial m_oMaterial;

   /** 
    * OpenGL display list ID
    */
   unsigned int m_uiList;

};

#endif // ALIENATION_MESH_H
