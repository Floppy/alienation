AUTOMAKE_OPTIONS = foreign

SUBDIRS = Data Math Physics 3D IO Game AI GL

bin_PROGRAMS = Alienation

Alienation_SOURCES = config.h Alienation.cpp

Alienation_LDADD = GL/libAlienationGL.a AI/libAlienationAI.a Game/libAlienationGame.a IO/libAlienationIO.a 3D/libAlienation3D.a Physics/libAlienationPhysics.a Math/libAlienationMath.a
