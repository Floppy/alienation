
#include "3ds.h"
//#include "3dmath.h"

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


//-------------------------------- CLOADS3DS ------------------------------------
//	This constructor initializes the tChunk data
//-------------------------------- CLOADS3DS ------------------------------------

CLoad3DS::CLoad3DS()
{
	m_pCurrentChunk = new CChunk;				 
	m_pTempChunk    = new CChunk;					
}

//---------------------------------- IMPORT 3DS ----------------------------------
//		This is called by the client to open the .3ds file, read it, then clean up
//---------------------------------- IMPORT 3DS -----------------------------------

bool CLoad3DS::import3DS(C3DModel *pModel, char *strFileName)
{
	m_pFilePointer = fopen(strFileName, "rb");
	
	if(!m_pFilePointer) 
	{
		fprintf(stderr, "Unable to find the file: %s!\n", strFileName);
		return false;
	}
	
	readChunk(m_pCurrentChunk);
	
	if (m_pCurrentChunk->m_uiID != PRIMARY)
	{
		fprintf(stderr, "Unable to load PRIMARY chuck from file: %s!\n", strFileName);
		return false;
	}
	
	processNextChunk(pModel, m_pCurrentChunk);
	
	computeNormals(pModel);
	
	cleanUp();
	
	return 0;
}

//---------------------------------- CLEAN UP ----------------------------------
//		This function cleans up our allocated memory and closes the file
//---------------------------------- CLEAN UP ----------------------------------

void CLoad3DS::cleanUp()
{
	fclose(m_pFilePointer);						 
	delete m_pCurrentChunk;						
	delete m_pTempChunk;							
}


//---------------------------------- PROCESS NEXT CHUNK-----------------------------------
//	This function reads the main sections of the .3DS file, then dives deeper with recursion
//---------------------------------- PROCESS NEXT CHUNK-----------------------------------

