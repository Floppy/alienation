// GLFont.cpp: implementation of the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#include "GL/GLFont.h"
#include "3D/TextureManager.h"
#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLFont::CGLFont() :
   m_uiTexture(0)
{
}

CGLFont::~CGLFont()
{
   g_oTextureManager.removeReference(m_uiTexture);
}

void CGLFont::load()
{
   m_uiTexture = g_oTextureManager.load("text.png");
}

//pos is obviously the position in world co-ordinates, size is in same co-ords
void CGLFont::print(char *str, CVector3 vecPos, float fSize)
{
	CMatrix matMatrix;
	CVector3 vecTempPos;
	float afCol[4];
	double adCoords[4][2];
	int iCharno, iRow, iCol, iLen;


	//Store the initial position
	vecTempPos = vecPos;
	iLen = strlen(str);
	glPushMatrix();
	glLoadIdentity();
	//Texture and blending stuff
	g_oTextureManager.activate(m_uiTexture);

	//manually sets the material properties. Hard coded, shouldnt be really
	glPushAttrib(GL_COLOR_MATERIAL);
	afCol[0] = 0.4f;
	afCol[1] = 1.0f;
	afCol[2] = 0.3f;
	afCol[3] = 0.06f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, afCol); 
	//then draw the particles
	glBegin(GL_QUADS);
		int iCount;
		for (iCount = 0 ; iCount < iLen ; iCount++)
		{
			iCharno = str[iCount];
			iRow = (int)(iCharno / 16);
			iCol = (iCharno - (iRow * 16));
		//	iRow = 16 - iRow - 1;

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
			glTexCoord2d(adCoords[3][0], adCoords[3][1]);
			glVertex3f(vecTempPos.m_fx - fSize, vecTempPos.m_fy + fSize, vecTempPos.m_fz);

			glTexCoord2d(adCoords[2][0], adCoords[2][1]);
			glVertex3f(vecTempPos.m_fx + fSize, vecTempPos.m_fy + fSize, vecTempPos.m_fz);
			
			glTexCoord2d(adCoords[1][0], adCoords[1][1]);
			glVertex3f(vecTempPos.m_fx + fSize, vecTempPos.m_fy - fSize, vecTempPos.m_fz);

			glTexCoord2d(adCoords[0][0], adCoords[0][1]);
			glVertex3f(vecTempPos.m_fx - fSize, vecTempPos.m_fy - fSize, vecTempPos.m_fz);
		
			//Move the position for the next letter
			vecTempPos.m_fx += fSize * 2.0f;
		}
	glEnd();
	glPopAttrib();
	glPopMatrix();
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
void CGLFont::print(char *str, CVector2 vecPos, float fSize)
{
	CMatrix matMatrix;
	CVector2 vecTempPos;
	float afCol[4];
	double adCoords[4][2];
	int iCharno, iRow, iCol, iLen;


	//Store the initial position
	vecTempPos = vecPos;
	iLen = strlen(str);
	//Texture and blending stuff
	g_oTextureManager.activate(m_uiTexture);

	//manually sets the material properties. Hard coded, shouldnt be really
	glPushAttrib(GL_COLOR_MATERIAL);
	afCol[0] = 0.4f;
	afCol[1] = 1.0f;
	afCol[2] = 0.3f;
	afCol[3] = 0.06f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, afCol); 
	//then draw the particles
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
			glTexCoord2d(adCoords[3][0], adCoords[3][1]);
			glVertex2f(vecTempPos.X() - fSize, vecTempPos.Y() - fSize);

			glTexCoord2d(adCoords[2][0], adCoords[2][1]);
			glVertex2f(vecTempPos.X() + fSize, vecTempPos.Y() - fSize);
			
			glTexCoord2d(adCoords[1][0], adCoords[1][1]);
			glVertex2f(vecTempPos.X() + fSize, vecTempPos.Y() + fSize);

			glTexCoord2d(adCoords[0][0], adCoords[0][1]);
			glVertex2f(vecTempPos.X() - fSize, vecTempPos.Y() + fSize);
		
			//Move the position for the next letter
			vecTempPos.X() += fSize * 2.0f;
		}
	glEnd();
	glPopAttrib();
}
