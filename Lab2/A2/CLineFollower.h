//-----------------------------------------------------------------------------
// CLineFollower.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// A robot that follows a line painted on the floor.
//
// It carries the two line sensors the handout specifies: one over the line and
// one to the side of it. Each reports only whether the floor beneath it is
// painted, so the robot has two bits of information to find its way around a
// closed loop with corners turning both ways.
//
// Putting the second sensor on one side rather than straddling the line is what
// makes the two readings tell the robot which way it has drifted:
//
//   centre on the line            -> going straight, stay the course
//   centre off, side on           -> the line has slid towards the side sensor,
//                                    so turn that way to get back over it
//   neither                       -> the line has gone the other way, turn the
//                                    opposite way to find it again
//
// That last case is what carries the robot around the sharp corners, where the
// line leaves both sensors for a moment.
//-----------------------------------------------------------------------------

#ifndef CLINEFOLLOWER_H
#define CLINEFOLLOWER_H

#include "CRobot.h"
#include "CLineSensor.h"

//-----------------------------------------------------------------------------
class CLineFollower : public CRobot
{
    public:
        //---Ctor---
        CLineFollower( const CPose& arStartPose );

    protected:
        //---CRobot---
        virtual void SenseAndSteer( const CWorld& arWorld );
        virtual void DrawSensors( CRender& arRender ) const;

    private:
        //---Steering---
        // Turn rate wanted for the current readings; positive turns right.
        float ChooseTurn() const;

        //---Sensor mounting---
        // The centre sensor sits ahead of the robot, the side sensor ahead and
        // out to the robot's left.
        static const float CentreSensorAngle;
        static const float CentreSensorReach;
        static const float SideSensorAngle;
        static const float SideSensorReach;

        //---Control tuning---
        static const float SearchTurn;      // units/s of wheel difference, line lost
        static const float CorrectingTurn;  // units/s, gentler nudge back on line
        static const float CruiseSpeed;     // units/s, both wheels

        //---Sensors---
        CLineSensor mCentreSensor;
        CLineSensor mSideSensor;
};

#endif
