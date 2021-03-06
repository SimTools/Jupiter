#ifndef __J4TPC__
#define __J4TPC__
//*************************************************************************
//* --------------------
//* J4TPC
//* --------------------
//* (Description)
//* 	Derivation class for TPC.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"
#include "J4TPCHalf.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPC : public J4VTPCDetectorComponent {	

public:
  J4TPC(J4VDetectorComponent *parent    = 0,
                       G4int  nclones   = 1,
                       G4int  nbrothers = 1, 
                       G4int  me        = 0,
                       G4int  copyno    = -1 );
  virtual ~J4TPC();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String      fFirstName;
  J4TPCHalf          **fTPCHalfs;
 
};

#endif

