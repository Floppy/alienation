// CheckBox.h: interface for the CCheckBox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKBOX_H__908283B5_F081_4899_9D4C_54CC605C9C08__INCLUDED_)
#define AFX_CHECKBOX_H__908283B5_F081_4899_9D4C_54CC605C9C08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GUI/Frame.h"

class CCheckBox : public CFrame  
{
public:
	void setSelected(bool bSelected);
	bool getIsSelected();
	void render();
	void init(float fXPos, float fYPos, float fWidth, float fHeight, char *sFilename);
	CCheckBox();
	virtual ~CCheckBox();
	void setMouseClickFunction(void(*ptfMouseClick)());

private:
	bool m_bolChecked;
	void (*m_ptfMouseClick)();
};

#endif // !defined(AFX_CHECKBOX_H__908283B5_F081_4899_9D4C_54CC605C9C08__INCLUDED_)
