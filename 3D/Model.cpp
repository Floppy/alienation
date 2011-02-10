#include "3D/Model.h"
#include <SDL_opengl.h>
#include <iostream>

using namespace std;

CModel::CModel() 
{
}

CModel::~CModel() 
{
   // Delete meshes
   for (vector<C3DObject*>::iterator it(m_oObjects.begin()); it!=m_oObjects.end(); ++it) {
      delete *it;
   }
}

void CModel::init() {
   vector<C3DObject*>::iterator it;

   // Init meshes
   for (it = m_oObjects.begin(); it!=m_oObjects.end(); ++it) {
      (*it)->init();
   }
   // Calculate bounding sphere
   for (it = m_oObjects.begin(); it!=m_oObjects.end(); ++it) {
      float fLength = (*it)->getTranslation().length() + (*it)->boundingSphere().m_fRadius;
      if (fLength > m_oSphere.m_fRadius) m_oSphere.m_fRadius = fLength;
   }
   C3DObject::init();
}

void CModel::render() const {

	NSDMath::CMatrix mat;

   if (!m_bInitialised) {
      //cerr << "WARNING: Model not initialised!" << endl;
      return;
   }
   // Push
   glPushMatrix();
   // Translate
   glTranslatef(m_vecTranslation.X(),m_vecTranslation.Y(),m_vecTranslation.Z());
	mat = CMatrix(GL_MODELVIEW_MATRIX);

	mat.invert();

   // Draw meshes
   for (vector<C3DObject*>::const_iterator it(m_oObjects.begin()); it!=m_oObjects.end(); ++it) {
		(*it)->setRotation(mat);
      (*it)->render();
   }
   // Pop
   glPopMatrix();
}

void CModel::addObject(C3DObject* pObject) {
   m_oObjects.push_back(pObject);
}
