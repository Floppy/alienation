// Radar.cpp: implementation of the CRadar class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/Radar.h"
#include "IO/3ds.h"



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRadar::CRadar()
{

}

CRadar::~CRadar()
{

}

void CRadar::addTarget(int iObjectID, int iTargetType, CVector3 vecPos)
{
	sTarget target;
	target.iObjectID = iObjectID;
	target.iTargetType = iTargetType;
	target.vecPos = vecPos;

	m_arrTarget.push_back(target);
}


//**************************************************************************************
// Function name    : CRadar::init
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 31/10/2003
// Description      : Initialises the radar  
//**************************************************************************************
void CRadar::init()
{
	NSDIO::CLoad3DS loader;

	m_poModel = new CGameObject(1, 0.0f);

	if (loader.import3DS(&m_poModel->m_oModel, "radar.3ds"))
	{
		m_poModel->m_oModel.init();
	}

	m_poModel->m_ppMasses[0]->m_vecPos = CVector3(0.0f, -1.0f, -15.0);

												//////////////////////////////////////////////
												//Create the off screen texture to copy to  //
												//                                          //
												//////////////////////////////////////////////

	m_uiOffScreenTexture = g_oTextureManager.create(128, 128);

												//////////////////////////////////////////////
												//Create the light to view the radar with   //
												//////////////////////////////////////////////

   CRGBAColour oLightAmbient(0.4f, 0.4f, 0.4f, 1.0f);
   CRGBAColour oLightDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
   CRGBAColour oLightSpecular(1.00f, 1.0f, 1.0f, 1.0f);
	CVector3 oPosition(-1500000.43553f, -1500000.0f, -1500000.0f);

	float ambient[] = {0.4f, 0.4f, 0.4f, 1.0f};
	m_oLight = new CLight(GL_LIGHT2);
        m_oLight->init(oLightAmbient, oLightDiffuse, oLightSpecular, oPosition);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

        // Create material
        setActiveMaterial(CRGBAColour(1.0f,1.0f,1.0f,1.0f),
                          CRGBAColour(1.0f,1.0f,1.0f,1.0f),
                          CRGBAColour(1.0f,1.0f,1.0f,1.0f),
                          m_uiOffScreenTexture);

}


