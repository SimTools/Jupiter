// $Id$
#ifndef __J4MUDENDCAP__
#define __J4MUDENDCAP__
//*************************************************************************
//* --------------------
//* J4MUDEndcap
//* --------------------
//* (Description)
//* 	Derivation class for MUD.
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
class J4MUDEndcap : public J4VMUDDetectorComponent {	

public:
  J4MUDEndcap( J4VDetectorComponent* parent    = 0,
                              G4int  nclones   = 1,
                              G4int  nbrothers = 1, 
                              G4int  me        = 0,
                              G4int  copyno    = -1 );
  virtual ~J4MUDEndcap();

  virtual void  InstallIn( J4VComponent*        mother,
                           G4RotationMatrix*    prot  = 0,
                           const G4ThreeVector& tlate = 0 );
  virtual void	Draw() {};
  virtual void	Print() const {};
  
private:
  void 	Assemble();    
  void  Cabling();
  
private:  
  static G4String  fFirstName;
  
};

#endif