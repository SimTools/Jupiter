// $Id$
#ifndef __J4IRBPPIPE__
#define __J4IRBPPIPE__
//*************************************************************************
//* --------------------
//* J4IRBPPipe
//* --------------------
//* (Description)
//* 	Derivation class for Pipeampipe.
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRBPBePipe.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPPipe : public J4VIRAcceleratorComponent {	

public:
  J4IRBPPipe(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  virtual ~J4IRBPPipe();

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
  J4IRBPBePipe* fpipe   ;
};

#endif




