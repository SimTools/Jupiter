// $Id$
#ifndef __J4BD__
#define __J4BD__
//*************************************************************************
//* --------------------
//* J4BD
//* --------------------
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/05/15  K.Hoshina	Argument changed in InstallIn().
//*
//*************************************************************************


// Class description

//_________________________________________________________________________
//
// J4BD
//
// This class represents Beam Delivery Area.
// Install all components in this class and stay within the boundary of
// the region assigned to you. 
// 


#include "J4VBDAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4BD : public J4VBDAcceleratorComponent {	

public:
  J4BD(J4VAcceleratorComponent *parent = 0,
                      G4int  nclones   = 1,
                      G4int  nbrothers = 1, 
                      G4int  me        = 0,
                      G4int  copyno    = -1 );

  virtual ~J4BD();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fFirstName;
  
};

#endif


