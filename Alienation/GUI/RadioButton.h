// RadioButton.h: interface for the CRadioButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADIOBUTTON_H__97380877_72BD_4F44_8D9F_53B6085D8A12__INCLUDED_)
#define AFX_RADIOBUTTON_H__97380877_72BD_4F44_8D9F_53B6085D8A12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Frame.h"

class CRadioButton : public CFrame  
{
public:
	void render();
   CRadioButton();
   virtual ~CRadioButton();
   void init(float fXPos, float fYPos, float fWidth, float fHeight, char *strFilename);
};

#endif // !defined(AFX_RADIOBUTTON_H__97380877_72BD_4F44_8D9F_53B6085D8A12__INCLUDED_)
