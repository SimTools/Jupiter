// $Id$
#ifndef __J4CALSUBLAYER__
#define __J4CALSUBLAYER__
//*************************************************************************
//* --------------------
//* J4CALSubLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALLayer.hh"
class J4VDetectorComponent;
class J4CALSubLayerSD;

//=====================================================================
//---------------------
// class definition
//---------------------

//class J4CALSubLayer : public J4VCALDetectorComponent {
class J4CALSubLayer : public J4CALLayer{

public:
  J4CALSubLayer(J4VDetectorComponent  *parent    = 0,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALSubLayer();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

//private:
protected:
  void 	Assemble();    
  void  Cabling ();
  
//private:  
protected:  
  static G4String   fFirstName;

  G4int fMiniTowerNClones;
  G4int fMiniConeNCBrohers;
  G4int fTowerNClones;
  G4int fConeNBrothers;
  
};

#endif
