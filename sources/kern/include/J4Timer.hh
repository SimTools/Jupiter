// $Id$
#ifndef __J4TIMER__
#define __J4TIMER__
//*************************************************************************
//* -----------------------
//* J4Timer
//* -----------------------
//* (Description)
//*   Timer class for JUPITER.
//* (Usage)
//*   
//*     
//* (Update Record)
//*	2001/03/27  K.Hoshina	Original version.
//*************************************************************************

#include "tpordvec.h"
#include "G4Timer.hh"
#include "G4String.hh"

// typedefs ============================================================

class G4String;

// =====================================================================

class J4Timer : public G4Timer
{
 
 public:

   J4Timer(G4int          &timerid, 
           const G4String &classname, 
           const G4String &timername);
          
   virtual ~J4Timer();
  
   static void    ResetAllTimers();
   static void    PrintAllAccumulatedTimes();
  
   inline virtual void     Start();
   inline virtual void     Stop();
   inline virtual G4bool   IsValid() const;
   inline virtual G4double GetRealElapsed() const;
   inline virtual G4double GetSystemElapsed() const;
   inline virtual G4double GetUserElapsed() const;
   
   inline virtual void     ResetTimer(G4int id = -1);
   inline virtual G4String GetClassName(G4int id = -1) const;
   inline virtual G4String GetTimerName(G4int id = -1) const;
   inline virtual G4double GetAccumulatedRealElapsed(G4int id = -1) const;
   inline virtual G4double GetAccumulatedSystemElapsed(G4int id = -1) const;
   inline virtual G4double GetAccumulatedUserElapsed(G4int id = -1) const;

 private:
   // class AccumulatedTime
   class AccumulatedTime 
   {
    public:
       AccumulatedTime(G4int          &id,
                       const G4String &classname,
                       const G4String &timername)
                       :fID(id), fClassName(classname), 
                        fTimerName(timername),
                        fAccumulatedRealElapsed(0),
                        fAccumulatedSystemElapsed(0),
                        fAccumulatedUserElapsed(0) {}
       virtual ~AccumulatedTime(){}
       
       inline void ResetTimes() 
                   { 
                      fAccumulatedRealElapsed = 0;
                      fAccumulatedSystemElapsed = 0;
                      fAccumulatedUserElapsed = 0;
                   }
       inline void AccumulateRealElapsed(G4double t) 
                             { fAccumulatedRealElapsed += t; }
       inline void AccumulateSystemElapsed(G4double t) 
                             { fAccumulatedSystemElapsed += t; }
       inline void AccumulateUserElapsed(G4double t) 
                             { fAccumulatedUserElapsed += t; }
       
       inline G4int    GetID() const { return fID; }
       inline G4String GetClassName() const { return fClassName; }
       inline G4String GetTimerName() const { return fTimerName; }
       inline G4double GetAccumulatedRealElapsed() const 
                             { return fAccumulatedRealElapsed; }
       inline G4double GetAccumulatedSystemElapsed() const 
                             { return fAccumulatedSystemElapsed; }
       inline G4double GetAccumulatedUserElapsed() const 
                             { return fAccumulatedUserElapsed; }
       
    private:
       G4int      fID;
       G4String   fClassName;
       G4String   fTimerName;
       G4double   fAccumulatedRealElapsed;
       G4double   fAccumulatedSystemElapsed;
       G4double   fAccumulatedUserElapsed;
   };
   // class AccumulatedTime end
                     
typedef  G4RWTPtrOrderedVector<J4Timer::AccumulatedTime> J4TimerArray;
 
private:
  static G4int         fgNtimers;
  static J4TimerArray  fgTimers;
  AccumulatedTime     *fCurrentTimer;
    
};

//=====================================================================
//---------------------
// inline functions
//---------------------

void J4Timer::Start()
{
   this->G4Timer::Start();
}

void J4Timer::Stop()
{
   this->G4Timer::Stop();
   fCurrentTimer->AccumulateRealElapsed(GetRealElapsed());
   fCurrentTimer->AccumulateSystemElapsed(GetSystemElapsed());
   fCurrentTimer->AccumulateUserElapsed(GetUserElapsed());
}

G4bool J4Timer::IsValid() const
{
   return this->G4Timer::IsValid();
}

G4double J4Timer::GetRealElapsed() const 
{
   return this->G4Timer::GetRealElapsed();
}

G4double J4Timer::GetSystemElapsed() const 
{
   return this->G4Timer::GetSystemElapsed();
}

G4double J4Timer::GetUserElapsed() const 
{
   return this->G4Timer::GetUserElapsed();
}

void J4Timer::ResetTimer(G4int id) 
{
   if (id == -1) {
      fCurrentTimer->ResetTimes();
   } else if (id < fgNtimers) {
      fgTimers[id]->ResetTimes();
   } else {
      std::cerr << "J4Timer::ResetTimer: your id exceeds current fgNtimers."
             << " abort. your id = " << id << std::endl;
      abort();
   }
}

G4String J4Timer::GetClassName(G4int id) const 
{
   if (id == -1) {
      return fCurrentTimer->GetClassName();
   } else if (id < fgNtimers) {
      return fgTimers[id]->GetClassName();
   } else {
      std::cerr << "J4Timer::GetClassName: your id exceeds current fgNtimers."
             << " abort. your id = " << id << std::endl;
      abort();
   }
}

G4String J4Timer::GetTimerName(G4int id) const 
{
   if (id == -1) {
      return fCurrentTimer->GetTimerName();
   } else if (id < fgNtimers) {
      return fgTimers[id]->GetTimerName();
   } else {
      std::cerr << "J4Timer::GetTimerName: your id exceeds current fgNtimers."
             << " abort. your id = " << id << std::endl;
      abort();
   }
}

G4double J4Timer::GetAccumulatedRealElapsed(G4int id) const 
{
   if (id == -1) {
      return fCurrentTimer->GetAccumulatedRealElapsed();
   } else if (id < fgNtimers) {
      return fgTimers[id]->GetAccumulatedRealElapsed();
   } else {
      std::cerr << "J4Timer::GetAccumulatedRealElapsed: your id exceeds"
             << " current fgNtimers. abort. your id = " << id << std::endl;
      abort();
   }
}

G4double J4Timer::GetAccumulatedSystemElapsed(G4int id) const 
{
   if (id == -1) {
      return fCurrentTimer->GetAccumulatedSystemElapsed();
   } else if (id < fgNtimers) {
      return fgTimers[id]->GetAccumulatedSystemElapsed();
   } else {
      std::cerr << "J4Timer::GetAccumulatedSystemElapsed: your id exceeds"
             << " current fgNtimers. abort. your id = " << id << std::endl;
      abort();
   }
}

G4double J4Timer::GetAccumulatedUserElapsed(G4int id) const 
{
   if (id == -1) {
      return fCurrentTimer->GetAccumulatedUserElapsed();
   } else if (id < fgNtimers) {
      return fgTimers[id]->GetAccumulatedUserElapsed();
   } else {
      std::cerr << "J4Timer::GetAccumulatedUserElapsed: your id exceeds"
             << " current fgNtimers. abort. your id = " << id << std::endl;
      abort();
   }
}

#endif
