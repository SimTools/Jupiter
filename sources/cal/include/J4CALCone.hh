// $Id$
#ifndef __J4CALCONE__
#define __J4CALCONE__
//*************************************************************************
//* --------------------
//* J4CALCone
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALTower;

class J4CALCone : public J4VCALDetectorComponent {	

public:
  J4CALCone(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALCone();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  inline virtual G4bool IsBarrel() const { return fIsBarrel; }
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String& fFirstName;

  J4CALTower           *fTower;
  G4bool                fIsBarrel;
  
};

#endif
