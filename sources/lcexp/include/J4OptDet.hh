// $Id$
#ifndef __J4OptDet__
#define __J4OptDet__
//*************************************************************************
//* --------------------
//* J4UniversalDetector
//* --------------------
//* (Description)
//* 	General purpose detector volume
//*    
//* (Update Record)
//*	2006/06/04  A.Miyamoto	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4OptDetMaterialStore.hh"

//=====================================================================
//---------------------
// class definition
//---------------------


class J4OptDet : public J4VDetectorComponent {	

public:
  J4OptDet(J4VComponent *parent=0, G4String name=G4String("J4OPT"), 
	   G4int nbrothers=1, G4int me=0);
  virtual ~J4OptDet();

  virtual void	Draw()      ;
  virtual void	Print() const ;

  virtual void  InstallIn(J4VComponent *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  inline G4double GetZCenter(){
    if( fShapeID == 0 ) { return (fGeom[2]+fGeom[3])*0.5; } //  TUBS 
    else if ( fShapeID == 1 ) { return (fGeom[4]+fGeom[5])*0.5; } // CONS 
    else { return 0 ; }
  }
  inline G4int GetOptDetID(){ return fOptDetID; }

private:
  void 	Assemble();    
  void  Cabling ();
  J4VMaterialStore*    OpenMaterialStore();
  static J4OptDetMaterialStore *fMaterialStore;  

private:  
  G4String	fName;
  G4int         fShapeID;
  G4double      fGeom[10];
  G4int         fOptDetID;
};

#endif




