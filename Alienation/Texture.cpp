// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "Texture.h"
#include <SDL_image.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTexture::CTexture(int iNum)
{
	m_iNoOfTextures = iNum;
	m_puiTexture = new unsigned int[m_iNoOfTextures];
}

CTexture::~CTexture()
{

}

bool CTexture::load(char *strDir, char **astrFnames, int iNoOfFiles)
{
	bool bStatus = false;						// Status Indicator
	char strFile[200];

	SDL_Surface *poTextureImage[1];					// Create Storage Space For The Texture
	poTextureImage[0] = NULL;

	int iCount;
	for ( iCount = 0 ; iCount < iNoOfFiles ; iCount++ )
	{
		if (strlen(astrFnames[iCount]) > 0)
		{
			if (strlen(strDir) > 0)
			{
				strcpy(strFile, strDir);
				strcat(strFile, "/");
			}
			else
			{
				strcpy(strFile, "");
			}
			strcat(strFile, astrFnames[iCount]);

			memset(poTextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL
	
			// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
			if (poTextureImage[0]= IMG_Load(strFile))
			{
				bStatus=true;									// Set The Status To TRUE
	
				glGenTextures(1, &m_puiTexture[iCount]);					// Create Three Textures

				// Create Linear Filtered Texture
				glBindTexture(GL_TEXTURE_2D, m_puiTexture[iCount]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, poTextureImage[0]->w, poTextureImage[0]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, poTextureImage[0]->pixels);
			}
		}
	}

	SDL_FreeSurface(poTextureImage[0]);

	return bStatus;										// Return The Status
}

void CTexture::setActive(unsigned int t)
{
	glBindTexture(GL_TEXTURE_2D, m_puiTexture[t]);
}
