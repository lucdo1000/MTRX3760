//-----------------------------------------------------------------------------
// CWorld.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// Everything the robots drive around in: the walls of the room and the line
// marked on the floor.
//
// CLoopReader reads one loop from one file, so the world owns two of them and
// keeps the two loops apart. Both are closed loops of straight segments, but
// they mean different things - a wall is something to be sensed at a distance
// and collided with, a line is something to be detected underfoot - so they are
// asked about through separate queries rather than being treated alike.
//
// The world answers questions about itself; it never reaches into a robot.
//-----------------------------------------------------------------------------

#ifndef CWORLD_H
#define CWORLD_H

#include "CLoopReader.h"
#include "CRender.h"

#include <string>
#include <vector>

//-----------------------------------------------------------------------------
class CWorld
{
    public:
        //---Ctor---
        CWorld();

        //---Loading---
        // Each returns false if the file could not be read, leaving that part
        // of the world empty.
        bool LoadWalls( const std::string& arFilename );
        bool LoadLine( const std::string& arFilename );

        //---Where the robots begin---
        const CPose& GetWallStartPose() const;
        const CPose& GetLineStartPose() const;

        //---Queries used by the sensors---
        // Distance from arFrom along aHeading to the nearest wall, or
        // CGeometry::NoHit if the ray leaves the room without meeting one.
        float DistanceToWallAlong( const Vec2D& arFrom,
                                   float aHeadingRadians ) const;

        // Shortest distance from arPoint to any wall, used for collisions.
        float DistanceToNearestWall( const Vec2D& arPoint ) const;

        // True when arPoint lies on the painted floor line.
        bool IsOverLine( const Vec2D& arPoint ) const;

        //---Drawing---
        void Draw( CRender& arRender ) const;

    private:
        //---Helpers---
        // Draws one closed loop of vertices as a run of segments.
        static void DrawLoop( CRender& arRender,
                              const std::vector<Vec2D>& arVertices,
                              float aThickness, Color aColour );

        //---Tuning---
        // The painted line is this wide, so a point within half of that is
        // over it.
        static const float LineWidth;
        static const float WallThickness;

        //---The two loops---
        std::vector<Vec2D> mWallVertices;
        std::vector<Vec2D> mLineVertices;
        CPose mWallStartPose;
        CPose mLineStartPose;
};

#endif
