// Hud.cpp: implementation of the CHud class.
//
//////////////////////////////////////////////////////////////////////

#include "Hud.h"
#include <SDL.h>
#include <SDL_opengl.h>
#include "3D/TextureManager.h"

#include <iostream>
using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHud::CHud() :
   m_iLastTime(SDL_GetTicks())
{
   for (int i=0; i<7; i++) {
      m_auiTextures[i] = 0;
   }
   init();
}

CHud::~CHud()
{
   for (int i=0; i<7; i++) {
      g_oTextureManager.removeReference(m_auiTextures[i]);
   }
}


//**************************************************************************************
// Function name    : CHud::draw
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 25/05/2003
// Argument         : float fSpeed
// Argument         : float fMaxSpeed
// Argument         : float fThrust
// Argument         : float fMaxThrust
// Description      : Draws the ship hud including all the information relevent to 
//                    the player ship. Will be enlarged over time to include 
//                    more ship information. Note: information regarding the 
//                    ships target will be drawn in the DrawHoloTarget routine.  
// History
//   Version         Date         Who      Description
//   =======         ====         ===      ===========
//     1.0           25/05/2003   GI       Initial Version
//     1.1           26/05/2003   GI       Using glOrtho to display hud as a 
//                                         proper 2d surface  
//     1.2           14/06/2003   FL       Sets the material properties properly 
//                                         now using new class   
//     1.1           14/06/2003   GI       Now drawn using 2d object class.  
//**************************************************************************************
void CHud::draw(float fSpeed, float fMaxSpeed, float fThrust, float fMaxThrust)
{   


	char strFont[20];
	float fWidthSpeed, fWidthThrust;
	CVector2 avecTex[4];

												//////////////////////////////////////////////
												//Calculate the size of the textures for    //
												//the ships speed and thrust. This diplays  //
												//a part of the thrust/speed texture as a   //
												//percentage of maximum thrust/speed. Will  //
												//be seperated out into a seperate          //
												//function soon as will need a lot more     //
												//like this (Shields armor etc)             //
												//////////////////////////////////////////////

	if (fSpeed == 0.0f)
	{
		fWidthSpeed = 0.001f;
	}
	else
	{
		fWidthSpeed = (fSpeed / fMaxSpeed) + 0.001f;
	}

	if (fThrust == 0.0f)
	{
		fWidthThrust = 0.001f;
	}
	else
	{
		fWidthThrust = (fThrust / fMaxThrust) + 0.001f;
	}
												//////////////////////////////////////////////
												//NEW!!! Now using goOrtho to display the   //
												//hud. This is in 2d so no worries over z   //
												//depth etc                                 //
												//////////////////////////////////////////////

												//////////////////////////////////////////////
												//First store the modelview matrix and      //
												//then reset it, then store the projection  //
												//matrix and reset it, finally set up the   //
												//2D ortho view                             //
												//////////////////////////////////////////////

	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);

												//////////////////////////////////////////////
												//Texture and blending stuff manually sets  //
												//the material properties. Hard coded,      //
												//shouldnt be really                        //
												//////////////////////////////////////////////
//<<<<<<< Hud.cpp
//   CMaterial oMaterial;
//   oMaterial.m_oEmissive = CRGBAColour(0.4f,1.0f,0.3f,0.06f);
//   oMaterial.render();
//	glEnable(GL_BLEND);
//=======
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        CMaterial oMaterial;
        oMaterial.m_oDiffuse = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
        oMaterial.m_oAmbient = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
        oMaterial.m_oEmissive = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
        oMaterial.render();
//>>>>>>> 1.11

												//////////////////////////////////////////////
												//Right Shield                              //
												//////////////////////////////////////////////

	avecTex[0] = CVector2( 0.0f, 1.0f);
	avecTex[1] = CVector2( 1.0f, 1.0f);
	avecTex[2] = CVector2( 1.0f, 0.0f);
	avecTex[3] = CVector2( 0.0f, 0.0f);

	g_oTextureManager.activate(m_auiTextures[6]);
//	draw2DQuad(.0f, 500.0f, 400.0f, 500.0f, avecTex);
	m_po2DObject->renderQuad(0.0f, 500.0f, 400.0f, 500.0f, avecTex);


	g_oTextureManager.activate(m_auiTextures[2]);
//	draw2DQuad(540.0f, 480.0f, 150.0f, 200.0f, avecTex);
	m_po2DObject->renderQuad(540.0f, 480.0f, 150.0f, 200.0f, avecTex);
	
												//////////////////////////////////////////////
												//Left Shield                               //
												//////////////////////////////////////////////


	g_oTextureManager.activate(m_auiTextures[3]);
