// CheckBox.cpp: implementation of the CCheckBox class.
//
//////////////////////////////////////////////////////////////////////

#include "GUI/CheckBox.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckBox::CCheckBox() : CFrame()
{
   m_bolChecked = false;
}

CCheckBox::~CCheckBox()
{

}

void CCheckBox::init(float fXPos, float fYPos, float fWidth, float fHeight, char *sFilename)
{
   CFrame::init(fXPos, fYPos, fWidth, fHeight, sFilename);
   this->setType(3);
   setAltTexture(g_oTextureManager.load("GUI/checkSelected.png"));

}

void CCheckBox::render()
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

bool CCheckBox::getIsSelected()
{
   return m_bolChecked;
}

void CCheckBox::setSelected(bool bSelected)
{
   m_bolChecked = bSelected;
}

void CCheckBox::setMouseClickFunction(void(*ptfMouseClick)())
{
	m_ptfMouseClick = ptfMouseClick;
}

