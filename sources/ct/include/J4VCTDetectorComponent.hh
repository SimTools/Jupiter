// $Id$
#ifndef __J4VCTDETECTORCOMPONENT__
#define __J4VCTDETECTORCOMPONENT__
//*************************************************************************
//* -----------------------
//* J4VCTDetectorComponent
//* -----------------------
//* (Description)
//* 	Class for describing his/her detector compornents.
//*     
//* (Update Record)
//*	2003/08/13  Akiya Miyamoto	Original version.(copied from J4IT.....)
//*************************************************************************

#include "J4CTMaterialStore.hh"
#include "J4CTParameterList.hh"
#include "J4VDetectorComponent.hh"

//=====================================================================
//---------------------
// class definition
//---------------------

class J4VCTDetectorComponent : public J4VDetectorComponent
{	// abstruct class

public:
  //default constructor...
  J4VCTDetectorComponent( const G4String       &name, 
  			  J4VDetectorComponent *parent    = 0,
                          G4int                 nclones   = 1,
                          G4int                 nbrothers = 1, 
                          G4int                 me        = 0,
                          G4int                 copyno    = -1 );
  J4VCTDetectorComponent(J4VCTDetectorComponent& right);
  //  virtual const J4VCTDetectorComponent& 
  //  		operator=(const J4VCTDetectorComponent& right);    

  virtual ~J4VCTDetectorComponent();
      
protected:    
  J4VMaterialStore* 	 OpenMaterialStore();
  J4CTParameterList* 	 OpenParameterList() { return J4CTParameterList::GetInstance(); }
  
private:
  static J4CTMaterialStore* fMaterialStore;
  static G4String fSubGroup;
       
};

//=====================================================================
//---------------------
// inline function
//---------------------


inline J4VCTDetectorComponent::J4VCTDetectorComponent(J4VCTDetectorComponent& right)
                              : J4VDetectorComponent(right)
{
          
}

//inline const J4VCTDetectorComponent& 
//J4VCTDetectorComponent::operator=(const J4VCTDetectorComponent& right)
//{
//  return *this;
//}


#endif


