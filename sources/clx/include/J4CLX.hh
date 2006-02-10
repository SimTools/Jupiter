// $Id$
#ifndef __J4CLX__
#define __J4CLX__
//*************************************************************************
//* --------------------
//* J4CLX
//* --------------------
//* (Description)
//* 	Derivation class for CLX.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*     2004/07/29  Hiroaki ONO revised
//*************************************************************************

#include "J4VCLXDetectorComponent.hh"
#include "J4CLXBlock.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4CLX : public J4VCLXDetectorComponent {	

public:
  J4CLX( J4VDetectorComponent *parent   = 0,
                        G4int nclones   = 1,
                        G4int nbrothers = 1, 
                        G4int me        = 0,
                        G4int copyno    = -1 );
  virtual ~J4CLX();
  virtual void  InstallIn( J4VComponent         *mother,
                           G4RotationMatrix     *prot  = 0,
                           const G4ThreeVector  &tlate = 0 );
  virtual void Draw() ;
  virtual void Print() const ;

  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:  
  static const G4String  fFirstName;
    J4CLXBlock**          fBlock;
  
};

#endif
