#include "3D/Material.h"
#include "3D/TextureManager.h"
#include <SDL_opengl.h>

#include <iostream>
using namespace std;

CMaterial::CMaterial() :
   m_oAmbient(0,0,0,0),
   m_oDiffuse(0,0,0,0),
   m_oEmissive(0,0,0,0),
   m_oSpecular(0,0,0,0),
   m_uiTexture(0)
{
}

CMaterial::~CMaterial() {
   g_oTextureManager.addReference(m_uiTexture);
}

CMaterial::CMaterial(const CMaterial& material) :
   m_oAmbient(material.m_oAmbient),
   m_oDiffuse(material.m_oDiffuse),
   m_oEmissive(material.m_oEmissive),
   m_oSpecular(material.m_oSpecular),
   m_uiTexture(material.m_uiTexture)
{
   g_oTextureManager.addReference(m_uiTexture);
}

const CMaterial& CMaterial::operator=(const CMaterial& material) {
   // Texture
   m_uiTexture = material.m_uiTexture;
   g_oTextureManager.addReference(m_uiTexture);
   // Colours
   m_oAmbient = material.m_oAmbient;
   m_oDiffuse = material.m_oDiffuse;
   m_oEmissive = material.m_oEmissive;
   m_oSpecular = material.m_oSpecular;
   // Done
   return *this;
}

void CMaterial::render() const {
   // Texture
	if (g_oTextureManager.valid(m_uiTexture))
	{
	   g_oTextureManager.activate(m_uiTexture);
	}
   // Colours
   glMaterialfv(GL_FRONT,GL_AMBIENT,m_oAmbient.glColour());
   glMaterialfv(GL_FRONT,GL_DIFFUSE,m_oDiffuse.glColour());
   glMaterialfv(GL_FRONT,GL_EMISSION,m_oEmissive.glColour());
   //glMaterialfv(GL_FRONT,GL_SPECULAR,m_oSpecular.glColour());
   // Done
   return;
}
