#include "GL/OpenGL.h"
#include "Sound/SoundManager.h"
#include "IO/Input.h"
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

   // Set video mode
   int iFlags = SDL_OPENGL | SDL_FULLSCREEN;
   // Attempt full-on SDL screen setup
   SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 5 );
   SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
   SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
   SDL_GL_SetAttribute( SDL_GL_STEREO, 1 );   
   // Try full settings
   if( SDL_SetVideoMode( 1024, 768, 16, iFlags ) == 0 ) {
      // Try without stereo
      cerr << "Disabling stereo display: " << SDL_GetError() << endl;
      SDL_GL_SetAttribute( SDL_GL_STEREO, 0 );
      if( SDL_SetVideoMode( 1024, 768, 16, iFlags ) == 0 ) {
         // Try without double buffer
         cerr << "Disabling double buffer: " << SDL_GetError() << endl;
         SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );
         if( SDL_SetVideoMode( 1024, 768, 16, iFlags ) == 0 ) {
            cerr << "Failed to set video mode: " << SDL_GetError() << endl;
            return 1;
         }
      }
   }

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
      
      if (oGame.DrawGLScene()) SDL_GL_SwapBuffers( );
      else bDone = true; // ESC or DrawGLScene Signalled A Quit

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

