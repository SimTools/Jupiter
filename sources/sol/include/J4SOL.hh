// $Id$
#ifndef __J4SOL__
#define __J4SOL__
//*************************************************************************
//* -----
//* J4SOL
//* -----
//* (Description)
//* 	Derivation class for SOL.
//*     Mother class : J4VSOLDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VSOLDetectorComponent.hh"
#include "J4AttMFieldMap.hh"
#include "J4SOLCoil.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4SOLMessenger;

class J4SOL : public J4VSOLDetectorComponent, public J4AttMFieldMap  {	

public:
  J4SOL(J4VDetectorComponent *parent = 0,
                       G4int  nclones   = 1,
                       G4int  nbrothers = 1, 
                       G4int  me        = 0,
                       G4int  copyno    = -1 );
  virtual ~J4SOL();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void  SetMagField();

  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  J4SOLCoil*            fCoil;

  J4SOLMessenger       *fMessenger;
  G4double  fMaxEps;
  G4double  fMinEps;
  G4double  fDeltaOneStep;
  G4double  fDeltaIntersection;
  G4double  fDeltaChord;

public:
  inline void SetMaxEps(G4double val){ fMaxEps=val;}
  inline void SetMinEps(G4double val){ fMinEps=val;}
  inline void SetDeltaOneStep(G4double val){ fDeltaOneStep=val; }
  inline void SetDeltaIntersection(G4double val){ fDeltaIntersection=val; }
  inline void SetDeltaChord(G4double val){ fDeltaChord=val;}

  inline G4double GetMaxEps(){ return fMaxEps;}
  inline G4double GetMinEps(){ return fMinEps;}
  inline G4double GetDeltaOneStep(){ return fDeltaOneStep;}
  inline G4double GetDeltaIntersection(){ return fDeltaIntersection;}
  inline G4double GetDeltaChord(){ return fDeltaChord;}

};

#endif
