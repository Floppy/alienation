AUTOMAKE_OPTIONS = foreign

SUBDIRS = Data Math 3D IO Physics Sound AI Game 2D Equipment GUI GL

bin_PROGRAMS = Alienation

Alienation_SOURCES = config.h Alienation.cpp

Alienation_LDADD = GL/libAlienationGL.a GUI/libAlienationGUI.a Game/libAlienationGame.a Equipment/libAlienationEquipment.a AI/libAlienationAI.a 2D/libAlienation2D.a Sound/libAlienationSound.a Physics/libAlienationPhysics.a IO/libAlienationIO.a 3D/libAlienation3D.a Math/libAlienationMath.a

EXTRA_DIST = README LICENSE config.lua

doc: all doc.cfg
	doxygen doc.cfg
