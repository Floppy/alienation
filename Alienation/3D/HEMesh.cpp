#include "3D/HEMesh.h"
#include <GL/gl.h>
#include <iostream>

using namespace std;

CHEMesh::CHEMesh() {
}

CHEMesh::~CHEMesh() {
}

void CHEMesh::init() {
   CMesh::init();
   return;
}

void CHEMesh::render() const {
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }
}
