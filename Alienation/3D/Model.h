#ifndef ALIENATION_MODEL_H
#define ALIENATION_MODEL_H

#include "config.h"
#include "3D/Mesh.h"
#include "3D/Material.h"

#include <vector>									

using namespace std;

class CModel {
   
 public:
   
   CModel();
   
   int m_iNumObjects;
   int m_iNumMaterials;
   vector<CMaterial> m_pMaterials;
   vector<CMesh> m_pObject;

};

#endif // ALIENATION_MODEL_H
