#ifndef ALIENATION_MATERIAL_H
#define ALIENATION_MATERIAL_H

#include "config.h"
#include "Math/Vector.h"

class CRGBAColour 
{

public:

   CRGBAColour(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) 
   {
      m_acColour[0] = cRed;
      m_acColour[1] = cGreen;
      m_acColour[2] = cBlue;
      m_acColour[3] = cAlpha;
   }
   // Constructor

   unsigned char R() 
      { return m_acColour[0]; }
   // Get red component

   unsigned char G() 
      { return m_acColour[1]; }
   // Get green component
   
   unsigned char B() 
      { return m_acColour[2]; }
   // Get blue component
   
   unsigned char A() 
      { return m_acColour[3]; }
   // Get blue component
   
   const unsigned char* GLColour() const
   { return m_acColour; }
   // Get the array for glColor4ubv

 protected:

   unsigned char m_acColour[4];

};


class CMaterial
{
public:
   
   CMaterial();
   // Constructor

   void render() const;
   // Render material using GL

   char m_strName[255];
   char m_strFile[255];

   // Surface properties
   CRGBAColour m_oDiffuse;

   unsigned int m_uiTexture;
   // Texture ID

   CVector2 m_oTexTranslation;
   // Texture translation
   
   CVector2 m_oTexScale;
   // Texture scaling
};

#endif // ALIENATION_MATERIAL_H
