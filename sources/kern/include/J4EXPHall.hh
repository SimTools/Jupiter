// $Id$
#ifndef __J4EXPHALL__
#define __J4EXPHALL__
//*************************************************************************
//* --------------------
//* J4EXPHALL
//* --------------------
//* (Description)
//* 	Derived class for EXPerimentalHall.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4EXPHall : public J4VComponent {	

public:

  J4EXPHall( J4VComponent *parent = 0,
             G4int  nclones       = 1,
             G4int  nbrothers     = 1, 
             G4int  me            = 0,
             G4int  copyno        = -1 );
  		  
  virtual ~J4EXPHall();

  virtual void   InstallIn(J4VComponent        *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = 0 );
  virtual void   Draw() ;
  virtual void   Print() const ;

  const G4ThreeVector &GetSizeOfEXPHall() const { return fSizeOfEXPHall; }

private:
  void 	            Assemble(); 
  void              Cabling () {}
  J4VMaterialStore *OpenMaterialStore();  

private: 
  static J4VMaterialStore* fMaterialStore;
  static G4String          fProjectName; 
  static G4String          fEXPName; 
  G4ThreeVector            fSizeOfEXPHall;

};

#endif


