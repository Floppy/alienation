# Initialise
AC_PREREQ(2.13)
AC_INIT(Alienation.cpp)
AM_INIT_AUTOMAKE(Alienation,0.0.4)

# Check for programs
AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB
AC_PROG_INSTALL

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
LIBS="$LIBS $SDL_LIBS -lSDL_image -lSDL_mixer"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
AC_CHECK_HEADER(SDL.h,,exit)
AC_CHECK_LIB(SDL,SDL_Init,,exit)
AC_CHECK_HEADER(SDL_image.h,,exit)
AC_CHECK_LIB(SDL_image,IMG_Load,,exit)
AC_CHECK_HEADER(SDL_mixer.h,,exit)
AC_CHECK_LIB(SDL_mixer,Mix_OpenAudio,,exit)

# Lua
LIBS="$LIBS -llua -llualib"
AC_CHECK_HEADER(lua.h,,exit)
AC_CHECK_HEADER(lualib.h,,exit)
AC_CHECK_LIB(lualib,lua_open,,exit)

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
          Data/Scripts/Makefile
          Data/Texture/Makefile
          Data/Texture/Hud/Makefile
          Game/Makefile
          GL/Makefile
          IO/Makefile
          GUI/Makefile
          Math/Makefile
          Physics/Makefile
          Sound/Makefile
          Makefile)