void CLoad3DS::processNextChunk(C3DModel *pModel, CChunk *pPreviousChunk)
{
	CMesh newObject;					 
	CMaterialInfo newTexture;				
	unsigned short iVersion = 0;					
	int aiBuffer[50000] = {0};					
	
	m_pCurrentChunk = new CChunk;				
	
	while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
	{
		readChunk(m_pCurrentChunk);
		
		switch (m_pCurrentChunk->m_uiID)
		{
		case VERSION:							
			
			m_pCurrentChunk->m_iBytesRead += fread(&iVersion, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			
			if (iVersion > 0x03) {
				fprintf(stderr,"This 3DS file is over version 3 so it may load incorrectly\n");
			}
			break;
			
		case OBJECTINFO:						
			readChunk(m_pTempChunk);
			
			m_pTempChunk->m_iBytesRead += fread(&iVersion, 1, m_pTempChunk->m_iLength - m_pTempChunk->m_iBytesRead, m_pFilePointer);
			
			m_pCurrentChunk->m_iBytesRead += m_pTempChunk->m_iBytesRead;
			
			processNextChunk(pModel, m_pCurrentChunk);
			break;
			
		case MATERIAL:						
			pModel->m_iNumOfMaterials++;
			
			pModel->m_pMaterials.push_back(newTexture);
			
			processNextMaterialChunk(pModel, m_pCurrentChunk);
			break;
			
		case OBJECT:							
			pModel->m_iNumOfObjects++;
			
			pModel->m_pObject.push_back(newObject);
			
			memset(&(pModel->m_pObject[pModel->m_iNumOfObjects - 1]), 0, sizeof(CMesh));
			
			m_pCurrentChunk->m_iBytesRead += getString(pModel->m_pObject[pModel->m_iNumOfObjects - 1].m_strName);
			
			processNextObjectChunk(pModel, &(pModel->m_pObject[pModel->m_iNumOfObjects - 1]), m_pCurrentChunk);
			break;
			
		case EDITKEYFRAME:
			
			m_pCurrentChunk->m_iBytesRead += fread(aiBuffer, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			break;
			
		default: 
			
			m_pCurrentChunk->m_iBytesRead += fread(aiBuffer, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			break;
		}
		
		pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
	}
	
	delete m_pCurrentChunk;
	m_pCurrentChunk = pPreviousChunk;
}


//---------------------------------- PROCESS NEXT OBJECT CHUNK -----------------------------------
//		This function handles all the information about the objects in the file
//---------------------------------- PROCESS NEXT OBJECT CHUNK -----------------------------------

void CLoad3DS::processNextObjectChunk(C3DModel *pModel, CMesh *pObject, CChunk *pPreviousChunk)
{
	int buffer[50000] = {0};					
	
	m_pCurrentChunk = new CChunk;
	
	while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
	{
		readChunk(m_pCurrentChunk);
		
		switch (m_pCurrentChunk->m_uiID)
		{
		case OBJECT_MESH:		
			processNextObjectChunk(pModel, pObject, m_pCurrentChunk);
			break;
			
		case OBJECT_VERTICES:			 
			readVertices(pObject, m_pCurrentChunk);
			break;
			
		case OBJECT_FACES:				 
			readVertexIndices(pObject, m_pCurrentChunk);
			break;
			
		case OBJECT_MATERIAL:			 
			readObjectMaterial(pModel, pObject, m_pCurrentChunk);			
			break;
			
		case OBJECT_UV:					
			readUVCoordinates(pObject, m_pCurrentChunk);
			break;
			
		default: 
			m_pCurrentChunk->m_iBytesRead += fread(buffer, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			break;
		}
		
		pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
	}
	
	delete m_pCurrentChunk;
	m_pCurrentChunk = pPreviousChunk;
}


//---------------------------------- PROCESS NEXT MATERIAL CHUNK -----------------------------------
//	This function handles all the information about the material (Texture)
//---------------------------------- PROCESS NEXT MATERIAL CHUNK -----------------------------------

void CLoad3DS::processNextMaterialChunk(C3DModel *pModel, CChunk *pPreviousChunk)
{
	int aiBuffer[50000] = {0};					  
	m_pCurrentChunk = new CChunk;
	
	while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
	{
		readChunk(m_pCurrentChunk);
		
		switch (m_pCurrentChunk->m_uiID)
		{
		case MATNAME:						 
			m_pCurrentChunk->m_iBytesRead += fread(pModel->m_pMaterials[pModel->m_iNumOfMaterials - 1].m_strName, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			break;
			
		case MATDIFFUSE:					 
			readColorChunk(&(pModel->m_pMaterials[pModel->m_iNumOfMaterials - 1]), m_pCurrentChunk);
			break;
			
		case MATMAP:						 
			processNextMaterialChunk(pModel, m_pCurrentChunk);
			break;
			
		case MATMAPFILE:						 
			m_pCurrentChunk->m_iBytesRead += fread(pModel->m_pMaterials[pModel->m_iNumOfMaterials - 1].m_strFile, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			break;
			
		default:  
			m_pCurrentChunk->m_iBytesRead += fread(aiBuffer, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
			break;
		}
		pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
	}
	
	delete m_pCurrentChunk;
	m_pCurrentChunk = pPreviousChunk;
}

//---------------------------------- READ CHUNK ----------------------------------
//		This function reads in a chunk ID and it's length in bytes
//---------------------------------- READ CHUNK -----------------------------------

void CLoad3DS::readChunk(CChunk *pChunk)
{
	pChunk->m_iBytesRead = fread(&pChunk->m_uiID, 1, 2, m_pFilePointer);
	
	pChunk->m_iBytesRead += fread(&pChunk->m_iLength, 1, 4, m_pFilePointer);
}

//---------------------------------- GET STRING -----------------------------------
//		This function reads in a string of characters
//---------------------------------- GET STRING -----------------------------------

int CLoad3DS::getString(char *pBuffer)
{
	int index = 0;
	
	fread(pBuffer, 1, 1, m_pFilePointer);
	
	while (*(pBuffer + index++) != 0) 
	{
		fread(pBuffer + index, 1, 1, m_pFilePointer);
	}
	
	return strlen(pBuffer) + 1;
}


//---------------------------------- READ COLOR ----------------------------------
//		This function reads in the RGB color data
//---------------------------------- READ COLOR -----------------------------------

void CLoad3DS::readColorChunk(CMaterialInfo *pMaterial, CChunk *pChunk)
{
	readChunk(m_pTempChunk);
	m_pTempChunk->m_iBytesRead += fread(pMaterial->m_uiColor, 1, m_pTempChunk->m_iLength - m_pTempChunk->m_iBytesRead, m_pFilePointer);
	pChunk->m_iBytesRead += m_pTempChunk->m_iBytesRead;
}


//---------------------------------- READ VERTEX INDECES ----------------------------------
//		This function reads in the indices for the vertex array
//---------------------------------- READ VERTEX INDECES -----------------------------------

void CLoad3DS::readVertexIndices(CMesh *pObject, CChunk *pPreviousChunk)
{
	unsigned short iIndex = 0;					 
	pPreviousChunk->m_iBytesRead += fread(&pObject->m_iNumFaces, 1, 2, m_pFilePointer);
	
	pObject->m_pFaces = new CFace [pObject->m_iNumFaces];
	memset(pObject->m_pFaces, 0, sizeof(CFace) * pObject->m_iNumFaces);
	
	int i, j;
	for(i = 0; i < pObject->m_iNumFaces; i++)
	{
		for(j = 0; j < 4; j++)
		{
			pPreviousChunk->m_iBytesRead += fread(&iIndex, 1, sizeof(iIndex), m_pFilePointer);
			
			if(j < 3)
			{
				pObject->m_pFaces[i].m_iVertIndex[j] = iIndex;
			}
		}
	}
}


//---------------------------------- READ UV COORDINATES -----------------------------------
//		This function reads in the UV coordinates for the object
//---------------------------------- READ UV COORDINATES -----------------------------------

void CLoad3DS::readUVCoordinates(CMesh *pObject, CChunk *pPreviousChunk)
{
	pPreviousChunk->m_iBytesRead += fread(&pObject->m_iNumTexVertex, 1, 2, m_pFilePointer);
	
	pObject->m_pTexVerts = new CVector2 [pObject->m_iNumTexVertex];
	
	pPreviousChunk->m_iBytesRead += fread(pObject->m_pTexVerts, 1, pPreviousChunk->m_iLength - pPreviousChunk->m_iBytesRead, m_pFilePointer);
}


//---------------------------------- READ VERTICES -----------------------------------
//	This function reads in the vertices for the object
//---------------------------------- READ VERTICES -----------------------------------

void CLoad3DS::readVertices(CMesh *pObject, CChunk *pPreviousChunk)
{ 
	pPreviousChunk->m_iBytesRead += fread(&(pObject->m_iNumVertices), 1, 2, m_pFilePointer);
	
	pObject->m_pVerts = new CVector3 [pObject->m_iNumVertices];
	memset(pObject->m_pVerts, 0, sizeof(CVector3) * pObject->m_iNumVertices);
	
	pPreviousChunk->m_iBytesRead += fread(pObject->m_pVerts, 1, pPreviousChunk->m_iLength - pPreviousChunk->m_iBytesRead, m_pFilePointer);
}


//---------------------------------- READ OBJECT MATERIAL -----------------------------------
//	This function reads in the material name assigned to the object and sets the materialID
//---------------------------------- READ OBJECT MATERIAL -----------------------------------

void CLoad3DS::readObjectMaterial(C3DModel *pModel, CMesh *pObject, CChunk *pPreviousChunk)
{
	char strMaterial[255] = {0};			
	int aiBuffer[50000] = {0};				
	char strTemp[255];

	pPreviousChunk->m_iBytesRead += getString(strMaterial);
	
	for(int i = 0; i < pModel->m_iNumOfMaterials; i++)
	{
		if(strcmp(strMaterial, pModel->m_pMaterials[i].m_strName) == 0)
		{
			pObject->m_iMaterialID = i;
			
			strcpy(strTemp, pModel->m_pMaterials[i].m_strFile);
			if(strlen(pModel->m_pMaterials[i].m_strFile) > 0) {
				
				pObject->m_bHasTexture = true;
			}	
			break;
		}
	}
	
	pPreviousChunk->m_iBytesRead += fread(aiBuffer, 1, pPreviousChunk->m_iLength - pPreviousChunk->m_iBytesRead, m_pFilePointer);
}			



//---------------------------------- COMPUTER NORMALS -----------------------------------
//		This function computes the normals and vertex normals of the objects
//---------------------------------- COMPUTER NORMALS -----------------------------------

void CLoad3DS::computeNormals(C3DModel *pModel)
{
	CVector3 vecVector1, vecVector2, vecNormal, vecPoly[3];
	
	if(pModel->m_iNumOfObjects <= 0)
		return;
	
	int index, i, j;
	for(index = 0; index < pModel->m_iNumOfObjects; index++)
	{
		CMesh *pObject = &(pModel->m_pObject[index]);
		
		CVector3 *pTempNormals	= new CVector3 [pObject->m_iNumFaces];
		pObject->m_pNormals		= new CVector3 [pObject->m_iNumVertices];
		
		for(i=0; i < pObject->m_iNumFaces; i++)
		{												
			vecPoly[0] = pObject->m_pVerts[pObject->m_pFaces[i].m_iVertIndex[0]];
			vecPoly[1] = pObject->m_pVerts[pObject->m_pFaces[i].m_iVertIndex[1]];
			vecPoly[2] = pObject->m_pVerts[pObject->m_pFaces[i].m_iVertIndex[2]];
			
			
			vecVector1 = vecPoly[0] - vecPoly[2];
			vecVector2 = vecPoly[2] - vecPoly[1];
			
			vecNormal  = vecVector1.cross(vecVector2);
			pTempNormals[i] = vecNormal;					
			vecNormal.unitize();				
			
		}
		
		
		CVector3 vecSum(0.0, 0.0, 0.0);
		CVector3 vecZero = vecSum;
		int shared=0;
		
		for (i = 0; i < pObject->m_iNumVertices; i++)			
		{
			for (j = 0; j < pObject->m_iNumFaces; j++)	
			{												
				if (pObject->m_pFaces[j].m_iVertIndex[0] == i || 
					pObject->m_pFaces[j].m_iVertIndex[1] == i || 
					pObject->m_pFaces[j].m_iVertIndex[2] == i)
				{
					vecSum = vecSum + pTempNormals[j];			
					shared++;								
				}
			}      
	
			pObject->m_pNormals[i] = vecSum / float(-shared);
	
			pObject->m_pNormals[i].unitize();	
			
			vecSum = vecZero;									 
			shared = 0;										
		}
		
		delete [] pTempNormals;
	}
}


