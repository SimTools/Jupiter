// $Id$
#ifndef __J4SUBTRACTIONSOLID__
#define __J4SUBTRACTIONSOLID__
//*************************************************************************
//* --------------------
//* J4SubtractionSolid
//* --------------------
//* (Description)
//*     
//* (Update Record)
//*	2001/08/26  K.Hoshina	Original version.
//*************************************************************************

#include "G4SubtractionSolid.hh"

class J4SubtractionSolid : public G4SubtractionSolid
{
  public:  // with description

    J4SubtractionSolid( const G4String& pName,
                        G4VSolid* pSolidA ,
                        G4VSolid* pSolidB   ) ;

    J4SubtractionSolid( const G4String& pName,
                        G4VSolid* pSolidA ,
                        G4VSolid* pSolidB ,
                        G4RotationMatrix* rotMatrix,
                  const G4ThreeVector& transVector    ) ;

    J4SubtractionSolid( const G4String& pName,
                        G4VSolid* pSolidA ,
                        G4VSolid* pSolidB ,
                  const G4Transform3D& transform   ) ;

    virtual ~J4SubtractionSolid() ;

  public:  // without description

    inline virtual void  SetOwner(G4bool isowner = true)
    					{ fIsOwner = isowner; }
    
private:

    G4bool	fIsOwner;
    G4VSolid   *fSolidA;
    G4VSolid   *fSolidB;

        
};

#endif



