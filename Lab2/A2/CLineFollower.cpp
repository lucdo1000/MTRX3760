//-----------------------------------------------------------------------------
// CLineFollower.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CLineFollower.h"
#include "CWorld.h"
#include "CPalette.h"

namespace
{
    const float Degrees40 = 0.698132f;
}

//---Where the sensors sit. A negative angle is out to the robot's left---
const float CLineFollower::CentreSensorAngle = 0.0f;
const float CLineFollower::CentreSensorReach = 13.0f;
const float CLineFollower::SideSensorAngle = -Degrees40;
const float CLineFollower::SideSensorReach = 15.0f;

//---Control tuning---
const float CLineFollower::SearchTurn = 34.0f;
const float CLineFollower::CorrectingTurn = 30.0f;
const float CLineFollower::CruiseSpeed = 46.0f;

//-----------------------------------------------------------------------------
CLineFollower::CLineFollower( const CPose& arStartPose )
    :
        CRobot( "LineFollower", arStartPose,
                CPalette::LineFollowerBody, CPalette::LineFollowerTrail ),
        mCentreSensor( CentreSensorAngle, CentreSensorReach ),
        mSideSensor( SideSensorAngle, SideSensorReach )
{
}

//-----------------------------------------------------------------------------
void CLineFollower::SenseAndSteer( const CWorld& arWorld )
{
    mCentreSensor.Sense( arWorld, GetPose() );
    mSideSensor.Sense( arWorld, GetPose() );

    const float Turn = ChooseTurn();

    Drive( CruiseSpeed + Turn, CruiseSpeed - Turn );
}

//-----------------------------------------------------------------------------
// The side sensor is mounted to the left, so "the side sensor can see it"
// means the line lies to the left and the robot should turn left, which is a
// negative turn. Losing the line from both sensors means it went the other
// way, so the robot turns right to sweep it back into view.
//-----------------------------------------------------------------------------
float CLineFollower::ChooseTurn() const
{
    const bool CentreOnLine = mCentreSensor.IsOverLine();
    const bool SideOnLine = mSideSensor.IsOverLine();

    float Result = 0.0f;

    if( CentreOnLine )
    {
        //---On the line. Ease left if it is starting to slide that way---
        Result = SideOnLine ? -CorrectingTurn : 0.0f;
    }
    else
    {
        //---Off the line: turn towards wherever it went---
        Result = SideOnLine ? -SearchTurn : SearchTurn;
    }

    return Result;
}

//-----------------------------------------------------------------------------
void CLineFollower::DrawSensors( CRender& arRender ) const
{
    mCentreSensor.Draw( arRender, GetPose() );
    mSideSensor.Draw( arRender, GetPose() );
}
