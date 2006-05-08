// $Id$
//*************************************************************************
//* --------------------
//* J4CLXPreHitKeeper
//* --------------------
//* (Description)
//*     Class to book keep pre hits for CLX.
//* (Update Record)
//*     2004/12/09  K.Fujii     Original version.
//*************************************************************************

#include "J4CLXPreHitKeeper.hh"

J4CLXPreHitKeeper *J4CLXPreHitKeeper::fgInstance = 0;

//=====================================================================
//* Constructor -------------------------------------------------------
J4CLXPreHitKeeper::J4CLXPreHitKeeper()
            : fCurrentPreHitPtr(0),
              fCurrentPreHitID(-1)
{
}
//=====================================================================
//* GetInstance -------------------------------------------------------
J4CLXPreHitKeeper *J4CLXPreHitKeeper::GetInstance()
{
  if (!fgInstance) fgInstance = new J4CLXPreHitKeeper;
  return fgInstance;
}

//=====================================================================
//* Destructor -------------------------------------------------------
J4CLXPreHitKeeper::~J4CLXPreHitKeeper()
{
}
