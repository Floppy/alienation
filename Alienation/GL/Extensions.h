// Extensions.h
// Definitions for OpenGL extensions

#ifndef SDS_EXTENSIONS_H
#define SDS_EXTENSIONS_H


#ifdef WIN32

extern PFNGLACTIVETEXTUREARBPROC   glActiveTextureARB;

extern PFNGLMULTITEXCOORD2FARBPROC glMultiTexCoord2fARB;

#endif

/**
 * Perform any initialisation required for OpenGL extensions.
 */
void InitGLExtensions();

#endif
