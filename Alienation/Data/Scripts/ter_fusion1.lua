-- ter_fusion1.lua
-- Configuration file for the Terran Mk.1 Fusion Engine

engine = {
	uname   	= "ter_fusion1",
	race    	= "terran",
	fullname	= "Fusion Engine Mk.1",
	thrust		= 5000,
	trail		= {
		type	= "particle",
		texture	= "star.png",
		colour  = {r=1, g=0.25, b=0.25, a=0.25},
		maxsize	= 1,
		number	= 250,
	},	
	flare		= {
		texture	= "flare.png",
		colour	= {r=1, g=1, b=1, a=1},
		maxsize	= 3,
	},
}
