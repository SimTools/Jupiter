// $Id$
#ifndef __J4MUDBARREL__
#define __J4MUDBARREL__
//*************************************************************************
//* --------------------
//* J4MUDBarrel
//* --------------------
//* (Description)
//* 	Derivation class for MUD Barrel.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VMUDDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4MUDBarrel : public J4VMUDDetectorComponent {	

public:

  J4MUDBarrel( J4VDetectorComponent* parent    = 0,
  	      G4int                 nclones   = 1,
  	      G4int                 nbrothers = 1, 
  	      G4int                 me        = 0,
              G4int                 copyno    = -1 );
  	     
  virtual ~J4MUDBarrel();

  virtual void  InstallIn( J4VComponent*        mother,
                           G4RotationMatrix*    prot  = 0,
                           const G4ThreeVector& tlate = 0 );

  virtual void Draw() { };
  virtual void Print() const { };
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  
  G4double   fRmin;
  G4double   fRmax;
  G4double   fLen;
  G4double   fDeltaPhi;
  
};

#endif
