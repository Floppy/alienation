// Frame.cpp: implementation of the CFrame class.
//
//////////////////////////////////////////////////////////////////////

#include "Frame.h"
#include "Button.h"
#include "CheckBox.h"
#include "RadioContainer.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrame::CFrame()
{
	m_strName = new char(20);
	m_strDescription = new char(40);
	m_strTitle = new char(20);
	m_iTitlePosX = 0;
	m_iTitlePosY = 0;
	m_iDescriptionPosX = 0;
	m_iDescriptionPosY = 0;
	m_vecFontColour = NSDMath::CVector3(0.0f, 0.0f, 0.0f);
	m_fFontSize = 7.0f;
}

CFrame::~CFrame()
{

}

char * CFrame::getName()
{
   return m_strName;
}

char * CFrame::getDescription()
{
	return m_strDescription;
}

void CFrame::setName(char *strName)
{
	strcpy(m_strName, strName);
}

void CFrame::setDescription(char *strDescription)
{
	strcpy(m_strDescription, strDescription);
}

void CFrame::addControl(CFrame *poFrame)
{
	m_arrControls.push_back(poFrame);
}


//**************************************************************************************
// Function name    : CFrame::removeControl
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 01/11/2003
// Argument         : CFrame *poFrame
// Description      : This method removes a control from the array of controls  
//**************************************************************************************
void CFrame::removeControl(CFrame *poFrame)
{
	vector<CFrame *>::iterator itrFrame;
												//////////////////////////////////////////////
												//iterate throught the list of controls to  //
												//find the correct one to remove            //
												//////////////////////////////////////////////

	for (itrFrame = m_arrControls.begin() ; itrFrame < m_arrControls.end() ; itrFrame++)
	{
	   if (strcmp((*itrFrame)->getName(), poFrame->getName()))
		{
	 		m_arrControls.erase (itrFrame);
		}
	}
}

void CFrame::setActive(bool bActive)
{
	m_bActive = bActive;
}

bool CFrame::getActive()
{
	return m_bActive;
}

void CFrame::renderFrameControls()
{
	int iCount;

	for (iCount = 0 ; iCount < m_arrControls.size() ; iCount++)
	{
		switch(m_arrControls[iCount]->getType())
		{
		case 2:
			CButton * poButton;
			poButton = (CButton *)m_arrControls[iCount]->getControl();
			poButton->render();
			break;
		case 3:
			CCheckBox * poCheckBox;
			poCheckBox = (CCheckBox *)m_arrControls[iCount]->getControl();
			poCheckBox->render();
			break;
		case 4:
			CRadioContainer * poRadioContainer;
			poRadioContainer = (CRadioContainer *)m_arrControls[iCount]->getControl();
			poRadioContainer->render();
			break;
		}
	}
}

bool CFrame::mouseClickInside(int iXClick, int iYClick)
{
	if (C2DObject::mouseClickedInside(iXClick, iYClick))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

CFrame  *CFrame::checkMouseClicks(int iXPos, int iYPos)
{
	int iCount;

	for (iCount = 0 ; iCount < m_arrControls.size() ; iCount++)
	{
		if (m_arrControls[iCount]->mouseClickInside(iXPos, iYPos))
		{
			return m_arrControls[iCount];
		}
	}
	return NULL;
}

int CFrame::getType()
{
	return m_iType;
}

void CFrame::init(float fXPos, float fYPos, float fWidth, float fHeight, char *strFilename)
{
	C2DObject::init2D(fXPos, fYPos, fWidth, fHeight, strFilename);
	setType(1);
}

void CFrame::setType(int iType)
{
	m_iType = iType;
}

CFrame *CFrame::getControl()
{
	return this;
}

void CFrame::render()
{
   int iParentPosX = getLeft();
   int iParentPosY = getTop();
   int iThisPosX = (int)getDescriptionXPos();
   int iThisPosY = (int)getDescriptionYPos();

   CGLFont *poFont;
   poFont = g_oFontManager.getFont(m_iFontID);
   C2DObject::renderQuad();
   poFont->print(this->getDescription(), NSDMath::CVector2(iParentPosX + iThisPosX,
										 iParentPosY + iThisPosY),
										 getFontSize(), getFontColour());
}

void CFrame::setTitle(char *strTitle)
{
	strcpy(m_strTitle, strTitle);
}

void CFrame::setFontID(int iID)
{
	m_iFontID = iID;
}

int CFrame::getFontID()
{
	return m_iFontID;
}


void CFrame::setTitlePosition(int iPosX, int iPosY)
{
   m_iTitlePosX = iPosX;
   m_iTitlePosY = iPosY;
}

void CFrame::setDescriptionPosition(int iPosX, int iPosY)
{
   m_iDescriptionPosX = iPosX;
   m_iDescriptionPosY = iPosY;
}


void CFrame::setFontColour(NSDMath::CVector3 vecColour)
{
   m_vecFontColour = vecColour;
}

void CFrame::setFontSize(float fSize)
{
   m_fFontSize = fSize;
}

void CFrame::setParent(CFrame *poFrame)
{
   m_poParent = poFrame;
}

CFrame * CFrame::getParent()
{
   return m_poParent;
}

int CFrame::getDescriptionXPos()
{
   return m_iDescriptionPosX;
}

int CFrame::getDescriptionYPos()
{
   return m_iDescriptionPosY;
}

float CFrame::getFontSize()
{
   return m_fFontSize;
}

NSDMath::CVector3 CFrame::getFontColour()
{
   return m_vecFontColour;
}

void CFrame::resetButton()
{
   int iCount;

   for (iCount = 0 ; iCount < m_arrControls.size() ; iCount++ )
   {
	  if (m_arrControls[iCount]->getType() == 2)
	  {
		 CButton *poButton;
		 poButton = (CButton *)m_arrControls[iCount]->getControl();
		 if (poButton->isMouseDown())
		 {
			poButton->swapTextures();
			poButton->setMouseDown(false);
		 }
	  }
   }
}

void CFrame::setMouseClickFunction(void(*ptfMouseClick)())
{
	m_ptfMouseClick = ptfMouseClick;
}	

void CFrame::setMouseOverFunction(void(*ptfMouseOver)())
{
	m_ptfMouseOver = ptfMouseOver;
}	
