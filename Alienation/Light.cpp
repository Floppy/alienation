// Light.cpp: implementation of the CLight class.
//
//////////////////////////////////////////////////////////////////////

#include "Light.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLight::CLight()
{

}

CLight::~CLight()
{

}

//Creates ambient and diffuse lighting. Really neds a seperate init for each type of light
//to make it easier to add specular and spotlights etc
void CLight::init(float afAmbient[4], float afDiffuse[4], float afPosition[4], GLenum Light)
{
	int i;
	for (i = 0; i < 4 ; i++)
	{
		m_afLightAmbient[i] = afAmbient[i];
		m_afLightDiffuse[i] = afDiffuse[i];
		m_afLightPosition[i] = afPosition[i];
	}

	glLightfv(Light, GL_AMBIENT, m_afLightAmbient);
	glLightfv(Light, GL_DIFFUSE, m_afLightDiffuse);
	glLightfv(Light, GL_POSITION, m_afLightPosition);

	glEnable(Light);
	glEnable(GL_LIGHTING);
}

//Update anything that already exists
void CLight::update(GLenum light, GLenum type, float afAmount[4])
{
	glLightfv(light, type, afAmount);
}
