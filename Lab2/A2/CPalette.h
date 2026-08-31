//-----------------------------------------------------------------------------
// CPalette.h
//
// MTRX3760 Lab 2 - A2, Wall Follower and Line Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// Every colour the simulator draws with, named and gathered in one place.
//
// CRender::DrawCircle and CRender::DrawLine take a raylib Color, so that one
// raylib type does reach the rest of the program despite the wrapper's intent.
// Confining every colour to this class means there is exactly one file to
// change if that leak is ever closed, and it keeps raw colour values out of
// the drawing code.
//-----------------------------------------------------------------------------

#ifndef CPALETTE_H
#define CPALETTE_H

#include "CRender.h"   // for Color

//-----------------------------------------------------------------------------
class CPalette
{
    public:
        //---The world---
        static const Color Wall;
        static const Color FloorLine;

        //---The wall following robot and its marks---
        static const Color WallFollowerBody;
        static const Color WallFollowerTrail;

        //---The line following robot and its marks---
        static const Color LineFollowerBody;
        static const Color LineFollowerTrail;

        //---Shared robot details---
        static const Color Heading;
        static const Color SensorBeam;
        static const Color SensorHit;

    private:
        //---Not instantiable: this class is a home for constants, not data---
        CPalette();
};

#endif
