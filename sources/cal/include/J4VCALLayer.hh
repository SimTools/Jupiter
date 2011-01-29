// $Id$
#ifndef __J4VCALLAYER__
#define __J4VCALLAYER__
//*************************************************************************
//* --------------------
//* J4VCALLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4VCALMiniTower.hh"
#include "J4VCALSubLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCALSubLayer;
class J4VCALLayer : public J4VCALDetectorComponent {	

public:
  J4VCALLayer( const G4String       &name,
               J4VDetectorComponent *parent    = 0,
                              G4int  nclones   = 1,
                              G4int  nbrothers = 1, 
                              G4int  me        = 0,
                              G4int  copyno    = -1 );
  virtual ~J4VCALLayer();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw() ;
  virtual void	Print() const ;

  virtual G4String GetFirstName     () const = 0;
  virtual G4double GetLayerThickness()       = 0;
  virtual G4String GetMaterial      ()       = 0;
  virtual G4bool   GetVisAtt        ()       = 0;
  virtual G4Color  GetColor         ()       = 0;

protected:
  virtual J4VCALSubLayer *CreateAbs( J4VDetectorComponent *parent    = 0,
                                                    G4int  nclones   = 1,
                                                    G4int  nbrothers = 1, 
                                                    G4int  me        = 0,
                                                    G4int  copyno    = -1 ) = 0;

  virtual J4VCALSubLayer *CreateActive( J4VDetectorComponent *parent    = 0,
                                                       G4int  nclones   = 1,
                                                       G4int  nbrothers = 1, 
                                                       G4int  me        = 0,
                                                       G4int  copyno    = -1 ) = 0;

private:
  void 	Assemble();    
  void  Cabling ();
  
protected:  
  J4VCALSubLayer  *fAbsLayer;
  J4VCALSubLayer  *fActiveLayer;

};

#endif
