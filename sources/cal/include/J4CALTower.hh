// $Id$
#ifndef __J4CALTOWER__
#define __J4CALTOWER__
//*************************************************************************
//* --------------------
//* J4CALTower
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALCone.hh"
#include "J4CALEM.hh"
#include "J4CALHD.hh"

//=====================================================================
//---------------------
// class definition //---------------------

class J4CALEM;
class J4CALHD;
class J4CALTower : public J4VCALDetectorComponent {	

public:
  J4CALTower(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALTower();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  inline virtual G4bool IsBarrel() const 
         { return ((J4CALCone *)GetMother())->IsBarrel(); }  
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String   fFirstName;
  
  J4CALEM          *fEMcal;
  J4CALHD          *fHDcal;
};

#endif
