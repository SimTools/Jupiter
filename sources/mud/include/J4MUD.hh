// $Id$
#ifndef __J4MUD__
#define __J4MUD__
//*************************************************************************
//* --------------------
//* J4MUD
//* --------------------
//* (Description)
//* 	Derivation class for MUD.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2003/08/13  A.Miyamoto Original version.(Copied from J4IT)
//*************************************************************************
#include "J4MUDBlock.hh"
#include "J4VMUDDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDBlock;
class J4MUD : public J4VMUDDetectorComponent {	

public:
  J4MUD( J4VDetectorComponent* parent    = 0,
                        G4int  nclones   = 1,
                        G4int  nbrothers = 1, 
                        G4int  me        = 0,
                        G4int  copyno    = -1 );
  virtual ~J4MUD();

  virtual void  InstallIn( J4VComponent*        mother,
                           G4RotationMatrix*    prot  = 0,
                           const G4ThreeVector& tlate = 0 );
  virtual void Draw() {};
  virtual void Print() const {};

private:
  void 	Assemble();
  void  Cabling();

private:  
  static G4String      fFirstName;

  J4MUDBlock**         fBlocks;
};

#endif
