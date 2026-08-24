// A clock model, with an alarm clock built by inheritance
//
// This program models a simple clock that keeps a time in minutes and can
// advance, report, and reset it. It also provides an alarm clock, which does
// everything a clock does and additionally holds an alarm time and reports
// whether it is ringing.
//
// The alarm clock here inherits from CClock. CClock itself is unchanged, and
// CAlarmClock adds only the three things a plain clock does not have: an alarm
// time, a way to set it, and a way to ask whether it is ringing. Ticking,
// resetting, reading the time and printing it all come from CClock.
//
// Copyright (c) Donald Dansereau, 2026

//--Includes-------------------------------------------------------------------
#include <iostream>
#include <string>

//---CClock--------------------------------------------------------------------
// A CClock keeps a time, measured in whole minutes, and can advance it one
// minute at a time, report it, and reset it to where it started.
class CClock
{
  public:
    // Creates a clock with the given name and starting time, in minutes
    // since midnight.
    CClock( const std::string& aName, int aStartMinutes );

    // Tick advances the clock by one minute.
    void Tick();

    // GetTime returns the current time, in minutes since midnight.
    int GetTime();

    // Reset returns the clock to its starting time.
    void Reset();

    // Report prints the clock's name and current time as HH:MM.
    void Report();

  private:
    std::string mName;          // the clock's label, e.g. "Kitchen"
    int mStartMinutes;          // the time the clock was initialised to
    int mCurrentMinutes;        // current time, in minutes since midnight
};

//---CAlarmClock---------------------------------------------------------------
// A CAlarmClock is a CClock that also holds an alarm time and reports whether
// the alarm is ringing.
//
// Everything a clock can already do - Tick, GetTime, Reset and Report - is
// inherited from CClock and is not written again here. Only the alarm itself
// is new.
class CAlarmClock : public CClock
{
  public:
    // Creates an alarm clock with the given name, starting time and alarm
    // time, all in minutes since midnight.
    CAlarmClock( const std::string& aName, int aStartMinutes, int aAlarmMinutes );

    // SetAlarm sets the time the alarm should sound, in minutes since midnight.
    void SetAlarm( int aAlarmMinutes );

    // IsRinging reports whether the clock has reached its alarm time.
    bool IsRinging();

  private:
    int mAlarmMinutes;          // the time the alarm should sound
};

//---main----------------------------------------------------------------------
// Creates one plain clock, starts it at 06:59, advances it one minute, and
// reports it. Then creates an alarm clock alongside it, sets its alarm, and
// advances it a minute at a time, reporting the time at each step, until the
// alarm rings.
int main()
{
  CClock clock( "Kitchen", 419 );    // 419 minutes = 06:59
  clock.Tick();
  clock.Report();

  CAlarmClock alarm( "Bedroom", 419, 421 );   // starts 06:59, alarm initially 07:01
  alarm.SetAlarm( 425 );                      // move the alarm later, to 07:05

  // Tick and Report below are inherited from CClock, only SetAlarm and
  // IsRinging are new.
  alarm.Report();

  while( !alarm.IsRinging() )
  {
    alarm.Tick();
    alarm.Report();
  }

  std::cout << "ALARM IS RINGING, WAKEUP!!!" << std::endl;

  return 0;
}

//---CClock Implementation-----------------------------------------------------
CClock::CClock( const std::string& aName, int aStartMinutes )
  : mName( aName ),
    mStartMinutes( aStartMinutes ),
    mCurrentMinutes( aStartMinutes )
{
}
//---
void CClock::Tick()
{
  ++mCurrentMinutes;
}
//---
int CClock::GetTime()
{
  return mCurrentMinutes;
}
//---
void CClock::Reset()
{
  mCurrentMinutes = mStartMinutes;
}
//---
void CClock::Report()
{
  int hours = ( mCurrentMinutes / 60 ) % 24;
  int minutes = mCurrentMinutes % 60;
  std::cout << mName << " "
            << ( hours < 10 ? "0" : "" ) << hours << ":"
            << ( minutes < 10 ? "0" : "" ) << minutes << std::endl;
}

//---CAlarmClock Implementation------------------------------------------------
// CClock has no default constructor, so the base class has to be constructed
// explicitly in the initialiser list. That is what passes the name and start
// time through to the CClock part of this object.
CAlarmClock::CAlarmClock( const std::string& aName, int aStartMinutes, int aAlarmMinutes )
  : CClock( aName, aStartMinutes ),
    mAlarmMinutes( aAlarmMinutes )
{
}
//---
void CAlarmClock::SetAlarm( int aAlarmMinutes )
{
  mAlarmMinutes = aAlarmMinutes;
}
//---
bool CAlarmClock::IsRinging()
{
  // mCurrentMinutes is private to CClock, so a derived class cannot read it
  // directly. The public GetTime() is the supported way in, and using it means
  // CClock did not have to be modified to make this work.
  //
  // Uses >= rather than ==, so the alarm still reports as ringing if the clock
  // is advanced past the alarm time rather than landing exactly on it.
  return GetTime() >= mAlarmMinutes;
}
