#ifndef ALIENATION_MESH_H
#define ALIENATION_MESH_H

#include "config.h"
#include "vector.h"

class CFace
{
public:
   int m_iVertIndex[3];
   int m_iCoordIndex[3];
};


class CMesh {
   
 public:
   
   CMesh();
   
   // Data inherited from C3DModel
   
   int  m_iNumVertices;
   int  m_iNumFaces;
   int  m_iNumTexVertex;
   int  m_iMaterialID;
   bool m_bHasTexture;
   char m_strName[255];
   unsigned int *m_pIndices;
   CVector3 *m_pVerts;
   CVector3 *m_pNormals;
   CVector2 *m_pTexVerts;
   CFace *m_pFaces;
   
};

#endif // ALIENATION_MESH_H
