// $Id$
//*************************************************************************
//* --------------------
//* J4Timer
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#ifdef __USEISOCXX__
#include <sstream>
#else
#include <sstream>
#endif
#include <iomanip>

#include "J4Timer.hh"

#define __NMAXTIMERS__ 100000

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

J4Timer::J4TimerArray J4Timer::fgTimers(__NMAXTIMERS__);
G4int                 J4Timer::fgNtimers = 0;

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4Timer::J4Timer(G4int          &timerid, 
                 const G4String &classname, 
                 const G4String &timername)
        : G4Timer(), fCurrentTimer(0)
{
          
   if (fgNtimers > (G4int)fgTimers.entries()) {
      abort();
   } 

   if (timerid == -1) {
      AccumulatedTime *timer = new AccumulatedTime(fgNtimers,
                                                   classname,
                                                   timername);
      fgTimers.append(timer);
      timerid = fgNtimers;
      fgNtimers ++;
      std::cerr << "J4Timer::New timer is created! timerID, name = "
      << timerid << " " << classname << " " << timername << std::endl;
   } 
   
   fCurrentTimer = fgTimers[timerid];
   
}

// ====================================================================
//* destructor --------------------------------------------------------
J4Timer::~J4Timer()
{	
}

// ====================================================================
//* ResetAllTimers ----------------------------------------------------
void J4Timer::ResetAllTimers()
{
   for (G4int i=0; i<fgNtimers; i++) {
      if (fgTimers[i]) {
         fgTimers[i]->ResetTimes();
      }
   }
}

// ====================================================================
//* PrintAllAccumulatedTimes ------------------------------------------
void J4Timer::PrintAllAccumulatedTimes()
{
   std::cerr.precision(6);
   std::cerr << " *********************************************************************************" << std::endl;
   std::cerr << " * Output of Accumulated Time ****************************************************" << std::endl;
   std::cerr << " * ---------+---------+---------+---------+---------+---------+---------+---------" << std::endl;
   std::cerr << " * Timer Name                                   Real[s]   System[s]     User[s]" << std::endl;
   std::cerr << " * ---------+---------+---------+---------+---------+---------+---------+---------" << std::endl;
   
   for (G4int i=0; i<fgNtimers; i++) {
      if (fgTimers[i]) {
         AccumulatedTime *timer = fgTimers[i];
#ifdef __USEISOCXX__
         std::stringstream name;
         name << timer->GetClassName() << ":" << timer->GetTimerName();
         std::cerr << " * " << std::setw(40) << name.str()
                << std::setw(12) <<  timer->GetAccumulatedRealElapsed()
                << std::setw(12) <<  timer->GetAccumulatedSystemElapsed()
                << std::setw(12) <<  timer->GetAccumulatedUserElapsed() << std::endl;
#else
         char buf[1024];
         std::strstream name(buf, 1024);
         name << timer->GetClassName() << ":" << timer->GetTimerName() << std::ends;
         std::cerr << " * " << std::setw(40) << buf 
                << std::setw(12) <<  timer->GetAccumulatedRealElapsed()
                << std::setw(12) <<  timer->GetAccumulatedSystemElapsed()
                << std::setw(12) <<  timer->GetAccumulatedUserElapsed() << std::endl;
#endif
      }
   }
   std::cerr << " *********************************************************************************" << std::endl;
}

