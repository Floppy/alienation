// GUI.h: interface for the CGUI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GUI_H__36BA7CCD_1FC9_492C_8F00_75BC886573B1__INCLUDED_)
#define AFX_GUI_H__36BA7CCD_1FC9_492C_8F00_75BC886573B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "2D/2DObject.h"
#include "GUI/Frame.h"
#include "GUI/Button.h"
#include <vector>
#include <string>
#include <SDL.h>
using namespace std;


class CGUI
{
public:
	CGUI();
	virtual ~CGUI();
	CFrame *addFrame(CFrame *poFrame);
	CFrame *removeFrame(CFrame *poFrame);
	void renderGUI();
	CFrame *getControlClicked(int iXPos, int iYPos);
	void resetGUIButtons();

private:
	bool m_bIsActive;
   vector<CFrame> m_arrFrames;

};

extern CGUI g_oGUI;

#endif // !defined(AFX_GUI_H__36BA7CCD_1FC9_492C_8F00_75BC886573B1__INCLUDED_)
