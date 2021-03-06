
/********************************************************************
 * FILENAME.: Program.cpp
 * NICKNAME.: Doubt
 * NAME.....: Daniel Vivas
 * E-MAIL...: daniel@vivas.com.br
 * DATE.....: 03/08/2002
 * HOME-PAGE: http://www.danielvivas.cjb.net
 * GROUP....: Jogos Brasil
 ********************************************************************/

#include <SDL_opengl.h>

#include "GL/OpenGL.h"
#include "GL/Extensions.h"
#include "IO/3ds.h"
#include "Math/Random.h"
#include "3D/TextureManager.h"
#include "Game/Asteroid.h"
#include "AI/AIShip.h"
#include "IO/Lua.h"
#include "Math/Vector.h"
#include "Game/ShipFactory.h"

#include <iostream>
#ifndef WIN32
using namespace std;
#endif

extern bool bNoBumps;

// We define the joystick axes here, because they
// seem to be different in windows and linux
#define JOYSTICK_AXIS_PITCH       1
#define JOYSTICK_AXIS_YAW         0
#ifdef WIN32
  #define JOYSTICK_AXIS_ROLL      3
  #define JOYSTICK_AXIS_THROTTLE  2
#else
  #define JOYSTICK_AXIS_ROLL      2
  #define JOYSTICK_AXIS_THROTTLE  3
#endif

const static int kiDeadzone(3200);

// All Setup For OpenGL Goes Here
COpenGL :: COpenGL(CVector2 vecScreenSize) :
	m_bFullScreen(true),
	m_fTimeElapsed(0.0f),
	m_fPitch(0.0f),
	m_fYaw(0.0f), 
	m_fRoll(0.0f), 
	m_fThrust(0.0f),
        m_vecScreenSize(vecScreenSize)
{
   
}

COpenGL::~COpenGL()
{
   std::vector<CGameObject*>::iterator it;
   for (it = m_opObjects.begin(); it != m_opObjects.end(); it++) {
      delete *it;
   }   
   delete m_poLight;
   delete m_poGlfont;
   delete m_poStars;
   delete m_poShip;
}

