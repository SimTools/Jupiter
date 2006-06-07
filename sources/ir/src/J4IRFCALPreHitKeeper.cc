//*************************************************************************
//* --------------------
//* J4IRFCALPreHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep pre hits for CAL.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************

#include "J4IRFCALPreHitKeeper.hh"

J4IRFCALPreHitKeeper *J4IRFCALPreHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4IRFCALPreHitKeeper::J4IRFCALPreHitKeeper()
            : fCurrentPreHitPtr(0),
              fCurrentPreHitID(-1)
{
}
//=====================================================================
//* GetInstance -------------------------------------------------------
J4IRFCALPreHitKeeper *J4IRFCALPreHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4IRFCALPreHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4IRFCALPreHitKeeper::~J4IRFCALPreHitKeeper()
{
}
