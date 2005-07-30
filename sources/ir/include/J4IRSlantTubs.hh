// $Id$
#ifndef __J4IRSlantTubs__
#define __J4IRSlantTubs__
//*************************************************************************
//* --------------------
//* J4IRSlantTubs
//* --------------------
//* (Description)
//* 	Derivation class for Tubs solid in IR Region
//*     Mother class : J4VIRAcceleratorComponent
//*    
//* (Update Record)
//*	2005/07/22  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"
#include "J4AttMFieldMap.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
//
// Geometry for of Slant Tubs subtracted by box.
// rmin, rmax defines minimum and maximum radius of Tubs
// hzlen and zcnt is used to define box which will be used to cut Tubs.
// solid is placed at Zcenter=zcnt;
// center of x is shifted by an amount for rotation of zcnt position
// around y axis.
//

class J4IRSlantTubs : public J4VIRAcceleratorComponent, public J4AttMFieldMap  {

public:
  J4IRSlantTubs(G4String name, G4double rmin, G4double rmax, 
		G4double hzlen, G4double zcnt, G4double rot,
		 J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRSlantTubs();

  G4RotationMatrix* GetRotation();
  G4ThreeVector&  GetTranslation();

  virtual void SetAttribute(G4String material, G4bool visatt, G4Color icol){
	fMaterial=material; fVisAtt=visatt; fColor=icol; }

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

  G4double      fRotation;

  G4String      fMaterial;
  G4bool        fVisAtt;
  G4Color       fColor;
  
};

#endif




