//-----------------------------------------------------------------------------
// CWorld.cpp
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//-----------------------------------------------------------------------------

#include "CWorld.h"
#include "CGeometry.h"
#include "CPalette.h"

const float CWorld::LineWidth = 5.0f;
const float CWorld::WallThickness = 3.0f;

//-----------------------------------------------------------------------------
CWorld::CWorld()
    :
        mWallVertices(),
        mLineVertices(),
        mWallStartPose(),
        mLineStartPose()
{
    //---Until a file is read there is nowhere to start from---
    mWallStartPose.mPosition.x = 0.0f;
    mWallStartPose.mPosition.y = 0.0f;
    mWallStartPose.mHeading = 0.0f;
    mLineStartPose = mWallStartPose;
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
bool CWorld::LoadLine( const std::string& arFilename )
{
    CLoopReader Reader;
    const bool Loaded = Reader.ReadFile( arFilename );

    if( Loaded )
    {
        mLineVertices = Reader.GetVertices();
        mLineStartPose = Reader.GetStartPose();
    }

    return Loaded;
}

//-----------------------------------------------------------------------------
const CPose& CWorld::GetWallStartPose() const
{
    return mWallStartPose;
}

//-----------------------------------------------------------------------------
const CPose& CWorld::GetLineStartPose() const
{
    return mLineStartPose;
}

//-----------------------------------------------------------------------------
// Tests the ray against every wall segment and keeps the nearest crossing.
// The loop is closed, so the last vertex joins back to the first; taking the
// previous vertex as (i + count - 1) % count covers that join without a
// special case for it.
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
// The line has width, so a point is over it when it lies within half that
// width of the centre of any of the line's segments.
//-----------------------------------------------------------------------------
bool CWorld::IsOverLine( const Vec2D& arPoint ) const
{
    bool Result = false;
    const std::size_t Count = mLineVertices.size();
    const float HalfWidth = LineWidth / 2.0f;

    for( std::size_t i = 0; ( i < Count ) && !Result; ++i )
    {
        const Vec2D& rStart = mLineVertices[i];
        const Vec2D& rEnd = mLineVertices[( i + 1 ) % Count];

        const float Distance = CGeometry::DistanceToSegment( arPoint,
                                                             rStart, rEnd );
        Result = ( Distance <= HalfWidth );
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
// The floor line is drawn first so the walls sit on top where they meet.
//-----------------------------------------------------------------------------
void CWorld::Draw( CRender& arRender ) const
{
    DrawLoop( arRender, mLineVertices, LineWidth, CPalette::FloorLine );
    DrawLoop( arRender, mWallVertices, WallThickness, CPalette::Wall );
}
