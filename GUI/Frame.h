// Frame.h: interface for the CFrame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAME_H__33CE5A13_13D9_4B6C_907B_69A70326A2FC__INCLUDED_)
#define AFX_FRAME_H__33CE5A13_13D9_4B6C_907B_69A70326A2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "2D/2DObject.h"
#include "2D/GLFont.h"
#include "2D/GLFontManager.h"
#include "Math/Vector.h"
#include <string>
#include <vector>
using namespace std;

class CFrame : public C2DObject  
{
public:
   void resetButton();
   NSDMath::CVector3 getFontColour();
   float getFontSize();
   int getDescriptionYPos();
   int getDescriptionXPos();
   CFrame * getParent();
   void setParent(CFrame * poFrame);
   void setFontSize(float fSize);
   void setFontColour(NSDMath::CVector3 vecColour);
   void setDescriptionPosition(int iPosX, int iPosY);
   void setTitlePosition(int iPosX, int iPosY);
   int getFontID();
   void setFontID(int iID);
   void setTitle(char *strTitle);
   void render();
   CFrame *getControl();
   void setType(int iType);
   void init(float fXPos, float fYPos, float fWidth, float fHeight, char * strFilename);
   int getType();
   CFrame *checkMouseClicks(int iXPos, int iYPos);
   bool mouseClickInside(int iXClick, int iYClick);
   char *getName();
   void setName(char *strName);
   char *getDescription();
   void setDescription(char * strDescription);
   CFrame();
   virtual ~CFrame();
   void addControl(CFrame *poControl);
   void removeControl(CFrame *poControl);
   void setActive(bool bActive);
   bool getActive();
   void renderFrameControls();
   void setMouseClickFunction(void(*ptfMouseClick)());
   void setMouseOverFunction(void(*ptfMouseOver)());

private:
   CFrame * m_poParent;
   float m_fFontSize;
   int m_iType;
   bool m_bActive;
   char * m_strName;
   char * m_strDescription;
   char * m_strTitle;
   int m_iFontID;
   int m_iTitlePosX;
   int m_iTitlePosY;
   int m_iDescriptionPosX;
   int m_iDescriptionPosY;
   NSDMath::CVector3 m_vecFontColour;
   vector<CFrame *> m_arrControls;
   void (*m_ptfMouseClick)();
   void (*m_ptfMouseOver)();
};

#endif // !defined(AFX_FRAME_H__33CE5A13_13D9_4B6C_907B_69A70326A2FC__INCLUDED_)
