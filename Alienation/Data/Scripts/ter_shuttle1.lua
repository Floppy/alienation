-- ter_shuttle1.lua
-- Configuration file for the Terran Mk.1 Shuttle

ship = {
	uname   	= "ter_shuttle1",
	race    	= "terran",
	fullname	= "Shuttle Mk.1",
	model   	= "shuttle.3ds",
	cockpit		= "canopy02.3ds",
	pitch   	= 40,
	yaw 		= 25,
	roll 		= 45,
	thrust		= 10000,
	mass		= 5000,
	trails		= {
		{x= 1.6, y=-0.25, z=3.75},
		{x=-1.6, y=-0.25, z=3.75}
	},
	weapons		= {
		{x=3, y=-0.7, z=-4},
		{x=-3, y=-0.7, z=-4},
		{x=0, y=-1.7, z=-7}
	},
	weapontype	= "ter_ppc2.lua",
	brakes		= {
		{x=0, y=0.7, z=-2.5}
	},
	shield_fore	= "ter_shield1.lua",
	shield_aft	= "ter_shield1.lua",
	shield_right	= "ter_shield1.lua",
	shield_left	= "ter_shield1.lua"
}
