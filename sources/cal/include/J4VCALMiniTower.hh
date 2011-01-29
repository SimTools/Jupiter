// $Id$
#ifndef __J4VCALMINITOWER__
#define __J4VCALMINITOWER__
//*************************************************************************
//* --------------------
//* J4VCALMiniTower
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4VCALMiniCone.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCALLayer;
class J4VCALMiniTower : public J4VCALDetectorComponent {	

public:
  J4VCALMiniTower( const G4String       &name,
                   J4VDetectorComponent *parent    = 0,
                                  G4int  nclones   = 1,
                                  G4int  nbrothers = 1, 
                                  G4int  me        = 0,
                                  G4int  copyno    = -1 );
  virtual ~J4VCALMiniTower();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;

  virtual G4String GetFirstName    () const = 0;
  virtual G4int    GetNofMiniTowers()       = 0;
  virtual G4int    GetNofLayers    ()       = 0;
  virtual G4String GetMaterial     ()       = 0;
  virtual G4bool   GetVisAtt       ()       = 0;
  virtual G4Color  GetColor        ()       = 0;

protected:
  virtual J4VCALLayer *Create( J4VDetectorComponent *parent    = 0,
                                              G4int  nclones   = 1,
                                              G4int  nbrothers = 1, 
                                              G4int  me        = 0,
                                              G4int  copyno    = -1 ) = 0;

private:
  void 	Assemble();    
  void  Cabling ();
  
protected:  
  std::vector<J4VCALLayer *> fLayers;
};

#endif
