//*************************************************************************
//* --------------------
//* J4IRBCALPreHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep pre hits for CAL.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************

#include "J4IRBCALPreHitKeeper.hh"

J4IRBCALPreHitKeeper *J4IRBCALPreHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4IRBCALPreHitKeeper::J4IRBCALPreHitKeeper()
            : fCurrentPreHitPtr(0),
              fCurrentPreHitID(-1)
{
}
//=====================================================================
//* GetInstance -------------------------------------------------------
J4IRBCALPreHitKeeper *J4IRBCALPreHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4IRBCALPreHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4IRBCALPreHitKeeper::~J4IRBCALPreHitKeeper()
{
}
