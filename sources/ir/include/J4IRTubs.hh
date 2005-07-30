// $Id$
#ifndef __J4IRTubs__
#define __J4IRTubs__
//*************************************************************************
//* --------------------
//* J4IRTubs
//* --------------------
//* (Description)
//* 	Derivation class for Tubs solid in IR Region
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2005/07/15  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4AttMFieldMap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRTubs : public J4VIRAcceleratorComponent, public J4AttMFieldMap {	

public:
  J4IRTubs(G4String name, G4double rmin, G4double rmax, G4double hzlen, G4double zcnt, 
	   G4String material, G4bool visatt, G4Color icol, 
			 J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRTubs();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();
  virtual void SetTranslation(G4double x, G4double y, G4double z){
	fXcnt=x; fYcnt=y; fZcnt=z; }
  virtual void SetRotation(G4double rot){ fRotation=rot; }

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  G4String	fName;
  G4double      fRmin;
  G4double      fRmax;
  G4double      fHZlen;
  G4double      fZcnt;
  G4String      fMaterial;
  G4bool        fVisAtt;
  G4Color       fColor;
  G4double      fRotation;
  G4double      fXcnt;
  G4double      fYcnt;
  
};

#endif




