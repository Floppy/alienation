# Initialise
AC_PREREQ(2.13)
AC_INIT(program.cpp)
AM_INIT_AUTOMAKE(Alienation,0.1)

# Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

# Enable all warnings
CPPFLAGS="$CPPFLAGS -Wall"

# Checks for libraries

# OpenGL
LIBS="$LIBS -lGL -lGLU"

# SDL
SDL_LIBS="`sdl-config --libs`"
SDL_CFLAGS="`sdl-config --cflags`"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
LIBS="$LIBS $SDL_LIBS -lSDL_image"
AC_CHECK_HEADER(SDL.h,,exit)
AC_CHECK_LIB(SDL,SDL_Init,,exit)
AC_CHECK_HEADER(SDL_image.h,,exit)
AC_CHECK_LIB(SDL_image,IMG_Load,,exit)

# fmod
AC_ARG_WITH(fmod,
    [ --with-fmod=<path> path to fmod library. e.g. /usr/lib or /usr/local/lib],
    [FMOD_PREFIX=$with_fmod],
)
LIBS="$LIBS -lfmod-3.62"
if test -n "$with_fmod"; then
  CPPFLAGS="$CPPFLAGS -I$with_fmod/inc"
  LIBS="$LIBS -L$with_fmod"
fi
AC_CHECK_HEADER(fmod.h,,exit)
AC_CHECK_LIB(fmod-3.62,FSOUND_Init,,exit)

# Checks for headers
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([atexit memset sqrt])

# Output
AC_OUTPUT(3D/Makefile
          AI/Makefile
          GL/Makefile
          IO/Makefile
          Math/Makefile
          Physics/Makefile
          Makefile)
