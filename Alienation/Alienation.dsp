# Microsoft Developer Studio Project File - Name="Alienation" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=Alienation - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Alienation.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Alienation.mak" CFG="Alienation - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Alienation - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "Alienation - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Alienation - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib SDL.lib SDL_image.lib SDL_mixer.lib lua.lib lualib.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "Alienation - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Alienation___Win32_Debug"
# PROP BASE Intermediate_Dir "Alienation___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "./" /I "./include" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib glu32.lib SDL.lib SDLmain.lib SDL_image.lib SDL_mixer.lib lua.lib lualib.lib /nologo /subsystem:console /profile /map /debug /machine:I386 /nodefaultlib:"msvcrt.lib" /libpath:"./library"

!ENDIF 

# Begin Target

# Name "Alienation - Win32 Release"
# Name "Alienation - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\2D\2DObject.cpp
# End Source File
# Begin Source File

SOURCE=.\IO\3ds.cpp
# End Source File
# Begin Source File

SOURCE=.\AI\AIShip.cpp
# End Source File
# Begin Source File

SOURCE=.\Alienation.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Asteroid.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\BoundingSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Brake.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\FMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Frustum.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\GameObject.cpp
# End Source File
# Begin Source File

SOURCE=.\GL\GLFont.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\HEMesh.cpp
# End Source File
# Begin Source File

SOURCE=.\2D\Hud.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Light.cpp
# End Source File
# Begin Source File

SOURCE=.\IO\Lua.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Material.cpp
# End Source File
# Begin Source File

SOURCE=.\Math\Matrix.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Mesh.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\GL\OpenGL.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Particle.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\ParticleEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\Math\Perlin.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\PlayerShip.cpp
# End Source File
# Begin Source File

SOURCE=.\Math\Quat.cpp
# End Source File
# Begin Source File

SOURCE=.\Math\Random.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Ship.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound\SoundManager.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Sprite.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Stars.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\Texture.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\TextureManager.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Trail.cpp
# End Source File
# Begin Source File

SOURCE=.\Game\Weapon.cpp
# End Source File
# Begin Source File

SOURCE=.\IO\WeaponFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\3D\WEMesh.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\2D\2DObject.h
# End Source File
# Begin Source File

SOURCE=.\3D\3DObject.h
# End Source File
# Begin Source File

SOURCE=.\IO\3ds.h
# End Source File
# Begin Source File

SOURCE=.\AI\AIShip.h
# End Source File
# Begin Source File

SOURCE=.\Game\Asteroid.h
# End Source File
# Begin Source File

SOURCE=.\3D\BoundingSphere.h
# End Source File
# Begin Source File

SOURCE=.\Game\Brake.h
# End Source File
# Begin Source File

SOURCE=.\config.h
# End Source File
# Begin Source File

SOURCE=.\3D\FMesh.h
# End Source File
# Begin Source File

SOURCE=.\3D\Frustum.h
# End Source File
# Begin Source File

SOURCE=.\Game\GameObject.h
# End Source File
# Begin Source File

SOURCE=.\GL\GLFont.h
# End Source File
# Begin Source File

SOURCE=.\3D\HalfEdge.h
# End Source File
# Begin Source File

SOURCE=.\3D\HEMesh.h
# End Source File
# Begin Source File

SOURCE=.\2D\Hud.h
# End Source File
# Begin Source File

SOURCE=.\Input.h
# End Source File
# Begin Source File

SOURCE=.\3D\Light.h
# End Source File
# Begin Source File

SOURCE=.\IO\Lua.h
# End Source File
# Begin Source File

SOURCE=.\3D\Material.h
# End Source File
# Begin Source File

SOURCE=.\Math\Matrix.h
# End Source File
# Begin Source File

SOURCE=.\3D\Mesh.h
# End Source File
# Begin Source File

SOURCE=.\3D\Model.h
# End Source File
# Begin Source File

SOURCE=.\GL\OpenGL.h
# End Source File
# Begin Source File

SOURCE=.\3D\Particle.h
# End Source File
# Begin Source File

SOURCE=.\3D\ParticleEngine.h
# End Source File
# Begin Source File

SOURCE=.\Math\Perlin.h
# End Source File
# Begin Source File

SOURCE=.\Physics\Physics1.h
# End Source File
# Begin Source File

SOURCE=.\Game\PlayerShip.h
# End Source File
# Begin Source File

SOURCE=.\Math\Quat.h
# End Source File
# Begin Source File

SOURCE=.\Math\Random.h
# End Source File
# Begin Source File

SOURCE=.\Game\Ship.h
# End Source File
# Begin Source File

SOURCE=.\Sound\SoundManager.h
# End Source File
# Begin Source File

SOURCE=.\3D\Sprite.h
# End Source File
# Begin Source File

SOURCE=.\Game\Stars.h
# End Source File
# Begin Source File

SOURCE=.\3D\Texture.h
# End Source File
# Begin Source File

SOURCE=.\3D\TextureManager.h
# End Source File
# Begin Source File

SOURCE=.\Game\Trail.h
# End Source File
# Begin Source File

SOURCE=.\Math\Vector.h
# End Source File
# Begin Source File

SOURCE=.\Game\Weapon.h
# End Source File
# Begin Source File

SOURCE=.\IO\WeaponFactory.h
# End Source File
# Begin Source File

SOURCE=.\3D\WEMesh.h
# End Source File
# Begin Source File

SOURCE=.\3D\WingedEdge.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
