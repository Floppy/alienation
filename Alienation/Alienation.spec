Summary: 3D mutliplayer space shooter client.
Name: Alienation
Version: 0.0.4
Release: 1
Copyright: commercial
Vendor: Steam Driven Software
Source: Alienation-0.0.4.tar.gz
Group: Amusements/Games
requires: lua >= 5
requires: SDL >= 1.2.5
requires: SDL_image >= 1.2.2
requires: SDL_mixer >= 1.2.4

%description 
The Alienation client program.

%define debug_package %{nil}
%undefine __check_files

%prep
%setup -q

%build
./configure
make RPM_OPT_FLAGS="$RPM_OPT_FLAGS"

%install
make install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)

/usr/local/bin/Alienation
/usr/local/share/Alienation/Data/Audio/background.ogg
/usr/local/share/Alienation/Data/Audio/thrust.wav
/usr/local/share/Alienation/Data/Audio/weapon.wav
/usr/local/share/Alienation/Data/Model/canopy02.3ds
/usr/local/share/Alienation/Data/Model/copper.3ds
/usr/local/share/Alienation/Data/Model/fighter.3ds
/usr/local/share/Alienation/Data/Model/gold1.3ds
/usr/local/share/Alienation/Data/Model/gold2.3ds
/usr/local/share/Alienation/Data/Model/ice1.3ds
/usr/local/share/Alienation/Data/Model/radar.3ds
/usr/local/share/Alienation/Data/Model/redcrystal1.3ds
/usr/local/share/Alienation/Data/Model/redcrystal2.3ds
/usr/local/share/Alienation/Data/Model/redcrystal3.3ds
/usr/local/share/Alienation/Data/Model/roid1.3ds
/usr/local/share/Alienation/Data/Model/shuttle.3ds
/usr/local/share/Alienation/Data/Texture/Hud/hud_aft.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_fore.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_left.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_reticle.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_right.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_speed.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_target.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_thrust.png
/usr/local/share/Alienation/Data/Texture/Hud/hud_scale.png
/usr/local/share/Alienation/Data/Texture/amethyst.jpg
/usr/local/share/Alienation/Data/Texture/amethyst.png
/usr/local/share/Alienation/Data/Texture/an01.png
/usr/local/share/Alienation/Data/Texture/an02.png
/usr/local/share/Alienation/Data/Texture/an03.png
/usr/local/share/Alienation/Data/Texture/ball.png
/usr/local/share/Alienation/Data/Texture/benedeti.jpg
/usr/local/share/Alienation/Data/Texture/blueDOT3.png
/usr/local/share/Alienation/Data/Texture/bluepan1.png
/usr/local/share/Alienation/Data/Texture/canopy01.png
/usr/local/share/Alienation/Data/Texture/fighter1DOT3.png
/usr/local/share/Alienation/Data/Texture/fighter1.png
/usr/local/share/Alienation/Data/Texture/fighter2DOT3.png
/usr/local/share/Alienation/Data/Texture/flare.png
/usr/local/share/Alienation/Data/Texture/goldmarb.jpg
/usr/local/share/Alienation/Data/Texture/loadscreen.png
/usr/local/share/Alienation/Data/Texture/smoke.png
/usr/local/share/Alienation/Data/Texture/star.png
/usr/local/share/Alienation/Data/Texture/sun.png
/usr/local/share/Alienation/Data/Texture/text.png
/usr/local/share/Alienation/Data/Texture/whtgran.jpg
/usr/local/share/Alienation/Data/Scripts/ter_shuttle1.lua
/usr/local/share/Alienation/Data/Scripts/ter_fighter1.lua
/usr/local/share/Alienation/Data/Scripts/ter_fusion1.lua
/usr/local/share/Alienation/Data/Scripts/ter_fusion2.lua
/usr/local/share/Alienation/Data/Scripts/ter_ppc1.lua
/usr/local/share/Alienation/Data/Scripts/ter_ppc2.lua
/usr/local/share/Alienation/Data/Scripts/ter_shield1.lua
/usr/local/share/Alienation/README
/usr/local/share/Alienation/LICENSE
/usr/local/share/Alienation/config.lua

%changelog
* Mon Dec 08 2003 James Smith <james@floppy.org.uk> 
- New RPM release of 0.0.4 client
