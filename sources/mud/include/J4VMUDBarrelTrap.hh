// $Id$
#ifndef __J4VMUDBARRELTRAP__
#define __J4VMUDBARRELTRAP__
//*************************************************************************
//* --------------------
//* J4VMUDBarrelTrap
//* --------------------
//* (Description)
//* 	Derivation class for MUD.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*  2004/10/26  Ono Hiroaki
//*************************************************************************
#include "J4MUDBarrelActiveSD.hh"
#include "J4MUDEndcapActiveSD.hh"
#include "J4VMUDDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDBarrelActiveSD;
class J4VMUDBarrelTrap : public J4VMUDDetectorComponent {	

public:
  J4VMUDBarrelTrap( const G4String&       name, 
                    J4VDetectorComponent* parent    = 0,
                                    G4int nclones   = 1,
                                    G4int nbrothers = 1, 
                                    G4int me        = 0,
                                    G4int copyno    = -1 );
  virtual ~J4VMUDBarrelTrap();

  virtual void  InstallIn( J4VComponent*        mother,
                           G4RotationMatrix*    prot  = 0,
                           const G4ThreeVector& tlate = 0 );
  virtual void	Draw();
  virtual void	Print() const;

  virtual G4String GetFirstName () const    = 0;
  virtual G4double GetFront     ( G4int i ) = 0;
  virtual G4double GetHalfL     ( G4int i ) = 0;
  virtual G4double GetThick     ( G4int i ) = 0;
  virtual G4String GetMaterial  ()          = 0;
  virtual G4bool   GetVisAtt    ()          = 0;
  virtual G4Color  GetColor     ()          = 0;

private:
  void 	Assemble();    
  void  Cabling();
  
};

#endif
