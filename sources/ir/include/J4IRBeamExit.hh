// $Id$
#ifndef __J4IRBEAMEXIT__
#define __J4IRBEAMEXIT__
//*************************************************************************
//* --------------------
//* J4IRBeamExit
//* --------------------
//* (Description)
//* 	Derivation class for QC1
//*     Mother class : J4VIRAcceleratorComponent
//*    
//*     QC1 - SUS
//*         - Coil - Collor 
//*                - Cooling - Vacuum
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRBeamExit : public J4VIRAcceleratorComponent {

public:
  J4IRBeamExit(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
                           G4int  copyno    = -1 ,
	                    G4bool reflect=false);
  virtual ~J4IRBeamExit();

  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  void  InstallIn(J4VIRAcceleratorComponent *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;

};

#endif




