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
#include "config.h"

#include <GL/gl.h>

#include <stdio.h>
#include "Game/Stars.h"
#include "Game/Ship.h"
#include "GL/GLFont.h"
#include "Game/Skybox.h"
#include "Game/PlayerShip.h"
#include "AI/AIShip.h"
#include "3D/Light.h"
#include "3D/Frustum.h"
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
      bool      m_bFullScreen;       // Fullscreen Flag Set To Fullscreen Mode By Default
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
		void Update (unsigned long int dMilliseconds);
      bool DrawGLScene(GLvoid);
      bool      initGL();
		float m_fPitch, m_fYaw, m_fRoll, m_fThrust;
		bool m_bSlowmo;
		bool m_bCamUp, m_bCamDown, m_bCamRight, m_bCamLeft, m_bFire;
		CKeys m_oKeys;
		CFrustum  m_oFrustum;
};

#endif
