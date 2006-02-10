// $Id$
#ifndef __J4IRFCAL__
#define __J4IRFCAL__
//*************************************************************************
//* --------------------
//* J4IRFCAL
//* --------------------
//* (Description)
//* 	Derivation class for IR FCAL
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2005/07/08  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4IRFCALLayer.hh"
//=====================================================================
//---------------------
// class definition
//---------------------


class J4IRFCAL : public J4VIRAcceleratorComponent {	

public:
  J4IRFCAL(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRFCAL();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();
  inline G4double GetGeom(G4int i){ return fGeom[i]; }

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  G4double              fGeom[6];
  J4IRFCALLayer        **fLayers;  
};

#endif




