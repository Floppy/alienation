// RadioContainer.h: interface for the CRadioContainer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADIOCONTAINER_H__5206C4FD_E068_4AC2_BA34_6CB348DC53E5__INCLUDED_)
#define AFX_RADIOCONTAINER_H__5206C4FD_E068_4AC2_BA34_6CB348DC53E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "Frame.h"
#include "RadioButton.h"

class CRadioContainer : public CFrame  
{
public:
	void render();
	void arrangeRadioButtons();
	void addRadioButton(CRadioButton * poRadioButton);
   CRadioContainer();
   virtual ~CRadioContainer();
   void init(float fXPos, float fYPos, float fWidth, float fHeight, char *strFilename);
private:
   vector<CRadioButton *> m_arrRadioButton;
};

#endif // !defined(AFX_RADIOCONTAINER_H__5206C4FD_E068_4AC2_BA34_6CB348DC53E5__INCLUDED_)
