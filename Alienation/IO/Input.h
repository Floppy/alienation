#ifndef SDS_INPUT_H
#define SDS_INPUT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace NSDIO {

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
   
   class CInput {

   public:

      CInput();

      virtual ~CInput();

      void getInput();
      
   protected:
      
   };
   
}
#endif // SDS_INPUT_H
