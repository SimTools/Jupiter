// $Id$
#ifndef __J4CAL__
#define __J4CAL__
//*************************************************************************
//* --------------------
//* J4CAL
//* --------------------
//* (Description)
//* 	Derivation class for CAL.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VCALDetectorComponent.hh"
#include "J4CALCone.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CAL : public J4VCALDetectorComponent {	

public:
  J4CAL(J4VDetectorComponent *parent = 0,
                       G4int  nclones   = 1,
                       G4int  nbrothers = 1, 
                       G4int  me        = 0,
                       G4int  copyno    = -1 );
virtual ~J4CAL();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  J4CALCone**           fCones;  
  
  
};

#endif
