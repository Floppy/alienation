CC   = gcc
CPP  = g++
LD   = ld
AR   = ar
MAKE = make

EXE = Alienation
DEPEND = .depend

CPPFLAGS = -g -Wall

INC = -I/usr/include/SDL/

LIBS = -lGL -lGLU -lSDL -lpthread -lSDL_image -lfmod-3.62

OBJS = 3ds.o 3dsLoader.o AIShip.o Brake.o \
	GLFont.o GUI.o Light.o matrix.o Mesh.o opengl.o \
	ParticleEngine.o PlayerShip.o program.o quat.o \
	Ship.o Stars.o Texture.o Trail.o Vertices.o \
	Weapon.o Widgit.o

SRCS = 3ds.cpp 3dsLoader.cpp AIShip.cpp Brake.cpp \
	GLFont.cpp GUI.cpp Light.cpp matrix.cpp Mesh.cpp opengl.cpp \
	ParticleEngine.cpp PlayerShip.cpp program.cpp quat.cpp \
	Ship.cpp Stars.cpp Texture.cpp Trail.cpp Vertices.cpp \
	Weapon.cpp Widgit.cpp 

demo: $(OBJS)
	$(CPP) -o $(EXE) $(LIBS) $(OBJS)

.cpp.o:
	$(CPP) -c $(INC) $(CPPFLAGS) $<

depend: $(DEPEND)
$(DEPEND):
	g++ -MM $(INC) $(CPPFLAGS) $(SRCS) > $(DEPEND)

include $(DEPEND)

clean:
	rm -f $(OBJS) $(DEPEND) *~

distclean: clean
	rm -f $(EXE)
