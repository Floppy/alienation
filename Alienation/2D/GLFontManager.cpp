// GLFontManager.cpp: implementation of the CGLFontManager class.
//
//////////////////////////////////////////////////////////////////////

#include "2D/GLFontManager.h"

CGLFontManager g_oFontManager;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLFontManager::CGLFontManager()
{
	m_iMaxID = 0;
}

CGLFontManager::~CGLFontManager()
{

}

int CGLFontManager::addFont(CGLFont *poFont)
{
	m_iMaxID += 1;
	poFont->setID(m_iMaxID);
	m_arrFont.push_back(poFont);
	return m_iMaxID;
}

CGLFont * CGLFontManager::getFont(int iID)
{
	int iCount;

	for (iCount = 0 ; iCount < m_arrFont.size() ; iCount++ )
	{
		if ((m_arrFont[iCount]->getID()) == iID)
		{
			return m_arrFont[iCount];
		}
	}
	return 0;
}
