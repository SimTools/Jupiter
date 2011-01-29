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
//*	2002/11/20  T.Aso	Remove RO
//*************************************************************************

#include "J4VVTXDetectorComponent.hh"

#include "J4VTXPixelArray.hh"

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
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	SwitchOn (G4String opt = "me")  ;
  virtual void	SwitchOff(G4String opt = "me") ;
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  J4VTXPixelArray  *fPixelArray;
};

#endif


