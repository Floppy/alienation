#ifndef _VECTOR_H
#define _VECTOR_H

#include "config.h"

#include <math.h>

/**
 * A 2D vector
 */
class CVector2 
{
public:
	float m_fx, m_fy;							// 2D vector coordinates

	CVector2() :								// Constructor to set x = y = z = 0
		m_fx(0.0f),
		m_fy(0.0f)
	{}

	CVector2(float fx, float fy) :			// Constructor that initializes this Vector3D to the intended values of x, y and z
		m_fx(fx),
		m_fy(fy)
	{}

	CVector2& operator= (CVector2 vecV)		// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
	{
		m_fx = vecV.m_fx;
		m_fy = vecV.m_fy;
		return *this;
	}
};

// class Vector3D		---> An object to represent a 3D vector or a 3D point in space
class CVector3
{
public:
	float m_fx;									// the x value of this Vector3D
	float m_fy;									// the y value of this Vector3D
	float m_fz;									// the z value of this Vector3D

	CVector3() :								// Constructor to set x = y = z = 0
		m_fx(0.0f),
		m_fy(0.0f),
		m_fz(0.0f)
	{}

	CVector3(float fx, float fy, float fz) :			// Constructor that initializes this Vector3D to the intended values of x, y and z
		m_fx(fx),
		m_fy(fy),
		m_fz(fz)
	{}

	CVector3& operator= (CVector3 vecV)		// operator= sets values of v to this Vector3D. example: v1 = v2 means that values of v2 are set onto v1
	{
		m_fx = vecV.m_fx;
		m_fy = vecV.m_fy;
		m_fz = vecV.m_fz;
		return *this;
	}

	bool operator== (CVector3 vecV)
	{
		if (this->m_fx == vecV.m_fx &&
			 this->m_fy == vecV.m_fy &&
			 this->m_fz == vecV.m_fz)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	CVector3 operator+ (CVector3 vecV)				// operator+ is used to add two Vector3D's. operator+ returns a new Vector3D
	{
		return CVector3(m_fx + vecV.m_fx, m_fy + vecV.m_fy, m_fz + vecV.m_fz);
	}

	CVector3 operator- (CVector3 vecV)				// operator- is used to take difference of two Vector3D's. operator- returns a new Vector3D
	{
		return CVector3(m_fx - vecV.m_fx, m_fy - vecV.m_fy, m_fz - vecV.m_fz);
	}

	CVector3 operator* (float fValue)			// operator* is used to scale a Vector3D by a value. This value multiplies the Vector3D's x, y and z.
	{
		return CVector3(m_fx * fValue, m_fy * fValue, m_fz * fValue);
	}

	CVector3 operator/ (float fValue)			// operator/ is used to scale a Vector3D by a value. This value divides the Vector3D's x, y and z.
	{
		return CVector3(m_fx / fValue, m_fy / fValue, m_fz / fValue);
	}

	CVector3& operator+= (CVector3 vecV)			// operator+= is used to add another Vector3D to this Vector3D.
	{
		m_fx += vecV.m_fx;
		m_fy += vecV.m_fy;
		m_fz += vecV.m_fz;
		return *this;
	}

	CVector3& operator-= (CVector3 vecV)			// operator-= is used to subtract another Vector3D from this Vector3D.
	{
		m_fx -= vecV.m_fx;
		m_fy -= vecV.m_fy;
		m_fz -= vecV.m_fz;
		return *this;
	}

	CVector3& operator*= (float fValue)			// operator*= is used to scale this Vector3D by a value.
	{
		m_fx *= fValue;
		m_fy *= fValue;
		m_fz *= fValue;
		return *this;
	}

	CVector3& operator/= (float fValue)			// operator/= is used to scale this Vector3D by a value.
	{
		m_fx /= fValue;
		m_fy /= fValue;
		m_fz /= fValue;
		return *this;
	}


	CVector3 operator- ()						// operator- is used to set this Vector3D's x, y, and z to the negative of them.
	{
		return CVector3(-m_fx, -m_fy, -m_fz);
	}

	float dot(CVector3 vecV)
	{
		return this->m_fx * vecV.m_fx + this->m_fy * vecV.m_fy + this->m_fz * vecV.m_fz;
	}

	float length()								// length() returns the length of this Vector3D
	{
		return (float)sqrt(m_fx*m_fx + m_fy*m_fy + m_fz*m_fz);
	};			   		

	void unitize()								// unitize() normalizes this Vector3D that its direction remains the same but its length is 1.
	{
		float fLength = this->length();

		if (fLength == 0)
			return;

		m_fx /= fLength;
		m_fy /= fLength;
		m_fz /= fLength;
	}

	CVector3 unit()								// unit() returns a new Vector3D. The returned value is a unitized version of this Vector3D.
	{
		float fLength = this->length();

		if (fLength == 0)
			return *this;
		
		return CVector3(m_fx / fLength, m_fy / fLength, m_fz / fLength);
	}

	CVector3 cross(CVector3 vecV)
	{
		CVector3 vecNormal;									
	
		vecNormal.m_fx = ((this->m_fy * vecV.m_fz) - (this->m_fz * vecV.m_fy));
		vecNormal.m_fy = ((this->m_fz * vecV.m_fx) - (this->m_fx * vecV.m_fz));
		vecNormal.m_fz = ((this->m_fx * vecV.m_fy) - (this->m_fy * vecV.m_fx));
	
		return vecNormal;
	}

};
#endif

