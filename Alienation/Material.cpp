#include "Material.h"

CMaterial::CMaterial() :
   m_iTexureId(0),
   m_fUTile(1),
   m_fVTile(1),
   m_fUOffset(0),
   m_fIvOffset(0)
{
   m_uiColor[0] = m_uiColor[1] = m_uiColor[2] = 0;

}

