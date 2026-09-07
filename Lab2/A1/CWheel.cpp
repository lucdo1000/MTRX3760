// CWheel.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//

#include "CWheel.h"

CWheel::CWheel( float aLateralOffset )
    :
        mSpeed( 0.0f ),
        mLateralOffset( aLateralOffset )
{
}

void CWheel::SetSpeed( float aSpeed )
{
    // The simulator sends wheel speeds in units per second, and the robot uses
    // the left/right difference to work out both forward motion and turn rate.
    mSpeed = aSpeed;
}

float CWheel::GetSpeed() const
{
    return mSpeed;
}

float CWheel::GetLateralOffset() const
{
    return mLateralOffset;
}
