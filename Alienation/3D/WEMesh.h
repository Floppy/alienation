#ifndef ALIENATION_WEMESH_H
#define ALIENATION_WEMESH_H

#include "config.h"
#include "3D/Mesh.h"
#include "3D/FMesh.h"
#include "3D/WingedEdge.h"
#include "Math/Vector.h"
#include <vector>

using namespace std;

/**
 * A winged-edge polygon mesh structure.
 */
class CWEMesh : public CMesh {
   
 public:
   
   /**
    * Constructor.
    */
   CWEMesh();

   /**
    * Constructor from fixed-topology mesh.
    * @param oMesh The mesh to convert to a winged-edge structure.
    */
   CWEMesh(CFMesh& oMesh);
   
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

   /**
    * Test vertex adjacency.
    * @param pVert1 First vertex to test.
    * @param pVert2 Second vertex to test.
    * @return If vertices are connected, return the connecting edge. Otherwise returns NULL.
    */
   CWEEdge* adjacent(CWEVertex* pVert1, CWEVertex* pVert2);

 protected:

   /**
    * Vertex list
    */
   vector<CWEVertex*> m_lpVertices;

   /**
    * Face list
    */
   vector<CWEFace*> m_lpFaces;

   /**
    * Edge list
    */
   vector<CWEEdge*> m_lpEdges;

   /**
    * Texture coordinate list
    */
   vector<CVector2> m_lTexVerts;

};

#endif // ALIENATION_WEMESH_H
