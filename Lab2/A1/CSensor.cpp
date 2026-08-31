//-----------------------------------------------------------------------------
// CSensor.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CSensor.h"
#include "CGeometry.h"

//-----------------------------------------------------------------------------
CSensor::CSensor( float aMountAngleRadians, float aMountDistance )
    :
        mMountAngle( aMountAngleRadians ),
        mMountDistance( aMountDistance )
{
}

//-----------------------------------------------------------------------------
CSensor::~CSensor()
{
}

//-----------------------------------------------------------------------------
// The mounting angle is relative to the robot, so the sensor's own heading is
// the robot's heading plus that offset.
//-----------------------------------------------------------------------------
float CSensor::HeadingFor( const CPose& arRobotPose ) const
{
    float Result = CGeometry::NormaliseAngle( arRobotPose.mHeading + mMountAngle );
    return Result;
}

//-----------------------------------------------------------------------------
Vec2D CSensor::PositionFor( const CPose& arRobotPose ) const
{
    Vec2D Result = CGeometry::PointAlong( arRobotPose.mPosition,
                                          HeadingFor( arRobotPose ),
                                          mMountDistance );
    return Result;
}
