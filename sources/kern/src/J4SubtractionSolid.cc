// $Id$
//*************************************************************************
//* --------------------
//* J4SubtractionSolid
//* --------------------
//* (Description)
//*     
//* (Update Record)
//*	2001/08/26  K.Hoshina	Original version.
//*************************************************************************

#include "J4SubtractionSolid.hh"

///////////////////////////////////////////////////////////////////
//
// Transfer all data members to G4BooleanSolid which is responsible
// for them. pName will be in turn sent to G4VSolid

J4SubtractionSolid:: J4SubtractionSolid( const G4String& pName,
                                         G4VSolid* pSolidA ,
                                         G4VSolid* pSolidB   ):
		G4SubtractionSolid(pName,pSolidA,pSolidB), fIsOwner(true),
                fSolidA(pSolidA), fSolidB(pSolidB)
{
   ;
}

/////////////////////////////////////////////////////////////////////
//
//
 
J4SubtractionSolid:: J4SubtractionSolid( const G4String& pName,
                                         G4VSolid* pSolidA ,
                                         G4VSolid* pSolidB ,
                                         G4RotationMatrix* rotMatrix,
                                   const G4ThreeVector& transVector    ):
		G4SubtractionSolid(pName,pSolidA,pSolidB,rotMatrix,transVector)
		, fIsOwner(true), fSolidA(pSolidA), fSolidB(pSolidB)

{
   ;
}

///////////////////////////////////////////////////////////
//
//
 
J4SubtractionSolid:: J4SubtractionSolid( const G4String& pName,
                                         G4VSolid* pSolidA ,
                                         G4VSolid* pSolidB ,
                                   const G4Transform3D& transform  ):
		G4SubtractionSolid(pName,pSolidA,pSolidB,transform)
		, fIsOwner(true), fSolidA(pSolidA), fSolidB(pSolidB)

{
   ;
} 


///////////////////////////////////////////////////////////
//
//

J4SubtractionSolid::~J4SubtractionSolid()
{
   if (fIsOwner) {
   	if (fSolidA) delete fSolidA;
   	if (fSolidB) delete fSolidB;
   }
}


