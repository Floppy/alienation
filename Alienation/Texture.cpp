// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "Texture.h"
#include <SDL_image.h>

#ifdef WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>

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
	bool bGood = false;
	char strFile[200];

	int iCount;
	for ( iCount = 0 ; iCount < iNoOfFiles ; iCount++ )
	{
		// We will load into an SDL surface
		SDL_Surface * poTextureImage = NULL;

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

			// Load the file
			poTextureImage = IMG_Load(strFile);

			// If texture was loaded OK
			if (poTextureImage)
			{
				bGood=true;
	
				glGenTextures(1, &m_puiTexture[iCount]);

				// Create Linear Filtered Texture
				glBindTexture(GL_TEXTURE_2D, m_puiTexture[iCount]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, poTextureImage->w, poTextureImage->h, 0, GL_RED, GL_UNSIGNED_BYTE, poTextureImage->pixels);
			}
		}
		// Free the SDL surface
		SDL_FreeSurface(poTextureImage);
	}
	// Done
	return bGood;
}

void CTexture::setActive(unsigned int t)
{
	glBindTexture(GL_TEXTURE_2D, m_puiTexture[t]);
}
