
// CNoise.h
//
// MTRX3760 Lab 2 - A5, Noise Bonus
// Written by SID 540700701 and SID 530838753
// Practical section: Practical Session 2
//
//
// The simulation's one source of randomness.
//
// Every random number the program uses comes out of this class, so the rest
// of the program never touches an engine or a distribution directly - the same
// idea as CRender hiding raylib. It also means there is exactly one seed, set
// in one place, and a run can be repeated by keeping it: the screenshot in the
// report is reproducible, not a one-off.
//
// The only operation offered is a uniform draw in [-spread, +spread]. That is
// all the noise in this lab needs, and keeping the interface that small keeps
// the callers honest about what they are asking for.

#ifndef CNOISE_H
#define CNOISE_H

#include <random>

class CNoise
{
    public:
        //---Ctor---
        // Every run seeded the same way produces the same numbers.
        explicit CNoise( unsigned int aSeed = DefaultSeed );

        //---Drawing numbers---
        // A value drawn uniformly from [-aSpread, +aSpread].
        float Uniform( float aSpread );

        //---Tuning---
        // Fixed so that a run is repeatable. Change it to see a different
        // fleet; seed from the clock to see a new one every run.
        static const unsigned int DefaultSeed;

    private:
        //---State---
        std::mt19937 mEngine;                             // the generator
        std::uniform_real_distribution<float> mUnit;      // draws in [-1, 1)
};

#endif
