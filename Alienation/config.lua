-- config.lua
-- Config file for Alienation

video = {

	-- Video mode
	resolution = {x=1024, y=768},
	bpp = 16,
	fullscreen = 0,
	
	-- OpenGL options
	colours = {r=5, g=6, b=5, a=5},
	depthbuffer = 16,
	doublebuffer = 1,
	stereo = 0,
	polygonsmooth = 0,
	perspectivecorrection = 1,
	texturefilter = 1, -- 1 = GL_NEAREST
	                   -- 2 = GL_LINEAR
	                   -- 3 = GL_NEAREST_MIPMAP_NEAREST
	                   -- 4 = GL_LINEAR_MIPMAP_NEAREST
	                   -- 5 = GL_NEAREST_MIPMAP_LINEAR
	                   -- 6 = GL_LINEAR_MIPMAP_LINEAR
}

sound = {

	enable = 0,

}

game = {

	playership = "ter_shuttle1.lua",
	aiships = {
		"ter_fighter1.lua",
		"ter_fighter1.lua",
		"ter_shuttle1.lua"
	},
	numroids = 40
}
