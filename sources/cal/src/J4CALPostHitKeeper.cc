//*************************************************************************
//* --------------------
//* J4CALPostHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep post hists for TPC.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************
#include "J4CALPostHitKeeper.hh"
#include "J4CALPostHit.hh"

J4CALPostHitKeeper *J4CALPostHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4CALPostHitKeeper::J4CALPostHitKeeper() { }

//=====================================================================
//* GetInstance -------------------------------------------------------
J4CALPostHitKeeper *J4CALPostHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4CALPostHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4CALPostHitKeeper::~J4CALPostHitKeeper() { }

//=====================================================================
//* Destructor -------------------------------------------------------
G4int J4CALPostHitKeeper::GetCurPostHitID() const
{
 return J4CALPostHit::GetCurPostHitID();
 // if ( J4CALPostHitKeeper::GetInstance()->GetCurTrackID() < INT_MAX ) {
 //   return J4CALPostHit::GetCurPostHitID();
 // } else {
 //   return J4CALPostHit::GetCurPostHitID();
 //   //G4cerr << "*** Error : J4CALPostHitID is out of INT_MAX, return -1"  << G4endl;
 //   //return -1;
 // }
}

//*=====================================================================
//* GetCurPostHitPtr ---------------------------------------------------
J4CALPostHit* J4CALPostHitKeeper::GetCurPostHitPtr() const
{
  return J4CALPostHit::GetCurPostHitPtr();
}
