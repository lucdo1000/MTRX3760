//-----------------------------------------------------------------------------
// CSensor.h
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// What every sensor on a robot has in common: a fixed mounting on the robot's
// body, and the arithmetic that turns that mounting into a position and a
// direction in the world once the robot has moved.
//
// The two kinds of sensor report different things - a range sensor reports a
// distance, a line sensor reports yes or no - so the reading itself is not part
// of this interface. What is shared is where the sensor is and which way it
// looks, and that is what lives here.
//-----------------------------------------------------------------------------

#ifndef CSENSOR_H
#define CSENSOR_H

#include "CLoopReader.h"   // for CPose
#include "CRender.h"

//-----------------------------------------------------------------------------
class CSensor
{
    public:
        //---Ctor/Dtor---
        // aMountAngle is measured from the robot's heading, positive towards
        // the robot's right. aMountDistance is how far from the robot's centre
        // the sensor sits, along that same angle.
        CSensor( float aMountAngleRadians, float aMountDistance );
        virtual ~CSensor();

        //---Placement in the world---
        // Where this sensor currently sits, given where the robot is.
        Vec2D PositionFor( const CPose& arRobotPose ) const;
        // Which way this sensor currently looks.
        float HeadingFor( const CPose& arRobotPose ) const;

    private:
        //---Mounting, fixed for the life of the sensor---
        const float mMountAngle;
        const float mMountDistance;
};

#endif
