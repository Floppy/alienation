AC_INIT(program.cpp)
AM_INIT_AUTOMAKE(Alienation,0.1)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

SDL_LIBS="`sdl-config --libs`"
SDL_CFLAGS="`sdl-config --cflags`"

CPPFLAGS="$CPPFLAGS $SDL_CFLAGS -I$with_fmod/inc -Wall"
LIBS="$LIBS $SDL_LIBS -lGL -lGLU -lSDL_image -lfmod-3.62 -L$with_fmod"

AC_CHECK_HEADER(fmod.h,,exit)
AC_CHECK_LIB(fmod-3.62,FSOUND_Init,,exit)

AC_OUTPUT(Makefile Math/Makefile IO/Makefile 3D/Makefile Physics/Makefile GL/Makefile)
