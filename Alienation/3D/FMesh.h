#ifndef ALIENATION_FMESH_H
#define ALIENATION_FMESH_H

#include "config.h"
#include "3D/Mesh.h"
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
 * A fixed-topology polygon mesh structure.
 */
class CFMesh : public CMesh {
   
 public:
   
   /**
    * Constructor.
    */
   CFMesh();
   // 
   
   /**
    * Destructor.
    * Deletes all allocated data.
    */
   virtual ~CFMesh();
   
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
    * OpenGL display list ID
    */
   unsigned int m_uiList;

};

#endif // ALIENATION_FMESH_H
