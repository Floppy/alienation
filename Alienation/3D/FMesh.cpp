#include "3D/FMesh.h"
#include <SDL_opengl.h>
#include <iostream>

using namespace std;

CFMesh::CFMesh() :
   m_iNumVertices(0),
   m_iNumFaces(0),
   m_iNumTexVertex(0),
   m_pVerts(NULL),
   m_pTexVerts(NULL),
   m_pFaces(NULL),
   m_pNormals(NULL),
   m_uiList(0)
{}

CFMesh::~CFMesh() {
   glDeleteLists(m_uiList,1);
   delete [] m_pFaces;
   delete [] m_pNormals;
   delete [] m_pVerts;
   delete [] m_pTexVerts;
}

void CFMesh::init() {

   // Initialise material
   m_oMaterial.init();

   // Calculate normals
   computeNormals();

   // Allocate new list
   m_uiList = glGenLists(1);
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
         glNormal3fv(m_pNormals[iIndex].glVector());
         // Texture coordinates
         if(m_pTexVerts) {
            glTexCoord2fv(m_pTexVerts[iIndex].glVector());
         }
         // Vertex coordinate
         glVertex3fv(m_pVerts[iIndex].glVector());
      }
   }
   // Done drawing
   glEnd();
   // Finish the list
   glEndList();   

   // Calculate bounding sphere
   for (int i=0; i<m_iNumVertices; i++) 
   {
      float fLength = m_pVerts[i].length();
      if (fLength > m_oSphere.m_fRadius) m_oSphere.m_fRadius = fLength;
   }

   // Done
   CMesh::init();
   return;
}

void CFMesh::render() const {
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }
   // Push
   glPushMatrix();
   // Translate
   glTranslatef(m_vecTranslation.X(),m_vecTranslation.Y(),m_vecTranslation.Z());
   // Render
   if (m_uiList)
      glCallList(m_uiList);
   // Pop
   glPopMatrix();
}

void CFMesh::computeNormals() {
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
      pFaceNormals[i].normalise();      
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
      m_pNormals[i].normalise();
   }

   // Dump face normals - don't need them
   delete [] pFaceNormals;   
}
