
// CWheel.cpp
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID 530838753
// Practical section: Practical Session 2
//

#include "CWheel.h"
#include "CNoise.h"

const float CWheel::SizeErrorSpread = 0.08f;
const float CWheel::SlipSpread = 0.08f;

CWheel::CWheel( float aLateralOffset, CNoise& arNoise )
    :
        mSpeed( 0.0f ),
        mLateralOffset( aLateralOffset ),
        mSizeError( arNoise.Uniform( SizeErrorSpread ) )
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

// Commanded travel, scaled by (1 + size error + slip). The size error is the
// same every step, so it pulls the robot steadily to one side and the
// controller settles a little off its ideal line; the slip is drawn fresh
// every step, so it only makes the path wobble.

float CWheel::Travel( float aDeltaTime, CNoise& arNoise ) const
{
    const float Commanded = mSpeed * aDeltaTime;
    const float Slip = arNoise.Uniform( SlipSpread );

    return Commanded * ( 1.0f + mSizeError + Slip );
}

float CWheel::GetLateralOffset() const
{
    return mLateralOffset;
}
