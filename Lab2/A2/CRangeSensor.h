//-----------------------------------------------------------------------------
// CRangeSensor.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// A sensor that reports how far it is to the first wall along the direction it
// faces. This is what the wall following robot steers by.
//
// A real range finder cannot see forever, so readings are capped at MaxRange.
// That cap matters to the controller as well as to realism: without it, the
// moment the robot passes an outside corner the reading would jump to an
// enormous number and any control law based on it would react violently.
//-----------------------------------------------------------------------------

#ifndef CRANGESENSOR_H
#define CRANGESENSOR_H

#include "CSensor.h"

class CWorld;

//-----------------------------------------------------------------------------
class CRangeSensor : public CSensor
{
    public:
        //---Ctor---
        CRangeSensor( float aMountAngleRadians, float aMountDistance );

        //---Sensing---
        void Sense( const CWorld& arWorld, const CPose& arRobotPose );

        //---The reading, from the last call to Sense---
        float GetDistance() const;
        // True when the last reading was the cap rather than a real wall.
        bool IsAtMaxRange() const;

        //---Drawing---
        void Draw( CRender& arRender, const CPose& arRobotPose ) const;

        //---Limits---
        static float GetMaxRange();

    private:
        //---Tuning---
        static const float MaxRange;   // units; readings are capped here

        //---State---
        float mDistance;               // units, from the last Sense
};

#endif
