#include "3D/Material.h"
#include "3D/TextureManager.h"
#include <GL/gl.h>

CMaterial::CMaterial() :
   m_oDiffuse(0,0,0,0),
   m_uiTexture(0)
{
}

void CMaterial::render() const {
   // Texture
   glEnable(GL_TEXTURE_2D);
   if (g_oTextureManager.activate(m_uiTexture)) {
      glDisable(GL_TEXTURE_2D);
   }
   // Diffuse colour
   glColor4ubv(m_oDiffuse.GLColour());
   // Done
   return;
}
