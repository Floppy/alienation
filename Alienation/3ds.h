#ifndef _3DS_H
#define _3DS_H

#include "config.h"
#include "vector.h"
#include "Mesh.h"

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>									
using namespace std;


//////////////////////////////////////
//The tMaterialInfo Struct
//////////////////////////////////////
class CMaterialInfo
{
public:
	char  m_strName[255];							
	char  m_strFile[255];							
	unsigned char  m_uiColor[3];								
	int   m_iTexureId;								
	float m_fUTile;								
	float m_fVTile;								
	float m_fUOffset;								
	float m_fIvOffset;									
};


//////////////////////////////////////
//The t3DModel Struct
//////////////////////////////////////
class C3DModel 
{
public:
	int m_iNumOfObjects;							
	int m_iNumOfMaterials;							
	vector<CMaterialInfo> m_pMaterials;
	vector<CMesh> m_pObject;
};





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

	bool import3DS(C3DModel *pModel, char *strFileName);

private:
	int getString(char *);

	void readChunk(CChunk *);

	void processNextChunk(C3DModel *pModel, CChunk *);

	void processNextObjectChunk(C3DModel *pModel, CMesh *pObject, CChunk *);

	void processNextMaterialChunk(C3DModel *pModel, CChunk *);

	void readColorChunk(CMaterialInfo *pMaterial, CChunk *pChunk);

	void readVertices(CMesh *pObject, CChunk *);

	void readVertexIndices(CMesh *pObject, CChunk *);

	void readUVCoordinates(CMesh *pObject, CChunk *);

	void readObjectMaterial(C3DModel *pModel, CMesh *pObject, CChunk *pPreviousChunk);
	
	void computeNormals(C3DModel *pModel);

	void cleanUp();
	
	FILE *m_pFilePointer;
	
	CChunk *m_pCurrentChunk;
	CChunk *m_pTempChunk;
};


#endif



