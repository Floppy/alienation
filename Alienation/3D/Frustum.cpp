// Frustrum.cpp: implementation of the CFrustrum class.
//
//////////////////////////////////////////////////////////////////////

#include "3D/Frustum.h"
#include "Math/matrix.h"
#include <GL\gl.h>

float CFrustum::m_Frustum[6][4];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrustum::CFrustum()
{

}

CFrustum::~CFrustum()
{

}




//**************************************************************************************
// Function name    : CFrustum::NormalizePlane
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 25/05/2003
// Argument         : int side
// Description      : Here we calculate the magnitude of the normal to the plane 
//                    (point A B C) Remember that (A, B, C) is that same thing 
//                    as the normal's (X, Y, Z). To calculate magnitude you use 
//                    the equation:  magnitude = sqrt( x^2 + y^2 + z^2)  
//**************************************************************************************
void CFrustum::NormalizePlane(int side)
{
	float magnitude = (float)sqrt( m_Frustum[side][A] * m_Frustum[side][A] + 
								   m_Frustum[side][B] * m_Frustum[side][B] + 
								   m_Frustum[side][C] * m_Frustum[side][C] );

	// Then we divide the plane's values by it's magnitude.
	// This makes it easier to work with.
	m_Frustum[side][A] /= magnitude;
	m_Frustum[side][B] /= magnitude;
	m_Frustum[side][C] /= magnitude;
	m_Frustum[side][D] /= magnitude; 
}



//**************************************************************************************
// Function name    : CFrustum::CalculateFrustum
// Author           : Gary Ingram
// Return type      : void 
// Date Created     : 25/05/2003
// Description      : Calculates the frustum from the modelview and projection 
//                    matrices, The frustrum that is set in this class is a 
//                    static member and so will be the same wherever it is used  
//**************************************************************************************
void CFrustum::CalculateFrustum()
{    
	CMatrix   proj;								// This will hold our projection matrix
	CMatrix   modl;								// This will hold our modelview matrix
	CMatrix   clip;								// This will hold the clipping planes

												//////////////////////////////////////////////
												//glGetFloatv() is used to extract          //
												//information about our OpenGL world.       //
												//Below, we pass in GL_PROJECTION_MATRIX    //
												//to abstract our projection matrix. It     //
												//then stores the matrix into an array of   //
												//[16].                                     //
												//////////////////////////////////////////////

	glGetFloatv( GL_PROJECTION_MATRIX, proj.m_afElement );

												//////////////////////////////////////////////
												//By passing in GL_MODELVIEW_MATRIX, we     //
												//can abstract our model view matrix. This  //
												//also stores it in an array of [16].       //
												//////////////////////////////////////////////

	glGetFloatv( GL_MODELVIEW_MATRIX, modl.m_afElement );

												//////////////////////////////////////////////
												//Now that we have our modelview and        //
												//projection matrix, if we combine these 2  //
												//matrices, it will give us our clipping    //
												//planes.  To combine 2 matrices, we        //
												//multiply them.                            //
												//////////////////////////////////////////////


	clip = proj * modl;

												//////////////////////////////////////////////
												//Now we actually want to get the sides of  //
												//the frustum.  To do this we take the      //
												//clipping planes we received above and     //
												//extract the sides from them.              //
												//////////////////////////////////////////////


												//////////////////////////////////////////////
												//This will extract the RIGHT side of the   //
												//frustum                                   //
												//////////////////////////////////////////////

	m_Frustum[RIGHT][A] = clip.m_afElement[ 3] - clip.m_afElement[ 0];
	m_Frustum[RIGHT][B] = clip.m_afElement[ 7] - clip.m_afElement[ 4];
	m_Frustum[RIGHT][C] = clip.m_afElement[11] - clip.m_afElement[ 8];
	m_Frustum[RIGHT][D] = clip.m_afElement[15] - clip.m_afElement[12];

												//////////////////////////////////////////////
												//Now that we have a normal (A,B,C) and a   //
												//distance (D) to the plane, we want to     //
												//normalize that normal and distance.       //
												//////////////////////////////////////////////


												//////////////////////////////////////////////
												//Normalize the RIGHT side                  //
												//////////////////////////////////////////////

	NormalizePlane(RIGHT);

												//////////////////////////////////////////////
												//This will extract the LEFT side of the    //
												//frustum                                   //
												//////////////////////////////////////////////

	m_Frustum[LEFT][A] = clip.m_afElement[ 3] + clip.m_afElement[ 0];
	m_Frustum[LEFT][B] = clip.m_afElement[ 7] + clip.m_afElement[ 4];
	m_Frustum[LEFT][C] = clip.m_afElement[11] + clip.m_afElement[ 8];
	m_Frustum[LEFT][D] = clip.m_afElement[15] + clip.m_afElement[12];

												//////////////////////////////////////////////
												//Normalize the LEFT side                   //
												//////////////////////////////////////////////

	NormalizePlane(LEFT);

												//////////////////////////////////////////////
												//This will extract the BOTTOM side of the  //
												//frustum                                   //
												//////////////////////////////////////////////

	m_Frustum[BOTTOM][A] = clip.m_afElement[ 3] + clip.m_afElement[ 1];
	m_Frustum[BOTTOM][B] = clip.m_afElement[ 7] + clip.m_afElement[ 5];
	m_Frustum[BOTTOM][C] = clip.m_afElement[11] + clip.m_afElement[ 9];
	m_Frustum[BOTTOM][D] = clip.m_afElement[15] + clip.m_afElement[13];

												//////////////////////////////////////////////
												//Normalize the BOTTOM side                 //
												//////////////////////////////////////////////

	NormalizePlane(BOTTOM);

												//////////////////////////////////////////////
												//This will extract the TOP side of the     //
												//Frustum                                   //
												//////////////////////////////////////////////

	m_Frustum[TOP][A] = clip.m_afElement[ 3] - clip.m_afElement[ 1];
	m_Frustum[TOP][B] = clip.m_afElement[ 7] - clip.m_afElement[ 5];
	m_Frustum[TOP][C] = clip.m_afElement[11] - clip.m_afElement[ 9];
	m_Frustum[TOP][D] = clip.m_afElement[15] - clip.m_afElement[13];

												//////////////////////////////////////////////
												//Normalize the TOP side                    //
												//////////////////////////////////////////////

	NormalizePlane(TOP);

												//////////////////////////////////////////////
												//This will extract the BACK side of the    //
												//frustum                                   //
												//////////////////////////////////////////////

	m_Frustum[BACK][A] = clip.m_afElement[ 3] - clip.m_afElement[ 2];
	m_Frustum[BACK][B] = clip.m_afElement[ 7] - clip.m_afElement[ 6];
	m_Frustum[BACK][C] = clip.m_afElement[11] - clip.m_afElement[10];
	m_Frustum[BACK][D] = clip.m_afElement[15] - clip.m_afElement[14];

												//////////////////////////////////////////////
												//Normalize the BACK side                   //
												//////////////////////////////////////////////

	NormalizePlane(BACK);

												//////////////////////////////////////////////
												//This will extract the FRONT side of the   //
												//frustum                                   //
												//////////////////////////////////////////////

	m_Frustum[FRONT][A] = clip.m_afElement[ 3] + clip.m_afElement[ 2];
	m_Frustum[FRONT][B] = clip.m_afElement[ 7] + clip.m_afElement[ 6];
	m_Frustum[FRONT][C] = clip.m_afElement[11] + clip.m_afElement[10];
	m_Frustum[FRONT][D] = clip.m_afElement[15] + clip.m_afElement[14];

												//////////////////////////////////////////////
												//Normalize the FRONT side                  //
												//////////////////////////////////////////////

	NormalizePlane(FRONT);

}


