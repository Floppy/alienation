#include "3D/FMesh.h"
#include <SDL_opengl.h>
#include <iostream>
#include "GL/Extensions.h"

extern bool bNoBumps;

using namespace std;

CFMesh::CFMesh() :
   m_iNumVertices(0),
   m_iNumFaces(0),
   m_iNumTexVertex(0),
   m_pVerts(NULL),
	m_pTangents(NULL),
	m_pBiNormals(NULL),
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
	delete [] m_pTangents;
	delete [] m_pBiNormals;
}

void CFMesh::init() {

	int i, j;
	int iFaceIndex = 0;
	CVector3 *tangent, *binormal;

   // Initialise material
   m_oMaterial.init();

	tangent = new CVector3();
	binormal = new CVector3();
	m_pTangents  = new CVector3[m_iNumVertices];
	m_pBiNormals = new CVector3[m_iNumVertices];

												//////////////////////////////////////////////
												//Calculating the tangent space (Should be  //
												//done eventually for every model, so is    //
												//now)                                      //
												//////////////////////////////////////////////

	if (m_oMaterial.m_bHasBumpMap)
	{
		for ( j = 0 ; j < m_iNumFaces ; j++)
		{
			tangentBasis(m_pVerts[m_pFaces[j].m_iVertIndex[0]], 
							 m_pVerts[m_pFaces[j].m_iVertIndex[1]], 
							 m_pVerts[m_pFaces[j].m_iVertIndex[2]],
							 m_pTexVerts[m_pFaces[j].m_iVertIndex[0]],
							 m_pTexVerts[m_pFaces[j].m_iVertIndex[1]], 
							 m_pTexVerts[m_pFaces[j].m_iVertIndex[2]],
							 tangent, binormal);
			for ( i = 0 ; i < 3 ; i++ )
			{
				m_pTangents [ m_pFaces[j].m_iVertIndex[i] ] = CVector3(tangent->X(), tangent->Y(), tangent->Z());
				m_pBiNormals[ m_pFaces[j].m_iVertIndex[i] ] = CVector3(binormal->X(), binormal->Y(), binormal->Z());
			}
		}
	}
   // Calculate normals
   computeNormals();

   // Allocate new list
   m_uiList = glGenLists(1);
   // Create display list   
   glNewList(m_uiList, GL_COMPILE);   
   
   // Set material
   m_oMaterial.render();
//   m_oMaterial.disableDot3();

   // Draw faces
   glBegin(GL_TRIANGLES);										
   // For each face
   for(j = 0; j < m_iNumFaces; j++)
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
				glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_pTexVerts[iIndex].X(), m_pTexVerts[iIndex].Y());
				glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_pTexVerts[iIndex].X(), m_pTexVerts[iIndex].Y());
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
   for (i=0; i<m_iNumVertices; i++) 
   {
      float fLength = m_pVerts[i].length();
      if (fLength > m_oSphere.m_fRadius) m_oSphere.m_fRadius = fLength;
   }

   // Done
   CMesh::init();
   return;
}

