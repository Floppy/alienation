#ifndef LIGHT_H
#define LIGHT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "config.h"

#include <SDL_opengl.h>

#include "3D/3DObject.h"
#include "3D/Material.h"
#include "Math/Vector.h"

using namespace NSDMath;

/**
 * A light in a 3D scene.
 */
class CLight : public C3DObject
{
public:
        /**
         * Constructor.
         * @param iLight An OpenGL light identifier, e.g. GL_LIGHT0. 
         */
	CLight(GLenum iLight);

	CLight();

        /**
         * Destructor.
         */
	virtual ~CLight();

        /**
         * Initialisation.
         */
	void init(const CRGBAColour& oAmbient, const CRGBAColour& oDiffuse, const CVector3& oPosition);

        /**
         * Render light.
         */ 
        void render() const;

        /**
         * Change colour.
         */
	void update(GLenum type, const CRGBAColour& oColour);

        /**
         * Turn on light.
         */
        void enable()
        { 
			  glEnable(GL_LIGHTING);
			  glEnable(m_iLight); 
		  }
        
        /**
         * Turn off light.
         */
        void disable()
        { glDisable(m_iLight); }

        /**
         * Set the value of the translation
         * @param vecTranslation The new translation value.
         * @sa getTranslation()
         */
        void setTranslation(CVector3 vecTranslation);
   

 private:
        
        /**
         * Initialisation.
         * Overridden and declared private to prevent usage.
         */ 
        void init() {}

 protected:

        /**
         * Ambient colour.
         */
	CRGBAColour m_oAmbient;

        /**
         * Diffuse colour.
         */
	CRGBAColour m_oDiffuse;

        /**
         * Position.
         * GL requires a 4D vector for this.
         */
	float m_afPosition[4];

        /**
         * GL light ID
         */
        GLenum m_iLight;

};

#endif // LIGHT_H
