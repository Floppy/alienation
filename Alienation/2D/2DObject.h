#ifndef SDS_2DOBJECT_H
#define SDS_2DOBJECT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "config.h"
#include "Math/Vector.h"

namespace NSD2D {

   using namespace NSDMath;
   

   /**
    * A 2D screen object.
    * Generally used for overlays, GUI elements etc.
    */
   class C2DObject {

   public:
      
      /** 
       * Constructor.
       */
      C2DObject();

      /** 
       * Destructor.
       */
      virtual ~C2DObject();

      void setScreen(int iWidth, int iHeight);

      void setPosition(int iXPos, int iYPos);

      void renderQuad(float fPosX, float fPosY, float fWidth, 
                      float fHeight, CVector2* vecTex);
      
   private:
      
      int m_iXPos;

      int m_iYPos;
      
      static int m_iWidth;

      static int m_iHeight;

   };
   
}

#endif // SDS_2DOBJECT_H
