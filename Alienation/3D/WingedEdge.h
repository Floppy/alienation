#ifndef ALIENATION_WINGEDEDGE_H
#define ALIENATION_WINGEDEDGE_H

#include "config.h"
#include "Math/Vector.h"


class CWEEdge;
class CWEVertex;
class CWEFace;

/**
 * An edge in a winged-edge mesh.
 */
class CWEEdge {
   
 public:
   
   /**
    * Constructor.
    */
   CWEEdge() :
      m_pStart(NULL),
      m_pEnd(NULL),
      m_pLeft(NULL),
      m_pRight(NULL),
      m_pPrevLeft(NULL),
      m_pNextLeft(NULL),
      m_pPrevRight(NULL),
      m_pNextRight(NULL)
   {}

   /**
    * The vertex this winged-edge begins from.
    */
   CWEVertex* m_pStart;

   /**
    * The vertex this winged-edge ends at.
    */
   CWEVertex* m_pEnd;

   /**
    * The face to the left of this winged-edge.
    */
   CWEFace* m_pLeft;

   /**
    * The face to the right of this winged-edge.
    */
   CWEFace* m_pRight;

   /**
    * The previous winged-edge on a traversal of the left face.
    */
   CWEEdge* m_pPrevLeft;

   /**
    * The next winged-edge on a traversal of the left face.
    */
   CWEEdge* m_pNextLeft;

   /**
    * The previous winged-edge on a traversal of the right face.
    */
   CWEEdge* m_pPrevRight;

   /**
    * The next winged-edge on a traversal of the right face.
    */
   CWEEdge* m_pNextRight;

};

/**
 * A vertex in a winged-edge mesh.
 */
class CWEVertex {
   
 public:

   /**
    * Constructor.
    * @param vecPosition The 3D position of the vertex.
    */
   CWEVertex(CVector3& vecPosition) :
      m_vecPosition(vecPosition),
      m_pEdge(NULL)      
   {}

   /**
    * The 3D position of the vertex.
    */
   CVector3 m_vecPosition;
   
   /**
    * A winged-edge that points away from this vertex.
    */
   CWEEdge* m_pEdge;

};

/**
 * A face in a winged-edge mesh.
 * For texturing purposes, we assume the face is triangular.
 */
class CWEFace {
   
 public:

   /**
    * Constructor.
    */
   CWEFace() :
      m_pEdge(NULL)      
   {}

   /**
    * Texture coordinate indices for each corner.
    * m_iCoordIndex[0] refers to the texture coordinate for the vertex pointed to by m_pEdge.
    */
   int m_iCoordIndex[3];

   /**
    * A winged-edge that borders this face.
    */
   CWEEdge* m_pEdge;

};


#endif // ALIENATION_WINGEDEDGE_H
