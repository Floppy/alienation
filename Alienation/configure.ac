AC_INIT(program.cpp)
AM_INIT_AUTOMAKE(Alienation,0.1)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_RANLIB

SDL_LIBS="`sdl-config --libs`"
SDL_CFLAGS="`sdl-config --cflags`"
AC_SUBST(SDL_LIBS)
AC_SUBST(SDL_CFLAGS)

AC_OUTPUT(Makefile Math/Makefile IO/Makefile)
