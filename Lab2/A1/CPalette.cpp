//-----------------------------------------------------------------------------
// CPalette.cpp
//
// MTRX3760 Lab 2 - A1, Wall Follower
// Written by SID 540700701 and SID <PARTNER SID>
// Practical section: <SECTION>
//
//
// The colour values themselves. Written as explicit red/green/blue/alpha
// quadruples rather than raylib's own named constants, so the palette reads
// the same whatever the underlying library calls its colours.
//-----------------------------------------------------------------------------

#include "CPalette.h"

//---The world---
const Color CPalette::Wall              = { 200, 200, 200, 255 };  // light grey

//---The wall following robot---
const Color CPalette::WallFollowerBody  = {  80, 180, 255, 255 };  // blue
const Color CPalette::WallFollowerTrail = {  30,  90, 140, 255 };  // dim blue

//---Shared robot details---
const Color CPalette::Heading           = { 255, 255, 255, 255 };  // white
const Color CPalette::SensorBeam        = {  70,  70,  70, 255 };  // faint grey
const Color CPalette::SensorHit         = { 255,  80,  80, 255 };  // red
