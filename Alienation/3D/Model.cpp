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
   for (vector<CMesh*>::iterator it(m_oMeshes.begin()); it!=m_oMeshes.end(); ++it) {
      delete *it;
   }
}

void CModel::init() {
   // Init meshes
   for (vector<CMesh*>::iterator it(m_oMeshes.begin()); it!=m_oMeshes.end(); ++it) {
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
   for (vector<CMesh*>::const_iterator it(m_oMeshes.begin()); it!=m_oMeshes.end(); ++it) {
      (*it)->render();
   }
   // Pop
   glPopMatrix();
}

void CModel::addMesh(CMesh* pMesh) {
   m_oMeshes.push_back(pMesh);
}