//**************************************************************************************
// Function name    : CRadar::renderOffScreen
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 31/10/2003
// Description      : Performs the rendering that is copied to a texture  
//**************************************************************************************
void CRadar::renderOffScreen(CVector3 vecShipPos, const CMatrix matRotMatrix)
{ 

	unsigned int i;
	CVector3 vecDistance;
	CVector3 vecDisplayDistance;
	float fDistance;
	CMatrix mat = matRotMatrix;
	CMaterial oMaterial;
	
												//////////////////////////////////////////////
												//Matrix to account for ship rotation       //
												//////////////////////////////////////////////

	mat.invert();

												//////////////////////////////////////////////
												//Distance of radar to camera               //
												//////////////////////////////////////////////

	float fRange = m_poModel->m_ppMasses[0]->m_vecPos.length();
   


												//////////////////////////////////////////////
												//Prepare the texture                       //
												//////////////////////////////////////////////

   CTexture* pTexture = g_oTextureManager.texture(m_uiOffScreenTexture);
   pTexture->preRenderToTexture();

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
												//////////////////////////////////////////////
												//Setup the rendering area (Camera at       //
												//origin, ortho screen where the radar is   //
												//////////////////////////////////////////////

   float fSize = m_poModel->m_oModel.boundingSphere().m_fRadius;
   
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(-fSize,fSize,-fSize,fSize,fRange-fSize,fRange+fSize);
   
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
												//////////////////////////////////////////////
												//look "down" on radar                      //
												//////////////////////////////////////////////

	gluLookAt(0.0f, 0.0f, 0.0f,
				m_poModel->m_ppMasses[0]->m_vecPos.X(),
				m_poModel->m_ppMasses[0]->m_vecPos.Y(),
				m_poModel->m_ppMasses[0]->m_vecPos.Z(),
				0.0f, 1.0f, 0.0f);


	glLineWidth(1.4f);

												//////////////////////////////////////////////
												//draw the model                            //
												//////////////////////////////////////////////

	glPushAttrib(GL_POLYGON_BIT | GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable( GL_BLEND );
	glDisable( GL_DEPTH_TEST );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE );
        glDisable( GL_TEXTURE_2D );
        glShadeModel( GL_SMOOTH );
	m_oLight->enable();
	m_oLight->render();
												//////////////////////////////////////////////
												//draw the radar "blips"                    //
												//////////////////////////////////////////////

	for (i = 0 ; i < m_arrTarget.size() ; i++)
	{
												//////////////////////////////////////////////
												//target distance from ship                 //
												//////////////////////////////////////////////

		vecDistance = m_arrTarget[i].vecPos - vecShipPos;
		fDistance = vecDistance.length();
		if (fDistance <= (float)m_uiRange)
		{
												//////////////////////////////////////////////
												//Scale to radar width and range            //
												//////////////////////////////////////////////

			vecDisplayDistance = vecDistance * (fSize / (float)m_uiRange);
			
												//////////////////////////////////////////////
												//account for ship rotation                 //
												//////////////////////////////////////////////

			vecDisplayDistance = (mat * vecDisplayDistance) * -1.0f;

												//////////////////////////////////////////////
												//translate the vectors                     //
												//////////////////////////////////////////////

			vecDisplayDistance += m_poModel->m_ppMasses[0]->m_vecPos;

												//////////////////////////////////////////////
												//Colour depending if ship or asteroid      //
												//////////////////////////////////////////////

			if (m_arrTarget[i].iTargetType == TGT_ASTEROID)
			{
				oMaterial.m_oAmbient = CRGBAColour(0.5f,0.5f,0.5f,0.99f);
				oMaterial.m_oDiffuse = CRGBAColour(0.5f,0.5f,0.5f,0.99f);
				oMaterial.m_oEmissive = CRGBAColour(0.5f,0.5f,0.5f,0.99f);
				oMaterial.render();
				glColor4f(0.5f,0.5f,0.5f,0.99f);
			}
			else
			{
				oMaterial.m_oAmbient = CRGBAColour(1.0f,0.2f,0.1f,0.99f);
				oMaterial.m_oDiffuse = CRGBAColour(1.0f,0.2f,0.1f,0.99f);
				oMaterial.m_oEmissive = CRGBAColour(1.0f,0.2f,0.1f,0.99f);
				oMaterial.render();	
				glColor4f(1.0f,0.2f,0.1f,0.99f);
			}

												//////////////////////////////////////////////
												//draw the blips                            //
												//////////////////////////////////////////////

			glBegin(GL_LINES);
				glVertex3f(vecDisplayDistance.X() + 0.2f,
							  vecDisplayDistance.Y(),
							  vecDisplayDistance.Z());
				glVertex3f(vecDisplayDistance.X(),
							  vecDisplayDistance.Y(),
							  vecDisplayDistance.Z());
				glVertex3f(vecDisplayDistance.X(),
							  vecDisplayDistance.Y(),
							  vecDisplayDistance.Z());
				glVertex3f(vecDisplayDistance.X(),
							  m_poModel->m_ppMasses[0]->m_vecPos.Y(),
							  vecDisplayDistance.Z());
			glEnd();
		}
	}
   m_poModel->draw( false );


	m_oLight->disable();
   glEnable( GL_TEXTURE_2D );
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
	glPopAttrib();
												//////////////////////////////////////////////
												//Copy to the texture                       //
												//////////////////////////////////////////////
   pTexture->postRenderToTexture(GL_RGB);

}

void CRadar::setTarget(int iTargetID)
{
	m_iTargetID = iTargetID;
}

void CRadar::setRange(unsigned int uiRange)
{
	m_uiRange = uiRange;
}

void CRadar::clearTargetList()
{
	m_arrTarget.clear();
}

unsigned int CRadar::getRange()
{
	return m_uiRange;
}
