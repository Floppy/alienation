/********************************************************************
 * FILENAME.: Program.cpp
 * NICKNAME.: Doubt
 * NAME.....: Daniel Vivas
 * E-MAIL...: daniel@vivas.com.br
 * DATE.....: 03/08/2002
 * HOME-PAGE: http://www.danielvivas.cjb.net
 * GROUP....: Jogos Brasil
 ********************************************************************/

#include "opengl.h"

// All Setup For OpenGL Goes Here
COpenGL :: COpenGL(HINSTANCE hinstance) {
	//Actually redundant now I'm using SDL, mmmmm
   FullScreen = true;
   hInstance  = hinstance;
   hDC        = NULL;        // Private GDI Device Context
   hRC        = NULL;        // Permanent Rendering Context
   hWnd       = NULL;        // Holds Our Window Handle
}

bool COpenGL :: initGL() {
	//All initialisation. Nothing rocket science here.
	float afAmbient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float afDiffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float afPosition[4] = {0.0f, 0.0f, 2.0f, 0.0f};

	m_bSlowmo = false;
	m_poLight = new CLight();
	m_poLight->init(afAmbient, afDiffuse, afPosition, GL_LIGHT0);
	m_bCamUp = m_bCamDown = m_bCamLeft = m_bCamRight = m_bFire = false;
	m_poGlfont = new CGLFont();
	m_poGlfont->load();
	int x;
	for (x = 0 ; x < 300 ; x++)
	{
		m_oKeys.m_abKeyDown[x] = false;
		m_oKeys.m_abStillPressed[x] =  false;
	}
	m_poAIShip = new CAIShip(1, 5000.0f);
	m_poAIShip->loadShip();
	m_poShip = new CPlayerShip();
	m_poShip->loadShip();
	m_poStars = new CStars;
	m_poStars->initStars();
	m_fTimeElapsed = 0.0f;
	m_fPitch = m_fYaw = m_fRoll = m_fThrust = 0.0f;
   glShadeModel(GL_SMOOTH);                           // Enable Smooth Shading
   glClearColor(0.0f, 0.0f, 0.0f, 0.5f);              // Black Background
   glClearDepth(1.0f);                                // Depth Buffer Setup
   glEnable(GL_DEPTH_TEST);                           // Enables Depth Testing
   glDepthFunc(GL_LEQUAL);                            // The Type Of Depth Testing To Do
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);                                 
//	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glBlendFunc(GL_ONE, GL_ONE);
	glEnable(GL_POLYGON_SMOOTH);
	glEnable(GL_TEXTURE_2D);		
   glViewport(0, 0, 1024, 768); // Reset The Current Viewport

   glMatrixMode(GL_PROJECTION);     // Select The Projection Matrix
   glLoadIdentity();                // Reset The Projection Matrix

   // Calculate The Aspect Ratio Of The Window
   gluPerspective(45.0f, (GLfloat)1024/(GLfloat)768, 0.1f, 25001.0f);

   glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
   glLoadIdentity();           // Reset The Modelview Matrix

   return true;
}

// Here's Where We Do All The Drawing. Nothing hard here. Only thing to note
//is all transparent objects are drawn last
bool COpenGL :: DrawGLScene(GLvoid) {
	char str[40];
	float p[4] = {0.0f, 2.0f, 2.0f, 0.0f};
	sprintf(str, "Speed: %.2f", m_poShip->m_poShips[0].m_fVel);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
   glLoadIdentity();					// Reset The Current Modelview Matrix
	m_poShip->draw();
	m_poAIShip->draw();
	m_poStars->draw(m_poShip->m_ppMasses[0]->m_vecPos);
	m_poShip->drawTrail();
	m_poAIShip->drawTrail();
	m_poShip->drawWeapons();
	m_poAIShip->drawWeapons();
	m_poShip->drawBrake();
	glEnable(GL_BLEND);
	glColor4f(0.0f, 1.0f, 1.0f, 0.7f);
	m_poGlfont->print(str, CVector3(-0.5f, 0.35f, -1.0f), 0.01f);
	if (m_poShip->m_poShips[0].m_iFlightMode == 1)
		sprintf(str, "Flight Mode: Normal");
	else
		if (m_poShip->m_poShips[0].m_iFlightMode == 2)
			sprintf(str, "Flight Mode: Turret");
		else
			sprintf(str, "Flight Mode: Straf");
		
	m_poGlfont->print(str, CVector3(-0.5f, 0.3f, -1.0f), 0.01f);
	sprintf(str,"Thrust: %.2f", m_poShip->m_poShips[0].m_fThrust);
	m_poGlfont->print(str, CVector3(-0.5f, 0.25f, -1.0f), 0.01f);

	sprintf(str,"A.I. Speed: %.2f", m_poAIShip->m_poShips[0].m_fVel);
	m_poGlfont->print(str, CVector3(-0.1f, 0.35f, -1.0f), 0.01f);
	sprintf(str,"Target: %.2f, %.2f, %.2f", m_poAIShip->m_vecTarget.m_fx, m_poAIShip->m_vecTarget.m_fy, m_poAIShip->m_vecTarget.m_fz);
	m_poGlfont->print(str, CVector3(-0.1f, 0.3f, -1.0f), 0.01f);
	sprintf(str,"PAngle: %.2f YAngle: %.2f", m_poAIShip->m_fXAngle, m_poAIShip->m_fYAngle);
	m_poGlfont->print(str, CVector3(-0.1f, 0.25f, -1.0f), 0.01f);
	
	glDisable(GL_BLEND);
   return true; // Everything Went OK
}

