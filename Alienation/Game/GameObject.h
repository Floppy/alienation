#ifndef SDS_GAMEOBJECT_H
#define SDS_GAMEOBJECT_H

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Physics/Physics1.h"
#include <stdio.h>
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "Math/Matrix.h"
#include "3D/Model.h"
#include "3D/Frustum.h"

enum eTargetType
{
	TGT_SHIP,
	TGT_ASTEROID
};

class CGameObject : public CSimulation 
{
 public:
	 int getObjectID();
	 int getObjectType();
	 void setObjectType(int iObjectType);
   
   CGameObject(int num, float mass);
   CGameObject();

   virtual ~CGameObject();

   virtual void draw(bool bTestFrustum = true);

   virtual void drawBlended() {}

   virtual void setTarget(CGameObject* pTarget)
   { m_poTarget = pTarget; }

   void rotate(float dt);

   virtual void rotHeading(CMatrix m);

   virtual void simulate(float dt);

   CFrustum m_oFrustum;

   CGameObject*          m_poTarget;

   CModel	         m_oModel;

   CVector3		m_vecForce;

   CVector3		m_vecHeading, m_vecUp, m_vecRight, m_vecDirection;

   float			m_fPitch, m_fYaw, m_fRoll;

   float			m_fPitchRate;

   float			m_fYawRate;

   float			m_fRollRate;

   CMatrix		m_matRotation;

   float			m_fVel;

   float			m_fDrag;


private:
	int			m_iObjectType;
	int			m_iObjectID;
	static int	m_iLastID;

};

#endif // SDS_GAMEOBJECT_H
