// $Id$
#ifndef __J4MUDBLOCK__
#define __J4MUDBLOCK__
//*************************************************************************
//* --------------------
//* J4MUDBlock
//* --------------------
//* (Description)
//* 	Derivation class for MUDBlock.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2003/08/13  A.Miyamoto Original version.(Copied from J4IT)
//*************************************************************************
#include "J4VMUDDetectorComponent.hh"
//#include "J4VMUDEndcapTrap.hh"
//#include "J4VMUDBarrelTrap.hh"
#include "J4MUDEndcapActive.hh"
#include "J4MUDEndcapAbs.hh"
#include "J4MUDBarrelActive.hh"
#include "J4MUDBarrelAbs.hh"
#include "J4MUDFrontEndcapActive.hh"
#include "J4MUDFrontEndcapAbs.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4MUDEndcapAbs;
class J4MUDEndcapActive;
class J4MUDBarrelAbs;
class J4MUDBarrelActive;
class J4MUDFrontEndcapAbs;
class J4MUDFrontEndcapActive;
class J4MUDBlock : public J4VMUDDetectorComponent {	

public:
  J4MUDBlock( J4VDetectorComponent* parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4MUDBlock();

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

  J4MUDEndcapActive**       fEndcapActive;
  J4MUDEndcapAbs**          fEndcapAbs;
  J4MUDBarrelAbs**          fBarrelAbs;
  J4MUDBarrelActive**       fBarrelActive;
#ifdef __GLD_V1__
  J4MUDFrontEndcapActive**  fFrontEndcapActive;
  J4MUDFrontEndcapAbs**     fFrontEndcapAbs;
#endif
};

#endif
