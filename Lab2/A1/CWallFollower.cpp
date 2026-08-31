//-----------------------------------------------------------------------------
// CWallFollower.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CWallFollower.h"
#include "CWorld.h"
#include "CPalette.h"

namespace
{
    const float Degrees45 = 0.785398f;
    const float Degrees90 = 1.570796f;
}

//---Where the sensors point, measured from the robot's heading---
const float CWallFollower::SideSensorAngle = Degrees90;
const float CWallFollower::DiagonalSensorAngle = Degrees45;

//---Control tuning---
const float CWallFollower::TargetWallDistance = 45.0f;
const float CWallFollower::DiagonalClearance = 62.0f;
const float CWallFollower::ProportionalGain = 0.9f;
const float CWallFollower::MaximumTurn = 42.0f;
const float CWallFollower::CruiseSpeed = 60.0f;

//-----------------------------------------------------------------------------
CWallFollower::CWallFollower( const CPose& arStartPose )
    :
        CRobot( "WallFollower", arStartPose,
                CPalette::WallFollowerBody, CPalette::WallFollowerTrail ),
        mSideSensor( SideSensorAngle, GetBodyRadius() ),
        mDiagonalSensor( DiagonalSensorAngle, GetBodyRadius() )
{
}

//-----------------------------------------------------------------------------
void CWallFollower::SenseAndSteer( const CWorld& arWorld )
{
    mSideSensor.Sense( arWorld, GetPose() );
    mDiagonalSensor.Sense( arWorld, GetPose() );

    const float Turn = ChooseTurn();

    //---A positive turn drives the left wheel faster, swinging the nose right---
    Drive( CruiseSpeed + Turn, CruiseSpeed - Turn );
}

//-----------------------------------------------------------------------------
// Two rules, in priority order.
//
// If the diagonal sensor sees a wall closing in, the robot is approaching an
// inside corner and must turn away from the wall regardless of how far the
// side sensor says it is. This rule has to win, because at an inside corner
// the side reading is still perfectly good right up until the robot hits the
// wall in front of it.
//
// Otherwise steer proportionally on how far the side reading has drifted from
// the distance we want to hold. Too far from the wall turns towards it, too
// close turns away. Capping the result keeps the robot from spinning when the
// side sensor runs off the end of a wall at an outside corner and reads its
// maximum range - which is exactly the behaviour that rounds the corner.
//-----------------------------------------------------------------------------
float CWallFollower::ChooseTurn() const
{
    float Result = 0.0f;

    if( mDiagonalSensor.GetDistance() < DiagonalClearance )
    {
        //---Wall closing in ahead and to the right: turn left, away from it---
        Result = -MaximumTurn;
    }
    else
    {
        const float Error = mSideSensor.GetDistance() - TargetWallDistance;
        Result = ProportionalGain * Error;

        if( Result > MaximumTurn )
        {
            Result = MaximumTurn;
        }
        else if( Result < -MaximumTurn )
        {
            Result = -MaximumTurn;
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
void CWallFollower::DrawSensors( CRender& arRender ) const
{
    mSideSensor.Draw( arRender, GetPose() );
    mDiagonalSensor.Draw( arRender, GetPose() );
}