bool COpenGL :: initGL() {

   bool bPerspCorr, bPolygonSmooth;
   int texfilter;   
   const char* strPlayerShip = NULL;
   vector<const char*> astrAIShips;

   int iNumRoids(0);
   {
     NSDIO::CLua config("config.lua");
     
     if (!config.setGlobalTable("video")) {
       cerr << "Couldn't read video config!" << endl;
       return false;
     }
     bPerspCorr = config.getNumber("perspectivecorrection") == 0.0f ? false : true;
     bPolygonSmooth = config.getNumber("polygonsmooth") == 0.0f? false : true;
     texfilter = static_cast<int>(config.getNumber("texturefilter"));

     // Get texture filtering mode
     switch (texfilter) {
     case 6:
        texfilter = GL_LINEAR_MIPMAP_LINEAR;
        break;
     case 5:
        texfilter = GL_NEAREST_MIPMAP_LINEAR;
        break;
     case 4:
        texfilter = GL_LINEAR_MIPMAP_NEAREST;
        break;
     case 3:
        texfilter = GL_NEAREST_MIPMAP_NEAREST;
        break;
     case 2:
        texfilter = GL_LINEAR;
        break;
     case 1:
     default:
        texfilter = GL_NEAREST;
        break;
     }

     config.pop();

     if (!config.setGlobalTable("game")) {
       cerr << "Couldn't read game config!" << endl;
       return false;
     }
     strPlayerShip = config.getString("playership");
     iNumRoids = static_cast<int>(config.getNumber("numroids"));
     config.push("aiships");
     int iNumAIShips(config.tableSize());
     for (int i=0; i<iNumAIShips; i++)
       astrAIShips.push_back(config.getString(i));
     config.pop();
     config.pop();

   }

   // Set up shading, lighting, and so on
   glShadeModel(GL_SMOOTH);                           // Enable Smooth Shading
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);              // Black Background
   glClearDepth(1.0f);                                // Depth Buffer Setup
   glEnable(GL_DEPTH_TEST);                           // Enables Depth Testing
   glDepthFunc(GL_LEQUAL);                            // The Type Of Depth Testing To Do
   glEnable(GL_POLYGON_SMOOTH);
   glEnable(GL_TEXTURE_2D);		

   // Enable backface culling
   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);

   // Setup texture filtering
   g_oTextureManager.textureFiltering(texfilter,texfilter);
   
   // Setup rendering hints
   if (bPerspCorr)
      glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   if (bPolygonSmooth)
      glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

   // Set viewport
   glViewport(0, 0, static_cast<int>(m_vecScreenSize.X()), static_cast<int>(m_vecScreenSize.Y()));

   // Init lighting
   glEnable(GL_LIGHTING);
   CRGBAColour oAmbient(0.2f, 0.2f, 0.2f, 1.0f);
   CRGBAColour oDiffuse(0.85f, 0.85f, 0.85f, 1.0f);
   CVector3 oPosition(0.0f, 0.0f, -1000.0f);

   m_poLight = new CLight(GL_LIGHT0);
   m_poLight->init(oAmbient, oDiffuse, oPosition);
   // Create sun sprite
   CMaterial oMaterial;
   oMaterial.m_oEmissive = CRGBAColour(1.0f, 1.0f, 1.0f,1.0f);
   oMaterial.m_oDiffuse  = CRGBAColour(0.0f, 0.0f, 0.0f,1.0f);
   oMaterial.m_oSpecular = CRGBAColour(0.0f, 0.0f, 0.0f,1.0f);
   // Load sun textures
   oMaterial.m_uiTexture = g_oTextureManager.load("sun.png");
   // Set material
   m_oSun = CSprite(oMaterial);
   m_oSun.setSize(850);
   m_oSun.init();

   //All initialisation. Nothing rocket science here.
   m_bSlowmo = false;
   m_bCamUp = m_bCamDown = m_bCamLeft = m_bCamRight = m_bFire = false;
   m_poGlfont = new CGLFont();
   m_poGlfont->load();
	g_oFontManager.addFont(m_poGlfont);
   int x;
   for (x = 0 ; x < 300 ; x++)
   {
      m_oKeys.m_abKeyDown[x] = false;
      m_oKeys.m_abStillPressed[x] =  false;
   }
   m_fTimeElapsed = 0.0f;
   m_fPitch = m_fYaw = m_fRoll = m_fThrust = 0.0f;
   
   // Create starfield
   m_poStars = new CStars;
   m_poStars->initStars();
   
   // Create player ship
   m_poShip = static_cast<CPlayerShip*>(CShipFactory::load(strPlayerShip,true));
   m_poShip->setPosition(CVector3(0,0,0));

   // Create and load AI ships
   CRandom prng(547343);
   for (vector<const char*>::iterator it(astrAIShips.begin()); it != astrAIShips.end(); it++) {
      CShip* poAIShip = CShipFactory::load(*it,false);
      poAIShip->setPosition(CVector3(prng.randDouble()*1000 - 500,
                                     prng.randDouble()*1000 - 500,
                                     prng.randDouble()*1000 - 500));
		poAIShip->setObjectType(0);
		m_poShip->addTarget(poAIShip);
      poAIShip->setTarget(m_poShip);
      m_opObjects.push_back(poAIShip);
   }

   // Set initial target
   m_poShip->setTarget(m_opObjects.front());


   // Load roids
   for (int r=0; r<iNumRoids; r++) {
      CAsteroid* pRoid = new CAsteroid(1,50000);
      // Select type
      float fRandom = prng.randDouble();
      TAsteroidType type = ROID_COPPER;
      if (fRandom < 0.25) 
         type = ROID_COMMON;
      else if (fRandom < 0.5) 
         type = ROID_GOLD;
      else if (fRandom < 0.75) 
         type = ROID_ICE;
      // Load
      pRoid->load(type);
      m_opObjects.push_back(pRoid);
		pRoid->setObjectType(1);
		m_poShip->addTarget(pRoid);
   }

   m_pTarget = m_opObjects.begin();

   //if (oLoader.import3DS(&m_oStation,"Data/Model/station.3ds"))
   //m_oStation.init();
   //m_oStation.setTranslation(CVector3(1000,1000,1000));

   // Done
   return true;
}

