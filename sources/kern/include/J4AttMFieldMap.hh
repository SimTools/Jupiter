// $Id$
#ifndef __J4ATTMFIELDMAP__
#define __J4ATTMFIELDMAP__
//*************************************************************************
//* --------------------
//* J4AttMFieldMap
//* --------------------
//* (Description)
//* 	This class applies the attribute for magnetic field.
//*     Mother class : None
//*    
//* (Update Record)
//*	2002/09/13  T.Aso	Original version.
//*************************************************************************
 
#include "globals.hh"
#include "J4VMField.hh"
#include "J4VComponent.hh"
// ====================================================================
// -----------------------
// class definition
// -----------------------

class J4AttMFieldMap{

public:
  J4AttMFieldMap();
  ~J4AttMFieldMap();

  void      SetMField(J4VMField* mfield) { fMfield = mfield; }

  void      InstallMField(J4VComponent* component);

  G4bool    IsMValid(const G4double point[3]);

  void      GetMFieldValue(const G4double  point[3], 
                                 G4double* bfield, 
                                 G4bool&   onlyFlag );  

  G4String* GetMFieldName() { return fMFname; }

private:
  void      DefineGlobalMValidBox();

private:
  G4String*         fMFname;
  J4VMField*        fMfield;
  G4ThreeVector     fTrans;
  G4RotationMatrix  fRot;
  G4RotationMatrix  fRotInverse;
  G4bool            fIsOrigin;

  G4double          fMValidX[2];
  G4double          fMValidY[2];
  G4double          fMValidZ[2];

};

#endif


