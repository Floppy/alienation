CC   = gcc
CPP  = g++
LD   = ld
AR   = ar
MAKE = make

EXE = Demo
DEPEND = .depend

CPPFLAGS = -Wall

INC = -I/usr/include/SDL

LIBS =

OBJS = 3ds.o GLFont.o ParticleEngine.o skybox.o Weapon.o \
	3dsLoader.o GUI.o PlayerShip.o Stars.o Widgit.o \
	AIShip.o Light.o program.o Texture.o \
	Brake.o matrix.o quat.o Trail.o \
	Cpp1.o opengl.o Ship.o Vertices.o

SRCS = 3ds.cpp GLFont.cpp ParticleEngine.cpp skybox.cpp Weapon.cpp \
        3dsLoader.cpp GUI.cpp PlayerShip.cpp Stars.cpp Widgit.cpp \
        AIShip.cpp Light.cpp program.cpp Texture.cpp \
        Brake.cpp matrix.cpp quat.cpp Trail.cpp \
        Cpp1.cpp opengl.cpp Ship.cpp Vertices.cpp

all: demo

demo: $(OBJS)
	$(CPP) -o $(EXE) $(LIBS) $(OBJS)

.cpp.o:
	$(CPP) -c $(INC) $(CPPFLAGS) $<

depend: $(DEPEND)
$(DEPEND):
	g++ -MM $(SRCS) > $(DEPEND)

include $(DEPEND)

clean:
	rm -f $(OBJS) $(DEPEND)

distclean: clean
	rm -f $(EXE)