void CFMesh::renderDOT3() const
{
	int i, j;
	CVector3 lightpos = CVector3(0.0f, 0.0f, -1000.0f);
	CVector3 lightVector;
	CVector3 colour;
	CVector3 vecTranslation;
	CMatrix  mat, rotMat;

	m_oMaterial.renderBumpMap();

	m_oMaterial.render();
	rotMat = CMatrix(this->getRotation());
	vecTranslation = CVector3(this->getTranslation());
	lightVector = (rotMat * lightVector) - vecTranslation;

	glBegin(GL_TRIANGLES);
   for(i = 0; i < m_iNumFaces; i++)
	{
		for(j=0;j<3;j++)
		{
         // Get vertex number
         int iIndex = m_pFaces[i].m_iVertIndex[j];

			lightVector = lightpos - m_pVerts[iIndex];

			if(lightVector.length() != 0.0f)
			{
				lightVector.normalise();
			}

//			colour = CVector3(lightVector.dot(m_pTangents [iIndex]),
//									lightVector.dot(m_pBiNormals[iIndex]),
//									lightVector.dot(m_pNormals  [iIndex]));

			mat.loadIdentity();
			mat.setElement(0,  m_pTangents[iIndex].X());
			mat.setElement(1,  m_pBiNormals[iIndex].X());
			mat.setElement(2,  m_pNormals[iIndex].X());
			mat.setElement(4,  m_pTangents[iIndex].Y());
			mat.setElement(5,  m_pBiNormals[iIndex].Y());
			mat.setElement(6,  m_pNormals[iIndex].Y());
			mat.setElement(8,  m_pTangents[iIndex].Z());
			mat.setElement(9,  m_pBiNormals[iIndex].Z());
			mat.setElement(10, m_pNormals[iIndex].Z());

			colour = mat * lightVector;

			colour = (colour * 0.5f) + 0.5f;

			glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_pTexVerts[iIndex].X(), m_pTexVerts[iIndex].Y());
			glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_pTexVerts[iIndex].X(), m_pTexVerts[iIndex].Y());
			glColor3fv(colour.glVector());
         glNormal3fv(m_pNormals[iIndex].glVector());
         glVertex3fv(m_pVerts[iIndex].glVector());
		}
	}
	glEnd();

	m_oMaterial.disableDot3();
}

void CFMesh::render() const {

	GLboolean bTexEnabled;

   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }

	glGetBooleanv(GL_TEXTURE_2D, &bTexEnabled);
	if (m_oMaterial.m_bHasBumpMap && bTexEnabled && !bNoBumps)
	{
		renderDOT3();
	}
	else
	{
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

void CFMesh::tangentBasis(CVector3 v0, CVector3 v1, CVector3 v2, CVector2 t0, CVector2 t1, CVector2 t2, CVector3 *tangent, CVector3 *binormal)
{
	CVector3 cp;
	float fTangentX(0.0f), fTangentY(0.0f), fTangentZ(0.0f);
	float fBiNormalX(0.0f), fBiNormalY(0.0f), fBiNormalZ(0.0f);

	CVector3 e0 = CVector3(v1.X() - v0.X(), t1.X() - t0.X(), t1.Y() - t0.Y() );
	CVector3 e1 = CVector3(v2.X() - v0.X(), t2.X() - t0.X(), t2.Y() - t0.Y() );

	cp = e0.cross(e1);

	if(fabs(cp.X())>0.00001f)
	{
		fTangentX  = -cp.Y() / cp.X();
		fBiNormalX = -cp.Z() / cp.X();
	}

	e0 = CVector3(v1.Y() - v0.Y(), t1.X() - t0.X(), t1.Y() - t0.Y() );
	e1 = CVector3(v2.Y() - v0.Y(), t2.X() - t0.X(), t2.Y() - t0.Y() );

	cp = e0.cross(e1);

	if(fabs(cp.X())>0.00001f)
	{
		fTangentY  = -cp.Y() / cp.X();
		fBiNormalY = -cp.Z() / cp.X();
	}

	e0 = CVector3(v1.Z() - v0.Z(), t1.X() - t0.X(), t1.Y() - t0.Y() );
	e1 = CVector3(v2.Z() - v0.Z(), t2.X() - t0.X(), t2.Y() - t0.Y() );

	cp = e0.cross(e1);

	if(fabs(cp.X())>0.00001f)
	{
		fTangentZ  = -cp.Y() / cp.X();
		fBiNormalZ = -cp.Z() / cp.X();
	}

	binormal->setX(fBiNormalX);
	binormal->setY(fBiNormalY);
	binormal->setZ(fBiNormalZ);

	tangent->setX(fTangentX);
	tangent->setY(fTangentY);
	tangent->setZ(fTangentZ);

	binormal->normalise();
	tangent->normalise();

}
