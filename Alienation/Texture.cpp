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

				// Convert surface to right pixel format
				if (poTextureImage->format->BitsPerPixel != 32) {
					// Create pixel format
					SDL_PixelFormat fmt;
					fmt.palette = NULL;
					fmt.BitsPerPixel = 32;
					#if SDL_BYTEORDER == 1234
				    fmt.Rmask=0x000000ff;
					fmt.Gmask=0x0000ff00;
					fmt.Bmask=0x00ff0000;
					fmt.Amask=0xff000000;
					#else
				    fmt.Rmask=0xff000000;
					fmt.Gmask=0x00ff0000;
					fmt.Bmask=0x0000ff00;
					fmt.Amask=0x000000ff;
					#endif
					// Convert
					SDL_Surface * tmp = poTextureImage;
					poTextureImage = SDL_ConvertSurface(tmp, &fmt, SDL_HWSURFACE);
					SDL_FreeSurface(tmp);
				}

				// Create Linear Filtered Texture
				glBindTexture(GL_TEXTURE_2D, m_puiTexture[iCount]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, poTextureImage->w, poTextureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, poTextureImage->pixels);
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
