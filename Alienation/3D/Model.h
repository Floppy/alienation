#ifndef ALIENATION_MODEL_H
#define ALIENATION_MODEL_H

#include "config.h"
#include "3D/3DObject.h"
#include "3D/Mesh.h"
#include "3D/Material.h"

#include <vector>

using namespace std;

/**
 * A 3D Model.
 * This is basically just a container object for multiple CMesh objects. 
 * This means that a model can consist of many meshes with different materials
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
    * Deletes all child meshes.
    */
   ~CModel();

   /**
    * Object initialisation. 
    * Calls init() on all child meshes, and should be called once the model is 
    * completely loaded/created.
    */
   void init();
   
   /**
    * Render to screen.
    * Applies this object's transform, and then calls render() on all child meshes.
    */
   void render() const;
   
   /**
    * Add a mesh to this model.
    * This model will take ownership of the mesh and will delete the pointer when it's done with.
    * @param pMesh A pointer to the mesh to add.
    */
   void addMesh(CMesh* pMesh);

 protected:

   /**
    * Child mesh pointers.
    * Will be deleted in destructor.
    */
   vector<CMesh*> m_oMeshes;

};

#endif // ALIENATION_MODEL_H
