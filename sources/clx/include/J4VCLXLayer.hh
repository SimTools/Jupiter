// $Id$
#ifndef __J4VCLXLAYER__
#define __J4VCLXLAYER__
//*************************************************************************
//* --------------------
//* J4VCLXLayer
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"
#include "J4VCLXSubLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCLXSubLayer;
class J4VCLXLayer : public J4VCLXDetectorComponent {

public:
  J4VCLXLayer( const G4String       &name,
               J4VDetectorComponent *parent    = 0,
                              G4int  nclones   = 1,
                              G4int  nbrothers = 1,
                              G4int  me        = 0,
                              G4int  copyno    = -1 );
  virtual ~J4VCLXLayer();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void	Draw() ;
  virtual void	Print() const ;

  virtual G4String GetFirstName     () const = 0;
  virtual G4double GetLayerThickness()       = 0;
    virtual G4int GetNLayers() = 0;
  virtual G4String GetMaterial      ()       = 0;
  virtual G4bool   GetVisAtt        ()       = 0;
  virtual G4Color  GetColor         ()       = 0;

protected:
  virtual J4VCLXSubLayer *CreateAbs( J4VDetectorComponent *parent    = 0,
                                                    G4int  nclones   = 1,
                                                    G4int  nbrothers = 1,
                                                    G4int  me        = 0,
                                                    G4int  copyno    = -1 ) = 0;

  virtual J4VCLXSubLayer *CreateActive( J4VDetectorComponent *parent    = 0,
                                                       G4int  nclones   = 1,
                                                       G4int  nbrothers = 1,
                                                       G4int  me        = 0,
                                                       G4int  copyno    = -1 ) = 0;

private:
  void 	Assemble();
  void  Cabling ();

protected:

    J4VCLXSubLayer *fAbsLayer;
    J4VCLXSubLayer *fActiveLayer;
};

#endif
