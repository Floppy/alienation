// GLFont.cpp: implementation of the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#include "GL/GLFont.h"

#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGLFont::CGLFont()
{
	//Create new texture
	m_poTexture = new CTexture(1);	
}

CGLFont::~CGLFont()
{
	delete [] m_poTexture;
}

void CGLFont::load()
{
	//Create list of textures to load (1 in this case)
	char **astrFiles = new char*[1];

	astrFiles[0] = new char(16);
	strcpy(astrFiles[0], "text.png");

	m_poTexture->load(astrFiles, 1);
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
	m_poTexture->setActive(0);

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

