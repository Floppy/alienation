AUTOMAKE_OPTIONS = foreign

SUBDIRS = Math

bin_PROGRAMS = Alienation

Alienation_SOURCES = 3ds.cpp Brake.cpp GUI.h Mesh.h ParticleEngine.h  Ship.cpp    Texture.cpp  Widgit.cpp /
	3ds.h          Brake.h     Light.cpp     Model.cpp           Particle.h        Ship.h      Texture.h    Widgit.h /
	3dsLoader.cpp  config.h    Light.h       Model.h             Physics1.h        skybox.cpp  Trail.cpp /
	3dsLoader.h    GLFont.cpp  Material.cpp  opengl.cpp          PlayerShip.cpp    Skybox.h    Trail.h /
	AIShip.cpp     GLFont.h    Material.h    opengl.h            PlayerShip.h      Stars.cpp   Weapon.cpp /
	AIShip.h       GUI.cpp     Mesh.cpp      ParticleEngine.cpp  program.cpp       Stars.h     Weapon.h /

LDADD = Math/libAlienationMath.a
