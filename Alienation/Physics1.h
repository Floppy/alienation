/**************************************************************************

  File: Physics1.h  

  Prepared by Erkin Tunca for http://nehe.gamedev.net

**************************************************************************/
#ifndef _PHYSICS1_H
#define _PHYSICS1_H

#include "config.h"

#include <math.h>
#include <stdio.h>												// Header File For Standard Input/Output
#include "Math/Quat.h"
#include "Math/Vector.h"



// class Mass			---> An object to represent a mass
// Calculates the physics for the physics engine. Not written by me (hence well commented)
//but made quite a few changes
class CMass
{
public:
	float m_fMass;									// The mass value
	CVector3 m_vecPos;								// Position in space
	CVector3 m_vecVel;								// Velocity
	CVector3 m_vecOldPos;
	CVector3 m_vecForce;								// Force applied on this mass at an instance

	CMass(float fMass) :     // Constructor
	   m_fMass(fMass)
	{}

	/*
	  void applyForce(Vector3D force) method is used to add external force to the mass. 
	  At an instance in time, several sources of force might affect the mass. The vector sum 
	  of these forces make up the net force applied to the mass at the instance.
	*/
	void applyForce(CVector3 vecForce)
	{
		this->m_vecForce += vecForce;					// The external force is added to the force of the mass
	}

	/*
	  void init() method sets the force values to zero
	*/
	void init()
	{
		m_vecForce.m_fx = 0;
		m_vecForce.m_fy = 0;
		m_vecForce.m_fz = 0;
	}

	/*
	  void simulate(float dt) method calculates the new velocity and new position of 
	  the mass according to change in time (dt). Here, a simulation method called
	  "The Euler Method" is used. The Euler Method is not always accurate, but it is 
	  simple. It is suitable for most of physical simulations that we know in common 
	  computer and video games.
	*/
	void simulate(float fDT)
	{
		m_vecVel += (m_vecForce / m_fMass) * fDT;				// Change in velocity is added to the velocity.
												// The change is proportinal with the acceleration (force / m) and change in time
		m_vecOldPos = m_vecPos;
		m_vecPos += m_vecVel * fDT;						// Change in position is added to the position.
												// Change in position is velocity times the change in time
	}

};

// class Simulation		---> A container object for simulating masses
class CSimulation
{
public:
	int m_iNumOfMasses;								// number of masses in this container
	CMass** m_ppMasses;									// masses are held by pointer to pointer. (Here Mass** represents a 1 dimensional array)
	CQuat m_quaOrientation;
	float m_fDelta_x, m_fDelta_y, m_fDelta_z;
	
	CSimulation(int iNumOfMasses, float fMass) :      // Constructor creates some masses with mass values m
		m_fDelta_x(0.0f),
		m_fDelta_y(0.0f),
		m_fDelta_z(0.0f)
	{
		this->m_iNumOfMasses = iNumOfMasses;
		
		m_ppMasses = new CMass*[m_iNumOfMasses];			// Create an array of pointers

		int a;
		for (a = 0; a < m_iNumOfMasses; ++a)		// We will step to every pointer in the array
			m_ppMasses[a] = new CMass(fMass);				// Create a Mass as a pointer and put it in the array
	}

	virtual ~CSimulation()									// Destructor
	{
		release();
	}

	virtual void release()							// delete the masses created
	{
		int a;
		for (a = 0; a < m_iNumOfMasses; ++a)		// we will delete all of them
		{
			delete(m_ppMasses[a]);
			m_ppMasses[a] = NULL;
		}
			
		delete(m_ppMasses);
		m_ppMasses = NULL;
	}

	CMass* getMass(int iIndex)
	{
		if (iIndex < 0 || iIndex >= m_iNumOfMasses)		// if the index is not in the array
			return NULL;							// then return NULL

		return m_ppMasses[iIndex];						// get the mass at the index
	}

	virtual void init()								// this method will call the init() method of every mass
	{
		int a;
		for (a = 0; a < m_iNumOfMasses; ++a)		// We will init() every mass
			m_ppMasses[a]->init();						// call init() method of the mass
	}

	virtual void solve()							// no implementation because no forces are wanted in this basic container
	{
													// in advanced containers, this method will be overrided and some forces will act on masses
	}

	virtual void simulate(float dt)					// Iterate the masses by the change in time
	{
		int a;
		for (a = 0; a < m_iNumOfMasses; ++a)	// We will iterate every mass
			m_ppMasses[a]->simulate(dt);				// Iterate the mass and obtain new position and new velocity

	}

	virtual void operate(float fDT)					// The complete procedure of simulation
	{
		init();										// Step 1: reset forces to zero
		solve();									// Step 2: apply forces
		simulate(fDT);								// Step 3: iterate the masses by the change in time
	}

	virtual void rotate()
	{
		float fRadian = 0.0174532925f;

		CQuat quaTemp;
		quaTemp.eulerToQuat(m_fDelta_x * fRadian, m_fDelta_y * fRadian, m_fDelta_z * fRadian);
		m_quaOrientation.multQuat(quaTemp);
	}
};

#endif
