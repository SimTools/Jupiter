// $Id$
#ifndef __J4CDCDRIFTREGION__
#define __J4CDCDRIFTREGION__
//*************************************************************************
//* --------------------
//* J4CDCDRIFTREGION
//* --------------------
//* (Description)
//* 	Derivation class for CDC DriftRegion.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCDCDriftRegion.hh"
#include "J4CDCLayer.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class J4CDCSenseWire;
class J4CDCDriftRegion : public J4VCDCDriftRegion {	

public:
  J4CDCDriftRegion( J4VDetectorComponent *parent    = 0,
                                   G4int  nclones   = 1,
                                   G4int  nbrothers = 1, 
                                   G4int  me        = 0,
                                   G4int  copyno    = -1 );

  J4CDCDriftRegion(const J4CDCDriftRegion &orig,                                   
                                    G4int  copyno ); 

  virtual ~J4CDCDriftRegion();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	SwitchOn (G4String opt = "me")  ;
  virtual void	SwitchOff(G4String opt = "me")  ; 
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
  
private:
  void 	Assemble(); 
  void  Cabling ();  
   
private:  
  static G4String fFirstName;
  
};

//=====================================================================
//---------------------
// inline function
//---------------------


#endif


