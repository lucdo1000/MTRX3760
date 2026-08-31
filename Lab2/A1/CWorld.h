//-----------------------------------------------------------------------------
// CWorld.h
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// The room the robot drives around: one closed loop of straight walls, read
// from a map file.
//
// The world answers questions about itself - how far is the wall along this
// ray, how close is the nearest wall to this point - and draws itself. It never
// reaches into a robot. Keeping the queries here rather than in the robot is
// what lets a second kind of robot be added later without the world changing.
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
        // Returns false if the file could not be read, leaving the room empty.
        bool LoadWalls( const std::string& arFilename );

        //---Where the robot begins---
        const CPose& GetWallStartPose() const;

        //---Queries used by the sensors---
        // Distance from arFrom along aHeading to the nearest wall, or
        // CGeometry::NoHit if the ray leaves the room without meeting one.
        float DistanceToWallAlong( const Vec2D& arFrom,
                                   float aHeadingRadians ) const;

        // Shortest distance from arPoint to any wall, used for collisions.
        float DistanceToNearestWall( const Vec2D& arPoint ) const;

        //---Drawing---
        void Draw( CRender& arRender ) const;

    private:
        //---Helpers---
        static void DrawLoop( CRender& arRender,
                              const std::vector<Vec2D>& arVertices,
                              float aThickness, Color aColour );

        //---Tuning---
        static const float WallThickness;

        //---The room---
        std::vector<Vec2D> mWallVertices;
        CPose mWallStartPose;
};

#endif
