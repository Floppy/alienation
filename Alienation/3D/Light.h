#ifndef LIGHT_H
#define LIGHT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "config.h"
#include "3D/Material.h"
#include "Math/Vector.h"
#include <GL/gl.h>

using namespace NSDMath;

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
	void init(const CRGBAColour& oAmbient, const CRGBAColour& oDiffuse, const CVector3& oPosition);

        /**
         * Change colour.
         */
	void update(GLenum type, const CRGBAColour& oColour);

        /**
         * Change position.
         */
        void updatePosition(const CVector3& position);

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
	CRGBAColour m_oAmbient;

        /**
         * Diffuse colour.
         */
	CRGBAColour m_oDiffuse;

        /**
         * Position.
         */
	float m_afPosition[4];


        /**
         * GL light ID
         */
        GLenum m_iLight;

};

#endif // LIGHT_H
