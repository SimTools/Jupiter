//*************************************************************************
//* --------------------
//* J4HistoryKeeper
//* --------------------
//* (Description)
//*     Base class to book keep history information.
//* (Update Record)
//*     2006/01/11  S.Yamamoto     Original version.
//*************************************************************************

#include "J4HistoryKeeper.hh"
#include "J4BreakPoint.hh"
#include "J4PHitKeeper.hh"

J4HistoryKeeper *J4HistoryKeeper::fgInstance = 0; 
//=====================================================================
//* Constructor -------------------------------------------------------
J4HistoryKeeper::J4HistoryKeeper()
{
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4HistoryKeeper::~J4HistoryKeeper()
{
}

//=====================================================================
//* PreTrackDoIt ------------------------------------------------------
void J4HistoryKeeper::PreTrackDoIt(const G4Track* aTrack)
{
  if (fPHitKeepers.empty()) return;
  // Create breakpoint
  G4bool isnext = true;
  std::vector<J4PHitKeeper *>::iterator iter;
  for (iter  = fPHitKeepers.begin(); 
       iter != fPHitKeepers.end(); iter++) {
    J4PHitKeeper *phkp = *iter;
    if (phkp && phkp->IsPHitCreated()) { 
      isnext = false;
      break;
    }
  }
  if (isnext) {
#ifndef __DEBUG__
    new J4BreakPoint(aTrack);
#else
    J4BreakPoint *bpp = new J4BreakPoint(aTrack);
    G4cerr << "track ID = " << bpp->GetTrackID() 
           << " parent track ID =  " << bpp->GetParentID() << G4endl;
#endif
  }
}

//=====================================================================
//* Clear -------------------------------------------------------------

void J4HistoryKeeper::Clear()
{
  J4BreakPoint::Clear();
}
