// GLFontManager.h: interface for the CGLFontManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLFONTMANAGER_H__C58DA592_23B8_4037_BCEB_917C4EDD1157__INCLUDED_)
#define AFX_GLFONTMANAGER_H__C58DA592_23B8_4037_BCEB_917C4EDD1157__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "GLFont.h"
using namespace std;

class CGLFontManager  
{
public:
	CGLFont * getFont(int iID);
	int addFont(CGLFont *poFont);
	CGLFontManager();
	virtual ~CGLFontManager();

private:
	int m_iMaxID;
	vector<CGLFont *> m_arrFont;

};

extern CGLFontManager g_oFontManager;

#endif // !defined(AFX_GLFONTMANAGER_H__C58DA592_23B8_4037_BCEB_917C4EDD1157__INCLUDED_)
