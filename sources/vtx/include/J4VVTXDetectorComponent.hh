// $Id$
#ifndef __J4VVTXDETECTORCOMPONENT__
#define __J4VVTXDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VVTXDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*	2002/11/19  T.Aso       modify to use ParameterList
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4VTXMaterialStore.hh"
#include "J4VTXParameterList.hh"
#include "G4UserLimits.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VVTXDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VVTXDetectorComponent( const G4String       &name, 
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );

  J4VVTXDetectorComponent( const J4VVTXDetectorComponent &orig, 
                                        G4int                    copyno);

  virtual ~J4VVTXDetectorComponent();
  void  SetMaxAllowedStep(G4double maxStep);

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4VTXParameterList* 	 OpenParameterList();
  
private:
  static J4VTXMaterialStore *fMaterialStore;
  static J4VTXParameterList *fParameterList;
  static G4String            fSubGroup;
  G4UserLimits              *fUserLimits;
       
};



#endif



