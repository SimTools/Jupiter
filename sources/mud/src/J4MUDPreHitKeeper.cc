//*************************************************************************
//* --------------------
//* J4MUDPreHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep pre hits for CAL.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************
#include "J4MUDPreHitKeeper.hh"

J4MUDPreHitKeeper* J4MUDPreHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4MUDPreHitKeeper::J4MUDPreHitKeeper()
 : fCurrentPreHitPtr(0), fCurrentPreHitID(-1)
{}
//=====================================================================
//* GetInstance -------------------------------------------------------
J4MUDPreHitKeeper* J4MUDPreHitKeeper::GetInstance()
{
  if ( !fgInstance ) fgInstance = new J4MUDPreHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4MUDPreHitKeeper::~J4MUDPreHitKeeper()
{ }
