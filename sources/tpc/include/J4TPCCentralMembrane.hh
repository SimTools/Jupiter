#ifndef __J4TPCCENTRALMEMBRANE__
#define __J4TPCCENTRALMEMBRANE__
//*************************************************************************
//* --------------------
//* J4TPCCentralMembrane
//* --------------------
//* (Description)
//* 	Derivation class for TPC.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPCCentralMembrane : public J4VTPCDetectorComponent {	

public:
  J4TPCCentralMembrane(J4VDetectorComponent *parent    = 0,
                                      G4int  nclones   = 1,
                                      G4int  nbrothers = 1, 
                                      G4int  me        = 0,
                                      G4int  copyno    = -1 );
  virtual ~J4TPCCentralMembrane();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String  fFirstName;
  
};

#endif

