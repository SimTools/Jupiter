// $Id$
#ifndef __J4VTX__
#define __J4VTX__
//*************************************************************************
//* --------------------
//* J4VTX
//* --------------------
//* (Description)
//* 	Derivation class for VTX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VTXLayer.hh"
#include "J4VVTXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTX : public J4VVTXDetectorComponent {	

public:
  J4VTX(J4VDetectorComponent *parent = 0,
                       G4int  nclones   = 1,
                       G4int  nbrothers = 1, 
                       G4int  me        = 0,
                       G4int  copyno    = -1 );

  virtual ~J4VTX();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  J4VTXLayer          **fLayers;
};

#endif


