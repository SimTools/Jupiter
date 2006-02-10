#ifndef __J4HISTORYKEEPER__ 
#define __J4HISTORYKEEPER__
//*************************************************************************
//* --------------------
//* J4HistoryKeeper
//* --------------------
//* (Description)
//* 	Base class to book keep history information.
//* (Update Record)
//*	2006/01/11  S.Yamamoto	Original version.
//*************************************************************************


#include "globals.hh"
#include "J4PHitKeeper.hh"

class J4HistoryKeeper : public J4VSubTrackingAction {
private:
  J4HistoryKeeper();
public:   
  virtual ~J4HistoryKeeper();

  virtual void    PreTrackDoIt(const G4Track* aTrack = 0);
  virtual void    Clear();
  static  J4HistoryKeeper *GetInstance() 
  { 
    return fgInstance ? fgInstance : (fgInstance = new J4HistoryKeeper());
  }
  void SetPHitKeeperPtr(J4PHitKeeper *phkp) { fPHitKeeperPtr = phkp; } 

private:
  J4PHitKeeper *fPHitKeeperPtr;
  static      J4HistoryKeeper *fgInstance; // pointer to this class (singleton)
};

#endif
