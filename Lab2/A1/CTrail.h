//-----------------------------------------------------------------------------
// CTrail.h
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// The path a robot has driven, kept so it can be drawn behind the robot for
// the whole run.
//
// Points are only recorded once the robot has moved a little way from the last
// one. Recording every update would store sixty points a second, nearly all of
// them too close together to see, so the spacing keeps the trail the same
// shape for a fraction of the memory.
//-----------------------------------------------------------------------------

#ifndef CTRAIL_H
#define CTRAIL_H

#include "CRender.h"

#include <vector>

//-----------------------------------------------------------------------------
class CTrail
{
    public:
        //---Ctor---
        CTrail( float aThickness, Color aColour );

        //---Recording---
        void AddPoint( const Vec2D& arPoint );
        void Clear();

        //---Drawing---
        void Draw( CRender& arRender ) const;

    private:
        //---Tuning---
        // Two consecutive points closer together than this are not worth
        // storing separately.
        static const float MinimumSpacing;

        //---State---
        std::vector<Vec2D> mPoints;
        const float mThickness;
        const Color mColour;
};

#endif