// Here's Where We Do All The Drawing. Nothing hard here. Only thing to note
//is all transparent objects are drawn last
bool COpenGL::DrawGLScene(GLvoid) {

   std::vector<CGameObject*>::iterator it;

   // Do offscreen rendering first
   m_poShip->renderOffScreen();

   // Clear screen
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Set camera
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, m_vecScreenSize.X()/m_vecScreenSize.Y(), 0.1f, 25001.0f);

   // Init modelview matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   m_poShip->drawCamera();
   m_poLight->enable();
   m_poLight->render();
   m_oSun.setTranslation(CVector3(0,0,8500) + m_poShip->m_ppMasses[0]->m_vecPos);
   m_oSun.render();
   m_poShip->draw();
   m_oFrustum.CalculateFrustum();
   m_poStars->draw(m_poShip->m_ppMasses[0]->m_vecPos);
   // Draw objects
   for (it = m_opObjects.begin(); it != m_opObjects.end(); it++) {
      (*it)->draw();
   }

   //m_oStation.render();

   // Draw objects
   m_poShip->drawBlended();
   for (it = m_opObjects.begin(); it != m_opObjects.end(); it++) {
      (*it)->drawBlended();
   }
   
   m_poShip->drawHud();
   m_poLight->disable();
   
   // Everything Went OK
   return true; 
}

