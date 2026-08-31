//-----------------------------------------------------------------------------
// CRangeSensor.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CRangeSensor.h"
#include "CWorld.h"
#include "CGeometry.h"
#include "CPalette.h"

//---Beyond this the sensor reports "nothing there" rather than a distance---
const float CRangeSensor::MaxRange = 250.0f;

//-----------------------------------------------------------------------------
CRangeSensor::CRangeSensor( float aMountAngleRadians, float aMountDistance )
    :
        CSensor( aMountAngleRadians, aMountDistance ),
        mDistance( MaxRange )
{
}

//-----------------------------------------------------------------------------
float CRangeSensor::GetMaxRange()
{
    return MaxRange;
}

//-----------------------------------------------------------------------------
void CRangeSensor::Sense( const CWorld& arWorld, const CPose& arRobotPose )
{
    const float Raw = arWorld.DistanceToWallAlong( PositionFor( arRobotPose ),
                                                   HeadingFor( arRobotPose ) );

    mDistance = ( Raw > MaxRange ) ? MaxRange : Raw;
}

//-----------------------------------------------------------------------------
float CRangeSensor::GetDistance() const
{
    return mDistance;
}

//-----------------------------------------------------------------------------
bool CRangeSensor::IsAtMaxRange() const
{
    return ( mDistance >= MaxRange );
}

//-----------------------------------------------------------------------------
// Drawn as a beam from the sensor to whatever it found, with a dot at the far
// end when that is a real wall. Seeing the beams is the quickest way to tell
// whether a steering problem is the controller or the sensing.
//-----------------------------------------------------------------------------
void CRangeSensor::Draw( CRender& arRender, const CPose& arRobotPose ) const
{
    const Vec2D Origin = PositionFor( arRobotPose );
    const Vec2D Far = CGeometry::PointAlong( Origin, HeadingFor( arRobotPose ),
                                             mDistance );

    arRender.DrawLine( Origin, Far, 1.0f, CPalette::SensorBeam );

    if( !IsAtMaxRange() )
    {
        arRender.DrawCircle( Far, 2, CPalette::SensorHit );
    }
}
