// $Id$
#ifndef __J4VTXPIXEL_
#define __J4VTXPIXEL__
//*************************************************************************
//* --------------------
//* J4VTXPixel
//* --------------------
//* (Description)
//* 	Derivation class for VTX Pixel.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2002/05/18 K.Hoshina 	Original version.
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"
#include "J4VTXPixelSD.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXPixel : public J4VVTXDetectorComponent {	

public:

  J4VTXPixel(J4VDetectorComponent *parent    = 0,
             G4int                 nclones   = 1,
             G4int                 nbrothers = 1, 
             G4int                 me        = 0,
             G4int                 copyno    = -1 );

  	     
  virtual ~J4VTXPixel();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	SwitchOn (G4String opt = "me")  ;
  virtual void	SwitchOff(G4String opt = "me") ;
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
};

#endif


