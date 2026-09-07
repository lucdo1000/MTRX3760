// CSensor.cpp
//
// Shared sensor placement logic: the mount angle and distance define where the
// sensor sits on the robot and which way it looks.

#include "CSensor.h"
#include "CGeometry.h"

CSensor::CSensor( float aMountAngleRadians, float aMountDistance )
    :
        mMountAngle( aMountAngleRadians ),
        mMountDistance( aMountDistance )
{
}

CSensor::~CSensor()
{
}

// The mounting angle is relative to the robot, so the sensor's own heading is
// the robot's heading plus that offset.
float CSensor::HeadingFor( const CPose& arRobotPose ) const
{
    float Result = CGeometry::NormaliseAngle( arRobotPose.mHeading + mMountAngle );
    return Result;
}

Vec2D CSensor::PositionFor( const CPose& arRobotPose ) const
{
    Vec2D Result = CGeometry::PointAlong( arRobotPose.mPosition,
                                          HeadingFor( arRobotPose ),
                                          mMountDistance );
    return Result;
}
