#include "3D/Material.h"
#include "3D/TextureManager.h"
#include <GL/gl.h>

#include <iostream>
using namespace std;

CMaterial::CMaterial() :
   m_oDiffuse(0,0,0,0),
   m_uiTexture(0)
{
}

CMaterial::~CMaterial() {
   g_oTextureManager.addReference(m_uiTexture);
}

CMaterial::CMaterial(const CMaterial& material) :
   m_oDiffuse(material.m_oDiffuse),
   m_uiTexture(material.m_uiTexture)
{
   g_oTextureManager.addReference(m_uiTexture);
}

const CMaterial& CMaterial::operator=(const CMaterial& material) {
   // Texture
   m_uiTexture = material.m_uiTexture;
   g_oTextureManager.addReference(m_uiTexture);
   // Colour
   m_oDiffuse = material.m_oDiffuse;
   // Done
   return *this;
}

void CMaterial::render() const {
   // Texture
   glEnable(GL_TEXTURE_2D);
   g_oTextureManager.activate(m_uiTexture);
   // Diffuse colour
   glColor4ubv(m_oDiffuse.glColour());
   // Done
   return;
}
