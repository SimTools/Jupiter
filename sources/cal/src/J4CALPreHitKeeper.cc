//*************************************************************************
//* --------------------
//* J4CALPreHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep pre hits for CAL.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************

#include "J4CALPreHitKeeper.hh"

J4CALPreHitKeeper *J4CALPreHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4CALPreHitKeeper::J4CALPreHitKeeper()
            : fCurrentPreHitPtr(0),
              fCurrentPreHitID(-1)
{
}
//=====================================================================
//* GetInstance -------------------------------------------------------
J4CALPreHitKeeper *J4CALPreHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4CALPreHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4CALPreHitKeeper::~J4CALPreHitKeeper()
{
}
