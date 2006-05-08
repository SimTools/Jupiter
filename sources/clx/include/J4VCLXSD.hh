// $Id$
#ifndef __J4VCLXSD__
#define __J4VCLXSD__
//*************************************************************************
//* --------------------
//* J4VCLXSD
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/07/29  Hiroaki ONO revised
//*************************************************************************

#include "G4VSensitiveDetector.hh"

//=====================================================================
//---------------------
// class definition
//---------------------
class G4Step;
class J4VCLXSD : public G4VSensitiveDetector {

public:
  
  J4VCLXSD();
  ~J4VCLXSD() { }

  virtual void Initialize( G4HCofThisEvent* ) { }
  virtual G4bool ProcessHits( G4Step*, G4TouchableHistory* ) { return false ; }
  virtual void EndOfEvent( G4HCofThisEvent* ) { }
  virtual void clear    () {}
  virtual void DrawAll  () {}
  virtual void PrintAll () {}

};

inline J4VCLXSD::J4VCLXSD()
  : G4VSensitiveDetector( "virtualSD" )
{}

#endif
