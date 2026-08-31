//-----------------------------------------------------------------------------
// CWorld.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CWorld.h"
#include "CGeometry.h"
#include "CPalette.h"

const float CWorld::WallThickness = 3.0f;

//-----------------------------------------------------------------------------
CWorld::CWorld()
    :
        mWallVertices(),
        mWallStartPose()
{
    //---Until a file is read there is nowhere to start from---
    mWallStartPose.mPosition.x = 0.0f;
    mWallStartPose.mPosition.y = 0.0f;
    mWallStartPose.mHeading = 0.0f;
}

//-----------------------------------------------------------------------------
bool CWorld::LoadWalls( const std::string& arFilename )
{
    CLoopReader Reader;
    const bool Loaded = Reader.ReadFile( arFilename );

    if( Loaded )
    {
        mWallVertices = Reader.GetVertices();
        mWallStartPose = Reader.GetStartPose();
    }

    return Loaded;
}

//-----------------------------------------------------------------------------
const CPose& CWorld::GetWallStartPose() const
{
    return mWallStartPose;
}

//-----------------------------------------------------------------------------
// Tests the ray against every wall segment and keeps the nearest crossing.
// The loop is closed, so the last vertex joins back to the first; taking the
// next vertex as (i + 1) % count covers that join without a special case.
//-----------------------------------------------------------------------------
float CWorld::DistanceToWallAlong( const Vec2D& arFrom,
                                   float aHeadingRadians ) const
{
    float Result = CGeometry::NoHit;
    const std::size_t Count = mWallVertices.size();

    for( std::size_t i = 0; i < Count; ++i )
    {
        const Vec2D& rStart = mWallVertices[i];
        const Vec2D& rEnd = mWallVertices[( i + 1 ) % Count];

        const float Hit = CGeometry::RayHitsSegment( arFrom, aHeadingRadians,
                                                     rStart, rEnd );

        if( Hit < Result )
        {
            Result = Hit;
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
float CWorld::DistanceToNearestWall( const Vec2D& arPoint ) const
{
    float Result = CGeometry::NoHit;
    const std::size_t Count = mWallVertices.size();

    for( std::size_t i = 0; i < Count; ++i )
    {
        const Vec2D& rStart = mWallVertices[i];
        const Vec2D& rEnd = mWallVertices[( i + 1 ) % Count];

        const float Distance = CGeometry::DistanceToSegment( arPoint,
                                                             rStart, rEnd );

        if( Distance < Result )
        {
            Result = Distance;
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
void CWorld::DrawLoop( CRender& arRender, const std::vector<Vec2D>& arVertices,
                       float aThickness, Color aColour )
{
    const std::size_t Count = arVertices.size();

    for( std::size_t i = 0; i < Count; ++i )
    {
        arRender.DrawLine( arVertices[i], arVertices[( i + 1 ) % Count],
                           aThickness, aColour );
    }
}

//-----------------------------------------------------------------------------
void CWorld::Draw( CRender& arRender ) const
{
    DrawLoop( arRender, mWallVertices, WallThickness, CPalette::Wall );
}
