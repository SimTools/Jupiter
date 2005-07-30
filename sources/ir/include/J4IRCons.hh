// $Id$
#ifndef __J4IRCons__
#define __J4IRCons__
//*************************************************************************
//* --------------------
//* J4IRCons
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
//

class J4IRCons : public J4VIRAcceleratorComponent {

public:
  J4IRCons(G4String name, G4double rmin1, G4double rmax1, 
	   G4double rmin2, G4double rmax2, G4double hzlen, G4double zcnt,
		 J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1, 
                           G4int  me        = 0,
 	                  G4int  copyno    = -1,
	                   G4bool reflect = false);

  virtual ~J4IRCons();

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
  G4double      fRmin1;
  G4double      fRmax1;
  G4double      fRmin2;
  G4double      fRmax2;
  G4double      fHZlen;
  G4double      fZcnt;

//  G4double      fRotation;

  G4String      fMaterial;
  G4bool        fVisAtt;
  G4Color       fColor;
  
};

#endif




