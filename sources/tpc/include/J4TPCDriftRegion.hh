#ifndef __J4TPCDRIFTREGION__
#define __J4TPCDRIFTREGION__
//*************************************************************************
//* --------------------
//* J4TPCDriftRegion
//* --------------------
//* (Description)
//* 	Derivation class for TPCDriftRegion.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4TPCLayer.hh"
#include "J4VTPCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPCDriftRegion : public J4VTPCDetectorComponent {	

public:
  J4TPCDriftRegion(J4VDetectorComponent *parent    = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );
  virtual ~J4TPCDriftRegion();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String        fFirstName;
  J4TPCLayer           **fLayers;
 
};

#endif

