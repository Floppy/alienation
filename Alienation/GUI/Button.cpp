// Button.cpp: implementation of the CButton class.
//
//////////////////////////////////////////////////////////////////////

#include "GUI/Button.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CButton::CButton() : CFrame()
{
   m_bMouseDown = false;
}

CButton::~CButton()
{

}

void CButton::init(float fXPos, float fYPos, float fWidth, float fHeight, char *sFilename)
{
   CFrame::init(fXPos, fYPos, fWidth, fHeight,sFilename);
   setType(2);
   setAltTexture(g_oTextureManager.load("GUI/button1Down.png"));   
}

void CButton::setMouseClickFunction(void(*ptfMouseClick)())
{
	m_ptfMouseClick = ptfMouseClick;
}	

void CButton::doMouseClick()
{
	(*m_ptfMouseClick)();
}

void CButton::render()
{
   int iParentPosX = getLeft();
   int iParentPosY = getTop();
   int iThisPosX = (int)getDescriptionXPos();
   int iThisPosY = (int)getDescriptionYPos();
   
   CGLFont *poFont;
   poFont = g_oFontManager.getFont(this->getFontID());
   C2DObject::renderQuad();

   poFont->print(this->getDescription(), NSDMath::CVector2(iParentPosX + iThisPosX,
										 iParentPosY + iThisPosY),
										 getFontSize(), getFontColour());
}

void CButton::setMouseDown(bool bStatus)
{
   m_bMouseDown = bStatus;
}

bool CButton::isMouseDown()
{
   return m_bMouseDown;
}
