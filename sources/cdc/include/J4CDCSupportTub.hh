// $Id$
#ifndef __J4CDCSUPPORTTUB__
#define __J4CDCSUPPORTTUB__
//*************************************************************************
//* --------------------
//* J4CDCSupportTub
//* --------------------
//* (Description)
//* 	Derivation class for CDC Support Tube.
//*     Mother class : J4CDCDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CDCSupportTub : public J4VCDCDetectorComponent {	

public:
  J4CDCSupportTub(G4double rmin,
  		  G4double rmax,
  		  G4double len,
  		  G4double totalphi,
  		  J4VDetectorComponent *parent = 0,
                  G4int  nclones   = 1,
                  G4int  nbrothers = 1, 
                  G4int  me        = 0,
                  G4int  copyno    = -1 );
  virtual ~J4CDCSupportTub();

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


