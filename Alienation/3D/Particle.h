#ifndef _Particle_h
#define _Particle_h

#include "config.h"

#include "3D/3DObject.h"
#include "Math/Vector.h"
#include "Physics/Physics1.h"

/**
 * A Particle in a particle system.
 * Used by CParticleEngine and it's derived children.
 */
class CParticle
{

 public:

   /**
    * Constructor.
    * Sets the geometry for the particle.
    * @param pGeometry The object to show at the particle position.
    */
   CParticle(C3DObject* pGeometry = NULL);

   /**
    * Access the particle geometry.
    * @return The object that will be shown at the particle position.
    */
   C3DObject* getGeometry()
   { return m_pGeometry; }

   /**
    * Set the particle geometry.
    * @param pGeometry The object to show at the particle position.
    */
   void setGeometry(C3DObject* pGeometry)
   { m_pGeometry = pGeometry; }

   /**
    * Current position.
    */
   CVector3 m_vecPosition;

   /**
    * Last position.
    */
   CVector3 m_vecOldPosition;

   /**
    * Current acceleration.
    */
   CVector3 m_vecAcceleration;

   /**
    * The age of the particle..
    */
   float m_fAge;

   /**
    * The size of the particle.
    */
   float m_fSize;
   
   /**
    * Time left for the particle to live
    */
   float m_fTimeToLive;

   /**
    * Distance?
    * @bug Not sure what this represents.
    */
   float m_fDistance;

   /**
    * The speed of the particle.
    */
   float m_fSpeed;

 protected:

   /**
    * The geometry of the particle.
    * Can be any 3D object.
    */
   C3DObject* m_pGeometry;

};

#endif

