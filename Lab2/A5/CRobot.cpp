//-----------------------------------------------------------------------------
// CRobot.cpp
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CRobot.h"
#include "CNoise.h"
#include "CWorld.h"
#include "CGeometry.h"
#include "CPalette.h"

#include <iomanip>
#include <iostream>
#include <sstream>

//---The handout fixes the body radius at 15 units---
const float CRobot::BodyRadius = 15.0f;
const float CRobot::WheelOffset = 10.0f;
const float CRobot::HeadingLineScale = 1.4f;
const float CRobot::TrailThickness = 1.5f;
const float CRobot::LapDepartureDistance = 150.0f;
const float CRobot::LapReturnDistance = 45.0f;

//-----------------------------------------------------------------------------
CRobot::CRobot( const std::string& arKind, int aIndex, const CPose& arStartPose,
                Color aBodyColour, Color aTrailColour, CNoise& arNoise )
    :
        mKind( arKind ),
        mName( MakeName( arKind, aIndex ) ),
        mPose( arStartPose ),
        mLeftWheel( -WheelOffset, arNoise ),   // negative: to the robot's left
        mRightWheel( WheelOffset, arNoise ),
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
// "WallFollower 07": the kind, then the index padded so the names line up in
// the console.
//-----------------------------------------------------------------------------
std::string CRobot::MakeName( const std::string& arKind, int aIndex )
{
    std::ostringstream Name;

    Name << arKind << " " << std::setw( 2 ) << std::setfill( '0' ) << aIndex;

    return Name.str();
}

//-----------------------------------------------------------------------------
const std::string& CRobot::GetKind() const
{
    return mKind;
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
//
// A robot that has finished its lap parks. With forty robots running, the
// quick ones would otherwise keep circling while the slow ones finish, and the
// screenshot would show two or three laps for some and one for others.
//-----------------------------------------------------------------------------
void CRobot::Update( const CWorld& arWorld, CNoise& arNoise, float aDeltaTime )
{
    if( !mLapComplete )
    {
        SenseAndSteer( arWorld );
        AdvancePose( arNoise, aDeltaTime );

        mTrail.AddPoint( mPose.mPosition );

        CheckForCollision( arWorld );
        CheckForLapCompletion();
    }
}

//-----------------------------------------------------------------------------
// Differential drive, written in distances rather than speeds because the
// wheels now report how far they actually went this step, slip included:
//
//     forward = (left + right) / 2
//     turn    = (left - right) / (distance between the wheels)
//
// The wheels supply their own offsets, so the separation is asked for rather
// than assumed. A positive turn increases the heading, and because headings
// run clockwise from the positive x axis, that swings the robot to its own
// right - which is what the left wheel covering more ground does.
//-----------------------------------------------------------------------------
void CRobot::AdvancePose( CNoise& arNoise, float aDeltaTime )
{
    const float LeftTravel = mLeftWheel.Travel( aDeltaTime, arNoise );
    const float RightTravel = mRightWheel.Travel( aDeltaTime, arNoise );
    const float WheelSeparation = mRightWheel.GetLateralOffset()
                                - mLeftWheel.GetLateralOffset();

    const float Forward = ( LeftTravel + RightTravel ) / 2.0f;
    const float Turn = ( LeftTravel - RightTravel ) / WheelSeparation;

    mPose.mHeading = CGeometry::NormaliseAngle( mPose.mHeading + Turn );
    mPose.mPosition = CGeometry::PointAlong( mPose.mPosition, mPose.mHeading,
                                             Forward );
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
