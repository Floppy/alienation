#include "3D/WEMesh.h"
#include <GL/gl.h>
#include <iostream>

using namespace std;

CWEMesh::CWEMesh() {
}

CWEMesh::~CWEMesh() {
}

void CWEMesh::init() {
   CMesh::init();
   return;
}

void CWEMesh::render() const {
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }
}
