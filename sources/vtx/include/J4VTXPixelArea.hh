// $Id$
#ifndef __J4VTXPIXELAREA_
#define __J4VTXPIXELAREA__
//*************************************************************************
//* --------------------
//* J4VTXPixelArea
//* --------------------
//* (Description)
//* 	Derivation class for VTX PixelArea.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2001/06/06  T.Aso	Original version.
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"

#ifdef __HOSHINA__
#include "J4VTXPixelArray.hh"
#else
#include "J4VTXPixelAreaSD.hh"
#endif

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXPixelArea : public J4VVTXDetectorComponent {	

public:

  J4VTXPixelArea(J4VDetectorComponent* parent       = 0);
  	     
  virtual ~J4VTXPixelArea();

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

  G4ThreeVector* fDxyzPixelArea;
  G4ThreeVector* fxyzPixelArea;   

#ifdef __HOSHINA__
  J4VTXPixelArray  *fPixelArray;
#endif

};

#endif


