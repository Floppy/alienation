#ifndef C3D_OBJECT_H
#define C3D_OBJECT_H

#include "config.h"
#include "Math/Vector.h"

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
      m_bInitialised(false)
   {}
   
   /**
    * Destructor
    */
   virtual ~C3DObject() {}
   
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
   const CVector3& getTranslation() const 
   { return m_vecTranslation; }

   /**
    * Set the value of the translation
    * @param: vecTranslation The new translation value.
    * @sa getTranslation()
    */
   void setTranslation(CVector3 vecTranslation) 
   { m_vecTranslation = vecTranslation; }
   
 protected:

   /**
    * The translation of the object.
    */
   CVector3 m_vecTranslation;

   /**
    * Has init() been called? 
    */
   bool m_bInitialised;

};

#endif // C3D_OBJECT_H
