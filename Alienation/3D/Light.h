#ifndef LIGHT_H
#define LIGHT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "config.h"
#include <GL/gl.h>

/**
 * A light in a 3D scene.
 */
class CLight  
{
public:
        /**
         * Constructor.
         * @param iLight An OpenGL light identifier, e.g. GL_LIGHT0. 
         */
	CLight(GLenum iLight);

        /**
         * Destructor.
         */
	virtual ~CLight();

        /**
         * Initialise.
         */
	void init(float afAmbient[4], float afDiffuse[4], float afPosition[4]);

        /**
         * Change colour.
         */
	void update(GLenum type, float afAmount[4]);

        /**
         * Turn on light.
         */
        void enable()
        { glEnable(m_iLight); }
        
        /**
         * Turn off light.
         */
        void disable()
        { glDisable(m_iLight); }

 protected:

        /**
         * Ambient colour.
         */
	float m_afLightAmbient[4];

        /**
         * Diffuse colour.
         */
	float m_afLightDiffuse[4];

        /**
         * Position.
         */
	float m_afLightPosition[4];


        /**
         * GL light ID
         */
        GLenum m_iLight;

};

#endif // LIGHT_H