//Called from main, this funnction gives time based movement. Needs seperating into seperate 
//function calls for readability
void COpenGL::Update (unsigned long int dMilliseconds)								
{
	int i;

	m_poShip->clearTargetList();
	for ( i = 0 ; i < m_opObjects.size() ; i++ )
	{
		m_poShip->addTarget(m_opObjects[i]);
	}

	float fDT = dMilliseconds / 1000.0f;							// Let's Convert Milliseconds To Seconds

	//Undocumented for debugging, makes everything move 100 times slower
	//Initiated with the f10 key
	if (m_bSlowmo)
		fDT /= 100;

	//For flight mode one and two, the js/mouse movements translate into 
	//pitch yaw and roll, This is done here
	if (m_poShip->m_iFlightMode == 1 || m_poShip->m_iFlightMode == 2)
	{
		if (m_fPitch == 0.0f)
		{
			m_poShip->m_fPitchRate = 0.0f;
		}																	
		else
		{
			m_poShip->m_fPitchRate = m_poShip->m_fMaxPitchRate * m_fPitch;
			if (m_poShip->m_fPitchRate > m_poShip->m_fMaxPitchRate)
				m_poShip->m_fPitchRate = m_poShip->m_fMaxPitchRate;
			if (m_poShip->m_fPitchRate < -m_poShip->m_fMaxPitchRate)
				m_poShip->m_fPitchRate = -m_poShip->m_fMaxPitchRate;
		}

		if (m_fYaw == 0.0f)
		{
			m_poShip->m_fYawRate = 0.0f;
		}																	
		else
		{
			m_poShip->m_fYawRate = m_poShip->m_fMaxYawRate * m_fYaw;
			if (m_poShip->m_fYawRate > m_poShip->m_fMaxPitchRate)
				m_poShip->m_fYawRate = m_poShip->m_fMaxPitchRate;
			if (m_poShip->m_fYawRate < -m_poShip->m_fMaxYawRate)
				m_poShip->m_fYawRate = -m_poShip->m_fMaxYawRate;
		}
	
		if (m_fRoll == 0.0f)
		{
			m_poShip->m_fRollRate = 0.0f;
		}																	
		else
		{
			m_poShip->m_fRollRate = m_poShip->m_fMaxRollRate * m_fRoll;
			if (m_poShip->m_fRollRate > m_poShip->m_fMaxRollRate)
				m_poShip->m_fRollRate = m_poShip->m_fMaxRollRate;
			if (m_poShip->m_fRollRate < -m_poShip->m_fMaxRollRate)
				m_poShip->m_fRollRate = -m_poShip->m_fMaxRollRate;
		}
	}
	else //Flight mode 3. The effects of this are done in the simulate function
		  //so simply notify it using bools
	{
		if (m_fPitch > 0.0f)
		{
			m_poShip->m_bStraffUp = true;
		}																	
		else
		{
			if (m_fPitch < 0.0f)
			{
				m_poShip->m_bStraffDown = true;
			}									
			else
			{
				m_poShip->m_bStraffDown = false;
				m_poShip->m_bStraffUp = false;
			}
		}

		if (m_fYaw > 0.0f)
		{
			m_poShip->m_bStraffRight = true;
		}																	
		else
		{
			if (m_fYaw < 0.0f)
			{
				m_poShip->m_bStraffLeft = true;
			}									
			else
			{
				m_poShip->m_bStraffRight = false;
				m_poShip->m_bStraffLeft = false;
			}
		}
	}

	//Set the weaponFire bool if the firekey being pressed
	if (m_bFire && !m_poShip->m_bWeaponFire)
	{
		m_poShip->m_bWeaponFire = true;
	}
	else
	{
		if (!m_bFire && m_poShip->m_bWeaponFire)
			m_poShip->m_bWeaponFire = false;
	}

	//Store thrust value
        m_poShip->setThrust(m_fThrust);

	//Basically these bools represent weather the hat switch/numeric key pad have been pressed.
	//The effect of these depends on whether it is an inside or outside view.
	//This is handled in the draw function.
	if (m_bCamUp)
	{
		if (m_poShip->m_bInsideView)
		{
			m_poShip->m_bUpLook = true;
		}
		else
		{
			m_poShip->m_fCamPitch = 10.0f;
		}
	}
	else
	{
		if (m_bCamDown)
		{
			if (m_poShip->m_bInsideView)
			{
				m_poShip->m_bBackLook = true;
			}
			else
			{
				m_poShip->m_fCamPitch = -10.0f;
			}
		}
		else
		{
			m_poShip->m_fCamPitch = 0.0f;
			m_poShip->m_bBackLook = m_poShip->m_bUpLook = false;
		}
	}

	if (m_bCamLeft)
	{
		if (m_poShip->m_bInsideView)
		{
			m_poShip->m_bLeftLook = true;
		}
		else
		{
			m_poShip->m_fCamYaw = 10.0f;
		}
	}
	else
	{
		if (m_bCamRight)
		{
			if (m_poShip->m_bInsideView)
			{
				m_poShip->m_bRightLook = true;
			}
			else
			{
				m_poShip->m_fCamYaw = -10.0f;
			}
		}
		else
		{
			m_poShip->m_fCamYaw = 0.0f;
			m_poShip->m_bRightLook = m_poShip->m_bLeftLook = false;
		}
	}

	//F1. Toggles outside/inside views
	if (m_oKeys.m_abKeyDown[SDLK_F1] && !m_oKeys.m_abStillPressed[SDLK_F1])
	{
		m_oKeys.m_abStillPressed[SDLK_F1] = true;
		if (m_poShip->m_bInsideView)
			m_poShip->m_bInsideView = false;
		else
			m_poShip->m_bInsideView = true;
	}
	
	//F2. Switches to normal flight
	if (m_oKeys.m_abKeyDown[SDLK_F2] && !m_oKeys.m_abStillPressed[SDLK_F2])
	{
		m_oKeys.m_abStillPressed[SDLK_F2] = true;
		if (m_poShip->m_iFlightMode != 1)
				m_poShip->m_iFlightMode = 1;
	}

	//F3. Switches to turret flight
	if (m_oKeys.m_abKeyDown[SDLK_F3] && !m_oKeys.m_abStillPressed[SDLK_F3])
	{
		m_oKeys.m_abStillPressed[SDLK_F3] = true;
		if (m_poShip->m_iFlightMode != 2)
			m_poShip->m_iFlightMode = 2;
	}

	//F4. Switches to straff flight
	if (m_oKeys.m_abKeyDown[SDLK_F4] && !m_oKeys.m_abStillPressed[SDLK_F4])
	{
		m_oKeys.m_abStillPressed[SDLK_F4] = true;
		if (m_poShip->m_iFlightMode != 3)
			m_poShip->m_iFlightMode = 3;
	}

	//F5. Next target
	if (m_oKeys.m_abKeyDown[SDLK_F5] && !m_oKeys.m_abStillPressed[SDLK_F5])
	{
           m_oKeys.m_abStillPressed[SDLK_F5] = true;
           if (m_pTarget == m_opObjects.begin()) m_pTarget = m_opObjects.end();
           m_pTarget--;
           m_poShip->setTarget(*m_pTarget);
	}

	//F6. previous target
	if (m_oKeys.m_abKeyDown[SDLK_F6] && !m_oKeys.m_abStillPressed[SDLK_F6])
	{
           m_oKeys.m_abStillPressed[SDLK_F6] = true;
           m_pTarget++;
           if (m_pTarget == m_opObjects.end()) m_pTarget = m_opObjects.begin();
           m_poShip->setTarget(*m_pTarget);
	}

	//SLOW MOTION !!
	if (m_oKeys.m_abKeyDown[SDLK_F10] && !m_oKeys.m_abStillPressed[SDLK_F10])
	{
		m_oKeys.m_abStillPressed[SDLK_F10] = true;
		if (m_bSlowmo)
			m_bSlowmo = false;
		else
			m_bSlowmo = true;
	}
	
	//Brakes the ship (As in slow down, not as in broken;))
	if (m_oKeys.m_abKeyDown[SDLK_SPACE])
	{
		if (!m_poShip->m_bBraking)
			m_poShip->m_bBraking = true;
	}
	else
	{
		m_poShip->m_bBraking = false;
	}

	if (m_oKeys.m_abKeyDown[SDLK_a])
	{
		m_poShip->increaseRadarRange();
	}
	if (m_oKeys.m_abKeyDown[SDLK_z])
	{
		m_poShip->decreaseRadarRange();
	}

	if (m_oKeys.m_abKeyDown[SDLK_b])
	{
		if (bNoBumps)
		{
			bNoBumps = false;
		}
		else
		{
			bNoBumps = true;
		}
	}
	// dt Is The Time Interval (As Seconds) From The Previous Frame To The Current Frame.
	// dt Will Be Used To Iterate Simulation Values Such As Velocity And Position Of Masses.


	m_fTimeElapsed += fDT;									// Iterate Elapsed Time


	float fMaxPossible_dt = 0.1f;								// Say That The Maximum Possible dt Is 0.1 Seconds
																// This Is Needed So We Do Not Pass Over A Non Precise dt Value

  	int iNumOfIterations = (int)(fDT / fMaxPossible_dt) + 1;		// Calculate Number Of Iterations To Be Made At This Update Depending On maxPossible_dt And dt
	if (iNumOfIterations != 0)									// Avoid Division By Zero
		fDT = fDT / iNumOfIterations;								// dt Should Be Updated According To numOfIterations

	int a;
	for (a = 0; a < iNumOfIterations; ++a)					// We Need To Iterate Simulations "numOfIterations" Times
	{
                for (std::vector<CGameObject*>::iterator it = m_opObjects.begin(); it != m_opObjects.end(); it++)
                   (*it)->operate(fDT);
		m_poShip->operate(fDT);							// Iterate constantVelocity Simulation By dt Seconds
	}

}

