# Initialise
AC_PREREQ(2.13)
AC_INIT(Alienation.cpp)
AM_INIT_AUTOMAKE(Alienation,0.1)

# Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

# Enable all warnings
CPPFLAGS="$CPPFLAGS -Wall"

# Profiling
AC_ARG_ENABLE(profiling,
    [ --enable-profiling=<type> - Enable profiling, either prof or gprof],
)
case "$enable_profiling" in
  prof) AC_CHECK_TOOL(PROF,prof)
        CPPFLAGS="$CPPFLAGS -p"
        CXXFLAGS="$CXXFLAGS -p" ;;
  gprof) AC_CHECK_TOOL(GPROF,gprof)
         CPPFLAGS="$CPPFLAGS -pg"
         CXXFLAGS="$CXXFLAGS -pg" ;;
esac

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
    [ --with-fmod=<path> path to fmod. e.g. /usr or /usr/local],
    [FMOD_PREFIX=$with_fmod]
)
LIBS="$LIBS -lfmod-3.62"
if test "$with_fmod"; then
  echo Using fmod API from $with_fmod
  FMOD_CPPFLAGS="-I$with_fmod/include"
  FMOD_LIBS="-L$with_fmod/lib"
fi
_OLD_CPPFLAGS="$CPPFLAGS"
_OLD_LIBS="$LIBS"
CPPFLAGS="$CPPFLAGS $FMOD_CPPFLAGS"
LIBS="$LIBS $FMOD_LIBS"
AC_CHECK_HEADER(fmod.h,,exit)
AC_CHECK_LIB(fmod-3.62,FSOUND_Init,,exit)
AC_SUBST(FMOD_CPPFLAGS)
AC_SUBST(FMOD_LIBS)
CPPFLAGS="$_OLD_CPPFLAGS"
LIBS="$_OLD_LIBS"

# Checks for headers
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
#AC_HEADER_STDBOOL
AC_C_CONST

# Checks for library functions.
AC_CHECK_FUNCS([atexit memset sqrt])

# Output
AC_OUTPUT(2D/Makefile
          3D/Makefile
          AI/Makefile
          Data/Makefile
          Data/Audio/Makefile
          Data/Model/Makefile
          Data/Texture/Makefile
          Data/Texture/Hud/Makefile
          Game/Makefile
          GL/Makefile
          IO/Makefile
          Math/Makefile
          Physics/Makefile
          Sound/Makefile
          Makefile)
