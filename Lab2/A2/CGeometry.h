//-----------------------------------------------------------------------------
// CGeometry.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// The geometry the simulator needs, gathered in one place so that no other
// class has to contain trigonometry. Every member is static: CGeometry holds
// no state and is never instantiated, it exists to give these operations a
// home rather than leaving them as loose functions.
//
// COORDINATE CONVENTION
//
// The whole program works in the renderer's space, described at the top of
// CLoopReader.h: x runs left to right, y runs top to bottom, and headings are
// in radians measured clockwise from the positive x axis. So a heading of 0
// faces right, PI/2 faces down the screen, and adding to a heading turns the
// robot to its own right.
//-----------------------------------------------------------------------------

#ifndef CGEOMETRY_H
#define CGEOMETRY_H

#include "CRender.h"   // for Vec2D

//-----------------------------------------------------------------------------
class CGeometry
{
    public:
        //---Constants---
        // Returned by RayHitsSegment when the ray meets nothing. Chosen to be
        // larger than any distance possible inside the window.
        static const float NoHit;

        //---Vector arithmetic---
        static Vec2D Add( const Vec2D& arLeft, const Vec2D& arRight );
        static Vec2D Subtract( const Vec2D& arLeft, const Vec2D& arRight );
        static Vec2D Scale( const Vec2D& arVector, float aFactor );
        static float Length( const Vec2D& arVector );
        static float DistanceBetween( const Vec2D& arFrom, const Vec2D& arTo );

        //---Angles---
        // A unit vector pointing along the given heading.
        static Vec2D UnitVector( float aHeadingRadians );
        // The point reached by travelling aDistance from arOrigin on aHeading.
        static Vec2D PointAlong( const Vec2D& arOrigin, float aHeadingRadians,
                                 float aDistance );
        // Wraps a heading into [0, 2*PI) so it cannot grow without bound.
        static float NormaliseAngle( float aAngleRadians );

        //---Intersection tests---
        // Distance from arOrigin along aHeading to the first crossing of the
        // segment arStart-arEnd, or NoHit if the ray misses it.
        static float RayHitsSegment( const Vec2D& arOrigin, float aHeadingRadians,
                                     const Vec2D& arStart, const Vec2D& arEnd );

        // Shortest distance from arPoint to the segment arStart-arEnd.
        static float DistanceToSegment( const Vec2D& arPoint,
                                        const Vec2D& arStart, const Vec2D& arEnd );

    private:
        //---Not instantiable: this class is a home for operations, not data---
        CGeometry();
};

#endif