//Handle Joystick events
bool COpenGL::jsUser(SDL_Event oEvent)
{
	bool done = getCommon(oEvent);

	switch(oEvent.type) {
		case SDL_JOYBUTTONDOWN:  /* Handle Joystick Button Presses */
			if ( oEvent.jbutton.button == 0 ) 
			{
				m_bFire = true;
 			}

			break;

		case SDL_JOYBUTTONUP:  /* Handle Joystick Button Presses */
			if ( oEvent.jbutton.button == 0 ) 
			{
				m_bFire = false;
 			}

			break;

		case SDL_JOYAXISMOTION:  /* Handle Joystick Motion */
			if( oEvent.jaxis.axis == JOYSTICK_AXIS_THROTTLE) 
			{
				m_fThrust = (float)((oEvent.jaxis.value * -1.0f) + 30000) / 65536; 
				if (m_fThrust < 0.0f)
				{
					m_fThrust = 0.0f;
				}
			}

			if ( ( oEvent.jaxis.value < -kiDeadzone ) || (oEvent.jaxis.value > kiDeadzone ) ) 
			{
				if( oEvent.jaxis.axis == JOYSTICK_AXIS_YAW) 
				{
					m_fYaw = (float)oEvent.jaxis.value/32768; 
				}
					
				if( oEvent.jaxis.axis == JOYSTICK_AXIS_PITCH) 
				{
					m_fPitch = (float)(oEvent.jaxis.value * -1.0f)/32768; 
				}

				if( oEvent.jaxis.axis == JOYSTICK_AXIS_ROLL) 
				{
					m_fRoll = (float)oEvent.jaxis.value/32768; 
				}
					
			}
			else
			{
				if( oEvent.jaxis.axis == JOYSTICK_AXIS_YAW) 
				{
					m_fYaw = 0.0f; 
				}

				if( oEvent.jaxis.axis == JOYSTICK_AXIS_PITCH) 
				{
					m_fPitch = 0.0f; 
				}

				if( oEvent.jaxis.axis == JOYSTICK_AXIS_ROLL) 
				{
					m_fRoll = 0.0f; 
				}

			}
			break;
				
		case SDL_JOYHATMOTION:  /* Handle Hat Motion */
			if ( oEvent.jhat.value & SDL_HAT_UP )
			{
				m_bCamUp = true;
		   }
			else
			{
				m_bCamUp = false;
			}

			if ( oEvent.jhat.value & SDL_HAT_LEFT )
			{
				m_bCamLeft = true;
		   }
			else
			{
				m_bCamLeft = false;
			}

			if ( oEvent.jhat.value & SDL_HAT_RIGHT )
			{
				m_bCamRight = true;
		   }
			else
			{
				m_bCamRight = false;
			}

			if ( oEvent.jhat.value & SDL_HAT_DOWN )
			{
				m_bCamDown = true;
		   }
			else
			{
				m_bCamDown = false;
			}
			break;
		}

		return done;
}

