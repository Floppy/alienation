// Light.cpp: implementation of the CLight class.
//
//////////////////////////////////////////////////////////////////////

#include "Light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLight::CLight(GLenum iLight) :
   m_oAmbient(0,0,0,1),
   m_oDiffuse(1,1,1,1),
   m_iLight(iLight)   
{
   for (int i=0; i<4; i++) 
      m_afPosition[i] = 0;
}

CLight::CLight()
{
}

CLight::~CLight()
{
}

void CLight::init(const CRGBAColour& oAmbient, const CRGBAColour& oDiffuse, const CVector3& oPosition)
{
   update(GL_AMBIENT,oAmbient);
   update(GL_DIFFUSE,oDiffuse);
   setTranslation(oPosition);
}

void CLight::update(GLenum type, const CRGBAColour& oColour)
{
   switch (type) {

   case GL_AMBIENT: {
      m_oAmbient = oColour;
      glLightfv(m_iLight, GL_AMBIENT, m_oAmbient.glColour());
   } break;

   case GL_DIFFUSE: {
      m_oDiffuse = oColour;
      glLightfv(m_iLight, GL_DIFFUSE, m_oDiffuse.glColour());
      glLightfv(m_iLight, GL_SPECULAR, m_oDiffuse.glColour());
   } break;

   default:
     break;
   }
}

void CLight::render()  const {
   // Position
   glLightfv(m_iLight, GL_POSITION, m_afPosition);
}

void CLight::setTranslation(CVector3 oPosition)
{
   // Set values
   for (int i = 0; i < 3 ; i++)
      m_afPosition[i] = oPosition.glVector()[i];
   // Call base
   C3DObject::setTranslation(oPosition);
}

