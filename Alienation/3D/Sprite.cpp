#include "3D/Sprite.h"
#include <SDL_opengl.h>
#include <iostream>

using namespace std;

CSprite::CSprite() :
   m_fSize(1),
   m_uiList(0)
{}

CSprite::CSprite(const CMaterial& oMaterial) :
   m_fSize(1),
   m_oMaterial(oMaterial),
   m_uiList(0)
{}

CSprite::~CSprite()
{
   if (m_uiList)
      glDeleteLists(m_uiList,1);
}

void CSprite::init() {

   // Allocate new list
   m_uiList = glGenLists(1);
   // Create display list   
   glNewList(m_uiList, GL_COMPILE);

   // Set material
   m_oMaterial.render();
   
   // Draw faces
   glBegin(GL_QUADS);										


   // Normal
   glNormal3f(0, 0, -1);

   // Vertices
   for (int i=0; i<2; i++) 
   {
      for (int j=0; j<2; j++) 
      {
         glTexCoord2f( ( i==j ? 1.0f : 0.0f ) , ( i==0 ? 1.0f : 0.0f ) );
         glVertex3f( ( i==j ? 1.0f : -1.0f ) , ( i==0 ? 1.0f : -1.0f ), 0.0f );
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

void CSprite::render() const {
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }

   
	// Push
   glPushMatrix();
   // Translate
   glTranslatef(m_vecTranslation.X(),m_vecTranslation.Y(),m_vecTranslation.Z());
   
   // Get matrix
   float afMatrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, afMatrix);
   // Remove rotation from model/view matrix
   afMatrix[0] = afMatrix[5] = afMatrix[10] = afMatrix[11] = 1.0f;
   afMatrix[1] = afMatrix[2] = afMatrix[3] = afMatrix[4] = 0.0f;
   afMatrix[6] = afMatrix[7] = afMatrix[8] = afMatrix[9] = 0.0f;
   glLoadMatrixf(afMatrix);   

   // Scale
   glScalef(m_fSize,m_fSize,m_fSize);

   // Render
   if (m_uiList)
      glCallList(m_uiList);

   // Pop
   glPopMatrix();
}
