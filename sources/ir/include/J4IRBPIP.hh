// $Id$
#ifndef __J4IRBPIP__
#define __J4IRBPIP__
//*************************************************************************
//* --------------------
//* J4IRBPIP
//* --------------------
//* (Description)
//* 	Derivation class for BePipeampipe.
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*     2005/07/25  A.Miyamoto  Renamed to J4IRBPIP from J4IRBPBePipe
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBPIP : public J4VIRAcceleratorComponent {	

public:
  J4IRBPIP(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  virtual ~J4IRBPIP();

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




