// Extensions.cpp
// Implementation for OpenGL extensions

#include "GL/Extensions.h"
#include <SDL.h>

#ifdef WIN32

PFNGLACTIVETEXTUREARBPROC   glActiveTextureARB   = NULL;
PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB = NULL;

#endif

void InitGLExtensions() {
   
#ifdef WIN32
   
   glActiveTextureARB   = (PFNGLACTIVETEXTUREARBPROC)   SDL_GL_GetProcAddress("glActiveTextureARB");
   glMultiTexCoord2fARB = (PFNGLMULTITEXCOORD2FARBPROC) SDL_GL_GetProcAddress("glMultiTexCoord2fARB");

#endif

}
