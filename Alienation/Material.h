#ifndef ALIENATION_MATERIAL_H
#define ALIENATION_MATERIAL_H

#include "config.h"

class CMaterial
{
public:
   
   CMaterial();

   char  m_strName[255];
   char  m_strFile[255];
   unsigned char  m_uiColor[3];
   int   m_iTexureId;
   float m_fUTile;
   float m_fVTile;
   float m_fUOffset;
   float m_fIvOffset;
};

#endif // ALIENATION_MATERIAL_H