//**************************************************************************************
// Function name    : CFrustum::PointInFrustum
// Author           : Gary Ingram
// Return type      : bool 
// Date Created     : 25/05/2003
// Argument         :  float x
// Argument         : float y
// Argument         : float z
// Description      : The code below will allow us to make checks within the 
//                    frustum.  For example, if we want to see if a point, a 
//                    sphere, or a cube lies inside of the frustum. Because all 
//                    of our planes point INWARDS (The normals are all pointing 
//                    inside the frustum) we then can assume that if a point is 
//                    in FRONT of all of the planes, it's inside.  
//**************************************************************************************
bool CFrustum::PointInFrustum( float x, float y, float z )
{
												//////////////////////////////////////////////
												//If you remember the plane equation (A*x   //
												//+ B*y + C*z + D = 0), then the rest of    //
												//this code should be quite obvious and     //
												//easy to figure out yourself. In case      //
												//don't know the plane equation, it might   //
												//be a good idea to look at our Plane       //
												//Collision tutorial at                     //
												//www.GameTutorials.com in OpenGL           //
												//Tutorials. I will briefly go over it      //
												//here.  (A,B,C) is the (X,Y,Z) of the      //
												//normal to the plane. They are the same    //
												//thing... but just called ABC because you  //
												//don't want to say: (x*x + y*y + z*z + d   //
												//= 0).  That would be wrong, so they       //
												//substitute them. the (x, y, z) in the     //
												//equation is the point that you are        //
												//testing.  The D is The distance the       //
												//plane is from the origin.  The equation   //
												//ends with "= 0" because that is true      //
												//when the point (x, y, z) is ON the        //
												//plane.  When the point is NOT on the      //
												//plane, it is either a negative number     //
												//(the point is behind the plane) or a      //
												//positive number (the point is in front    //
												//of the plane).  We want to check if the   //
												//point is in front of the plane, so all    //
												//we have to do is go through each point    //
												//and make sure the plane equation goes     //
												//out to a positive number on each side of  //
												//the frustum. The result (be it positive   //
												//or negative) is the distance the point    //
												//is front the plane.                       //
												//////////////////////////////////////////////


												//////////////////////////////////////////////
												//Go through all the sides of the frustum   //
												//////////////////////////////////////////////

	for(int i = 0; i < 6; i++ )
	{
												//////////////////////////////////////////////
												//Calculate the plane equation and check    //
												//if the point is behind a side of the      //
												//frustum                                   //
												//////////////////////////////////////////////

		if(m_Frustum[i][A] * x + m_Frustum[i][B] * y + m_Frustum[i][C] * z + m_Frustum[i][D] <= 0)
		{
												//////////////////////////////////////////////
												//The point was behind a side, so it ISN'T  //
												//in the frustum                            //
												//////////////////////////////////////////////

			return false;
		}
	}

												//////////////////////////////////////////////
												//The point was inside of the frustum (In   //
												//front of ALL the sides of the frustum)    //
												//////////////////////////////////////////////

	return true;
}