//Handle mouse events
bool COpenGL::mouseUser(SDL_Event oEvent)
{
	bool done = getCommon(oEvent);

	switch(oEvent.type) {

		case SDL_KEYDOWN:
			switch (oEvent.key.keysym.sym)
			{
				case SDLK_UP:
					m_fThrust += 0.01f;
					break;

				case SDLK_DOWN:

					m_fThrust -= 0.01f;
					if (m_fThrust < 0.00)
						m_fThrust = 0.00;
					break;

				case SDLK_KP8:

					m_bCamUp = true;
					break;

				case SDLK_KP2:

					m_bCamDown = true;
					break;

				case SDLK_KP6:

					m_bCamRight = true;
					break;

				case SDLK_KP4:

					m_bCamLeft = true;
					break;

				case SDLK_RIGHT:

					m_fRoll += 1.0;
					break;

				case SDLK_LEFT:

					m_fRoll -= 1.0;
					break;
				default:
					break;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:  /* Handle Joystick Button Presses */
			if ( oEvent.button.button == SDL_BUTTON_LEFT ) 
			{
				m_bFire = true;
 			}

			break;

		case SDL_MOUSEBUTTONUP:  /* Handle Joystick Button Presses */
			if ( oEvent.button.button == SDL_BUTTON_LEFT ) 
			{
				m_bFire = false;
 			}

			break;

		case SDL_MOUSEMOTION:  /* Handle Joystick Motion */

			m_fYaw = (float)oEvent.motion.xrel / 10.0f;
			m_fPitch = (float)oEvent.motion.yrel / 10.0f;

			break;

		default:
			m_fYaw = 0.0f;
			m_fPitch = 0.0f;
			m_fRoll = 0.0f;
			m_bCamUp = m_bCamDown = m_bCamRight = m_bCamLeft = false;
		}

		return done;

}

//Events used by both mouse/joystick
bool COpenGL::getCommon(SDL_Event oEvent)
{
	bool bDone = false;

	switch (oEvent.type)
	{
		case SDL_QUIT:
			bDone = true; // If So done=true
			break;

		case SDL_KEYDOWN:
			if (oEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				bDone = true; // If So done=true
			}
			m_oKeys.m_abKeyDown[oEvent.key.keysym.sym] = true;
			break;

		case SDL_KEYUP:
			m_oKeys.m_abKeyDown[oEvent.key.keysym.sym] = false;
			m_oKeys.m_abStillPressed[oEvent.key.keysym.sym] = false;
			break;
	}

	return bDone;
}

void COpenGL::DrawSplashScreen()
{
   CFrame oFrame;

   glEnable(GL_TEXTURE_2D);		

   // Set viewport
   glViewport(0, 0, static_cast<int>(m_vecScreenSize.X()), static_cast<int>(m_vecScreenSize.Y()));

   // Set camera
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f, (GLfloat)1024/(GLfloat)768, 0.1f, 25001.0f);

   // Init modelview matrix
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   oFrame.init(0.0f, 0.0f, 1.0f, 1.0f, "loadscreen.png");

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   oFrame.renderQuad();

}

void COpenGL::stopShipMovement()
{
	m_fYaw = 0.0f;
	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_bCamUp = m_bCamDown = m_bCamRight = m_bCamLeft = false;
}
