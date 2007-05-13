// $Id$
#ifndef __J4IR__
#define __J4IR__
//*************************************************************************
//* --------------------
//* J4IR
//* --------------------
//* (Description)
//* 	Derivation class for IR region
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

// Sub-Component

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IR : public J4VIRAcceleratorComponent {	

public:
  J4IR(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
                           G4int  copyno    = -1 );

  virtual ~J4IR();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  void  Assemble_Qx(const char *name, G4double rmin, G4double rmax, 
	G4double zlen, G4double zpos, G4double isDownStream,
	G4double ebeam, G4double bgrad);

  void  Assemble_BeamPipeMiddle();
  
private:  
  static G4String	fName;

  std::vector<J4VComponent*> fComponents;

};

#endif