//	draw2DQuad(340.0f, 480.0f, 150.0f, 200.0f, avecTex);
	m_po2DObject->renderQuad(340.0f, 480.0f, 150.0f, 200.0f, avecTex);

												//////////////////////////////////////////////
												//Front Shield                              //
												//////////////////////////////////////////////

	g_oTextureManager.activate(m_auiTextures[1]);
//	draw2DQuad(415.0f, 560.0f, 200.0f, 150.0f, avecTex);
	m_po2DObject->renderQuad(415.0f, 560.0f, 200.0f, 150.0f, avecTex);

												//////////////////////////////////////////////
												//Back Shield                               //
												//////////////////////////////////////////////

	g_oTextureManager.activate(m_auiTextures[0]);
//	draw2DQuad(415.0f, 350.0f, 200.0f, 150.0f, avecTex);
	m_po2DObject->renderQuad(415.0f, 350.0f, 200.0f, 150.0f, avecTex);

												//////////////////////////////////////////////
												//Speed Bar                                 //
												//////////////////////////////////////////////

	avecTex[0] = CVector2( 0.0f, 1.0f);
	avecTex[1] = CVector2( fWidthSpeed - 0.001f, 1.0f);
	avecTex[2] = CVector2( fWidthSpeed - 0.001f, 0.0f);
	avecTex[3] = CVector2( 0.0f, 0.0f);
	
	g_oTextureManager.activate(m_auiTextures[4]);
//	draw2DQuad(415.0f, 420.0f, 200.0f * fWidthSpeed, 200.0f, avecTex);
	m_po2DObject->renderQuad(415.0f, 420.0f, 200.0f * fWidthSpeed, 200.0f, avecTex);

												//////////////////////////////////////////////
												//Thrust Bar                                //
												//////////////////////////////////////////////

	avecTex[0] = CVector2( 0.0f, 1.0f);
	avecTex[1] = CVector2( fWidthThrust - 0.001f, 1.0f);
	avecTex[2] = CVector2( fWidthThrust - 0.001f, 0.0f);
	avecTex[3] = CVector2( 0.0f, 0.0f);

	g_oTextureManager.activate(m_auiTextures[5]);
//	draw2DQuad(415.0f, 550.0f, 200.0f * fWidthThrust, 200.0f, avecTex);
	m_po2DObject->renderQuad(415.0f, 550.0f, 200.0f * fWidthThrust, 200.0f, avecTex);

	sprintf(strFont,"Velocity: %.1f", fSpeed);
	m_poFont->print(strFont, CVector2(420.0f, 210.0f), 5.0f);

	sprintf(strFont,"Thrust: %.1f", fThrust);
	m_poFont->print(strFont, CVector2(420.0f, 560.0f), 5.0f);

        // Calc FPS
        unsigned long iTime = SDL_GetTicks();
        unsigned long iFPS = 0;
        if (iTime != m_iLastTime) {
           iFPS = 1000/(iTime - m_iLastTime);
        }
	sprintf(strFont,"%3d FPS", iFPS);
	m_poFont->print(strFont, CVector2(900.0f, 20.0f), 5.0f);
        m_iLastTime = iTime;

	glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}


//**************************************************************************************
// Function name    : CHud::init
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 25/05/2003
// Description      : Initialises the hud. Loads all the textures (quite a few)  
//**************************************************************************************
void CHud::init()
{
	m_poFont = new CGLFont;
	m_poFont->load();

   m_auiTextures[0] = g_oTextureManager.load("Hud/hud_fore.png");
   m_auiTextures[1] = g_oTextureManager.load("Hud/hud_aft.png");
   m_auiTextures[2] = g_oTextureManager.load("Hud/hud_right.png");
   m_auiTextures[3] = g_oTextureManager.load("Hud/hud_left.png");
   m_auiTextures[4] = g_oTextureManager.load("Hud/hud_speed.png");
   m_auiTextures[5] = g_oTextureManager.load("Hud/hud_thrust.png");
   m_auiTextures[6] = g_oTextureManager.load("Hud/hud_target.png");
	m_po2DObject = new C2DObject;
}


//**************************************************************************************
// Function name    : CHud::drawQuad
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 25/05/2003
// Argument         : CVector3 *Verts
// Argument         : CVector2 *Tex
// Description      : This draws a quad with texture co-ordinates. Should be in 
//                    a utility class or what ever, which I think floppy is 
//                    doing. Still, helped out for a while tho ;)  
// History
//   Version         Date         Who      Description
//   =======         ====         ===      ===========
//     1.0           26/05/2003   GI       Initial Version
//**************************************************************************************
void CHud::drawQuad(CVector3 *Verts, CVector2 *Tex)
{
	int iCount;

	glBegin(GL_QUADS);

		for ( iCount = 0 ; iCount < 4 ; iCount ++ )
		{
			glTexCoord2fv(Tex[iCount].glVector());
			glVertex3fv(Verts[iCount].glVector());
		}
	glEnd();
}






