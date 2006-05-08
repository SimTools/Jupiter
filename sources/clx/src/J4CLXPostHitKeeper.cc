// $Id$
//*************************************************************************
//* --------------------
//* J4CLXPostHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep post hists for TPC.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************
#include "J4CLXPostHitKeeper.hh"
#include "J4CLXPostHit.hh"

J4CLXPostHitKeeper *J4CLXPostHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4CLXPostHitKeeper::J4CLXPostHitKeeper() { }

//=====================================================================
//* GetInstance -------------------------------------------------------
J4CLXPostHitKeeper *J4CLXPostHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4CLXPostHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4CLXPostHitKeeper::~J4CLXPostHitKeeper() { }

//=====================================================================
//* Destructor -------------------------------------------------------
G4int J4CLXPostHitKeeper::GetCurPostHitID() const
{
 return J4CLXPostHit::GetCurPostHitID();
 // if ( J4CLXPostHitKeeper::GetInstance()->GetCurTrackID() < INT_MAX ) {
 //   return J4CLXPostHit::GetCurPostHitID();
 // } else {
 //   return J4CLXPostHit::GetCurPostHitID();
 //   //G4cerr << "*** Error : J4CLXPostHitID is out of INT_MAX, return -1"  << G4endl;
 //   //return -1;
 // }
}

//*=====================================================================
//* GetCurPostHitPtr ---------------------------------------------------
J4CLXPostHit* J4CLXPostHitKeeper::GetCurPostHitPtr() const
{
  return J4CLXPostHit::GetCurPostHitPtr();
}
