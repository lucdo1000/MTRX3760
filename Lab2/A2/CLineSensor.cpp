//-----------------------------------------------------------------------------
// CLineSensor.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CLineSensor.h"
#include "CWorld.h"
#include "CPalette.h"

const int CLineSensor::MarkerRadius = 3;

//-----------------------------------------------------------------------------
CLineSensor::CLineSensor( float aMountAngleRadians, float aMountDistance )
    :
        CSensor( aMountAngleRadians, aMountDistance ),
        mOverLine( false )
{
}

//-----------------------------------------------------------------------------
void CLineSensor::Sense( const CWorld& arWorld, const CPose& arRobotPose )
{
    mOverLine = arWorld.IsOverLine( PositionFor( arRobotPose ) );
}

//-----------------------------------------------------------------------------
bool CLineSensor::IsOverLine() const
{
    return mOverLine;
}

//-----------------------------------------------------------------------------
// A dot at the sensor's position, lit when it is over the line. Watching the
// two dots is how you tell a steering bug from a sensing bug.
//-----------------------------------------------------------------------------
void CLineSensor::Draw( CRender& arRender, const CPose& arRobotPose ) const
{
    const Color Shade = mOverLine ? CPalette::SensorHit : CPalette::SensorBeam;
    arRender.DrawCircle( PositionFor( arRobotPose ), MarkerRadius, Shade );
}
