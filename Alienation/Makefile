CC   = gcc
CPP  = g++
LD   = ld
AR   = ar
MAKE = make

EXE = Demo

CPPFLAGS = -Wall

OBJS = 3ds.o GLFont.o ParticleEngine.o skybox.o Weapon.o \
	3dsLoader.o GUI.o PlayerShip.o Stars.o Widgit.o \
	AIShip.o Light.o program.o Texture.o \
	Brake.o matrix.o quat.o Trail.o \
	Cpp1.o opengl.o Ship.o Vertices.o

all: demo

demo: $(OBJS)
	$(CPP) -o $(EXE) $(OBJS)

.cpp.o:
	$(CPP) -c $(CPPFLAGS) $<
