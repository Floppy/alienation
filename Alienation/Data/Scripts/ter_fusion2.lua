-- ter_fusion2.lua
-- Configuration file for the Terran Mk.2 Fusion Engine

engine = {
	uname   	= "ter_fusion2",
	race    	= "terran",
	fullname	= "Fusion Engine Mk.2",
	thrust		= 10000,
	trail		= {
		type	= "particle",
		texture	= "star.png",
		colour  = {r=1, g=1, b=0.25, a=0.75},
		maxsize	= 1,
		number	= 500,
	},	
	flare		= {
		texture	= "flare.png",
		colour	= {r=1, g=1, b=1, a=1},
		maxsize	= 3,
	},
}
