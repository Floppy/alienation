// GLFont.cpp: implementation of the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#include <SDL_opengl.h>

#include "GL/GLFont.h"
#include "3D/TextureManager.h"

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
   m_oMaterial.m_oEmissive = CRGBAColour(0.4f,1.0f,0.3f,0.75f);
   m_oMaterial.m_oAmbient = CRGBAColour(0.0f,0.0f,0.0f,0.75f);
   m_oMaterial.m_oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,0.75f);
   m_oMaterial.m_uiTexture = g_oTextureManager.load("text.png");
   m_oMaterial.init();
}

//pos is obviously the position in world co-ordinates, size is in same co-ords
void CGLFont::print(char *str, CVector3 vecPos, float fSize)
{
	CMatrix matMatrix;
	CVector3 vecTempPos;
	double adCoords[4][2];
	int iCharno, iRow, iCol, iLen;


	//Store the initial position
	vecTempPos = vecPos;
	iLen = strlen(str);
	glPushMatrix();
	glLoadIdentity();
        
        // Set material
        m_oMaterial.render();

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
			adCoords[3][0] = static_cast<double>(iCol * 16)/256.0; 
			adCoords[0][1] = static_cast<double>(iRow * 16 + 16)/256.0; 

			adCoords[1][0] = static_cast<double>(iCol * 16 + 16)/256.0; 
			adCoords[1][1] = adCoords[0][1];

			adCoords[2][0] = adCoords[1][0]; 
		 	adCoords[2][1]= static_cast<double>(iRow * 16)/256.0; 
                        
			adCoords[0][0] = adCoords[3][0]; 
			adCoords[3][1] = adCoords[2][1]; 


			//Draw the letter
			glTexCoord2d(adCoords[2][0], adCoords[2][1]);
			glVertex3f(vecTempPos.X() + fSize, vecTempPos.Y() + fSize, vecTempPos.Z());
			
			glTexCoord2d(adCoords[3][0], adCoords[3][1]);
			glVertex3f(vecTempPos.X() - fSize, vecTempPos.Y() + fSize, vecTempPos.Z());

			glTexCoord2d(adCoords[0][0], adCoords[0][1]);
			glVertex3f(vecTempPos.X() - fSize, vecTempPos.Y() - fSize, vecTempPos.Z());
		
			glTexCoord2d(adCoords[1][0], adCoords[1][1]);
			glVertex3f(vecTempPos.X() + fSize, vecTempPos.Y() - fSize, vecTempPos.Z());

			//Move the position for the next letter
			vecTempPos.X() += fSize * 2.0f;
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
	double adCoords[4][2];
	int iCharno, iRow, iCol, iLen;


	//Store the initial position
	vecTempPos = vecPos;
	iLen = strlen(str);

        // Set material
        m_oMaterial.render();

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
			adCoords[3][0] = static_cast<double>(iCol * 16)/256.0; 
			adCoords[0][1] = static_cast<double>(iRow * 16 + 16)/256.0; 

			adCoords[1][0] = static_cast<double>(iCol * 16 + 16)/256.0; 
			adCoords[1][1] = adCoords[0][1];

			adCoords[2][0] = adCoords[1][0]; 
		 	adCoords[2][1]= static_cast<double>(iRow * 16)/256.0; 
                        
			adCoords[0][0] = adCoords[3][0]; 
			adCoords[3][1] = adCoords[2][1]; 


			//Draw the letter
			glTexCoord2d(adCoords[2][0], adCoords[2][1]);
			glVertex2f(vecTempPos.X() + fSize, vecTempPos.Y() - fSize);
			
			glTexCoord2d(adCoords[3][0], adCoords[3][1]);
			glVertex2f(vecTempPos.X() - fSize, vecTempPos.Y() - fSize);

			glTexCoord2d(adCoords[0][0], adCoords[0][1]);
			glVertex2f(vecTempPos.X() - fSize, vecTempPos.Y() + fSize);

			glTexCoord2d(adCoords[1][0], adCoords[1][1]);
			glVertex2f(vecTempPos.X() + fSize, vecTempPos.Y() + fSize);

		
			//Move the position for the next letter
			vecTempPos.X() += fSize * 2.0f;
		}
	glEnd();
	glPopAttrib();
}
