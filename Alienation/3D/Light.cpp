// Light.cpp: implementation of the CLight class.
//
//////////////////////////////////////////////////////////////////////

#include "Light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLight::CLight(GLenum iLight) :
   m_iLight(iLight)
{
}

CLight::~CLight()
{
}

void CLight::init(float afAmbient[4], float afDiffuse[4], float afPosition[4])
{
   // Turn on lighting
   glEnable(GL_LIGHTING);

   // Set values
   for (int i = 0; i < 4 ; i++)
   {
      m_afLightAmbient[i] = afAmbient[i];
      m_afLightDiffuse[i] = afDiffuse[i];
      m_afLightPosition[i] = afPosition[i];
   }

   // Setup GL
   glLightfv(m_iLight, GL_AMBIENT, m_afLightAmbient);
   glLightfv(m_iLight, GL_DIFFUSE, m_afLightDiffuse);
   glLightfv(m_iLight, GL_POSITION, m_afLightPosition);
   
}

void CLight::update(GLenum type, float afAmount[4])
{
   glLightfv(m_iLight, type, afAmount);
}
