#ifndef ALIENATION_WEMESH_H
#define ALIENATION_WEMESH_H

#include "config.h"
#include "3D/Mesh.h"
#include "3D/WingedEdge.h"
#include "Math/Vector.h"

/**
 * A winged-edge polygon mesh structure.
 */
class CWEMesh : public CMesh {
   
 public:
   
   /**
    * Constructor.
    */
   CWEMesh();
   // 
   
   /**
    * Destructor.
    * Deletes all allocated data.
    */
   virtual ~CWEMesh();
   
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

#endif // ALIENATION_WEMESH_H
