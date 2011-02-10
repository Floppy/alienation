// Button.h: interface for the CButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUTTON_H__061B1863_B8A2_4CE3_91A6_A6E8B5EA5568__INCLUDED_)
#define AFX_BUTTON_H__061B1863_B8A2_4CE3_91A6_A6E8B5EA5568__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUI/Frame.h"

class CButton : public CFrame  
{
public:
	bool isMouseDown();
	void setMouseDown(bool bStatus);
	void render();
	void doMouseClick();
   CButton();
   virtual ~CButton();
   void init(float fXPos, float fYPos, float fWidth, float fHeight, char *sFilename);
	void setMouseClickFunction(void(*ptfMouseClick)());


private:
	bool m_bMouseDown;
   unsigned int m_uiPressedTexture;
	void (*m_ptfMouseClick)();
	void (*m_ptfMouseOver)();
};

#endif // !defined(AFX_BUTTON_H__061B1863_B8A2_4CE3_91A6_A6E8B5EA5568__INCLUDED_)
