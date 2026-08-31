//-----------------------------------------------------------------------------
// CWallFollower.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// A robot that drives around a room keeping the wall on its right.
//
// It carries the two range sensors the handout specifies: one looking directly
// to its right, and one looking forward and to the right at forty five degrees.
// Two sensors is the minimum that makes wall following work, and each has a
// distinct job:
//
//   - the side sensor answers "am I the right distance from the wall", which is
//     what keeps the robot parallel to a straight wall;
//   - the diagonal sensor answers "is there a wall about to be in front of me",
//     which is what gets the robot around an inside corner before it drives
//     into one. The room in SimpleWalls.map has such a corner at the notch, so
//     a robot with only a side sensor cannot finish the lap.
//
// Everything else - the body, the wheels, the trail, collisions, laps - comes
// from CRobot.
//-----------------------------------------------------------------------------

#ifndef CWALLFOLLOWER_H
#define CWALLFOLLOWER_H

#include "CRobot.h"
#include "CRangeSensor.h"

//-----------------------------------------------------------------------------
class CWallFollower : public CRobot
{
    public:
        //---Ctor---
        CWallFollower( const CPose& arStartPose );

    protected:
        //---CRobot---
        virtual void SenseAndSteer( const CWorld& arWorld );
        virtual void DrawSensors( CRender& arRender ) const;

    private:
        //---Steering---
        // Turn rate wanted for the current readings; positive turns right.
        float ChooseTurn() const;

        //---Sensor mounting---
        static const float SideSensorAngle;      // radians, to the right
        static const float DiagonalSensorAngle;  // radians, forward and right

        //---Control tuning---
        static const float TargetWallDistance;   // units, held on the right
        static const float DiagonalClearance;    // units; closer means a corner
        static const float ProportionalGain;     // turn per unit of distance error
        static const float MaximumTurn;          // units/s of wheel difference
        static const float CruiseSpeed;          // units/s, both wheels

        //---Sensors---
        CRangeSensor mSideSensor;
        CRangeSensor mDiagonalSensor;
};

#endif
