//-----------------------------------------------------------------------------
// CGeometry.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// Implementation of the shared geometry. See CGeometry.h for the coordinate
// convention these all assume.
//-----------------------------------------------------------------------------

#include "CGeometry.h"

#include <cmath>

//---A ray that meets nothing reports this. Larger than the window diagonal---
const float CGeometry::NoHit = 100000.0f;

namespace
{
    // Denominators smaller than this are treated as zero, which is how the
    // parallel case is detected without comparing floats for equality.
    const float Epsilon = 1.0e-6f;

    const float TwoPi = 6.28318530718f;
}

//-----------------------------------------------------------------------------
Vec2D CGeometry::Add( const Vec2D& arLeft, const Vec2D& arRight )
{
    Vec2D Result = { arLeft.x + arRight.x, arLeft.y + arRight.y };
    return Result;
}

//-----------------------------------------------------------------------------
Vec2D CGeometry::Subtract( const Vec2D& arLeft, const Vec2D& arRight )
{
    Vec2D Result = { arLeft.x - arRight.x, arLeft.y - arRight.y };
    return Result;
}

//-----------------------------------------------------------------------------
Vec2D CGeometry::Scale( const Vec2D& arVector, float aFactor )
{
    Vec2D Result = { arVector.x * aFactor, arVector.y * aFactor };
    return Result;
}

//-----------------------------------------------------------------------------
float CGeometry::Length( const Vec2D& arVector )
{
    float Result = std::sqrt( ( arVector.x * arVector.x )
                            + ( arVector.y * arVector.y ) );
    return Result;
}

//-----------------------------------------------------------------------------
float CGeometry::DistanceBetween( const Vec2D& arFrom, const Vec2D& arTo )
{
    float Result = Length( Subtract( arTo, arFrom ) );
    return Result;
}

//-----------------------------------------------------------------------------
Vec2D CGeometry::UnitVector( float aHeadingRadians )
{
    Vec2D Result = { std::cos( aHeadingRadians ), std::sin( aHeadingRadians ) };
    return Result;
}

//-----------------------------------------------------------------------------
Vec2D CGeometry::PointAlong( const Vec2D& arOrigin, float aHeadingRadians,
                             float aDistance )
{
    Vec2D Result = Add( arOrigin,
                        Scale( UnitVector( aHeadingRadians ), aDistance ) );
    return Result;
}

//-----------------------------------------------------------------------------
float CGeometry::NormaliseAngle( float aAngleRadians )
{
    float Result = std::fmod( aAngleRadians, TwoPi );

    if( Result < 0.0f )
    {
        Result += TwoPi;
    }

    return Result;
}

//-----------------------------------------------------------------------------
// Solves Origin + t*Direction = Start + u*(End - Start) for t and u.
//
// Writing D for the ray direction, E for the segment vector and F for
// (Start - Origin), the two component equations are
//
//     t*D.x - u*E.x = F.x
//     t*D.y - u*E.y = F.y
//
// which Cramer's rule solves directly. The ray hits the segment when t is not
// behind the origin and u lands between the segment's two ends. Because D is a
// unit vector, t is the distance travelled.
//-----------------------------------------------------------------------------
float CGeometry::RayHitsSegment( const Vec2D& arOrigin, float aHeadingRadians,
                                 const Vec2D& arStart, const Vec2D& arEnd )
{
    float Result = NoHit;

    const Vec2D Direction = UnitVector( aHeadingRadians );
    const Vec2D Edge = Subtract( arEnd, arStart );
    const Vec2D ToStart = Subtract( arStart, arOrigin );

    const float Determinant = ( Edge.x * Direction.y ) - ( Direction.x * Edge.y );

    //---A determinant of zero means the ray and the segment are parallel---
    if( std::fabs( Determinant ) > Epsilon )
    {
        const float AlongRay = ( ( Edge.x * ToStart.y )
                               - ( ToStart.x * Edge.y ) ) / Determinant;
        const float AlongSegment = ( ( Direction.x * ToStart.y )
                                   - ( ToStart.x * Direction.y ) ) / Determinant;

        const bool InFront = ( AlongRay >= 0.0f );
        const bool WithinSegment = ( AlongSegment >= 0.0f )
                                && ( AlongSegment <= 1.0f );

        if( InFront && WithinSegment )
        {
            Result = AlongRay;
        }
    }

    return Result;
}

//-----------------------------------------------------------------------------
// Projects the point onto the infinite line through the segment, then clamps
// that projection to the segment itself, so that points beyond either end
// measure to the nearer end rather than to empty space.
//-----------------------------------------------------------------------------
float CGeometry::DistanceToSegment( const Vec2D& arPoint,
                                    const Vec2D& arStart, const Vec2D& arEnd )
{
    const Vec2D Edge = Subtract( arEnd, arStart );
    const float EdgeLengthSquared = ( Edge.x * Edge.x ) + ( Edge.y * Edge.y );

    float Result = 0.0f;

    //---A zero-length segment is just a point---
    if( EdgeLengthSquared < Epsilon )
    {
        Result = DistanceBetween( arPoint, arStart );
    }
    else
    {
        const Vec2D ToPoint = Subtract( arPoint, arStart );
        float Projection = ( ( ToPoint.x * Edge.x ) + ( ToPoint.y * Edge.y ) )
                         / EdgeLengthSquared;

        if( Projection < 0.0f )
        {
            Projection = 0.0f;
        }
        else if( Projection > 1.0f )
        {
            Projection = 1.0f;
        }

        const Vec2D Closest = Add( arStart, Scale( Edge, Projection ) );
        Result = DistanceBetween( arPoint, Closest );
    }

    return Result;
}