//**************************************************************************************
// Function name    : CFrustum::SphereInFrustum
// Author           : Gary Ingram
// Return type      : bool 
// Date Created     : 25/05/2003
// Argument         :  float x
// Argument         : float y
// Argument         : float z
// Argument         : float radius
// Description      : This determines if a sphere is inside of our frustum by 
//                    it's center and radius.  
//**************************************************************************************
bool CFrustum::SphereInFrustum( CBoundingSphere *poSphere )
{
												//////////////////////////////////////////////
												//Now this function is almost identical to  //
												//the PointInFrustum(), except we now have  //
												//to deal with a radius around the point.   //
												//The point is the center of the radius.    //
												//So, the point might be outside of the     //
												//frustum, but it doesn't mean that the     //
												//rest of the sphere is.  It could be half  //
												//and half.  So instead of checking if      //
												//it's less than 0, we need to add on the   //
												//radius to that.  Say the equation         //
												//produced -2, which means the center of    //
												//the sphere is the distance of 2 behind    //
												//the plane.  Well, what if the radius was  //
												//5?  The sphere is still inside, so we     //
												//would say, if(-2 < -5) then we are        //
												//outside.  In that case it's false, so we  //
												//are inside of the frustum, but a          //
												//distance of 3.  This is reflected below.  //
												//                                          //
												//////////////////////////////////////////////


												//////////////////////////////////////////////
												//Go through all the sides of the frustum   //
												//////////////////////////////////////////////

	for(int i = 0; i < 6; i++ )	
	{
												//////////////////////////////////////////////
												//If the center of the sphere is farther    //
												//away from the plane than the radius       //
												//////////////////////////////////////////////

		if( m_Frustum[i][A] * poSphere->m_vecPos.m_fx + m_Frustum[i][B] * poSphere->m_vecPos.m_fy + m_Frustum[i][C] * poSphere->m_vecPos.m_fz + m_Frustum[i][D] <= -poSphere->m_fRadius )
		{
												//////////////////////////////////////////////
												//The distance was greater than the radius  //
												//so the sphere is outside of the frustum   //
												//////////////////////////////////////////////

			return false;
		}
	}
	
												//////////////////////////////////////////////
												//The sphere was inside of the frustum!     //
												//////////////////////////////////////////////

	return true;
}




//**************************************************************************************
// Function name    : CFrustum::CubeInFrustum
// Author           : Gary Ingram
// Return type      : bool 
// Date Created     : 25/05/2003
// Argument         :  float x
// Argument         : float y
// Argument         : float z
// Argument         : float size
// Description      : This test is a bit more work, but not too much more 
//                    complicated. Basically, what is going on is, that we are 
//                    given the center of the cube, and half the length.  Think 
//                    of it like a radius.  Then we checking each point in the 
//                    cube and seeing if it is inside the frustum.  If a point 
//                    is found in front of a side, then we skip to the next 
//                    side.  If we get to a plane that does NOT have a point in 
//                    front of it, then it will return false.  *Note* - This 
//                    will sometimes say that a cube is inside the frustum when 
//                    it isn't. This happens when all the corners of the 
//                    bounding box are not behind any one plane. This is rare 
//                    and shouldn't effect the overall rendering speed.  
//**************************************************************************************
bool CFrustum::CubeInFrustum( float x, float y, float z, float size )
{


	for(int i = 0; i < 6; i++ )
	{
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;
		if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
		   continue;

												//////////////////////////////////////////////
												//If we get here, it isn't in the frustum   //
												//////////////////////////////////////////////

		return false;
	}

	return true;
}
