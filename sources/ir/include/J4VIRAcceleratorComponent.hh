// $Id$
#ifndef __J4VIRACCELERATORCOMPONENT__
#define __J4VIRACCELERATORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VIRAcceleratorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4IRMaterialStore.hh"
#include "J4VAcceleratorComponent.hh"
#include "J4IRParameter.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VIRAcceleratorComponent : public J4VAcceleratorComponent
{	// abstruct class

public:
  //default constructor...
  J4VIRAcceleratorComponent( const G4String       &name, 
  			  J4VAcceleratorComponent *parent    = 0,
                          G4int                 nclones   = 1,
                          G4int                 nbrothers = 1, 
                          G4int                 me        = 0,
                          G4int                 copyno    = -1 );

  virtual ~J4VIRAcceleratorComponent();
#if 0 		          
  J4VIRAcceleratorComponent(J4VIRAcceleratorComponent& right);
  virtual const J4VIRAcceleratorComponent& 
  		operator=(const J4VIRAcceleratorComponent& right);    
#endif
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  
private:
  static J4IRMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

#if 0
//=====================================================================
//---------------------
// inline function
//---------------------


inline J4VIRAcceleratorComponent::J4VIRAcceleratorComponent(J4VIRAcceleratorComponent& right)
{

  fMaterialStore = right.fMaterialStore;
  fSubGroup      = right.fSubGroup;
          
}

inline const J4VIRAcceleratorComponent& 
J4VIRAcceleratorComponent::operator=(const J4VIRAcceleratorComponent& right)
{

  fMaterialStore = right.fMaterialStore;
  fSubGroup      = right.fSubGroup;
  
  return *this;
            
}

#endif



#endif


