// GUI.cpp: implementation of the CGUI class.
//
//////////////////////////////////////////////////////////////////////

#include "GUI/GUI.h"
using namespace std;


CGUI g_oGUI;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGUI::CGUI()
{

}

CGUI::~CGUI()
{


}

CFrame *CGUI::addFrame(CFrame *poFrame)
{

   m_arrFrames.push_back(*poFrame);
   return poFrame;
}

CFrame *CGUI::removeFrame(CFrame *poFrame)
{
   vector<CFrame>::iterator itrFrames;

   for (itrFrames = m_arrFrames.begin(); itrFrames != m_arrFrames.end(); itrFrames++) 
   {
	  if (strcmp((*itrFrames).getName(), poFrame->getName()))
	  {
		 m_arrFrames.erase (itrFrames);
	  }	 
   }
   return poFrame;
}

void CGUI::renderGUI()
{
	int iCount;

	for (iCount = 0 ; iCount < m_arrFrames.size() ; iCount++)
	{
		if (m_arrFrames[iCount].getActive())
		{
			m_arrFrames[iCount].render();
			m_arrFrames[iCount].renderFrameControls();
		}
	}
}

CFrame *CGUI::getControlClicked(int iXPos, int iYPos)
{
	int iCount;
	CFrame *poFrame;

	for ( iCount = 0 ; iCount < m_arrFrames.size() ; iCount++ )
	{
		poFrame = m_arrFrames[iCount].checkMouseClicks(iXPos, iYPos);
		return poFrame;
	}
	return (CFrame *)NULL;
}

void CGUI::resetGUIButtons()
{
   int iCount;

   for ( iCount = 0 ; iCount < m_arrFrames.size() ; iCount++ )
   {
	  m_arrFrames[iCount].resetButton();	
   }
}

