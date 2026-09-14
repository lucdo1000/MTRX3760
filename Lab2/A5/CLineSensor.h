
// CLineSensor.h
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID 530838753
// Practical section: Practical Session 2
//
//
// A sensor that reports only whether the floor directly beneath it is painted
// line or bare floor. This is what the line following robot steers by.
//
// It is deliberately a single yes or no, matching the handout: the robot has to
// find its way around the loop from two bits of information, which is what
// makes the control interesting.

#ifndef CLINESENSOR_H
#define CLINESENSOR_H

#include "CSensor.h"

class CWorld;

class CLineSensor : public CSensor
{
    public:
        //---Ctor---
        CLineSensor( float aMountAngleRadians, float aMountDistance );

        //---Sensing---
        void Sense( const CWorld& arWorld, const CPose& arRobotPose );

        //---The reading, from the last call to Sense---
        bool IsOverLine() const;

        //---Drawing---
        void Draw( CRender& arRender, const CPose& arRobotPose ) const;

    private:
        //---Tuning---
        static const int MarkerRadius;

        //---State---
        bool mOverLine;
};

#endif
