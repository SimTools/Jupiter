// $Id$
//*************************************************************************
//* --------------------
//* J4MagneticField
//* --------------------
//* (Description)
//* 	This class applies magnetic field.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/02/18  K.Hoshina	Original version.
//*				This class is temporary, and should be 
//*                             removed eventually.
//*************************************************************************
 
#include "globals.hh"
#include "J4MagneticField.hh"
#include "J4SOLParameterList.hh"

//=====================================================================
//---------------------
// class description
//---------------------

void J4MagneticField::GetFieldValue(const  G4double Point[3], 
				           G4double* Bfield ) const
{
   G4double maxBRad    = fParameterList->GetOR();
   G4double maxBZ      = fParameterList->GetLength();
   G4double zBfield    = fParameterList->GetBField();
   G4double maxBRad_sq = maxBRad * maxBRad;

   Bfield[0] = 0.;
   Bfield[1] = 0.;  
   if (abs(Point[2]) < maxBZ && (sqr(Point[0])+sqr(Point[1])) < maxBRad_sq) { 
      Bfield[2] = zBfield; 
   } else {
      Bfield[2] = 0; 
   }
}

