// GLFont.cpp: implementation of the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#include "2D/GLFont.h"
#include "3D/TextureManager.h"
#include "3D/Material.h"
#include "2D/2DObject.h"
#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLFont::CGLFont()
{
}

CGLFont::~CGLFont()
{
}

void CGLFont::load()
{
   m_oMaterial.m_uiTexture = g_oTextureManager.load("text.png",false);
   m_oMaterial.init();
}


//**************************************************************************************
// Function name    : CGLFont::print
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 26/05/2003
// Argument         : char *str : String to print
// Argument         : CVector2 vecPos : 2D Position of text
// Argument         : float fSize : Size of each letter
// Description      : This function is similar to the standard 3d print routine. 
//                    It simply draws using glVertex2f. One other change is that 
//                    the Y axis is inverted (makes mnore sense in a 2d 
//                    environment)  
// History
//   Version         Date         Who      Description
//   =======         ====         ===      ===========
//     1.0           26/05/2003   GI       Initial Version
//**************************************************************************************
void CGLFont::print(char *str, NSDMath::CVector2 vecPos, float fSize, NSDMath::CVector3 vecColour)
{
   float fXSize(fSize * 0.75);
   float fYSize(fSize);

   NSDMath::CMatrix matMatrix;
   NSDMath::CVector2 vecTempPos;
   double adCoords[4][2];
   int iCharno, iRow, iCol, iLen;
   C2DObject p2DObject;
   
   //Store the initial position
   vecTempPos = vecPos;
   iLen = strlen(str);
   
   //manually sets the material properties. Hard coded, shouldnt be really
   m_oMaterial.m_oEmissive = CRGBAColour(vecColour.X(),vecColour.Y(),vecColour.Z(),0.5f);
   m_oMaterial.m_oDiffuse =  CRGBAColour(vecColour.X(),vecColour.Y(),vecColour.Z(),0.5f);
   m_oMaterial.m_oAmbient =  CRGBAColour(0,0,0,0.5f);
   m_oMaterial.render();

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode(GL_PROJECTION); 
   glPushMatrix(); 
   glLoadIdentity(); 
   glEnable(GL_TEXTURE_2D);
	m_oMaterial.disableDot3();
//   glColor4f( vecColour.X(), vecColour.Y(), vecColour.Z(), 0.5f );
   glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);
		int iCount;
		for (iCount = 0 ; iCount < iLen ; iCount++)
		{
			iCharno = str[iCount];
			iRow = (int)(iCharno / 16);
			iCol = (iCharno - (iRow * 16));

			//work out the u,v coordinates of the texture for the letter
			//uses double precision as float didnt seem accurate enought
			adCoords[3][0] = 1.0 /(256.0/(double)(iCol * 16)); 
			adCoords[0][1] = 1.0 /(256.0/(double)(iRow * 16 + 16)); 

			adCoords[1][0] = 1.0 /(256.0/(double)(iCol * 16 + 16));
			adCoords[1][1] = 1.0 /(256.0/(double)(iRow * 16 + 16)); 

			adCoords[2][0] = 1.0 /(256.0/(double)(iCol * 16 + 16)); 
			adCoords[2][1] = 1.0 /(256.0/(double)(iRow * 16)); 

			adCoords[0][0] = 1.0 /(256.0/(double)(iCol * 16)); 
			adCoords[3][1] = 1.0 /(256.0/(double)(iRow * 16)); 


			//Draw the letter
			glTexCoord2d(adCoords[2][0], adCoords[2][1]);
			glVertex2f(vecTempPos.X() + fXSize, vecTempPos.Y() - fYSize);
			
			glTexCoord2d(adCoords[3][0], adCoords[3][1]);
			glVertex2f(vecTempPos.X() - fXSize, vecTempPos.Y() - fYSize);

			glTexCoord2d(adCoords[0][0], adCoords[0][1]);
			glVertex2f(vecTempPos.X() - fXSize, vecTempPos.Y() + fYSize);

			glTexCoord2d(adCoords[1][0], adCoords[1][1]);
			glVertex2f(vecTempPos.X() + fXSize, vecTempPos.Y() + fYSize);

		
			//Move the position for the next letter
			vecTempPos.X() += fXSize * 2.0f;
		}
   glEnd();
   glPopAttrib();
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void CGLFont::setID(int iID)
{
	m_iID = iID;
}

int CGLFont::getID()
{
	return m_iID;
}
