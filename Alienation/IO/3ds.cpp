
#include "IO/3ds.h"
#include "3D/TextureManager.h"

// Primary Chunk, at the beginning of each file
#define _3DS_PRIMARY       0x4D4D

// Main Chunks
#define _3DS_OBJECTINFO    0x3D3D				 
#define _3DS_VERSION       0x0002				
#define _3DS_EDITKEYFRAME  0xB000				

// Sub defines of OBJECTINFO
#define _3DS_MATERIAL	   0xAFFF				
#define _3DS_OBJECT	   0x4000				

// Sub defines of MATERIAL
#define _3DS_MATNAME       0xA000				
#define _3DS_MATDIFFUSE    0xA020				
#define _3DS_MATMAP        0xA200				
#define _3DS_MATMAPFILE    0xA300				

#define _3DS_OBJECT_MESH   0x4100				

// Sub defines of OBJECT_MESH
#define _3DS_OBJECT_VERTICES     0x4110			
#define _3DS_OBJECT_FACES	 0x4120			
#define _3DS_OBJECT_MATERIAL	 0x4130			
#define _3DS_OBJECT_UV		 0x4140			


//-------------------------------- CLOADS3DS ------------------------------------
//	This constructor initializes the tChunk data
//-------------------------------- CLOADS3DS ------------------------------------

CLoad3DS::CLoad3DS() :
   m_pCurrentChunk(NULL),
   m_pTempChunk(NULL)
{
}

//---------------------------------- IMPORT 3DS ----------------------------------
//		This is called by the client to open the .3ds file, read it, then clean up
//---------------------------------- IMPORT 3DS -----------------------------------

