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
std::ofstream* J4Global::fErrorOfs = 0;
G4int            J4Global::fErrorCounter = 1;
G4int            J4Global::fErrorNevents = 1;
G4int            J4Global::fErrorOutputDeviceID = 1;
G4String         J4Global::fErrorOutputFilename = "lastevtError.log";
G4String         J4Global::fErrorOutputUnit     = "Track";

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
      std::cerr << "J4Global::constructor: fGlobal is singleton!" << std::endl;
   }
}

// ====================================================================
//* destructor --------------------------------------------------------
J4Global::~J4Global()
{	
}

// ====================================================================
//* GetErrrorOutputStream   -------------------------------------------
std::ostream& J4Global::GetErrorOutputStream()
{
   switch (fErrorOutputDeviceID) {
      case 0:
         return std::cerr;
         break;
      case 1:
         if (fErrorOfs) {
            return *fErrorOfs;
         } else {
            return std::cerr;
         }
         break;
      default:
         std::cerr << "J4Global::GetErrorOutputStream:"
                << " invalid device ID!" << std::endl;
         abort();
   }
}

// ====================================================================
//* GetEndl   ---------------------------------------------------------
std::ostream& J4Global::GetEndl(std::ostream& outs)
{
   switch (fErrorOutputDeviceID) {
      case 0:
         return (outs << std::endl);
         break;
      case 1:
         if (fErrorOfs && fErrorOfs->is_open()) {
            return (outs << std::endl << std::flush);
         } else {
            return (outs << std::endl);
         }
         break;
      default:
         std::cerr << "J4Global::GetEndl:"
         << " invalid device ID!" << std::endl;
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
      fErrorCounter = 1;
      fErrorOfs->close();
   }
}
