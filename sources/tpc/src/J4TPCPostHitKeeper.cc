//*************************************************************************
//* --------------------
//* J4TPCPostHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep post hists for TPC.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************

#include "J4TPCPostHitKeeper.hh"
#include "J4TPCPostHit.hh"

J4TPCPostHitKeeper *J4TPCPostHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4TPCPostHitKeeper::J4TPCPostHitKeeper()
{
}
//=====================================================================
//* GetInstance -------------------------------------------------------
J4TPCPostHitKeeper *J4TPCPostHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4TPCPostHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4TPCPostHitKeeper::~J4TPCPostHitKeeper()
{
}

//=====================================================================
//* Destructor -------------------------------------------------------
G4int J4TPCPostHitKeeper::GetCurPostHitID() const
{
  if (J4TPCPostHitKeeper::GetInstance()->GetCurTrackID() < INT_MAX) {
    return J4TPCPostHit::GetCurPostHitID();
  } else {
    return -1;
  }
}
