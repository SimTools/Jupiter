// $Id$
#ifndef __J4VMUDENDCAPTRAP__
#define __J4VMUDENDCAPTRAP__
//*************************************************************************
//* --------------------
//* J4VMUDEndcapTrap
//* --------------------
//* (Description)
//* 	Derivation class for MUD.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*  2004/10/26  Ono Hiroaki
//*************************************************************************
#include "J4VMUDDetectorComponent.hh"
#include "J4MUDEndcapActiveSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDEndcapActiveSD;
class J4VMUDEndcapTrap : public J4VMUDDetectorComponent {

public:
  J4VMUDEndcapTrap( const G4String&       name, 
                    J4VDetectorComponent* parent    = 0,
                                    G4int nclones   = 1,
                                    G4int nbrothers = 1, 
                                    G4int me        = 0,
                                    G4int copyno    = -1 );
  virtual ~J4VMUDEndcapTrap();

  virtual void  InstallIn( J4VComponent*        mother,
                           G4RotationMatrix*    prot  = 0,
                           const G4ThreeVector& tlate = 0 );
  virtual void	Draw();
  virtual void	Print() const;

  virtual G4String GetFirstName () const    = 0;
  virtual G4double GetFront     ( G4int i ) = 0;
  virtual G4double GetHeight    ( G4int i ) = 0;
  virtual G4double GetEndcapZ   ( G4int i ) = 0;
  virtual G4double GetThick     ( G4int i ) = 0;
  virtual G4int    GetNLayers   ()          = 0;
  virtual G4String GetMaterial  ()          = 0;
  virtual G4bool   GetVisAtt    ()          = 0;
  virtual G4Color  GetColor     ()          = 0;

private:
  void 	Assemble();    
  void  Cabling() = 0;

};

#endif
