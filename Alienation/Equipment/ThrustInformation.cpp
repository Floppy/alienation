// ThrustInformation.cpp: implementation of the CThrustInformation class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/ThrustInformation.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CThrustIndicator::CThrustIndicator()
{

}

CThrustIndicator::~CThrustIndicator()
{

}

void CThrustIndicator::init2D(float fXPos, float fYPos, float fWidth, float fHeight, const char * strFilename) {
   
   float fHalfHeight = fHeight * 0.5;

   // Initialise scale
   m_oScale.init2D(fXPos,fYPos,fWidth,fHalfHeight,"Hud/hud_scale.png");

   // Initialise display
   C2DObject::init2D(fXPos,fYPos+fHalfHeight,fWidth,fHalfHeight,strFilename);

}

void CThrustIndicator::renderQuad() {
   m_oScale.renderQuad();
   C2DObject::renderQuad();
}

void CThrustIndicator::setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive) {
   m_oScale.setActiveMaterial(oDiffuse,oAmbient,oEmissive);
   C2DObject::setActiveMaterial(oDiffuse,oAmbient,oEmissive);
}
