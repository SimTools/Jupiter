#ifndef __J4TPCSUPPORTTUB__
#define __J4TPCSUPPORTTUB__
//*************************************************************************
//* --------------------
//* J4TPCSupportTub
//* --------------------
//* (Description)
//* 	Derivation class for TPC Support Tube.
//*     Mother class : J4TPCDetectorComponent
//*    
//* (Update Record)
//*	2004/08/06  A.Yamaguchi	Original version.
//*************************************************************************

#include "J4VTPCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4TPCSupportTub : public J4VTPCDetectorComponent {	

public:
  J4TPCSupportTub(G4double rmin,
  		  G4double rmax,
  		  G4double len,
  		  G4double totalphi,
  		  J4VDetectorComponent *parent = 0,
                  G4int  nclones   = 1,
                  G4int  nbrothers = 1, 
                  G4int  me        = 0,
                  G4int  copyno    = -1 );
  virtual ~J4TPCSupportTub();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw();
  virtual void	Print() const;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String fFirstName;
  G4double	  fRmin;
  G4double 	  fRmax;
  G4double	  fLen;
  G4double	  fTotalPhi;
};

#endif

