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

#ifdef WIN32
  #include <windows.h>
#endif
#include <GL/gl.h>

#include <stdio.h>
#include "Stars.h"
#include "Ship.h"
#include "GLFont.h"
#include "Skybox.h"
#include "PlayerShip.h"
#include "AIShip.h"
#include "Light.h"
#include <SDL.h>

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
      COpenGL();
		void Update (DWORD dMilliseconds);
      bool DrawGLScene(GLvoid);
      bool      initGL();
		float m_fPitch, m_fYaw, m_fRoll, m_fThrust;
		bool m_bSlowmo;
		bool m_bCamUp, m_bCamDown, m_bCamRight, m_bCamLeft, m_bFire;
		CKeys m_oKeys;
};

#endif
