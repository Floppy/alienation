#include "3D/Mesh.h"
#include <GL/gl.h>
#include <iostream>

using namespace std;

CMesh::CMesh() :
   m_iNumVertices(0),
   m_iNumFaces(0),
   m_iNumTexVertex(0),
   m_pIndices(NULL),
   m_pVerts(NULL),
   m_pNormals(NULL),
   m_pTexVerts(NULL),
   m_pFaces(NULL),
   m_uiList(0)
{}

CMesh::~CMesh() {
   glDeleteLists(m_uiList,1);
   delete [] m_pFaces;
   delete [] m_pNormals;
   delete [] m_pVerts;
   delete [] m_pTexVerts;
   delete [] m_pIndices;
}

void CMesh::init() {

   // Calculate normals
   computeNormals();

   // Allocate new list
   m_uiList = glGenLists(1);
   glEnable(GL_TEXTURE_2D);
   // Create display list   
   glNewList(m_uiList, GL_COMPILE);   
   
   // Set material
   m_oMaterial.render();
   
   // Draw faces
   glBegin(GL_TRIANGLES);										
   // For each face
   for(int j = 0; j < m_iNumFaces; j++)
   {
      // For each vertex in the face
      for(int iWhichVertex = 0; iWhichVertex < 3; iWhichVertex++)
      {
         // Get vertex number
         int iIndex = m_pFaces[j].m_iVertIndex[iWhichVertex];
         // Normal
         glNormal3f(m_pNormals[iIndex].m_fx, m_pNormals[iIndex].m_fy, m_pNormals[iIndex].m_fz);
         // Texture coordinates
         if(m_pTexVerts) {
            glTexCoord2fv(m_pTexVerts[iIndex].glVector());
         }
         // Vertex coordinate
         glVertex3f(m_pVerts[ iIndex ].m_fx, m_pVerts[ iIndex ].m_fy, m_pVerts[ iIndex ].m_fz);
      }
   }
   // Done drawing
   glEnd();
   // Finish the list
   glEndList();   
   // Done
   C3DObject::init();
   return;
}

void CMesh::render() const {
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }
   // Push
   glPushMatrix();
   // Translate
   glTranslatef(m_vecTranslation.m_fx,m_vecTranslation.m_fy,m_vecTranslation.m_fz);
   // Render
   if (m_uiList)
      glCallList(m_uiList);
   // Pop
   glPopMatrix();
}

void CMesh::computeNormals() {
   // If we already have normals, quit
   if (m_pNormals) return;
   
   // Allocate storage
   CVector3 *pFaceNormals = new CVector3 [m_iNumFaces];
   m_pNormals = new CVector3 [m_iNumVertices];
   
   // Calculate face normals
   int i;
   for(i=0; i < m_iNumFaces; i++)
   {												
      // Calculate edge vectors
      CVector3 vecEdge1(m_pVerts[m_pFaces[i].m_iVertIndex[0]] - m_pVerts[m_pFaces[i].m_iVertIndex[2]]);
      CVector3 vecEdge2(m_pVerts[m_pFaces[i].m_iVertIndex[2]] - m_pVerts[m_pFaces[i].m_iVertIndex[1]]);
      // Do cross product to get normal
      pFaceNormals[i] = vecEdge1.cross(vecEdge2);
      pFaceNormals[i].unitize();      
   }
   
   // Calculate vertex normals from face normals
   for (i = 0; i < m_iNumVertices; i++)		
   {
      // Initialise vertex normal
      m_pNormals[i] = CVector3(0.0, 0.0, 0.0);
      // Find all faces adjoining this vertex
      for (int j = 0; j < m_iNumFaces; j++)	
      {												
         if (m_pFaces[j].m_iVertIndex[0] == i || 
             m_pFaces[j].m_iVertIndex[1] == i || 
             m_pFaces[j].m_iVertIndex[2] == i)
         {
            // Add normal
            m_pNormals[i] += pFaceNormals[j];
         }
      }
      // Normalise
      m_pNormals[i].unitize();
   }

   // Dump face normals - don't need them
   delete [] pFaceNormals;   
}
