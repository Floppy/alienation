/************************************************************
*	APRON TUTORIAL PRESENTED BY MORROWLAND					*
*************************************************************
*	Author					: Ronny André Reierstad			*
*	Web Page				: www.morrowland.com			*
*	E-Mail					: apron@morrowland.com			*
************************************************************/

#include"3dsLoader.h"

#ifdef WIN32
  #include <windows.h>
#endif

#include <GL/gl.h>


/////////////////////////////////////////////////////////////////////////////////////////////////
//										 INIT 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::init3ds(char* pFilename)
{
	char strTemp[255];
	m_o3DModel.m_iNumOfMaterials = 0;
	m_o3DModel.m_iNumOfObjects = 0;

	//Actually load the model here
	m_oLoad3ds.import3DS(&m_o3DModel, pFilename);						

	//My addition, Creates new instance of the texture class
	m_poTexture = new CTexture(m_o3DModel.m_iNumOfMaterials);

	//Create the list of texture files to load
	char **astrFilenames = new char*[m_o3DModel.m_iNumOfMaterials];
	int n;
	for(n = 0; n < m_o3DModel.m_iNumOfMaterials; n++)				
	{
		astrFilenames[n] = new char(26);
		memset ((void *) astrFilenames[n], 32, 26);
	}

	int z;
	for(n = 0; n < m_o3DModel.m_iNumOfMaterials; n++)				
	{	
		z = strlen(m_o3DModel.m_pMaterials[n].m_strFile);
		if ( z < 26)
		{
			strcpy(astrFilenames[n], m_o3DModel.m_pMaterials[n].m_strFile);
		}
		m_o3DModel.m_pMaterials[n].m_iTexureId = n;						
	}

	//Loads the textures :***********problem inside this routine******************
	m_poTexture->load("Data/texture", astrFilenames, m_o3DModel.m_iNumOfMaterials);

	//This library didnt at first use display lists, so here I altered so it did :)
	m_uiList = glGenLists(1);
	glNewList(m_uiList, GL_COMPILE);

	//loop through all objects
	int i;
	for(i = 0; i < m_o3DModel.m_iNumOfObjects; i++)
	{
		
		if(m_o3DModel.m_pObject.size() <= 0) 
		{
			break;
		}
		
		C3DObject *pObject = &m_o3DModel.m_pObject[i];					


		//problem with this code here. If object has different materials with different 
		//texture, it wont accept them. I'm afraid its one texture per model
		if(pObject->m_bHasTexture)									
		{									
			
			glColor3ub(255, 255, 255);		

			if (glIsTexture(m_poTexture->m_puiTexture[pObject->m_iMaterialID]))
			{
				m_poTexture->setActive(pObject->m_iMaterialID);
			}
		} 
		else 
		{
			glDisable(GL_TEXTURE_2D);								
	
			glColor3ub(255, 255, 255);								
		}

		//draw faces
		glBegin(GL_TRIANGLES);										
		
		int j, iWhichVertex;
		for(j = 0; j < pObject->m_iNumOfFaces; j++)
		{
			
			for(iWhichVertex = 0; iWhichVertex < 3; iWhichVertex++)
			{
				int iIndex = pObject->m_pFaces[j].m_iVertIndex[iWhichVertex];
				
				glNormal3f(pObject->m_pNormals[ iIndex ].m_fx, pObject->m_pNormals[ iIndex ].m_fy, pObject->m_pNormals[ iIndex ].m_fz);
				
				if(pObject->m_bHasTexture) {
					
					if(pObject->m_pTexVerts) {
						glTexCoord2f(pObject->m_pTexVerts[ iIndex ].m_fx, 1 - pObject->m_pTexVerts[ iIndex ].m_fy);
					}
				} else {
					
					if(m_o3DModel.m_pMaterials.size() < pObject->m_iMaterialID) 
					{
						unsigned char *pColor = m_o3DModel.m_pMaterials[pObject->m_iMaterialID].m_uiColor;
						
						glColor3ub(pColor[0], pColor[1], pColor[2]);
					}
				}
				
				glVertex3f(pObject->m_pVerts[ iIndex ].m_fx, pObject->m_pVerts[ iIndex ].m_fy, pObject->m_pVerts[ iIndex ].m_fz);
			}
		}
		
		glEnd();
	}
	glEndList();


}


/////////////////////////////////////////////////////////////////////////////////////////////////
//										RENDER 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::render3ds()
{
	//simple :)
	glCallList(m_uiList);
}	


/////////////////////////////////////////////////////////////////////////////////////////////////
//										UNLOAD 3DS
/////////////////////////////////////////////////////////////////////////////////////////////////
void C3dsLoader::unload3ds()
{
	for(int i = 0; i < m_o3DModel.m_iNumOfObjects; i++)	
	{
		delete [] m_o3DModel.m_pObject[i].m_pFaces;
		delete [] m_o3DModel.m_pObject[i].m_pNormals;
		delete [] m_o3DModel.m_pObject[i].m_pVerts;
		delete [] m_o3DModel.m_pObject[i].m_pTexVerts;
	}
}












