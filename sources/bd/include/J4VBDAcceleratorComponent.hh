// $Id$
#ifndef __J4VBDACCELERATORCOMPONENT__
#define __J4VBDACCELERATORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VBDAcceleratorComponent
//* -----------------------
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

//=====================================================================
//---------------------
// Class description
//---------------------

//_________________________________________________________________________
//
// J4VBDAcceleratorComponent
//
// This class is the abstract base class of components in Beam Delivery Area.
// Use this class by inheriting from it and overriding its mother's pure
// virtual functions, Assemble() and InstallIn().
//


#include "J4BDMaterialStore.hh"
#include "J4BDParameterList.hh"
#include "J4VAcceleratorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VBDAcceleratorComponent : public J4VAcceleratorComponent
{	// abstruct class

public:
  //default constructor...
  J4VBDAcceleratorComponent( const G4String          &name, 
  			     J4VAcceleratorComponent *parent    = 0,
                             G4int                    nclones   = 1,
                             G4int                    nbrothers = 1, 
                             G4int                    me        = 0,
                             G4int                    copyno    = -1 );

  virtual ~J4VBDAcceleratorComponent();

protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4BDParameterList* 	 OpenParameterList() 
                         { return J4BDParameterList::GetInstance(); }
  
private:
  static J4BDMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

#endif



