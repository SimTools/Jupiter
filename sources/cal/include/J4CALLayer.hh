// $Id$
#ifndef __J4CALLAYER__
#define __J4CALLAYER__
//*************************************************************************
//* --------------------
//* J4CALLayer
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
class J4VDetectorComponent;
class J4CALSubLayer;
class J4CALSubLayerSD;

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CALLayer : public J4VCALDetectorComponent {	

public:
  J4CALLayer(J4VDetectorComponent  *parent    = 0,
                            G4bool  isem      = true,
                             G4int  nclones   = 1,
                             G4int  nbrothers = 1, 
                             G4int  me        = 0,
                             G4int  copyno    = -1 );
  virtual ~J4CALLayer();

  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String          fFirstName;
  std::vector<J4CALSubLayer *>   fSubLayers;

};

#endif
