// Input.h: interface for the CInput class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUT_H__1F13C87F_D365_4BC9_82EC_FB9722792CB7__INCLUDED_)
#define AFX_INPUT_H__1F13C87F_D365_4BC9_82EC_FB9722792CB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum enInputType
{
	FIRE,
	PITCH_UP,
	PITCH_DOWN,
	YAW_RIGHT,
	YAW_LEFT,
	ROLL_RIGHT,
	ROLL_LEFT,
	GUN_FIRE,
	MISSILE_FIRE,
	THROTTLE_UP,
	THROTTLE_DOWN,
	BRAKE,
	LOOK_RIGHT,
	LOOK_LEFT,
	LOOK_UP,
	LOOK_BACK,
	BOOST_THRUST,
	TOGGLE_FLIGHT_MODE,
	TOGGLE_VIEW,
	SLOW_MOTION
};

class CInput  
{
public:
	void getInput();
	CInput();
	virtual ~CInput();

protected:

};

#endif // !defined(AFX_INPUT_H__1F13C87F_D365_4BC9_82EC_FB9722792CB7__INCLUDED_)
