// SpeedIndicator.cpp: implementation of the CSpeedIndicator class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/SpeedIndicator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpeedIndicator::CSpeedIndicator()
{

}

CSpeedIndicator::~CSpeedIndicator()
{

}

void CSpeedIndicator::operator = (CSpeedIndicator * poSpeed)
{
 
}

void CSpeedIndicator::setSpeed(float fSpeed)
{
   m_fSpeed = fSpeed;
}

float CSpeedIndicator::getSpeed()
{
   return m_fSpeed;
}

void CSpeedIndicator::init2D(float fXPos, float fYPos, float fWidth, float fHeight, const char * strFilename) {
   
   float fHalfHeight = fHeight * 0.5;

   // Initialise display
   C2DObject::init2D(fXPos,fYPos,fWidth,fHalfHeight,strFilename);

   // Initialise scale
   m_oScale.init2D(fXPos,fYPos+fHalfHeight,fWidth,fHalfHeight,"Hud/hud_scale.png");

}

void CSpeedIndicator::renderQuad() {
   m_oScale.renderQuad();
   C2DObject::renderQuad();
}

void CSpeedIndicator::setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive) {
   m_oScale.setActiveMaterial(oDiffuse,oAmbient,oEmissive);
   C2DObject::setActiveMaterial(oDiffuse,oAmbient,oEmissive);
}
