#include "Skybox.h"
#include <stdio.h>


CSkybox::CSkybox()
{
}

CSkybox::~CSkybox()
{
}

void CSkybox::DrawSB(CVector3 pos)
{
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glScalef(2000.0f, 2000.0f, 2000.0f);
	glCallList(list);
	glPopMatrix();
}



void CSkybox::initSB()
{
	LoadGLTextures();
	list = glGenLists(1);
	glNewList(list, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-4.0f, 4.0f, -4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(4.0f, 4.0f, -4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(4.0f, -4.0f, -4.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-4.0f, -4.0f, -4.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(4.0f, -4.0f, 4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(4.0f, 4.0f, 4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(4.0f, 4.0f, -4.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(4.0f, -4.0f, -4.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(4.0f, 4.0f, 4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-4.0f, 4.0f, 4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-4.0f, -4.0f, 4.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(4.0f, -4.0f, 4.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-4.0f, 4.0f, 4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-4.0f, 4.0f, -4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-4.0f, -4.0f, -4.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-4.0f, -4.0f, 4.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-4.0f, 4.0f, -4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(4.0f, 4.0f, -4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(4.0f, 4.0f, 4.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-4.0f, 4.0f, 4.0f);
		glEnd();
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-4.0f, -4.0f, -4.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(4.0f, -4.0f, -4.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(4.0f, -4.0f, 4.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-4.0f, -4.0f, 4.0f);
		glEnd();
	glEndList();

//	model.Init_3ds("Data/model/Sphere01.3ds");
}

AUX_RGBImageRec * CSkybox::LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File=NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File=fopen(Filename,"r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

bool CSkybox::LoadGLTextures()
{
	bool Status=false;						// Status Indicator
	char fileArr[6][22] = 
	{"Data/clouds01.bmp",
	"Data/clouds02.bmp",
	"Data/clouds03.bmp",
	"Data/clouds04.bmp",
	"Data/clouds07.bmp",
	"Data/clouds08.bmp"};

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	for ( int count = 0 ; count < 6 ; count++ )
	{

		memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

		// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		if (TextureImage[0]=LoadBMP((char *)fileArr[count]))
		{
			Status=true;									// Set The Status To TRUE

			glGenTextures(1, &texture[count]);					// Create Three Textures

			// Create Linear Filtered Texture
			glBindTexture(GL_TEXTURE_2D, texture[count]);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		}
	}

	if (TextureImage[0])								// If Texture Exists
	{
		if (TextureImage[0]->data)						// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[0]);							// Free The Image Structure
	}

	return Status;										// Return The Status
}
