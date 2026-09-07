// CWheel.cpp
//
// The wheel object keeps the per-wheel speed and offset separate from the robot
// itself, which is what makes the differential-drive math easy to follow.

#include "CWheel.h"

CWheel::CWheel( float aLateralOffset )
    :
        mSpeed( 0.0f ),
        mLateralOffset( aLateralOffset )
{
}

void CWheel::SetSpeed( float aSpeed )
{
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
