#include "GL/OpenGL.h"
#include "Sound/SoundManager.h"
#include "IO/Input.h"
#include "IO/Lua.h"
#include "Math/Vector.h"
#include "3D/Material.h"
#include <SDL.h>

#include <iostream>
using namespace std;
using namespace NSDSound;

/**
 * Program entry point.
 */
int main(int argc, char* argv[])
{
   
   bool bDone(false);  // Bool Variable To Exit Loop
   unsigned long int		dTickCount;	
   unsigned long int		dLastTickCount;
   COpenGL oGame;
   SDL_Event oEvent;
   SDL_Joystick *poJoystick;
   bool bNoJoystick = true;
   
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
   {
      cerr << "Failed to initialise SDL: " << SDL_GetError() << endl;
      return 1;
   }

	// Get config variables;
	int iDepth, iDouble, iStereo, iBPP;
	CRGBAColour colDepth(0,0,0,0);
	CVector2 vecSize(0,0);
	bool bFullScreen, bEnableSound;
	{
		NSDIO::CLua config("config.lua");
		if (!config.setGlobalTable("video")) {
			cerr << "Couldn't load config file!" << endl;
			return 1;
		}
		vecSize = config.getVector2("resolution");
		iBPP = static_cast<int>(config.getNumber("bpp"));
		bFullScreen = static_cast<bool>(config.getNumber("fullscreen"));
		colDepth = config.getColour("colours");
		iDepth = static_cast<int>(config.getNumber("depthbuffer"));
		iDouble = static_cast<int>(config.getNumber("doublebuffer"));
		iStereo = static_cast<int>(config.getNumber("stereo"));

		if (!config.setGlobalTable("sound")) {
			cerr << "Couldn't load config file!" << endl;
			return 1;
		}
                bEnableSound = static_cast<bool>(config.getNumber("enable"));

	}
	


   // Set video mode
   int iFlags = SDL_OPENGL;
   if (bFullScreen) iFlags |= SDL_FULLSCREEN;
   // Attempt SDL screen setup
   SDL_GL_SetAttribute( SDL_GL_RED_SIZE, static_cast<int>(colDepth.R()));
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, static_cast<int>(colDepth.G()));
   SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, static_cast<int>(colDepth.B()));
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, static_cast<int>(colDepth.A()));
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, iDepth );
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, iDouble );
#ifdef SDL_GL_STEREO
   SDL_GL_SetAttribute( SDL_GL_STEREO, iStereo );   
#endif
   // Try full settings
   if( SDL_SetVideoMode( static_cast<int>(vecSize.X()), static_cast<int>(vecSize.Y()), iBPP, iFlags ) == 0 ) {
      cerr << "Failed to set video mode: " << SDL_GetError() << endl;
      return 1;
   }

   // Disable sound if apt
   if (!bEnableSound)
      g_oSoundManager.disable();

   // Play sound
   if (!g_oSoundManager.playMusicFile("background.ogg"))
      cerr << "Failed to open background.ogg" << endl;
   
   // Set window title
#ifdef VERSION
   SDL_WM_SetCaption("Alienation v" VERSION, "Alienation");
#else
   SDL_WM_SetCaption("Alienation", "Alienation");
#endif
   
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

   if (!oGame.initGL())
     return 0;
   
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
      
      if (oGame.DrawGLScene()) SDL_GL_SwapBuffers( );
      else bDone = true; // ESC or DrawGLScene Signalled A Quit
		if (bNoJoystick)
		{
			oGame.stopShipMovement();
		}
   }
   
   // Shutdown
   SDL_ShowCursor(1);
   
#ifdef WIN32
   SDL_WM_GrabInput(SDL_GRAB_OFF);
#endif
   
   // Exit The Program
   atexit(SDL_Quit);
   return 0;
}

