//-----------------------------------------------------------------------------
// CRobot.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CWorld.h"
#include "CGeometry.h"
#include "CPalette.h"

#include <iostream>

//---The handout fixes the body radius at 15 units---
const float CRobot::BodyRadius = 15.0f;
const float CRobot::WheelOffset = 10.0f;
const float CRobot::HeadingLineScale = 1.4f;
const float CRobot::TrailThickness = 1.5f;
const float CRobot::LapDepartureDistance = 150.0f;
const float CRobot::LapReturnDistance = 30.0f;

//-----------------------------------------------------------------------------
CRobot::CRobot( const std::string& arName, const CPose& arStartPose,
                Color aBodyColour, Color aTrailColour )
    :
        mName( arName ),
        mPose( arStartPose ),
        mLeftWheel( -WheelOffset ),   // negative offset: out to the robot's left
        mRightWheel( WheelOffset ),
        mTrail( TrailThickness, aTrailColour ),
        mBodyColour( aBodyColour ),
        mStartPosition( arStartPose.mPosition ),
        mHasLeftStart( false ),
        mLapComplete( false ),
        mCollisionCount( 0 ),
        mWasColliding( false )
{
    mTrail.AddPoint( mPose.mPosition );
}

//-----------------------------------------------------------------------------
CRobot::~CRobot()
{
}

//-----------------------------------------------------------------------------
float CRobot::GetBodyRadius()
{
    return BodyRadius;
}

//-----------------------------------------------------------------------------
const std::string& CRobot::GetName() const
{
    return mName;
}

//-----------------------------------------------------------------------------
const CPose& CRobot::GetPose() const
{
    return mPose;
}

//-----------------------------------------------------------------------------
int CRobot::GetCollisionCount() const
{
    return mCollisionCount;
}

//-----------------------------------------------------------------------------
bool CRobot::HasCompletedLap() const
{
    return mLapComplete;
}

//-----------------------------------------------------------------------------
void CRobot::Drive( float aLeftSpeed, float aRightSpeed )
{
    mLeftWheel.SetSpeed( aLeftSpeed );
    mRightWheel.SetSpeed( aRightSpeed );
}

//-----------------------------------------------------------------------------
// One slice of simulated time: sense and decide, then move, then take note of
// what moving caused. The order matters - steering is decided from where the
// robot was, which is what a real control loop does.
//-----------------------------------------------------------------------------
void CRobot::Update( const CWorld& arWorld, float aDeltaTime )
{
    SenseAndSteer( arWorld );
    AdvancePose( aDeltaTime );

    mTrail.AddPoint( mPose.mPosition );

    CheckForCollision( arWorld );
    CheckForLapCompletion();
}

//-----------------------------------------------------------------------------
// Differential drive. The robot's forward speed is the average of its two
// wheels, and it turns because they differ:
//
//     forward = (left + right) / 2
//     turn    = (left - right) / (distance between the wheels)
//
// The wheels supply their own offsets, so the separation is asked for rather
// than assumed. A positive turn rate increases the heading, and because
// headings run clockwise from the positive x axis, that swings the robot to
// its own right - which is what driving the left wheel faster does.
//-----------------------------------------------------------------------------
void CRobot::AdvancePose( float aDeltaTime )
{
    const float LeftSpeed = mLeftWheel.GetSpeed();
    const float RightSpeed = mRightWheel.GetSpeed();
    const float WheelSeparation = mRightWheel.GetLateralOffset()
                                - mLeftWheel.GetLateralOffset();

    const float ForwardSpeed = ( LeftSpeed + RightSpeed ) / 2.0f;
    const float TurnRate = ( LeftSpeed - RightSpeed ) / WheelSeparation;

    mPose.mHeading = CGeometry::NormaliseAngle( mPose.mHeading
                                              + ( TurnRate * aDeltaTime ) );
    mPose.mPosition = CGeometry::PointAlong( mPose.mPosition, mPose.mHeading,
                                             ForwardSpeed * aDeltaTime );
}

//-----------------------------------------------------------------------------
// The robot is a disc, so it is touching a wall when its centre is within one
// body radius of that wall. mWasColliding makes a single scrape along a wall
// count once rather than once per update.
//-----------------------------------------------------------------------------
void CRobot::CheckForCollision( const CWorld& arWorld )
{
    const float ToWall = arWorld.DistanceToNearestWall( mPose.mPosition );
    const bool Touching = ( ToWall < BodyRadius );

    if( Touching && !mWasColliding )
    {
        ++mCollisionCount;
        std::cout << "Collision: " << mName << " hit a wall at ("
                  << mPose.mPosition.x << ", " << mPose.mPosition.y
                  << "), collision number " << mCollisionCount << std::endl;
    }

    mWasColliding = Touching;
}

//-----------------------------------------------------------------------------
// A lap is counted once the robot has been well away from where it started and
// has then come back near it. Requiring the departure first is what stops the
// first few updates from registering as a completed lap.
//-----------------------------------------------------------------------------
void CRobot::CheckForLapCompletion()
{
    const float FromStart = CGeometry::DistanceBetween( mPose.mPosition,
                                                        mStartPosition );

    if( FromStart > LapDepartureDistance )
    {
        mHasLeftStart = true;
    }
    else if( mHasLeftStart && ( FromStart < LapReturnDistance ) )
    {
        mLapComplete = true;
    }
}

//-----------------------------------------------------------------------------
// Trail first so the robot sits on top of its own path, then the body, then a
// line showing which way it faces, then whatever sensors it carries.
//-----------------------------------------------------------------------------
void CRobot::Draw( CRender& arRender ) const
{
    mTrail.Draw( arRender );

    arRender.DrawCircle( mPose.mPosition, static_cast<int>( BodyRadius ),
                         mBodyColour );

    const Vec2D Nose = CGeometry::PointAlong( mPose.mPosition, mPose.mHeading,
                                              BodyRadius * HeadingLineScale );
    arRender.DrawLine( mPose.mPosition, Nose, 2.0f, CPalette::Heading );

    DrawSensors( arRender );
}
