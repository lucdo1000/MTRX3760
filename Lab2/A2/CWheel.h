//-----------------------------------------------------------------------------
// CWheel.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// One of a robot's two independently driven wheels.
//
// A wheel knows how fast it has been told to turn and how far it sits to the
// side of the robot's centre. Keeping the offset here rather than in CRobot is
// what lets the differential drive read as "ask each wheel where it is and how
// fast it is going" instead of arithmetic on a bare pair of numbers.
//-----------------------------------------------------------------------------

#ifndef CWHEEL_H
#define CWHEEL_H

//-----------------------------------------------------------------------------
class CWheel
{
    public:
        //---Ctor---
        // aLateralOffset is measured to the robot's right, so the left wheel
        // takes a negative offset and the right wheel a positive one.
        explicit CWheel( float aLateralOffset );

        //---Speed---
        void SetSpeed( float aSpeed );      // units of distance per second
        float GetSpeed() const;

        //---Placement---
        float GetLateralOffset() const;

    private:
        //---State---
        float mSpeed;                  // units of distance per second
        const float mLateralOffset;    // units, positive to the robot's right
};

#endif