bool CLoad3DS::import3DS(CModel *pModel, const char *strFileName)
{
	m_pCurrentChunk = new CChunk;				 
	m_pTempChunk    = new CChunk;

	m_pFilePointer = fopen(strFileName, "rb");
	
	if(!m_pFilePointer) 
	{
		fprintf(stderr, "Unable to find the file: %s!\n", strFileName);
                cleanUp();
		return false;
	}
	
	readChunk(m_pCurrentChunk);
	
	if (m_pCurrentChunk->m_uiID != _3DS_PRIMARY)
	{
		fprintf(stderr, "Unable to load PRIMARY chuck from file: %s!\n", strFileName);
                cleanUp();
		return false;
	}
	
	processNextChunk(pModel, m_pCurrentChunk);
	
	cleanUp();
	
	return true;
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

void CLoad3DS::processNextChunk(CModel *pModel, CChunk *pPreviousChunk)
{
   unsigned short iVersion = 0;
   int aiBuffer[50000] = {0};
   
   m_pCurrentChunk = new CChunk;
   
   while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
   {
      readChunk(m_pCurrentChunk);
      
      switch (m_pCurrentChunk->m_uiID)
      {
         case _3DS_VERSION: {
            // Read version
            m_pCurrentChunk->m_iBytesRead += fread(&iVersion, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
            // Check version
            if (iVersion > 0x03) {
               fprintf(stderr,"This 3DS file is over version 3 so it may load incorrectly\n");
            }
         } break;
         
         case _3DS_OBJECTINFO: {
            // Read chunk
            readChunk(m_pTempChunk);                   
            m_pTempChunk->m_iBytesRead += fread(&iVersion, 1, m_pTempChunk->m_iLength - m_pTempChunk->m_iBytesRead, m_pFilePointer);
            m_pCurrentChunk->m_iBytesRead += m_pTempChunk->m_iBytesRead;
            processNextChunk(pModel, m_pCurrentChunk);
         } break;
         
         case _3DS_MATERIAL: {
            processNextMaterialChunk(pModel, m_pCurrentChunk);
         } break;
         
         case _3DS_OBJECT: {
            processNextObjectChunk(pModel, m_pCurrentChunk);
         } break;
         
         case _3DS_EDITKEYFRAME:
         default: {
            m_pCurrentChunk->m_iBytesRead += fread(aiBuffer, 1, m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, m_pFilePointer);
         } break;
      }
      
      pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
   }
   
   delete m_pCurrentChunk;
   m_pCurrentChunk = pPreviousChunk;
}


//---------------------------------- PROCESS NEXT OBJECT CHUNK -----------------------------------
//		This function handles all the information about the objects in the file
//---------------------------------- PROCESS NEXT OBJECT CHUNK -----------------------------------

void CLoad3DS::processNextObjectChunk(CModel *pModel, CChunk *pPreviousChunk)
{
   CMesh* pMesh = new CMesh;
   
   // Read name
   char buffer[50000];
   memset(buffer,0,50000);
   m_pCurrentChunk->m_iBytesRead += getString(buffer);
	
   m_pCurrentChunk = new CChunk;
	
   while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
   {
      readChunk(m_pCurrentChunk);
      
      switch (m_pCurrentChunk->m_uiID)
      {

      case _3DS_OBJECT_MESH: {
         processNextObjectChunk2(pMesh, m_pCurrentChunk);
      } break;

      default: {
         m_pCurrentChunk->m_iBytesRead += fread(buffer, 
                                                1, 
                                                m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, 
                                                m_pFilePointer);
      } break;
      }

      pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
   }
   
   // Store
   pModel->addMesh(pMesh);

   // Tidy
   delete m_pCurrentChunk;
   m_pCurrentChunk = pPreviousChunk;
}

void CLoad3DS::processNextObjectChunk2(CMesh *pMesh, CChunk *pPreviousChunk)
{
   	
   char buffer[50000];
   memset(buffer,0,50000);
   m_pCurrentChunk = new CChunk;
	
   while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
   {
      readChunk(m_pCurrentChunk);
      
      switch (m_pCurrentChunk->m_uiID)
      {

      case _3DS_OBJECT_VERTICES: {
         readVertices(pMesh, m_pCurrentChunk);
      } break;

      case _3DS_OBJECT_FACES: {
         readVertexIndices(pMesh, m_pCurrentChunk);
      } break;

      case _3DS_OBJECT_MATERIAL: {
         readObjectMaterial(pMesh, m_pCurrentChunk);			
      } break;

      case _3DS_OBJECT_UV: {
         readUVCoordinates(pMesh, m_pCurrentChunk);
      } break;

      default: {
         m_pCurrentChunk->m_iBytesRead += fread(buffer, 
                                                1, 
                                                m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, 
                                                m_pFilePointer);
      } break;
      }
		
      pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
   }
   
   // Tidy
   delete m_pCurrentChunk;
   m_pCurrentChunk = pPreviousChunk;
}


//---------------------------------- PROCESS NEXT MATERIAL CHUNK -----------------------------------
//	This function handles all the information about the material (Texture)
//---------------------------------- PROCESS NEXT MATERIAL CHUNK -----------------------------------

void CLoad3DS::processNextMaterialChunk(CModel *pModel, CChunk *pPreviousChunk)
{
   CMaterial newMaterial;   
   char strMaterialName[128];

   // Read new chunk
   m_pCurrentChunk = new CChunk;
   // Read contents of previous chunk
   while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
   {
      readChunk(m_pCurrentChunk);
   
      switch (m_pCurrentChunk->m_uiID)
      {
      case _3DS_MATDIFFUSE: {
         // Read colour into material
         readColorChunk(&newMaterial, m_pCurrentChunk);
      }	break;
			
      case _3DS_MATNAME: {         
         // Read material name
         m_pCurrentChunk->m_iBytesRead += fread(strMaterialName,
                                                1, 
                                                m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, 
                                                m_pFilePointer);
      } break;
			
      case _3DS_MATMAP: {
         processNextMaterialChunk2(newMaterial, m_pCurrentChunk);
      }	break;
			
      default: {
         // Eat chunk
         char aiBuffer[50000] = {0};
         m_pCurrentChunk->m_iBytesRead += fread(aiBuffer, 
                                                1, 
                                                m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, 
                                                m_pFilePointer);
      } break;
      
      }
      pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
   }

   // Add material to map
   m_oMaterials[strMaterialName] = newMaterial;

   // Tidy up and finish
   delete m_pCurrentChunk;
   m_pCurrentChunk = pPreviousChunk;
}

void CLoad3DS::processNextMaterialChunk2(CMaterial& oMaterial, CChunk *pPreviousChunk)
{
   char strMaterialName[128];

   // Read new chunk
   m_pCurrentChunk = new CChunk;
   // Read contents of previous chunk
   while (pPreviousChunk->m_iBytesRead < pPreviousChunk->m_iLength)
   {
      readChunk(m_pCurrentChunk);
   
      switch (m_pCurrentChunk->m_uiID)
      {
      case _3DS_MATMAPFILE: {
         // Get filename
         char strFilename[64];
         m_pCurrentChunk->m_iBytesRead += fread(strFilename, 
                                                1, 
                                                m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, 
                                                m_pFilePointer);         
         // Load texture and store ID
         oMaterial.m_uiTexture = g_oTextureManager.load(strFilename);
      }	break;
			
      default: {
         // Eat chunk
         char aiBuffer[50000] = {0};
         m_pCurrentChunk->m_iBytesRead += fread(aiBuffer, 
                                                1, 
                                                m_pCurrentChunk->m_iLength - m_pCurrentChunk->m_iBytesRead, 
                                                m_pFilePointer);
      } break;
      
      }
      pPreviousChunk->m_iBytesRead += m_pCurrentChunk->m_iBytesRead;
   }

   // Tidy up and finish
   delete m_pCurrentChunk;
   m_pCurrentChunk = pPreviousChunk;
}

//---------------------------------- READ CHUNK ----------------------------------
//		This function reads in a chunk ID and it's length in bytes
//---------------------------------- READ CHUNK -----------------------------------

void CLoad3DS::readChunk(CChunk *pChunk)
{
   //fprintf(stderr, "readChunk called\n");
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

void CLoad3DS::readColorChunk(CMaterial *pMaterial, CChunk *pChunk)
{
   // Allocate colour storage
   unsigned char col[4] = {0,0,0,0};
   // Read data
   readChunk(m_pTempChunk);   
   m_pTempChunk->m_iBytesRead += fread(col, 1, m_pTempChunk->m_iLength - m_pTempChunk->m_iBytesRead, m_pFilePointer);
   pChunk->m_iBytesRead += m_pTempChunk->m_iBytesRead;
   // store
   pMaterial->m_oDiffuse = CRGBAColour(col[0]/255.0,col[1]/255.0,col[2]/255.0,col[3]/255.0);
   pMaterial->m_oAmbient = pMaterial->m_oDiffuse;
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
        
        //Invert V
        for (int i=0; i<pObject->m_iNumTexVertex; i++) {
           pObject->m_pTexVerts[i].Y() = -pObject->m_pTexVerts[i].Y();
        }

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

void CLoad3DS::readObjectMaterial(CMesh *pObject, CChunk *pPreviousChunk)
{
	char strMaterial[255];	
        memset(strMaterial,0,255);
	int aiBuffer[50000] = {0};

	pPreviousChunk->m_iBytesRead += getString(strMaterial);
	
        pObject->setMaterial(m_oMaterials[strMaterial]);
	
	pPreviousChunk->m_iBytesRead += fread(aiBuffer, 1, pPreviousChunk->m_iLength - pPreviousChunk->m_iBytesRead, m_pFilePointer);
}			



