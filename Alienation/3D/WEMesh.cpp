#include "3D/WEMesh.h"
#include <SDL_opengl.h>
#include <iostream>

using namespace std;

CWEMesh::CWEMesh() {
}

CWEMesh::CWEMesh(CFMesh& oMesh) {
   int i;
   // Preallocate storage
   m_lpVertices.reserve(oMesh.m_iNumVertices);
   m_lpFaces.reserve(oMesh.m_iNumFaces);
   m_lTexVerts.reserve(oMesh.m_iNumTexVertex);   

   // Copy texture coordinates
   for (i=0; i<oMesh.m_iNumTexVertex; i++)
      m_lTexVerts.push_back(oMesh.m_pTexVerts[i]);

   // Copy vertices
   for (i=0; i<oMesh.m_iNumVertices; i++)
   {
      CWEVertex* pNewVertex = new CWEVertex(oMesh.m_pVerts[i]);
      m_lpVertices.push_back(pNewVertex);
   }

   // Insert faces
   for (i=0; i<oMesh.m_iNumFaces; i++)
   {
      CWEFace* pNewFace = new CWEFace;
      for (int j=0; j<3; j++) 
      {
         // Copy texture coordinate
         pNewFace->m_iCoordIndex[j] = oMesh.m_pFaces[i].m_iCoordIndex[j];
         // Find edge
         int iFrom = oMesh.m_pFaces[i].m_iVertIndex[j];
         int iTo = oMesh.m_pFaces[i].m_iVertIndex[(j+1)%3];
         // Check if edge already exists
         CWEEdge* pEdge = adjacent(m_lpVertices[iFrom],m_lpVertices[iTo]);
         if (pEdge) {
            // Edge does exist
            if (pEdge->m_pStart == m_lpVertices[iFrom] && pEdge->m_pRight == NULL) {
               pEdge->m_pRight = pNewFace;
            }
            else if (pEdge->m_pLeft == NULL) {
               pEdge->m_pLeft = pNewFace;
            }
            else {
               cerr << "ERROR: Non-manifold surface" << endl;
            }
         }
         else {
            // Edge does not exist - create it
            pEdge = new CWEEdge;
            pEdge->m_pStart = m_lpVertices[iFrom];
            pEdge->m_pEnd = m_lpVertices[iTo];
            pEdge->m_pRight = pNewFace;
            
         }
      }
   }   
   
}

CWEMesh::~CWEMesh() {
}

void CWEMesh::init() {
   CMesh::init();
   return;
}

void CWEMesh::render() const {
   // We're not using a display list for this, as it could change at any time.
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }

   // Set material
   m_oMaterial.render();
   
   // Draw faces
   glBegin(GL_TRIANGLES);
   // For each face
   for(vector<CWEFace*>::const_iterator it(m_lpFaces.begin()); it != m_lpFaces.end(); it++)
   {
      // Get starting edge
      CWEEdge* pFirst = (*it)->m_pEdge;
      CWEEdge* pCurrent = pFirst;
      // Traverse edges
      do {
         // Vertex coordinate
         glVertex3fv(pCurrent->m_pStart->m_vecPosition.glVector());
         // Done
      } while (pCurrent != pFirst);
   } 
   // Done drawing
   glEnd();

   

}

CWEEdge* CWEMesh::adjacent(CWEVertex* pVert1, CWEVertex* pVert2) {
   // Get edge
   CWEEdge* pEdge = pVert1->m_pEdge;
   if (!pEdge) return pEdge;
   // Search all attached edges 
   do {
      // Get other vertex
      CWEVertex* pOther = (pEdge->m_pStart == pVert1) ? pEdge->m_pEnd : pEdge->m_pStart;
      // Check if we've found what we want
      if (pOther == pVert2) return pEdge;
      // If not, go to the next left edge
      else pEdge = pEdge->m_pNextLeft;
   } while (pEdge && pEdge != pVert1->m_pEdge);
   // failed
   return NULL;
}

void CWEMesh::setWings(CWEEdge* pEdge1, CWEEdge* pEdge2) {
   if (pEdge1->m_pStart == pEdge2->m_pStart) {
      if (pEdge1->m_pLeft == pEdge2->m_pRight) {
         pEdge1->m_pNextLeft = pEdge2;
         pEdge2->m_pPrevRight = pEdge1;
      }
      else if (pEdge1->m_pRight == pEdge2->m_pLeft) {
         pEdge1->m_pPrevRight = pEdge2;
         pEdge2->m_pNextLeft = pEdge1;
      }      
   }
   else if (pEdge1->m_pStart == pEdge2->m_pEnd) {
      if (pEdge1->m_pLeft == pEdge2->m_pLeft) {
         pEdge1->m_pNextLeft = pEdge2;
         pEdge2->m_pPrevLeft = pEdge1;         
      }
      else if (pEdge1->m_pRight == pEdge2->m_pRight) {
         pEdge1->m_pPrevRight = pEdge2;
         pEdge2->m_pNextRight = pEdge1;
      }
   }
   else if (pEdge1->m_pEnd == pEdge2->m_pStart) {
      if (pEdge1->m_pRight == pEdge2->m_pRight) {
         pEdge1->m_pNextRight = pEdge2;
         pEdge2->m_pPrevRight = pEdge1;         
      }
      else if (pEdge1->m_pLeft == pEdge2->m_pLeft) {
         pEdge1->m_pPrevLeft = pEdge2;
         pEdge2->m_pNextLeft = pEdge1;
      }
   }
   else if (pEdge1->m_pEnd == pEdge2->m_pEnd) {
      if (pEdge1->m_pRight == pEdge2->m_pLeft) {
         pEdge1->m_pNextRight = pEdge2;
         pEdge2->m_pPrevLeft = pEdge1;
      }
      else if (pEdge1->m_pLeft == pEdge2->m_pRight) {
         pEdge1->m_pPrevLeft = pEdge2;
         pEdge2->m_pNextRight = pEdge1;
      }
   }
}
