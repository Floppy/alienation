#ifndef ALIENATION_MATERIAL_H
#define ALIENATION_MATERIAL_H

#include "config.h"
#include "Math/Vector.h"

/**
 * Colour with Red, Green, Blue and Alpha components.
 * Designed to be easy to use as a GL colour. Values are stored as bytes 0..255
 */ 
class CRGBAColour 
{

public:

   /**
    * Constructor
    * Arguments are byte colour values to set this colour to.
    * @param cRed The red value.
    * @param cGreen The green value.
    * @param cBlue The blue value.
    * @param cAlpha The alpha value.
    */ 
   CRGBAColour(unsigned char cRed, unsigned char cGreen, unsigned char cBlue, unsigned char cAlpha) 
   {
      m_acColour[0] = cRed;
      m_acColour[1] = cGreen;
      m_acColour[2] = cBlue;
      m_acColour[3] = cAlpha;
   }

   /**
    * Component access.
    * @return The red value.
    */ 
   unsigned char R() 
      { return m_acColour[0]; }

   /**
    * Component access.
    * @return The green value.
    */ 
   unsigned char G() 
      { return m_acColour[1]; }
   
   /**
    * Component access.
    * @return The blue value.
    */ 
   unsigned char B() 
      { return m_acColour[2]; }
   
   /**
    * Component access.
    * @return The alpha value.
    */ 
   unsigned char A() 
      { return m_acColour[3]; }
   
   /**
    * Array access
    * @return An array suitable for using directly with glColor4ubv()
    */ 
   const unsigned char* glColour() const
   { return m_acColour; }

 protected:

   /**
    * Component array.
    */ 
   unsigned char m_acColour[4];

};


/**
 * Surface material.
 * This class should encapsulate everything about a single surface, i.e. colours,
 * textures, shininess, and so on.
 */ 
class CMaterial
{
   
 public:
   
   /**
    * Constructor.
    */ 
   CMaterial();

   /**
    * Destructor.
    * Decrements the reference counter for the texture.
    */ 
   ~CMaterial();

   /**
    * Copy constructor.
    * Increments the reference counter for the texture.
    * @param material The material to copy values from.
    */ 
   CMaterial(const CMaterial& material);

   /**
    * Assignment operator.
    * Increments the reference counter for the texture.
    * @param material The material to copy values from.
    */ 
   const CMaterial& operator=(const CMaterial& material);

   /**
    * Render material using GL.
    */ 
   void render() const;

   /**
    * Diffuse Colour.
    */ 
   CRGBAColour m_oDiffuse;

   /**
    * Texture ID.
    */ 
   unsigned int m_uiTexture;

};

#endif // ALIENATION_MATERIAL_H
