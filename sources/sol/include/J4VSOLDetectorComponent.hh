// $Id$
#ifndef __J4VSOLDETECTORCOMPONENT__
#define __J4VSOLDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VSOLDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4VDetectorComponent.hh"
#include "J4SOLMaterialStore.hh"
#include "J4SOLParameterList.hh"
#include "G4String.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VSOLDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VSOLDetectorComponent( const G4String       &name, 
  			   J4VDetectorComponent *parent    = 0,
                           G4int                 nclones   = 1,
                           G4int                 nbrothers = 1, 
                           G4int                 me        = 0,
                           G4int                 copyno    = -1 );
  virtual ~J4VSOLDetectorComponent();
  static J4SOLParameterList * GetParameterList() { return fParameterList; }
      
protected:    
  J4VMaterialStore   * 	 OpenMaterialStore();
  J4SOLParameterList * 	 OpenParameterList();
  
private:
  static J4SOLMaterialStore *fMaterialStore;
  static J4SOLParameterList *fParameterList;
  static G4String            fSubGroup;
       
};

#endif


