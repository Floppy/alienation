// RadioButton.cpp: implementation of the CRadioButton class.
//
//////////////////////////////////////////////////////////////////////

#include "RadioButton.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadioButton::CRadioButton() : CFrame ()
{
}

CRadioButton::~CRadioButton()
{

}

void CRadioButton::init(float fXPos, float fYPos, float fWidth, float fHeight, char *strFilename)
{
   CFrame::init(0.0f, 0.0f, 0.0f, 0.0f, strFilename);
   setType(5);

}

void CRadioButton::render()
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
