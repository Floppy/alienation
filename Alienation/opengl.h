/********************************************************************
 * FILENAME.: Program.cpp
 * NICKNAME.: Doubt
 * NAME.....: Daniel Vivas
 * E-MAIL...: daniel@vivas.com.br
 * DATE.....: 03/08/2002
 * HOME-PAGE: http://www.danielvivas.cjb.net
 * GROUP....: Jogos Brasil
 ********************************************************************/

#ifndef OPENGL_H
#define OPENGL_H

#define WIN32_LEAN_AND_MEAN

#include <windows.h>     // Header File For Windows
#include <stdio.h>
#include <gl\gl.h>    // Header File For The OpenGL32 Library
#include <gl\glu.h>   // Header File For The GLu32 Library
#include <gl\glaux.h> // Header File For The GLaux Library
#include "stars.h"
#include "camera.h"
#include "ship.h"
#include "glfont.h"
#include "skybox.h"
#include "planet.h"
#include "playership.h"
#include "aiship.h"
#include "light.h"
#include "SDL.h"

class CKeys {											// Structure For Keyboard Stuff
public:
	bool m_abKeyDown [300];								// Holds TRUE / FALSE For Each Key
	bool m_abStillPressed[300];
};												// Keys

//The main game class. This class brings it all together.
class COpenGL {
   protected:
	   bool getCommon(SDL_Event event);
      bool      FullScreen;       // Fullscreen Flag Set To Fullscreen Mode By Default
      HDC       hDC;              // Private GDI Device Context
      HGLRC     hRC;              // Permanent Rendering Context
      HWND      hWnd;             // Holds Our Window Handle
      HINSTANCE hInstance;        // Holds The Instance Of The Application
		CGLFont	 *m_poGlfont;
		float m_fTimeElapsed;
   public:
	   bool mouseUser(SDL_Event oEvent);
	   bool jsUser(SDL_Event oEvent);
		CLight *m_poLight;
		CStars  *m_poStars;
		CPlayerShip *m_poShip;
		CSkybox *m_poSkybox;
		CAIShip *m_poAIShip;
		CPlanet *m_poEarth;
      COpenGL(HINSTANCE hinstance);
		void Update (DWORD dMilliseconds);
      bool DrawGLScene(GLvoid);
      friend LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
      bool      initGL();
		float m_fPitch, m_fYaw, m_fRoll, m_fThrust;
		bool m_bSlowmo;
		bool m_bCamUp, m_bCamDown, m_bCamRight, m_bCamLeft, m_bFire;
		CKeys m_oKeys;
};

#endif;