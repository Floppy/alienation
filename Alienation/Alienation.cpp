/********************************************************************
 * FILENAME.: Program.cpp
 * NICKNAME.: Doubt
 * NAME.....: Daniel Vivas
 * E-MAIL...: daniel@vivas.com.br
 * DATE.....: 03/08/2002
 * HOME-PAGE: http://www.danielvivas.cjb.net
 * GROUP....: Jogos Brasil
 ********************************************************************/

/*
 *      This Code Was Created By Jeff Molofee 2000
 *      A HUGE Thanks To Fredric Echols and Daniel Vivas For Cleaning Up
 *      And Optimizing This Code, Making It More Flexible!
 *      If You've Found This Code Useful, Please Let Me Know.
 *      Visit My Site At nehe.gamedev.net
 */

#include "GL/OpenGL.h"
#include "Sound/SoundManager.h"
#include <SDL.h>

#include <iostream>
using namespace std;

#define RANDOM_FLOAT ((float)(rand()%1000)/1000.0f)     // Returns a random value between 0.0f and 1.0f
#define piover180 	(0.0174532925f)

int main(int argc, char* argv[])
{
   bool     bDone = false;  // Bool Variable To Exit Loop
   int      iVirtual_code;
	unsigned long int		dTickCount;	
	unsigned long int		dLastTickCount;
   COpenGL	oGame = COpenGL();
	SDL_Event oEvent;
	SDL_Joystick *poJoystick;
	bool bNoJoystick = true;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1)
	{
		cerr << "Failed to initialise SDL" << endl;
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	int iFlags = SDL_OPENGL;// | SDL_FULLSCREEN;

	// Play sound
	CSoundManager oSndMgr;
	if (oSndMgr.Ready()) {
	  if (!oSndMgr.PlayLoopedMP3("./Data/Audio/demo.mp3"))
	    cerr << "Failed to open demo.mp3" << endl;
	}
	else 
	  cerr << "Failed to initialise sound subsystem!" << endl;  


	// Set the video mode
	if( SDL_SetVideoMode( 1024, 768, 16, iFlags ) == 0 ) {
		cerr << "Failed to set video mode" << endl;
		return 1;
	}

	SDL_JoystickEventState(SDL_ENABLE);


	poJoystick = SDL_JoystickOpen(0);
	if (poJoystick)
	{
		bNoJoystick = false;
	}

	SDL_ShowCursor(0);

        #ifdef WIN32
	SDL_WM_GrabInput(SDL_GRAB_ON);
        #endif


	oGame.initGL();

	dLastTickCount = SDL_GetTicks();


	// Loop That Runs While done=false   
	while (!bDone) {

      // Is There A Message Waiting?
		while (SDL_PollEvent(&oEvent))
		{
			if (bNoJoystick)
			{
				bDone = oGame.mouseUser(oEvent);
			}
			else
			{
				bDone = oGame.jsUser(oEvent);
			}

		}

		// Draw The Scene
		dTickCount = SDL_GetTicks ();				// Get The Tick Count
		oGame.Update (dTickCount - dLastTickCount);	// Update The Counter
		dLastTickCount = dTickCount;			// Set Last Count To Current Count

		if (oGame.DrawGLScene()) 
		{
			 SDL_GL_SwapBuffers( );
		}
		else 
		{
			bDone = true; // ESC or DrawGLScene Signalled A Quit
		}
	} //while

	// Shutdown
	SDL_ShowCursor(1);

        #ifdef WIN32
	SDL_WM_GrabInput(SDL_GRAB_OFF);
        #endif

	// Exit The Program
	atexit(SDL_Quit);
	return 0;
}

