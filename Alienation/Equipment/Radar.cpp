// Radar.cpp: implementation of the CRadar class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/Radar.h"



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
	unsigned int uiTexture;

												//////////////////////////////////////////////
												//Create the quadric                        //
												//////////////////////////////////////////////
	
	m_poQuadric = gluNewQuadric();
												//////////////////////////////////////////////
												//Create smooth normals for the quadric     //
												//////////////////////////////////////////////

	gluQuadricNormals(m_poQuadric, GLU_SMOOTH);
	gluQuadricTexture(m_poQuadric, GL_TRUE);

												//////////////////////////////////////////////
												//Create the various materials for          //
												//texturing the radar images                //
												//////////////////////////////////////////////

	uiTexture = g_oTextureManager.load("OuterSphere.png");
	m_oOuterSphereTexture.m_oEmissive = CRGBAColour(1.0f, 1.0f, 1.0f, 0.5f);
	m_oOuterSphereTexture.m_oAmbient = CRGBAColour(1.0f, 1.0f, 1.0f, 0.5f);
	m_oOuterSphereTexture.m_oDiffuse = CRGBAColour(1.0f, 1.0f, 1.0f, 0.5f);
	m_oOuterSphereTexture.m_uiTexture = uiTexture;
	m_oOuterSphereTexture.init();

	uiTexture = g_oTextureManager.load("MidSphere.png");
	m_oMidSphereTexture.m_oEmissive = CRGBAColour(1.0f, 1.0f, 1.0f, 0.4f);
	m_oMidSphereTexture.m_oAmbient = CRGBAColour(1.0f, 1.0f, 1.0f, 0.4f);
	m_oMidSphereTexture.m_oDiffuse = CRGBAColour(1.0f, 1.0f, 1.0f, 0.4f);
	m_oMidSphereTexture.m_uiTexture = uiTexture;
	m_oMidSphereTexture.init();

	uiTexture = g_oTextureManager.load("InnerSphere.png");
	m_oInnerSphereTexture.m_oEmissive = CRGBAColour(1.0f, 1.0f, 1.0f, 0.3f);
	m_oInnerSphereTexture.m_oAmbient = CRGBAColour(1.0f, 1.0f, 1.0f, 0.3f);
	m_oInnerSphereTexture.m_oDiffuse = CRGBAColour(1.0f, 1.0f, 1.0f, 0.3f);
	m_oInnerSphereTexture.m_uiTexture = uiTexture;
	m_oInnerSphereTexture.init();

												//////////////////////////////////////////////
												//Create the off screen texture to copy to  //
												//                                          //
												//////////////////////////////////////////////

	m_uiOffScreenTexture = g_oTextureManager.create(128, 128);

												//////////////////////////////////////////////
												//Create the light to view the radar with   //
												//////////////////////////////////////////////

   CRGBAColour oLightAmbient(0.25f, 0.25f, 0.25f, 1.0f);
   CRGBAColour oLightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
	CVector3 oPosition(100.0f, 100.0f, -100.0f);

	m_oLight = new CLight(GL_LIGHT2);
   m_oLight->init(oLightAmbient, oLightDiffuse, oPosition);
}


