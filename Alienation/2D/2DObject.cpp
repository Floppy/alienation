#include "2D/2DObject.h"
#include <SDL_opengl.h>

namespace NSD2D {

   int C2DObject::m_iWidth(0);
   int C2DObject::m_iHeight(0);
   
   C2DObject::C2DObject()
   {
   }
   
   C2DObject::~C2DObject()
   {
   }
   
   void C2DObject::renderQuad(float fPosX, float fPosY, float fWidth, float fHeight, CVector2* vecTex)
   {
      glBegin(GL_QUADS);
      
      glTexCoord2fv(vecTex[0].glVector());
      glVertex2f(fPosX, fPosY);
      glTexCoord2fv(vecTex[1].glVector());
      glVertex2f(fPosX + fWidth, fPosY);
      glTexCoord2fv(vecTex[2].glVector());
      glVertex2f(fPosX + fWidth, fPosY - fHeight);
      glTexCoord2fv(vecTex[3].glVector());
      glVertex2f(fPosX, fPosY - fHeight);
      
      glEnd();
   }
   
   void C2DObject::setPosition(int iXPos, int iYPos)
   {
      m_iXPos = iXPos;
      m_iYPos = iYPos;
   }
   
   void C2DObject::setScreen(int iWidth, int iHeight)
   {
      m_iWidth  = iWidth;
      m_iHeight = iHeight;
   }

}
