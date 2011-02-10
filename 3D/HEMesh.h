#ifndef ALIENATION_HEMESH_H
#define ALIENATION_HEMESH_H

#include "config.h"
#include "3D/Mesh.h"
#include "3D/HalfEdge.h"
#include "Math/Vector.h"

/**
 * A half-edge polygon mesh structure.
 */
class CHEMesh : public CMesh {
   
 public:
   
   /**
    * Constructor.
    */
   CHEMesh();
   // 
   
   /**
    * Destructor.
    * Deletes all allocated data.
    */
   virtual ~CHEMesh();
   
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

#endif // ALIENATION_HEMESH_H
