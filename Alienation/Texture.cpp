// Texture.cpp: implementation of the CTexture class.
//
//////////////////////////////////////////////////////////////////////

#include "Texture.h"

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

AUX_RGBImageRec * CTexture::loadBMP(char *strFilename)				// Loads A Bitmap Image
{
	FILE *poFile=NULL;									// File Handle

	if (!strFilename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	poFile=fopen(strFilename,"r");							// Check To See If The File Exists

	if (poFile)											// Does The File Exist?
	{
		fclose(poFile);									// Close The Handle
		//**********Line that causes the exception********************************************
		return auxDIBImageLoad(strFilename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

bool CTexture::load(char *strDir, char **astrFnames, int iNoOfFiles)
{
	bool bStatus = false;						// Status Indicator
	char strFile[200];

	AUX_RGBImageRec *poTextureImage[1];					// Create Storage Space For The Texture

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
			if (poTextureImage[0]=loadBMP(strFile))
			{
				bStatus=true;									// Set The Status To TRUE
	
				glGenTextures(1, &m_puiTexture[iCount]);					// Create Three Textures

				// Create Linear Filtered Texture
				glBindTexture(GL_TEXTURE_2D, m_puiTexture[iCount]);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, poTextureImage[0]->sizeX, poTextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, poTextureImage[0]->data);
			}
		}
	}

	if (poTextureImage[0])								// If Texture Exists
	{
		if (poTextureImage[0]->data)						// If Texture Image Exists
		{
			free(poTextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(poTextureImage[0]);							// Free The Image Structure
	}

	return bStatus;										// Return The Status
}

void CTexture::setActive(unsigned int t)
{
	glBindTexture(GL_TEXTURE_2D, m_puiTexture[t]);
}