//Called from main, this funnction gives time based movement. Needs seperating into seperate 
//function calls for readability
void COpenGL::Update (DWORD dMilliseconds)								
{


	float fDT = dMilliseconds / 1000.0f;							// Let's Convert Milliseconds To Seconds

	//Undocumented for debugging, makes everything move 100 times slower
	//Initiated with the f10 key
	if (m_bSlowmo)
		fDT /= 100;

	//For flight mode one and two, the js/mouse movements translate into 
	//pitch yaw and roll, This is done here
	if (m_poShip->m_poShips[0].m_iFlightMode == 1 || m_poShip->m_poShips[0].m_iFlightMode == 2)
	{
		if (m_fPitch == 0.0f)
		{
			m_poShip->m_poShips[0].m_fPitchRate = 0.0f;
		}																	
		else
		{
			m_poShip->m_poShips[0].m_fPitchRate = m_poShip->m_poShips[0].m_fMaxPitchRate * m_fPitch;
			if (m_poShip->m_poShips[0].m_fPitchRate > m_poShip->m_poShips[0].m_fMaxPitchRate)
				m_poShip->m_poShips[0].m_fPitchRate = m_poShip->m_poShips[0].m_fMaxPitchRate;
			if (m_poShip->m_poShips[0].m_fPitchRate < -m_poShip->m_poShips[0].m_fMaxPitchRate)
				m_poShip->m_poShips[0].m_fPitchRate = -m_poShip->m_poShips[0].m_fMaxPitchRate;
		}

		if (m_fYaw == 0.0f)
		{
			m_poShip->m_poShips[0].m_fYawRate = 0.0f;
		}																	
		else
		{
			m_poShip->m_poShips[0].m_fYawRate = m_poShip->m_poShips[0].m_fMaxYawRate * m_fYaw;
			if (m_poShip->m_poShips[0].m_fYawRate > m_poShip->m_poShips[0].m_fMaxPitchRate)
				m_poShip->m_poShips[0].m_fYawRate = m_poShip->m_poShips[0].m_fMaxPitchRate;
			if (m_poShip->m_poShips[0].m_fYawRate < -m_poShip->m_poShips[0].m_fMaxYawRate)
				m_poShip->m_poShips[0].m_fYawRate = -m_poShip->m_poShips[0].m_fMaxYawRate;
		}
	
		if (m_fRoll == 0.0f)
		{
			m_poShip->m_poShips[0].m_fRollRate = 0.0f;
		}																	
		else
		{
			m_poShip->m_poShips[0].m_fRollRate = m_poShip->m_poShips[0].m_fMaxRollRate * m_fRoll;
			if (m_poShip->m_poShips[0].m_fRollRate > m_poShip->m_poShips[0].m_fMaxRollRate)
				m_poShip->m_poShips[0].m_fRollRate = m_poShip->m_poShips[0].m_fMaxRollRate;
			if (m_poShip->m_poShips[0].m_fRollRate < -m_poShip->m_poShips[0].m_fMaxRollRate)
				m_poShip->m_poShips[0].m_fRollRate = -m_poShip->m_poShips[0].m_fMaxRollRate;
		}
	}
	else //Flight mode 3. The effects of this are done in the simulate function
		  //so simply notify it using bools
	{
		if (m_fPitch > 0.0f)
		{
			m_poShip->m_poShips[0].m_bStraffUp = true;
		}																	
		else
		{
			if (m_fPitch < 0.0f)
			{
				m_poShip->m_poShips[0].m_bStraffDown = true;
			}									
			else
			{
				m_poShip->m_poShips[0].m_bStraffDown = false;
				m_poShip->m_poShips[0].m_bStraffUp = false;
			}
		}

		if (m_fYaw > 0.0f)
		{
			m_poShip->m_poShips[0].m_bStraffRight = true;
		}																	
		else
		{
			if (m_fYaw < 0.0f)
			{
				m_poShip->m_poShips[0].m_bStraffLeft = true;
			}									
			else
			{
				m_poShip->m_poShips[0].m_bStraffRight = false;
				m_poShip->m_poShips[0].m_bStraffLeft = false;
			}
		}
	}

	//Set the weaponFire bool if the firekey being pressed
	if (m_bFire && !m_poShip->m_poShips[0].m_bWeaponFire)
	{
		m_poShip->m_poShips[0].m_bWeaponFire = true;
	}
	else
	{
		if (!m_bFire && m_poShip->m_poShips[0].m_bWeaponFire)
			m_poShip->m_poShips[0].m_bWeaponFire = false;
	}

	//Thrust. Note that the max thrust is hard coded (10000), Ooooo naughty
	if (m_fThrust == 0.0f)
	{
		m_poShip->m_poShips[0].m_fThrust = 0.0f;
	}																	
	else
	{
		m_poShip->m_poShips[0].m_fThrust = m_fThrust * 10000.00f;
	}

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
			m_poShip->m_poShips[0].m_fCamPitch = 10.0f;
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
				m_poShip->m_poShips[0].m_fCamPitch = -10.0f;
			}
		}
		else
		{
			m_poShip->m_poShips[0].m_fCamPitch = 0.0f;
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
			m_poShip->m_poShips[0].m_fCamYaw = 10.0f;
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
				m_poShip->m_poShips[0].m_fCamYaw = -10.0f;
			}
		}
		else
		{
			m_poShip->m_poShips[0].m_fCamYaw = 0.0f;
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
		if (m_poShip->m_poShips[0].m_iFlightMode != 1)
				m_poShip->m_poShips[0].m_iFlightMode = 1;
	}

	//F3. Switches to turret flight
	if (m_oKeys.m_abKeyDown[SDLK_F3] && !m_oKeys.m_abStillPressed[SDLK_F3])
	{
		m_oKeys.m_abStillPressed[SDLK_F3] = true;
		if (m_poShip->m_poShips[0].m_iFlightMode != 2)
			m_poShip->m_poShips[0].m_iFlightMode = 2;
	}

	//F4. Switches to straff flight
	if (m_oKeys.m_abKeyDown[SDLK_F4] && !m_oKeys.m_abStillPressed[SDLK_F4])
	{
		m_oKeys.m_abStillPressed[SDLK_F4] = true;
		if (m_poShip->m_poShips[0].m_iFlightMode != 3)
			m_poShip->m_poShips[0].m_iFlightMode = 3;
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
		if (!m_poShip->m_poShips[0].m_bBraking)
			m_poShip->m_poShips[0].m_bBraking = true;
	}
	else
	{
		m_poShip->m_poShips[0].m_bBraking = false;
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
		m_poAIShip->m_vecTargetPos = m_poShip->m_ppMasses[0]->m_vecPos;
		m_poAIShip->operate(fDT);
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
			if( oEvent.jaxis.axis == 2) 
			{
				m_fThrust = (float)((oEvent.jaxis.value * -1.0f) + 30000) / 65536; 
				if (m_fThrust < 0.0f)
				{
					m_fThrust = 0.0f;
				}
			}

			if ( ( oEvent.jaxis.value < -3200 ) || (oEvent.jaxis.value > 3200 ) ) 
			{
				if( oEvent.jaxis.axis == 0) 
				{
					m_fYaw = (float)oEvent.jaxis.value/32768; 
				}
					
				if( oEvent.jaxis.axis == 1) 
				{
					m_fPitch = (float)(oEvent.jaxis.value * -1.0f)/32768; 
				}

				if( oEvent.jaxis.axis == 3) 
				{
					m_fRoll = (float)oEvent.jaxis.value/32768; 
				}
					
			}
			else
			{
				if( oEvent.jaxis.axis == 0) 
				{
					m_fYaw = 0.0f; 
				}

				if( oEvent.jaxis.axis == 1) 
				{
					m_fPitch = 0.0f; 
				}

				if( oEvent.jaxis.axis == 3) 
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
