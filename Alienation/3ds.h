#ifndef _3DS_H
#define _3DS_H

// Primary Chunk, at the beginning of each file
#define PRIMARY       0x4D4D

// Main Chunks
#define OBJECTINFO    0x3D3D				 
#define VERSION       0x0002				
#define EDITKEYFRAME  0xB000				

// Sub defines of OBJECTINFO
#define MATERIAL	  0xAFFF				
#define OBJECT		  0x4000				

// Sub defines of MATERIAL
#define MATNAME       0xA000				
#define MATDIFFUSE    0xA020				
#define MATMAP        0xA200				
#define MATMAPFILE    0xA300				

#define OBJECT_MESH   0x4100				

// Sub defines of OBJECT_MESH
#define OBJECT_VERTICES     0x4110			
#define OBJECT_FACES		0x4120			
#define OBJECT_MATERIAL		0x4130			
#define OBJECT_UV			0x4140			

#include "vector.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>									
using namespace std;

class CVector2 
{
public:
	float m_fx, m_fy;							// 2D vector coordinates
};

//////////////////////////////////////
//The tFace Struct
//////////////////////////////////////
class CFace
{
public:
	int m_iVertIndex[3];							
	int m_iCoordIndex[3];							
};

//////////////////////////////////////
//The tMaterialInfo Struct
//////////////////////////////////////
class CMaterialInfo
{
public:
	char  m_strName[255];							
	char  m_strFile[255];							
	BYTE  m_uiColor[3];								
	int   m_iTexureId;								
	float m_fUTile;								
	float m_fVTile;								
	float m_fUOffset;								
	float m_fIvOffset;									
};

//////////////////////////////////////
//The t3DObject Struct
//////////////////////////////////////
class C3DObject 
{
public:
	int  m_iNumOfVerts;			
	int  m_iNumOfFaces;			
	int  m_iNumTexVertex;			
	int  m_iMaterialID;			
	bool m_bHasTexture;			
	char m_strName[255];			
	UINT      *m_pIndices;		
	CVector3  *m_pVerts;			
	CVector3  *m_pNormals;		
	CVector2  *m_pTexVerts;		
	CFace *m_pFaces;				
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
	vector<C3DObject> m_pObject;					
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

	void processNextObjectChunk(C3DModel *pModel, C3DObject *pObject, CChunk *);

	void processNextMaterialChunk(C3DModel *pModel, CChunk *);

	void readColorChunk(CMaterialInfo *pMaterial, CChunk *pChunk);

	void readVertices(C3DObject *pObject, CChunk *);

	void readVertexIndices(C3DObject *pObject, CChunk *);

	void readUVCoordinates(C3DObject *pObject, CChunk *);

	void readObjectMaterial(C3DModel *pModel, C3DObject *pObject, CChunk *pPreviousChunk);
	
	void computeNormals(C3DModel *pModel);

	void cleanUp();
	
	FILE *m_pFilePointer;
	
	CChunk *m_pCurrentChunk;
	CChunk *m_pTempChunk;
};


#endif



