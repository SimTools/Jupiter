// $Id$
//*************************************************************************
//* --------------------
//* J4Global
//* --------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************


#include "J4Global.hh"
#include "J4GlobalMessenger.hh"

// ====================================================================
//--------------------------------
// constants (detector parameters)
//--------------------------------

J4Global*        J4Global::fGlobal   = 0;
G4std::ofstream* J4Global::fErrorOfs = 0;
G4int     J4Global::fErrorCounter = 0;
G4int     J4Global::fErrorNevents = 1;
G4int     J4Global::fErrorOutputDeviceID = 1;
G4String  J4Global::fErrorOutputFilename = "lastevtError.log";

//=====================================================================
//---------------------
// Class Description
//---------------------

// ====================================================================
//* constructor -------------------------------------------------------

J4Global::J4Global() 
{
   if (!fGlobal) {
      fGlobal = this;
      fMessenger = new J4GlobalMessenger(this);
   } else {
      G4cerr << "J4Global::constructor: fGlobal is singleton!" << G4endl;
   }
}

// ====================================================================
//* destructor --------------------------------------------------------
J4Global::~J4Global()
{	
}

// ====================================================================
//* GetErrrorOutputStream   -------------------------------------------
G4std::ostream& J4Global::GetErrorOutputStream()
{
   switch (fErrorOutputDeviceID) {
      case 0:
         return G4cerr;
         break;
      case 1:
         if (fErrorOfs && fErrorOfs->is_open()) {
            return *fErrorOfs;
         } else {
            return G4cerr;
         }
         break;
      default:
         G4cerr << "J4Global::GetErrorOutputStream:"
                << " invalid device ID!" << G4endl;
         abort();
   }
}

// ====================================================================
//* GetEndl   ---------------------------------------------------------
G4std::ostream& J4Global::GetEndl(G4std::ostream& outs)
{
   switch (fErrorOutputDeviceID) {
      case 0:
         return (outs << G4endl);
         break;
      case 1:
         if (fErrorOfs && fErrorOfs->is_open()) {
            return (outs << G4endl << G4std::flush);
         } else {
            return (outs << G4endl);
         }
         break;
      default:
         G4cerr << "J4Global::GetEndl:"
         << " invalid device ID!" << G4endl;
         abort();
   }
}

// ====================================================================
//* CloseErrrorOutputStream   -----------------------------------------
void J4Global::CloseErrorOutputStream()
{
   if (fErrorCounter < fErrorNevents) {
      fErrorCounter++;
   } else {
      fErrorCounter = 0;
      fErrorOfs->close();
   }
}
