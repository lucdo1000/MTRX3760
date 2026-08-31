//-----------------------------------------------------------------------------
// CTrail.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CTrail.h"
#include "CGeometry.h"

//---Points closer than this are merged into the previous one---
const float CTrail::MinimumSpacing = 2.0f;

//-----------------------------------------------------------------------------
CTrail::CTrail( float aThickness, Color aColour )
    :
        mPoints(),
        mThickness( aThickness ),
        mColour( aColour )
{
}

//-----------------------------------------------------------------------------
void CTrail::AddPoint( const Vec2D& arPoint )
{
    bool WorthKeeping = true;

    if( !mPoints.empty() )
    {
        const float Moved = CGeometry::DistanceBetween( mPoints.back(), arPoint );
        WorthKeeping = ( Moved >= MinimumSpacing );
    }

    if( WorthKeeping )
    {
        mPoints.push_back( arPoint );
    }
}

//-----------------------------------------------------------------------------
void CTrail::Clear()
{
    mPoints.clear();
}

//-----------------------------------------------------------------------------
// Drawn as a run of short straight segments joining consecutive points, which
// reads as a smooth curve at this spacing.
//-----------------------------------------------------------------------------
void CTrail::Draw( CRender& arRender ) const
{
    for( std::size_t i = 1; i < mPoints.size(); ++i )
    {
        arRender.DrawLine( mPoints[i - 1], mPoints[i], mThickness, mColour );
    }
}
