AUTOMAKE_OPTIONS = foreign

SUBDIRS = Data Math 3D IO Physics Sound 2D AI Game Equipment GUI GL Server

bin_PROGRAMS = Alienation

Alienation_SOURCES = config.h Alienation.cpp

Alienation_LDADD = GL/libAlienationGL.la GUI/libAlienationGUI.la Game/libAlienationGame.la Equipment/libAlienationEquipment.la AI/libAlienationAI.la 2D/libAlienation2D.la Sound/libAlienationSound.la Physics/libAlienationPhysics.la IO/libAlienationIO.la 3D/libAlienation3D.la Math/libAlienationMath.la

EXTRA_DIST = README LICENSE config.lua

docdir = $(datadir)/Alienation

doc_DATA = README LICENSE config.lua

doc: all doc.cfg
	doxygen doc.cfg
