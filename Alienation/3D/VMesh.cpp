#include "3D/VMesh.h"
#include <GL/gl.h>
#include <iostream>

using namespace std;

CVMesh::CVMesh() {
}

CVMesh::~CVMesh() {
}

void CVMesh::init() {
   CMesh::init();
   return;
}

void CVMesh::render() const {
   if (!m_bInitialised) {
      cerr << "WARNING: Mesh not initialised!" << endl;
      return;
   }
}
