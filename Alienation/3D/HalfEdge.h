#ifndef ALIENATION_HALFEDGE_H
#define ALIENATION_HALFEDGE_H

#include "config.h"
#include "Math/Vector.h"


class CHEEdge;
class CHEVertex;
class CHEFace;


/**
 * An edge in a half-edge mesh.
 */
class CHEEdge {
   
 public:
   
   /**
    * The vertex this half-edge points to.
    */
   CHEVertex* m_pVertex;

   /**
    * The face this half-edge borders.
    */
   CHEFace* m_pFace;

   /**
    * The half-edge that this half-edge is paired with.
    */
   CHEEdge* m_pPair;

   /**
    * The next half-edge that borders m_pFace.
    */
   CHEEdge* m_pNext;

};

/**
 * A vertex in a half-edge mesh.
 */
class CHEVertex {
   
 public:

   /**
    * The 3D position of the vertex.
    */
   CVector3 m_vecPosition;
   
   /**
    * A half-edge that points away from this vertex.
    */
   CHEEdge* m_pEdge;

};

/**
 * A face in a half-edge mesh.
 * For texturing purposes, we assume the face is triangular.
 */
class CHEFace {
   
 public:

   /**
    * A half-edge that borders this face.
    */
   CHEEdge* m_pEdge;

   /**
    * Texture coordinate indices for each corner.
    * m_iCoordIndex[0] refers to the texture coordinate for the vertex pointed to by m_pEdge.
    */
   int m_iCoordIndex[3];

};


#endif // ALIENATION_HALFEDGE_H
