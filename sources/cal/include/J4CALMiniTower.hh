// $Id$
#ifndef __J4CALMINITOWER__
#define __J4CALMINITOWER__
//*************************************************************************
//* --------------------
//* J4CALMiniTower
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALMiniCone.hh"
//#include "J4CALEM.hh"
//#include "J4CALHD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALLayer;
class J4CALMiniTower : public J4VCALDetectorComponent {	

public:
  J4CALMiniTower(J4VDetectorComponent *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALMiniTower();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  //  inline virtual G4bool IsBarrel() const 
  //         { return ((J4CALMiniCone *)GetMother())->IsBarrel(); }  
  //         { return ((J4CALCone *)GetMother())->IsBarrel(); }  
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String   fFirstName;
   
  std::vector<J4CALLayer *> fLayers;
  //G4bool fIsBarrel;
};

#endif
