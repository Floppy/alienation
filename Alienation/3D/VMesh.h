#ifndef ALIENATION_VMESH_H
#define ALIENATION_VMESH_H

#include "config.h"
#include "3D/Mesh.h"
#include "Math/Vector.h"

/**
 * A variable-topology polygon mesh structure.
 */
class CVMesh : public CMesh {
   
 public:
   
   /**
    * Constructor.
    */
   CVMesh();
   // 
   
   /**
    * Destructor.
    * Deletes all allocated data.
    */
   virtual ~CVMesh();
   
   /**
    * Perform one-time initialisation.
    * Should be called once the mesh is completely loaded/created.
    */
   void init();

   /** 
    * Render to screen.
    */
   void render() const;
    
};

#endif // ALIENATION_VMESH_H
