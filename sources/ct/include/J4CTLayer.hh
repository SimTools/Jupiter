// $Id$
#ifndef __J4CTLAYER__
#define __J4CTLAYER__
//*************************************************************************
//* --------------------
//* J4CTLayer
//* --------------------
//* (Description)
//* 	Derivation class for CT Layer.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCTDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CTLayer : public J4VCTDetectorComponent {	

public:

  J4CTLayer(J4VDetectorComponent* parent    = 0,
  	    G4int                 nclones   = 1,
  	    G4int                 nbrothers = 1, 
  	    G4int                 me        = 0,
            G4int                 copyno    = -1);
  	     
  J4CTLayer(G4double 		  rmin, 	// Inner radius
  	    G4double 		  rmax,         // Outer radius
  	    G4double 		  len,		// Helf length along z-axis
  	    G4double 		  offset   = 0,	// Offcet azimutial angle
  	    J4VDetectorComponent *parent   = 0,
  	    G4int    		  nclones  = 1,
  	    G4int    		  nbrothes = 1, 
  	    G4int    		  me       = 0,
            G4int                 copyno   = -1);
  	     
  virtual ~J4CTLayer();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  
  G4double   fRmin;
  G4double   fRmax;
  G4double   fLen;
  G4double   fTotalPhi;
  G4double   fOffset;
  
};

#endif


