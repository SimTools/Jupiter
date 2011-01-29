// $Id$
#ifndef __J4CTSUPPORTTUB__
#define __J4CTSUPPORTTUB__
//*************************************************************************
//* --------------------
//* J4CTSupportTub
//* --------------------
//* (Description)
//* 	Derivation class for CT Support Tube.
//*     Mother class : J4CTDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCTDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CTSupportTub : public J4VCTDetectorComponent {	

public:
  J4CTSupportTub(G4double rmin,
  		  G4double rmax,
  		  G4double len,
  		  G4double totalphi,
  		  J4VDetectorComponent *parent = 0,
                  G4int  nclones   = 1,
                  G4int  nbrothers = 1, 
                  G4int  me        = 0,
                  G4int  copyno    = -1 );
  virtual ~J4CTSupportTub();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
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


