#ifndef ALIENATION_MATERIAL_H
#define ALIENATION_MATERIAL_H

#include "config.h"
#include <SDL/SDL_opengl.h>
#include <GL/glext.h>

#include "Math/Vector.h"

/**
 * Colour with Red, Green, Blue and Alpha components.
 * Designed to be easy to use as a GL colour. Values are stored as floating-point values 0..1
 */ 
class CRGBAColour 
{

public:

   /**
    * Constructor
    * Arguments are float colour values to set this colour to.
    * @param fRed The red value.
    * @param fGreen The green value.
    * @param fBlue The blue value.
    * @param fAlpha The alpha value.
    */ 
   CRGBAColour(float fRed, float fGreen, float fBlue, float fAlpha) 
   {
      m_afColour[0] = fRed;
      m_afColour[1] = fGreen;
      m_afColour[2] = fBlue;
      m_afColour[3] = fAlpha;
   }

   CRGBAColour() 
   {
   }

   /**
    * Component access.
    * @return The red value.
    */ 
   float R() const
      { return m_afColour[0]; }

   /**
    * Component access.
    * @return The green value.
    */ 
   float G() const
      { return m_afColour[1]; }
   
   /**
    * Component access.
    * @return The blue value.
    */ 
   float B() const
      { return m_afColour[2]; }
   
   /**
    * Component access.
    * @return The alpha value.
    */ 
   float A() const
      { return m_afColour[3]; }
   
   /**
    * Array access
    * @return An array suitable for using directly with glColor4fv() and other similar functions.
    */ 
   const float* glColour() const
   { return m_afColour; }

 protected:

   /**
    * Component array.
    */ 
   float m_afColour[4];

};


/**
 * Surface material.
 * This class should encapsulate everything about a single surface, i.e. colours,
 * textures, shininess, and so on.
 */ 
class CMaterial
{
   
 public:
	 void disableDot3() const;
	 void renderBumpMap() const;
   
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
    * Prepare material for rendering.
    */ 
   void init();

   /**
    * Render material using GL.
    */ 
   void render() const;

   /**
    * Boolean to say if material has bump map
    */ 
	bool m_bHasBumpMap;

   /**
    * Colour under ambient lighting.
    */ 
   CRGBAColour m_oAmbient;

   /**
    * Colour under diffuse lighting.
    */ 
   CRGBAColour m_oDiffuse;

   /**
    * Colour that this object emits.
    */ 
   CRGBAColour m_oEmissive;

   /**
    * Colour that this object reflects.
    */ 
   CRGBAColour m_oSpecular;

   /**
    * Materials shininess value
    */ 
	float m_fShininess;

   /**
    * Texture ID.
    */ 
   unsigned int m_uiTexture;

	/**
    * Bump map texture ID.
    */ 
   unsigned int m_uiBumpTexture;
};

#endif // ALIENATION_MATERIAL_H
