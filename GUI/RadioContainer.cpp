// RadioContainer.cpp: implementation of the CRadioContainer class.
//
//////////////////////////////////////////////////////////////////////

#include "RadioContainer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadioContainer::CRadioContainer() : CFrame()
{

}

CRadioContainer::~CRadioContainer()
{

}

void CRadioContainer::init(float fXPos, float fYPos, float fWidth, float fHeight, char *strFilename)
{
   CFrame::init(fXPos, fYPos, fWidth, fHeight, strFilename);
   setType(4);
}

void CRadioContainer::addRadioButton(CRadioButton *poRadioButton)
{
   m_arrRadioButton.push_back(poRadioButton);
}

void CRadioContainer::arrangeRadioButtons()
{
   int iHeight = getHeight();
   int iDiv = (int)(iHeight / m_arrRadioButton.size());
   int iSpace = (int)(iDiv / 2);
   int iLeft = getWidth() - 30;
   int iCount;

   for (iCount = 0 ; iCount < m_arrRadioButton.size() ; iCount ++)
   {
	  m_arrRadioButton[iCount]->setPosition((float)(getLeft() + iLeft),
										    (float)((getTop() + 30) + ((iCount + 1) * iSpace)),
											10.0f, 10.0f);
   }

}

void CRadioContainer::render()
{
   int iParentPosX = getLeft();
   int iParentPosY = getTop();
   int iThisPosX = (int)getDescriptionXPos();
   int iThisPosY = (int)getDescriptionYPos();
   int iCount;
   
   CGLFont *poFont;
   poFont = g_oFontManager.getFont(this->getFontID());
   C2DObject::renderQuad();

   poFont->print(this->getDescription(), NSDMath::CVector2(iParentPosX + iThisPosX,
										 iParentPosY + iThisPosY),
										 getFontSize(), getFontColour());

   for (iCount = 0 ; iCount < m_arrRadioButton.size() ; iCount ++)
   {
	  m_arrRadioButton[iCount]->render();
   }
}
