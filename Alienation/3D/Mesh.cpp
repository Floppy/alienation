#include "3D/Mesh.h"

CMesh::CMesh() :
   m_iNumVertices(0),
   m_iNumFaces(0),
   m_iNumTexVertex(0),
   m_iMaterialID(0),
   m_bHasTexture(false),
   m_pIndices(NULL),
   m_pVerts(NULL),
   m_pNormals(NULL),
   m_pTexVerts(NULL),
   m_pFaces(NULL)
{}

