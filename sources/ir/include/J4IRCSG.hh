// $Id$
#ifndef __J4IRCSG__
#define __J4IRCSG__
//*************************************************************************
//* --------------------
//* J4IRCSG
//* --------------------
//* (Description)
//* 	Derivation class for Beampipe.
//*     Mother class : J4VAcceleratorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VIRAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4IRCSG : public J4VIRAcceleratorComponent {	

public:
  J4IRCSG(J4VAcceleratorComponent *parent = 0,
                           G4int  nclones   = 1,
                           G4int  nbrothers = 1,
                           G4int  me        = 0,
                           G4int  copyno    = -1 ,
	                    G4bool reflect=false);
  virtual ~J4IRCSG();

  virtual void	Draw()      ;
  virtual void	Print() const ;

  G4ThreeVector&  GetTranslation();

private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static G4String	fName;
  
};

#endif




