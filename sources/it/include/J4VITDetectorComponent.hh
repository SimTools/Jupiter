// $Id$
#ifndef __J4VITDETECTORCOMPONENT__
#define __J4VITDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VITDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2000/12/08  K.Hoshina	Original version.
//*************************************************************************

#include "J4ITMaterialStore.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VITDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VITDetectorComponent( const G4String       &name, 
  			  J4VDetectorComponent *parent    = 0,
                          G4int                 nclones   = 1,
                          G4int                 nbrothers = 1, 
                          G4int                 me        = 0,
                          G4int                 copyno    = -1 );
  J4VITDetectorComponent(J4VITDetectorComponent& right);
  virtual const J4VITDetectorComponent& 
  		operator=(const J4VITDetectorComponent& right);    

  virtual ~J4VITDetectorComponent();
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  
private:
  static J4ITMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

//=====================================================================
//---------------------
// inline function
//---------------------


inline J4VITDetectorComponent::J4VITDetectorComponent(J4VITDetectorComponent& right)
                              : J4VDetectorComponent(right)
{
          
}

inline const J4VITDetectorComponent& 
J4VITDetectorComponent::operator=(const J4VITDetectorComponent& right)
{
  return *this;
}


#endif


