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

#include "config.h"

#include <SDL.h>

#include <stdio.h>
#include "Game/Stars.h"
#include "Game/Ship.h"
#include "2D/GLFont.h"
#include "Game/PlayerShip.h"
#include "3D/Light.h"
#include "3D/Frustum.h"
#include "3D/Model.h"
#include "3D/Sprite.h"
#include "Math/Vector.h"

#include <vector>

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
	   void DrawSplashScreen();	   bool mouseUser(SDL_Event oEvent);
	   bool jsUser(SDL_Event oEvent);
		CLight *m_poLight;
		CStars  *m_poStars;
		CPlayerShip *m_poShip;
      COpenGL();
      ~COpenGL();
		void Update (unsigned long int dMilliseconds);
      bool DrawGLScene(GLvoid);
      bool      initGL();
		float m_fPitch, m_fYaw, m_fRoll, m_fThrust;
		bool m_bSlowmo;
		bool m_bCamUp, m_bCamDown, m_bCamRight, m_bCamLeft, m_bFire;
		CKeys m_oKeys;
		CFrustum  m_oFrustum;

                std::vector<CGameObject*> m_opObjects;
                std::vector<CGameObject*>::iterator m_pTarget;

                CVector2 m_vecScreenSize;

                CSprite m_oSun;
                //CModel m_oStation;
};

#endif
