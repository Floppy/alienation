#ifndef ALIENATION_MODEL_H
#define ALIENATION_MODEL_H

#include "config.h"
#include "3D/3DObject.h"
#include "3D/3DObject.h"
#include "3D/Material.h"
#include "Math/Matrix.h"

#include <vector>

using namespace std;

/**
 * A 3D Model.
 * This is basically just a container object for multiple C3DObject objects. 
 * This means that a model can consist of many objects with different materials
 * and still be easily rendered.
 */
class CModel : public C3DObject {
   
 public:
   
   /**
    * Constructor.
    */
   CModel();

   /**
    * Destructor.
    * Deletes all child objects.
    */
   ~CModel();

   /**
    * Object initialisation. 
    * Calls init() on all child objects, and should be called once the model is 
    * completely loaded/created.
    */
   void init();
   
   /**
    * Render to screen.
    * Applies this object's transform, and then calls render() on all child objects.
    */
   void render() const;
   
   /**
    * Get the number of objects in the model.
    * @return The number of objects in the model.
    */
   unsigned int numObjects() 
   { return m_oObjects.size(); }

   /**
    * Add a object to this model.
    * This model will take ownership of the object and will delete the pointer when it's done with.
    * @param pObject A pointer to the object to add.
    */
   void addObject(C3DObject* pObject);

   /**
    * Get a object pointer.
    * @param uiObject The object index to get. Should be less that numObjects().
    */
   C3DObject* getObject(unsigned int uiObject) 
   { return m_oObjects[uiObject]; }

 protected:

   /**
    * Child object pointers.
    * Will be deleted in destructor.
    */
   vector<C3DObject*> m_oObjects;

};

#endif // ALIENATION_MODEL_H
