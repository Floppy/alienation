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
AC_CHECK_HEADER(GL/gl.h,,exit)
AC_CHECK_LIB(GL,glEnable,,exit)
AC_CHECK_HEADER(GL/glu.h,,exit)
AC_CHECK_LIB(GLU,gluProject,,exit)

# SDL
SDL_LIBS="`sdl-config --libs`"
SDL_CFLAGS="`sdl-config --cflags` -DNO_SDL_GLEXT"
LIBS="$LIBS $SDL_LIBS"
CPPFLAGS="$CPPFLAGS $SDL_CFLAGS"
AC_CHECK_HEADER(SDL.h,,exit)
AC_CHECK_LIB(SDL,SDL_Init,,exit)
AC_CHECK_HEADER(SDL_image.h,,exit)
AC_CHECK_LIB(SDL_image,IMG_Load,,exit)
AC_CHECK_HEADER(SDL_mixer.h,,exit)
AC_CHECK_LIB(SDL_mixer,Mix_OpenAudio,,exit)
AC_CHECK_HEADER(SDL_net.h,,exit)
AC_CHECK_LIB(SDL_net,SDLNet_Init,,exit)

# Lua
AC_ARG_WITH(lua,"--with-lua=<dir> - Path to Lua files",
[	if test $withval != "yes"; then
		LDFLAGS="$LDFLAGS -L$withval/lib"
		CPPFLAGS="$CPPFLAGS -I$withval/include"
	fi
])
AC_CHECK_HEADER(lua.h,,exit)
AC_CHECK_HEADER(lualib.h,,exit)
AC_CHECK_HEADER(lauxlib.h,,exit)
AC_CHECK_LIB(lua,lua_open,,exit)
AC_CHECK_LIB(lualib,lua_dofile,,exit)

# ODE
#AC_ARG_WITH(ode,"--with-ode=<dir> - Path to ODE files",
#[	if test $withval != "yes"; then
#		LDFLAGS="$LDFLAGS -L$withval/lib"
#		CPPFLAGS="$CPPFLAGS -I$withval/include"
#	fi
#])
#AC_CHECK_HEADER(ode/ode.h,,exit)
#AC_CHECK_LIB(ode,dWorldCreate,,exit)

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
	  Equipment/Makefile
          Game/Makefile
          GL/Makefile
          IO/Makefile
          GUI/Makefile
          Math/Makefile
          Physics/Makefile
          Server/Makefile
          Sound/Makefile
          Makefile)
