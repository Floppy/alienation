#include "3D/Model.h"
#include <GL/gl.h>
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
   // Init meshes
   for (vector<C3DObject*>::iterator it(m_oObjects.begin()); it!=m_oObjects.end(); ++it) {
      (*it)->init();
   }
   C3DObject::init();
}

void CModel::render() const {
   if (!m_bInitialised) {
      //cerr << "WARNING: Model not initialised!" << endl;
      return;
   }
   // Push
   glPushMatrix();
   // Translate
   glTranslatef(m_vecTranslation.X(),m_vecTranslation.Y(),m_vecTranslation.Z());
   // Draw meshes
   for (vector<C3DObject*>::const_iterator it(m_oObjects.begin()); it!=m_oObjects.end(); ++it) {
      (*it)->render();
   }
   // Pop
   glPopMatrix();
}

void CModel::addObject(C3DObject* pObject) {
   m_oObjects.push_back(pObject);
}
