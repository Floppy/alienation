#ifndef _3DS_H
#define _3DS_H

#include "config.h"
#include "Math/Vector.h"
#include "3D/Mesh.h"
#include "3D/Model.h"
#include "3D/Material.h"

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <map>
#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Here is our structure for our 3DS indicies (since .3DS stores 4 unsigned shorts)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CIndices {							
public:
	unsigned short a, b, c, bVisible;		
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This holds the chunk info
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CChunk
{
public:
	unsigned short m_uiID;					
	unsigned int m_iLength;					
	unsigned int m_iBytesRead;					
};

//DAMN, complex stuff not touched it, but it works, so best left alone ;)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class handles all of the loading code
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CLoad3DS
{
public:
	CLoad3DS();								

	bool import3DS(CModel *pModel, const char *strFileName);

private:
	int getString(char *);

	void readChunk(CChunk *);

	void processNextChunk(CModel *pModel, CChunk *);

	void processNextObjectChunk(CModel *pModel, CChunk *);
	void processNextObjectChunk2(CMesh *pMesh, CChunk *);

	void processNextMaterialChunk(CModel *pModel, CChunk *);
	void processNextMaterialChunk2(CMaterial &pModel, CChunk *);

	void readColorChunk(CMaterial *pMaterial, CChunk *pChunk);

	void readVertices(CMesh *pObject, CChunk *);

	void readVertexIndices(CMesh *pObject, CChunk *);

	void readUVCoordinates(CMesh *pObject, CChunk *);

	void readObjectMaterial(CMesh *pObject, CChunk *pPreviousChunk);
	
	void cleanUp();
	
	FILE *m_pFilePointer;
	
	CChunk* m_pCurrentChunk;
	CChunk* m_pTempChunk;

        map<string,CMaterial> m_oMaterials;

};


#endif



