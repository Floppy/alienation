
#ifndef _3DSLOADER_H
#define _3DSLOADER_H

#pragma comment(lib, "data/lib/jpeg.lib")

#include "3ds.h"
#include "Texture.h"
#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#define MAXTEXTURE 100


//NOT written by me, but quite heavilly modifed. Like this loader as it allows for multi
//object models. Used to have a jpeb library in it, but I ripped it out and put the CTexture
//class in it for loading testures.

//////////////////////////////////////
//The 3dsLoader Class
//////////////////////////////////////
class C3dsLoader
{
	public:
		CLoad3DS m_oLoad3ds;
		CTexture *m_poTexture;				
//		unsigned int TextureArray3ds[MAXTEXTURE];	
		C3DModel m_o3DModel;
		unsigned int m_uiList;

		void init3ds(char* filename);
		void render3ds();
		void unload3ds();
};


#endif
