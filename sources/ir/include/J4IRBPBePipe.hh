// $Id$
#ifndef __J4IRBPBEPIPE__
#define __J4IRBPBEPIPE__
//*************************************************************************
//* --------------------
//* J4IRBPBePipe
//* --------------------
//* (Description)
//* 	Derivation class for BePipeampipe.
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPBePipe : public J4VIRAcceleratorComponent {	

public:
  J4IRBPBePipe(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  virtual ~J4IRBPBePipe();

  virtual void  InstallIn(J4VComponent *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
};

#endif




