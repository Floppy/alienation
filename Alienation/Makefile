CC   = gcc
CPP  = g++
LD   = ld
AR   = ar
MAKE = make

EXE = Demo
DEPEND = .depend

CPPFLAGS = -Wall

INC = -I/usr/include/SDL/

LIBS = -lGL -lGLU -lSDL -lpthread -lSDL_image

OBJS = 3ds.o 3dsLoader.o AIShip.o Brake.o \
	GLFont.o GUI.o Light.o main.o matrix.o opengl.o \
        ParticleEngine.o PlayerShip.o quat.o Ship.o \
	skybox.o Stars.o Texture.o Trail.o Vertices.o \
        Weapon.o Widgit.o

SRCS = 3ds.cpp 3dsLoader.cpp AIShip.cpp Brake.cpp \
        GLFont.cpp GUI.cpp Light.cpp main.cpp matrix.cpp opengl.cpp \
        ParticleEngine.cpp PlayerShip.cpp quat.cpp Ship.cpp \
        skybox.cpp Stars.cpp Texture.cpp Trail.cpp Vertices.cpp \
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
	rm -f $(OBJS) $(DEPEND)

distclean: clean
	rm -f $(EXE)