//**************************************************************************************
// Function name    : CRadar::renderOffScreen
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 31/10/2003
// Description      : Performs the rendering that is copied to a texture  
//**************************************************************************************
void CRadar::renderOffScreen(CVector3 vecShipPos)
{ 


	// Perform offscreen rendering
	int i;
	CMaterial oMaterial;
	CVector3 vecDistance;
	CVector3 vecDisplayDistance;
	float fDistance;
	CTexture *poTexture = g_oTextureManager.texture(m_uiOffScreenTexture);
	unsigned int uiID = poTexture->init();
	
												//////////////////////////////////////////////
												//Create a material to draw the radar       //
												//////////////////////////////////////////////


												//////////////////////////////////////////////
												//Change the view port to the textures      //
												//size                                      //
												//////////////////////////////////////////////

	poTexture->preRenderToTexture();
												//////////////////////////////////////////////
												//Clear screen                              //
												//////////////////////////////////////////////

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
												//////////////////////////////////////////////
												//Set Projection Matrix                     //
												//////////////////////////////////////////////

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
												//////////////////////////////////////////////
												//Setup the projection view                 //
												//////////////////////////////////////////////

	glOrtho(-5.0f, 5.0f, -5.0f, 5.0f, 1.0f, -200.0f);

												//////////////////////////////////////////////
												//Set Modelview Matrix                      //
												//////////////////////////////////////////////

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

												//////////////////////////////////////////////
												//Smooth is probably the default option,    //
												//but specifying it to be sure              //
												//////////////////////////////////////////////

	glShadeModel(GL_SMOOTH);
												//////////////////////////////////////////////
												//Turn the light on                         //
												//////////////////////////////////////////////

	m_oLight->enable();
	m_oLight->render();
												//////////////////////////////////////////////
												//I want to view the radar from slightly    //
												//above                                     //
												//////////////////////////////////////////////

	gluLookAt(0.0f, 3.0f, 0.0f,
				 0.0f, 0.0f, -5.0f,
				 0.0f, 0.0f, 1.0f);

	glLineWidth(2.0);
	glTranslatef(0.0f, 0.0f, -5.0f);
												//////////////////////////////////////////////
												//Blending stuff                            //
												//////////////////////////////////////////////

   glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);

												//////////////////////////////////////////////
												//Apply the material and move the object    //
												//////////////////////////////////////////////


	m_oInnerSphereTexture.render();
												//////////////////////////////////////////////
												//Draw the first sphere (Smallest one       //
												//first for the depth testing)              //
												//////////////////////////////////////////////

	gluSphere(m_poQuadric, 5.0f, 64, 64);
												
												//////////////////////////////////////////////
												//Alter the material for the next sphere    //
												//////////////////////////////////////////////

	m_oMidSphereTexture.render();
	gluSphere(m_poQuadric, 6.0f, 64, 64);

												//////////////////////////////////////////////
												//And the last sphere                       //
												//////////////////////////////////////////////

	m_oOuterSphereTexture.render();
	gluSphere(m_poQuadric, 7.0f, 64, 64);
												//////////////////////////////////////////////
												//Light off!                                //
												//////////////////////////////////////////////

	m_oLight->disable();
												//////////////////////////////////////////////
												//Blending off                              //
												//////////////////////////////////////////////

   glDisable(GL_BLEND);

												//////////////////////////////////////////////
												//draw the radar "blips"                    //
												//////////////////////////////////////////////

	for (i = 0 ; i < m_arrTarget.size() ; i++)
	{
		vecDistance = m_arrTarget[i].vecPos - vecShipPos;
		fDistance = vecDistance.length();
		if (fDistance <= (float)m_uiRange)
		{
			vecDisplayDistance = vecDistance * (5.0f / (float)m_uiRange);
			if (m_arrTarget[i].iTargetType = TGT_ASTEROID)
			{
				oMaterial.m_oAmbient = CRGBAColour(0.5f,0.5f,0.5f,1.0f);
				oMaterial.m_oDiffuse = CRGBAColour(0.5f,0.5f,0.5f,1.0f);
				oMaterial.m_oEmissive = CRGBAColour(0.5f,0.5f,0.5f,1.0f);
				oMaterial.render();	
			}
			else
			{
				oMaterial.m_oAmbient = CRGBAColour(1.0f,0.2f,0.1f,1.0f);
				oMaterial.m_oDiffuse = CRGBAColour(1.0f,0.2f,0.1f,1.0f);
				oMaterial.m_oEmissive = CRGBAColour(1.0f,0.2f,0.1f,1.0f);
				oMaterial.render();	
			}

			glBegin(GL_LINES);
				glVertex3f(vecDisplayDistance.X(),
							  vecDisplayDistance.Y(),
							  vecDisplayDistance.Z());
				glVertex3f(vecDisplayDistance.X() + 2.5f,//Silly big value, still no lines tho
							  vecDisplayDistance.Y(),
							  vecDisplayDistance.Z());
			glEnd();
		}
	}

												//////////////////////////////////////////////
												//Copy to the texture                       //
												//////////////////////////////////////////////

	poTexture->postRenderToTexture(GL_RGBA);   
}


//**************************************************************************************
// Function name    : CRadar::render
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 31/10/2003
// Description      : Draws the texture created above  
//**************************************************************************************
void CRadar::render()
{

	CTexture *poTexture = g_oTextureManager.texture(m_uiOffScreenTexture);

	CMaterial *poMaterial;
	poMaterial = new CMaterial();
												//////////////////////////////////////////////
												//Create the material for drawing the       //
												//texture                                   //
												//////////////////////////////////////////////

	poMaterial->m_oAmbient = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
	poMaterial->m_oDiffuse = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
	poMaterial->m_oEmissive = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
	poMaterial->m_uiTexture = m_uiOffScreenTexture;

												//////////////////////////////////////////////
												//Set this texture as the 2D active         //
												//material                                  //
												//////////////////////////////////////////////

	this->setActiveMaterial(poMaterial);
												//////////////////////////////////////////////
												//Blending stuff                            //
												//////////////////////////////////////////////

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

												//////////////////////////////////////////////
												//Draw the quad (using the 2D parent        //
												//function                                  //
												//////////////////////////////////////////////

	this->renderQuad();
												//////////////////////////////////////////////
												//Blending off                              //
												//////////////////////////////////////////////

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

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
