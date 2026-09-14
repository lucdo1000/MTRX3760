
// CNoise.cpp
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID 530838753
// Practical section: Practical Session 2
//

#include "CNoise.h"

const unsigned int CNoise::DefaultSeed = 3760u;

CNoise::CNoise( unsigned int aSeed )
    :
        mEngine( aSeed ),
        mUnit( -1.0f, 1.0f )
{
}

// The distribution hands out [-1, 1); scaling that by the spread gives the
// range the caller asked for without a second distribution per call site.

float CNoise::Uniform( float aSpread )
{
    return mUnit( mEngine ) * aSpread;
}
