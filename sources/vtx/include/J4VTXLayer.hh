// $Id$
#ifndef __J4VTXLAYER__
#define __J4VTXLAYER__
//*************************************************************************
//* --------------------
//* J4VTXLayer
//* --------------------
//* (Description)
//* 	Derivation class for VTX Layer.
//*     Mother class : J4VDetectorComponent
//*    
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/11/19  T.Aso       Modify to use ParameterList.
//*************************************************************************

#include "J4VTXLadder.hh"
#include "J4VVTXDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VTXLayer : public J4VVTXDetectorComponent {	

public:

  J4VTXLayer(J4VDetectorComponent* parent       = 0,
  	     G4int 		   nbrothers    = 1, 
  	     G4int 		   me           = 0);
  	     
  virtual ~J4VTXLayer();

  virtual void  InstallIn(J4VComponent         *mother,
                          G4RotationMatrix     *prot  = 0,
                          const G4ThreeVector  &tlate = G4ThreeVector(0.) );
  virtual void	Draw()      ;
  virtual void	Print() const ;
  
private:
  void 	Assemble();    
  void  Cabling ();
  
private:
  
  static G4String fFirstName;
  J4VTXLadder   **fLadders;
};

#endif


