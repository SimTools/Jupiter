// $Id$
#ifndef __J4VIRDETECTORCOMPONENT__
#define __J4VIRDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VIRDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4IRMaterialStore.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VIRDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VIRDetectorComponent( const G4String       &name, 
  			   J4VComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  J4VIRDetectorComponent( const J4VIRDetectorComponent &orig, 
                                        G4int                    copyno);

  virtual ~J4VIRDetectorComponent();

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  
private:
  static J4IRMaterialStore* fMaterialStore;
  static G4String fSubGroup;

};

#endif



