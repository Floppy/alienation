#include "3D/Material.h"
#include "3D/TextureManager.h"
#include <SDL_opengl.h>
#include "GL/Extensions.h"

#include <iostream>
using namespace std;

CMaterial::CMaterial() :
   m_bHasBumpMap(false),
   m_oAmbient(0,0,0,0),
   m_oDiffuse(0,0,0,0),
   m_oEmissive(0,0,0,0),
   m_oSpecular(0,0,0,0),
   m_fShininess(10.0f),
   m_uiTexture(0),
   m_uiBumpTexture(0)
{
}

CMaterial::CMaterial(const CMaterial& material) :
   m_bHasBumpMap(material.m_bHasBumpMap),
   m_oAmbient(material.m_oAmbient),
   m_oDiffuse(material.m_oDiffuse),
   m_oEmissive(material.m_oEmissive),
   m_oSpecular(material.m_oSpecular),
   m_fShininess(material.m_fShininess),
   m_uiTexture(material.m_uiTexture),
   m_uiBumpTexture(material.m_uiBumpTexture)
{
   g_oTextureManager.addReference(m_uiTexture);
}

CMaterial::~CMaterial() 
{
   g_oTextureManager.addReference(m_uiTexture);
}

const CMaterial& CMaterial::operator=(const CMaterial& material) 
{
   // Texture
   m_uiTexture = material.m_uiTexture;
	m_uiBumpTexture = material.m_uiBumpTexture;
   g_oTextureManager.addReference(m_uiTexture);
	g_oTextureManager.addReference(m_uiBumpTexture);
   // Colours
   m_oAmbient = material.m_oAmbient;
   m_oDiffuse = material.m_oDiffuse;
   m_oEmissive = material.m_oEmissive;
   m_oSpecular = material.m_oSpecular;
	m_fShininess = material.m_fShininess;
	m_bHasBumpMap = material.m_bHasBumpMap;
   // Done
   return *this;
}

void CMaterial::init() 
{
   if (g_oTextureManager.texture(m_uiTexture))
      g_oTextureManager.texture(m_uiTexture)->init();

	if (g_oTextureManager.texture(m_uiBumpTexture))
		g_oTextureManager.texture(m_uiBumpTexture)->init();
}

void CMaterial::render() const 
{
	glActiveTextureARB(GL_TEXTURE1_ARB);

  	glEnable(GL_TEXTURE_2D);

	// Texture
   g_oTextureManager.render(m_uiTexture);
   // Colours
   glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,m_oAmbient.glColour());
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,m_oDiffuse.glColour());
   glMaterialfv(GL_FRONT,GL_EMISSION,m_oEmissive.glColour());
   glMaterialfv(GL_FRONT,GL_SPECULAR,m_oSpecular.glColour());
	glMaterialfv(GL_FRONT, GL_SHININESS, &m_fShininess);
   // Done
   return;
}

void CMaterial::renderBumpMap() const
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	
	glEnable(GL_TEXTURE_2D);

	g_oTextureManager.render(m_uiBumpTexture);
	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);
	glTexEnvf(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_DOT3_RGB_EXT);
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PRIMARY_COLOR_EXT);
	glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);
	glTexEnvf(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);
	glTexEnvf(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);

}

void CMaterial::disableDot3() const
{
	glActiveTextureARB(GL_TEXTURE0_ARB);
	glDisable(GL_TEXTURE_2D);
	glActiveTextureARB(GL_TEXTURE1_ARB);
	glEnable(GL_TEXTURE_2D);
}
