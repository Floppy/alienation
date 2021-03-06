#ifndef C3D_OBJECT_H
#define C3D_OBJECT_H

#include "config.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"
#include "3D/BoundingSphere.h"

using namespace NSDMath;

/**
 * Base class for 3D objects. 
 * This class is intended to be a base for all renderable objects. Anything that can
 * be rendered should be derived from here. It provides a standard interface to drawable
 * objects, enabling other classes to ignore exact details of what they are rendering.
 */
class C3DObject {
   
 public:
   
   /**
    * Constructor
    */
   C3DObject() :
      m_vecTranslation(0,0,0),
      m_bInitialised(false)
   {}
   
   /**
    * Destructor
    */
   virtual ~C3DObject() {}
   
	void setRotation(CMatrix matRotation)
	{
		m_matRotation = matRotation;
	}

	const CMatrix & getRotation() const
	{ return m_matRotation; }

	/**
    * Object initialisation. 
    * This function should be overridden in derived classes to set up any data required for 
    * rendering. For instance, normal computations, display list generation, and so on. Derived 
    * class members that override this functions should generally call their base class init() 
    * at some point.
    * @sa render()
    */
   virtual void init() 
   { m_bInitialised = true; }

   /**
    * Render to screen.
    * All derived classes MUST override this function, and use it to render themselves to screen
    * (currently using OpenGL). Any one-time rendering setup should be done in an overridden init() function.
    * @sa init()
    */
   virtual void render() const = 0;

   /**
    * Access the value of the translation
    * @return The translation value.
    * @sa setTranslation()
    */
   virtual const CVector3& getTranslation() const 
   { return m_vecTranslation; }

   /**
    * Set the value of the translation
    * @param vecTranslation The new translation value.
    * @sa getTranslation()
    */
   virtual void setTranslation(CVector3 vecTranslation) 
   { m_vecTranslation = vecTranslation; }
   
   /**
    * Get bounding sphere.
    * @return Bounding sphere.
    */
   CBoundingSphere& boundingSphere()
   { return m_oSphere; }

   /**
    * Get bounding sphere.
    * @return Bounding sphere.
    */
   const CBoundingSphere& boundingSphere() const
   { return m_oSphere; }

 protected:

	CMatrix   m_matRotation;
   /**
    * The translation of the object.
    */
   CVector3 m_vecTranslation;

   /**
    * Has init() been called? 
    */
   bool m_bInitialised;

   /**
    * Bounding sphere.
    */
   CBoundingSphere m_oSphere;

};

#endif // C3D_OBJECT_H
