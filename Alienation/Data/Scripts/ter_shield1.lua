-- ter_shield1.lua
-- Configuration file for the Terran Plasma Shield Mk.1

shield = {
	uname   	= "ter_shield1",
	race    	= "terran",
	fullname	= "Plasma Shield Mk. 1",
	fore 		= {
		hud		= {
			texture		= "Hud/hud_fore.png",
			position	= { x=0.375, y=0.32 },
			size		= { x=0.25, y=0.03 },
			colour 		= {r=1, g=1, b=1, a=1},
		}
	},
	aft 		= {
		hud		= {
			texture		= "Hud/hud_aft.png",
			position	= { x=0.375, y=0.65 },
			size		= { x=0.25, y=0.03 },
			colour 		= {r=1, g=1, b=1, a=1},
		}
	},
	right 		= {
		hud		= {
			texture		= "Hud/hud_right.png",
			position	= { x=0.625, y=0.35 },
			size		= { x=0.03, y=0.3 },
			colour 		= {r=1, g=1, b=1, a=1},
		}
	},
	left 		= {
		hud		= {
			texture		= "Hud/hud_left.png",
			position	= { x=0.345, y=0.35 },
			size		= { x=0.03, y=0.3 },
			colour 		= {r=1, g=1, b=1, a=1},
		}
	}
}