//**************************************************************************************
// Function name    : CHud::drawHoloTarget
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 25/05/2003
// Argument         : CShipData *poTarget
// Argument         : CMass **poMass
// Argument         : CShip *poThisShip
// Description      : This routine draws the hologram on the target on the hud. 
//                    Although this is its main function it is also used to 
//                    display other target information  
// History
//   Version         Date         Who      Description
//   =======         ====         ===      ===========
//     1.0           25/05/2003   GI       Initial Version
//     1.1           26/05/2003   GI       First working version :) As well as 
//                                         using glOrtho for the 2D stuff, it now 
//                                         correctly calculates the pitch and yaw 
//                                         required to view the target correctly. 
//                                         (Note: To work 100%, needs to render 
//                                         to texture, so all work is in 2D)  
//**************************************************************************************
void CHud::drawHoloTarget(CShipData *poTarget, CMass **poMass, CShip *poThisShip)
{

	CVector3 vecTarget, vecTemp;
	CVector3 vecThisRight, vecThisUp, vecThisHead, vecThisLeft;

												//////////////////////////////////////////////
												//Initialise all the variables. The         //
												//vecTarget variable is the vector between  //
												//the player ship and the target. This      //
												//vector is normalised. All the other       //
												//vectors (up heading and right) are moved  //
												//to the origin                             //
												//////////////////////////////////////////////

	vecTarget =  poMass[0]->m_vecPos - poThisShip->m_ppMasses[0]->m_vecPos;
	vecThisRight = poThisShip->m_poShips[0].m_vecRight    - poThisShip->m_ppMasses[0]->m_vecPos;
	vecThisUp    = poThisShip->m_poShips[0].m_vecUp       - poThisShip->m_ppMasses[0]->m_vecPos;	
	vecThisHead  = poThisShip->m_poShips[0].m_vecHeading  - poThisShip->m_ppMasses[0]->m_vecPos;	
	vecThisLeft = vecThisRight * -1.0f;

	vecThisRight = CVector3(1.0f, 0.0f, 0.0f);
	vecThisHead = CVector3(0.0f, 0.0f, -1.0f);
	vecThisUp = CVector3(0.0f, 1.0f, 0.0f);

        int iRange = static_cast<int>(vecTarget.length());

	vecTarget.normalise();

												//////////////////////////////////////////////
												//Store the vecTarget as we will need it    //
												//for calculating the yaw angle	           //
												//////////////////////////////////////////////

	vecTemp = vecTarget;

												//////////////////////////////////////////////
												// project the target vector onto the ships //
												// zy plane (for pitch)                     //
												//////////////////////////////////////////////

	vecTarget = vecTarget - (vecThisRight * vecThisRight.dot(vecTarget));

												//////////////////////////////////////////////
												// Unitise the new target vector so that the//
												// dot product with the heading will produce//
												// the correct angle (heading is also unit  //
												// length)                                  //
												//////////////////////////////////////////////

	vecTarget.normalise();

												//////////////////////////////////////////////
												// calculate the pitch angle from the ships //
												// heading in radians                       //
												//////////////////////////////////////////////

	float fAPitch = vecThisHead.dot(vecTarget);

												//////////////////////////////////////////////
												// Calculate the final pitch in degrees     //
												//////////////////////////////////////////////

	float fPitch = RAD_TO_DEG(acos(fAPitch));

												//////////////////////////////////////////////
												// Next, check the new target vector against//
												// the ships up vector to check for negative//
												// or positive. This will decide if it is a //
												// positive or negative pitch.              //
												//////////////////////////////////////////////

	float fPAngle = vecThisUp.dot(vecTarget);
	if (fPAngle <= 0.0f)
	{
		fPitch = -fPitch;
	}

												//////////////////////////////////////////////
												//Now we have the pitch we need to rotate   //
												//the target (Held in vecTemp) around the   //
												//pitch and then calculate the yaw. So      //
												//first we create a pitch matrix and        //
												//rotate the target.                        //
												//////////////////////////////////////////////


	CQuat quaPitch(0.0f, 0.0f, DEG_TO_RAD(fPitch));
	CMatrix matP(quaPitch);
	vecTemp = matP * vecTemp;

												//////////////////////////////////////////////
												//Now we have our new rotated target        //
												//vector. To find the angle we do the same  //
												//as above, this time comparing against     //
												//the up vector.                            //
												//////////////////////////////////////////////

	vecTarget = vecTemp;
	vecTarget = vecTarget - (vecThisUp * vecThisUp.dot(vecTarget));

	vecTarget.normalise();

	float fAYaw = vecThisHead.dot(vecTarget);

	float fYaw = RAD_TO_DEG(acos(fAYaw));

	float fYAngle = vecThisRight.dot(vecTarget);
	if (fYAngle <= 0.0f)
	{
		fYaw = -fYaw;
	}

												//////////////////////////////////////////////
												//Now calculate the yaw matrix (as above)   //
												//and multiply this with the pitch matrix   //
												//for the final matrix. As this is a view   //
												//matrix it needs to be inverted to         //
												//operate correctly                         //
												//////////////////////////////////////////////

	CQuat quaYaw(DEG_TO_RAD(fYaw), 0.0f, 0.0f);
	CMatrix matY(quaYaw);
	CMatrix matM(matP * matY);

	matM.invert();

												//////////////////////////////////////////////
												//Now to draw the actual holo ship.         //
												//Actually, this part of the routine also   //
												//draws some text to disply data from the   //
												//target ship such as speed and distance    //
												//etc.                                      //
												//////////////////////////////////////////////

												//////////////////////////////////////////////
												//Will also display more graphics soon      //
												//////////////////////////////////////////////

												//////////////////////////////////////////////
												//Change 26/05/2003. The drawing of any 2D  //
												//stuff (hud quads, text etc) is now done   //
												//using glOrtho. Only the actual Target     //
												//hologramis displayed using a              //
												//non-orthoganal view                       //
												//////////////////////////////////////////////

	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glLoadIdentity();

	CVector3 vecHoloPos = vecTemp * 30.0f;

	glMultMatrixf(matM.glElements());

	glTranslatef(vecHoloPos.X(), vecHoloPos.Y(), vecHoloPos.Z());
	glMultMatrixf(poTarget->m_matRotation.glElements());

	CMatrix matGet(GL_MODELVIEW_MATRIX);

	matGet.element(12) = -0.87f;
	matGet.element(13) = 0.59f;
	matGet.element(14) = -2.0f;

	glLoadMatrixf(matGet.glElements());

	glScalef(0.02f, 0.02f, 0.02f);

	poTarget->m_oModel.render();


	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
	CVector2 avecTex[4];

	avecTex[0] = CVector2(0.0f, 1.0f); 
	avecTex[1] = CVector2(1.0f, 1.0f); 
	avecTex[0] = CVector2(1.0f, 0.0f); 
	avecTex[0] = CVector2(0.0f, 0.0f); 
//	m_poTexture->setActive(6);
//	draw2DQuad(100.0f, 100.0f, 100.0f, 100.0f, avecTex);

	char strFont[20];

//	sprintf(strFont,"Pitch: %.1f AI Pitch: %.1f", fPitch, poTarget->m_fPitchRate);
//	m_poFont->print(strFont, CVector2(50.0f, 200.0f), 5.0f);

	sprintf(strFont,"%dm", iRange);
	m_poFont->print(strFont, CVector2(50.0f, 230.0f), 5.0f);

	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);	

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glPopMatrix(); 

}


//**************************************************************************************
// Function name    : CHud::draw2DQuad
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 26/05/2003
// Argument         : float fPosX : X Position of quad
// Argument         : float fPosY : Y position of quad
// Argument         : float fWidth	: Width of quad
// Argument         : float fHeight : Height of quad
// Argument         : CVector2 *Tex : Array containing texure coordinates
// Description      : This routine draws a 2d quad on a orthonganal display  
// History
//   Version         Date         Who      Description
//   =======         ====         ===      ===========
//     1.0           26/05/2003   GI        Initial Version
//**************************************************************************************
void CHud::draw2DQuad(float fPosX, float fPosY, float fWidth, float fHeight, CVector2 *Tex)
{
	glBegin(GL_QUADS);

		glTexCoord2fv(Tex[0].glVector());
		glVertex2f(fPosX, fPosY);
		glTexCoord2fv(Tex[1].glVector());
		glVertex2f(fPosX + fWidth, fPosY);
		glTexCoord2fv(Tex[2].glVector());
		glVertex2f(fPosX + fWidth, fPosY - fHeight);
		glTexCoord2fv(Tex[3].glVector());
		glVertex2f(fPosX, fPosY - fHeight);

	glEnd();
}
