-- ter_fighter1.lua
-- Configuration file for the Terran Mk.1 Fighter

ship = {
	uname   	= "ter_fighter1",
	race    	= "terran",
	fullname	= "Fighter Mk.1",
	model   	= "fighter.3ds",
	cockpit		= "canopy02.3ds",
	pitch   	= 80,
	yaw 		= 50,
	roll 		= 90,
	thrust		= 10000,
	mass		= 2500,
	trails		= {
		{x=0, y=0, z=5}
	},
	weapons		= {
		{x=0, y=-1.5, z=-5},
	},
	weapontype	= "ter_ppc1.lua",
	brakes		= {
		{x=1.6, y=0.7, z=-2.5},
		{x=-1.6, y=0.7, z=-2.5}
	},
	shield_fore	= "ter_shield1.lua",
	shield_aft	= "ter_shield1.lua",
	shield_right	= "ter_shield1.lua",
	shield_left	= "ter_shield1.lua"
}
